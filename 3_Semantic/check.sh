#!/bin/bash

make clean
make all

# 결과를 저장할 디렉토리 설정
result_directory="./my_result"
answer_directory="./testresult"

# cminus_semantic 실행 파일 확인
cminus_executable="./cminus_semantic"
if [ ! -x "$cminus_executable" ]; then
    echo "cminus_semantic 실행 파일이 현재 디렉토리에 없거나 실행 권한이 없습니다."
    exit 1
fi

# 현재 디렉토리 및 하위 디렉토리에서의 *.cm 파일 목록 가져오기
cm_files=($(find . -type f -name "*.cm"))

# 결과를 저장할 디렉토리 생성
rm -rf "$result_directory"
mkdir -p "$result_directory"

# 각 *.cm 파일에 대해 cminus_semantic 실행 및 결과 저장
for file in "${cm_files[@]}"; do
    output_file="$result_directory/$(basename ${file%.*}).result"
    ./"$cminus_executable" "$file" > "$output_file"
    #echo "File '$file'의 실행 결과는 '$output_file'에 저장되었습니다."
done

# ready to make grades
good_count = 0
bad_count = 0
no_count = 0
total_count = 0
> "./note.txt"

# move to the answer folder
cd "$result_directory" || exit

# iterate per an answer file
for res in *.result; do
  # find the same name in the result folder
  name=`basename $res`
  filename="${name%.*}"
  ans="../$answer_directory/${filename}_result"

  #echo "$ans, $filename"

  # check the file
  if [ -e "$ans" ]; then
    # compare the content
    diff_output=$(diff "$ans" "$res")

    if [ -z "$diff_output" ]; then
      # echo "Good"
      ((good_count++))
      ((total_count++))
    else
      # echo "Bad"
      ((bad_count++))
      ((total_count++))
      echo "$res" >> "../note.txt"
    fi
  else
    echo "There is no result file"
    ((no_count++))
  fi
done

# print the grade
echo "$good_count / $total_count"
echo "Missing files : $no_count"
