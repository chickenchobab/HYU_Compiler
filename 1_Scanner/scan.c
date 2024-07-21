/****************************************************/
/* File: scan.c                                     */
/* The scanner implementation for the TINY compiler */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "util.h"
#include "scan.h"

/* states in scanner DFA */
typedef enum
   { START,INEQ,INLT,INGT,INNE,INOVER,INCOMMENT,INNUM,INID,DONE }
   StateType;

/* lexeme of identifier or reserved word */
char tokenString[MAXTOKENLEN+1];

/* BUFLEN = length of the input buffer for
   source code lines */
#define BUFLEN 256

static char lineBuf[BUFLEN]; /* holds the current line */
static int linepos = 0; /* current position in LineBuf */
static int bufsize = 0; /* current size of buffer string */
static int EOF_flag = FALSE; /* corrects ungetNextChar behavior on EOF */

/* getNextChar fetches the next non-blank character
   from lineBuf, reading in a new line if lineBuf is
   exhausted */
static int getNextChar(void) 
{ if (!(linepos < bufsize))
  { lineno++;
    if (fgets(lineBuf,BUFLEN-1,source))
    { if (EchoSource) fprintf(listing,"%4d: %s",lineno,lineBuf);
      bufsize = strlen(lineBuf);
      linepos = 0;
      return lineBuf[linepos++];
    }
    else
    { EOF_flag = TRUE;
      return EOF;
    }
  }
  else return lineBuf[linepos++];
}

/* ungetNextChar backtracks one character
   in lineBuf */
static void ungetNextChar(void)
{ if (!EOF_flag) linepos-- ;}

/* lookup table of reserved words */
static struct
    { char* str;
      TokenType tok;
    } reservedWords[MAXRESERVED]
   = {{"if",IF},{"else",ELSE},{"while",WHILE},
   {"return", RETURN},{"int",INT}, {"void",VOID}};

/* lookup an identifier to see if it is a reserved word */
/* uses linear search */
static TokenType reservedLookup (char * s)
{ int i;
  for (i=0;i<MAXRESERVED;i++)
    if (!strcmp(s,reservedWords[i].str))
      return reservedWords[i].tok;
  return ID;
}

/****************************************/
/* the primary function of the scanner  */
/****************************************/
/* function getToken returns the 
 * next token in source file
 */
TokenType getToken(void)
{  /* index for storing into tokenString */
   int tokenStringIndex = 0;
   /* holds current token to be returned */
   TokenType currentToken;
   /* current state - always begins at START */
   StateType state = START;
   /* flag to indicate save to tokenString */
   int save;
   while (state != DONE)
   { int c = getNextChar();
     save = TRUE; /* digit or alpha should be saved in case extended */
     switch (state)
     { case START:
         if (isdigit(c))      /* number */
           state = INNUM;
         else if (isalpha(c)) /* identifier or reserved word */
           state = INID;
    
         /* blank spaces ignored */
         else if ((c == ' ') || (c == '\t') || (c == '\n')) 
           save = FALSE;

         /* there can be one more operator */
         else if (c == '=')
           state = INEQ;            
         else if (c == '!')
           state = INNE;          
         else if (c == '<')   
           state = INLT;         
         else if (c == '>')
           state = INGT; 
         else if (c == '/') {
           save = FALSE;       /* this save should be set false */
           state = INOVER;     /* because comment ends with start state */
         }

         /* token completed in itself */
         else 
         { state = DONE;
           switch (c)
           { case EOF:
               save = FALSE;
               currentToken = ENDFILE;
               break;
             case '+':
               currentToken = PLUS;
               break;
             case '-':
               currentToken = MINUS;
               break;
             case '*':
               currentToken = TIMES;
               break;
             case '(':
               currentToken = LPAREN;
               break;
             case ')':
               currentToken = RPAREN;
               break;
             case '[':
               currentToken = LBRACE;
               break;
             case ']':
               currentToken = RBRACE;
               break;
             case '{':
               currentToken = LCURLY;
               break;
             case '}':
               currentToken = RCURLY;
               break;
             case ';':
               currentToken = SEMI;
               break;
             case ',':
               currentToken = COMMA;
               break;
             default:
               currentToken = ERROR;
               break;
           }
         }
         break;
      
       /* previous char (=) */
       case INEQ:
         state = DONE;
         if(c=='=') currentToken=EQ;
         else{
          ungetNextChar();      /* cursor goes back knowing to assign */
          currentToken=ASSIGN;
         }
         break;

       /* previous char (!) */
       case INNE:
         state = DONE;
         if(c=='=') currentToken = NE;
         else{
          ungetNextChar();      /* cursor goes back knowing to face error */ 
          save = FALSE;
          currentToken=ERROR;
         }
         break;

       /* previous char (<) */
       case INLT:
         state = DONE;
         if(c=='='){
          currentToken = LE;
         }
         else{
          ungetNextChar();
          currentToken = LT;
         }
         break;

       /* previous char (>) */  
       case INGT:
         state = DONE;
         if(c=='='){
          currentToken = GE;
         }
         else{
          ungetNextChar();
          currentToken = GT;
         }
         break;

       /* previous char (/) */
       case INOVER:
         if(c=='*'){           /* comment starts */
          save = FALSE;
          state = INCOMMENT;
         }
         else {                /* cursor goes back knowing to divide */
          ungetNextChar();
          state = DONE;
          currentToken = OVER;
         }
         break;

       /* comment like this */
       case INCOMMENT:
			   save = FALSE;
          /* comment can be finished */
          if (c == '*')            
          {
            c = getNextChar();
            if (c == '/')       /* comment ends start to read */
              state = START;
            else if (c == EOF)  /* file ends with comment */
            {
              state = DONE;
              currentToken = ENDFILE;
            }
            else                /* cursor goes back knowing to face meaningless star */
              ungetNextChar();
          }
          /* file ends with comment */
          else if (c == EOF) 
          {
            state = DONE;
            currentToken = ENDFILE;
          }
          break;

       case INNUM:
         /* next char can be digit */
         if (!isdigit(c))
         { /* backup in the input */
           ungetNextChar();
           save = FALSE;
           state = DONE;
           currentToken = NUM;
         }
         break;

       case INID:
         /* started with an alpha */
         /* so next char can be alpha or digit */
         if (!isalpha(c) && !isdigit(c))
         { /* backup in the input */
           ungetNextChar();
           save = FALSE;
           state = DONE;
           currentToken = ID;
         }
         break;

       case DONE:

       default: /* should never happen */
         fprintf(listing,"Scanner Bug: state= %d\n",state);
         state = DONE;
         currentToken = ERROR;
         break;
     }
     if ((save) && (tokenStringIndex <= MAXTOKENLEN))
       tokenString[tokenStringIndex++] = (char) c;
     if (state == DONE)
     { tokenString[tokenStringIndex] = '\0';
       if (currentToken == ID)
         currentToken = reservedLookup(tokenString);
     }
   }
   if (TraceScan) {
     fprintf(listing,"\t%d: ",lineno);
     printToken(currentToken,tokenString);
   }
   return currentToken;
} /* end getToken */

