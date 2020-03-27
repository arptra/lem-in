#!/bin/bash

check_errors(){
SUB="ERROR"
echo -e "\n\e[1;34mERROR MANAGEMENT TESTS\e[0m\n"
dir="validation_errs/*"
i=1;
for file in $dir
do
err=$(./lem-in 2>&1 < $file)
test_name=$(printf $file | awk -F"/" '{print $(NF - 1), $NF}' | awk -F" " '{print $2}' | awk -F"." '{print $1}')
if [[ "$err" == *"$SUB"* ]]
then
echo -en "test #:$i $test_name PASS: \033[32m \033[32m OK \033[0m ERROR TYPE: $err\n"
else
echo -en "test #:$i NOT PASS: $test_name \033[31m \033[31m KO \033[0m\n"
fi
i=$((i+1))
done
}

check_leak_errors(){
echo -e "\n\e[1;34mMEMORY LEAK WITH INVALID MAP TESTS\e[0m\n"
dir="validation_errs/*"
i=1
echo -en "\t\033[32m \033[32m LOOK FOR LEAK \033[32m \033[32m  \033[0m\n"
for file in $dir
do
echo -en "\t\033[32m \033[32m TEST NUMBER $i $file \033[32m \033[32m  \033[0m\n"
valgrind 2>&1 --leak-check=full --show-leak-kinds=all ./lem-in < $file | grep "LEAK SUMMARY:" -A5 | awk -F":" '{print $1 $2}'
i=$((i+1))
done
}

check_ouput(){
echo -e "\n\e[1;34mLEM_IN'S OUTPUT CHECK\e[0m\n"

if [ -d $"42_lem-in_tools" ]
then
    cp lem-in 42_lem-in_tools
else
    git clone https://github.com/apft/42_lem-in_tools.git
    cp lem-in 42_lem-in_tools
fi

cd 42_lem-in_tools
dir="../valid_tests/*"
i=1
for file in $dir
do
echo -en "\t\033[32m \033[32m test #:$i  $file\033[32m \033[32m  \033[0m\n"
bash checker.sh lem-in $file
i=$((i+1))
done
cd ../
}

check_leak_valid(){
echo -e "\n\e[1;34mMEMORY LEAK WITH VALID MAP TESTS\e[0m\n"
i=1
dir="valid_tests/*"
for file in $dir
do
echo -en "\t\033[32m \033[32m TEST NUMBER $i $file \033[32m \033[32m  \033[0m\n"
valgrind 2>&1 --leak-check=full --show-leak-kinds=all ./lem-in < $file | grep "LEAK SUMMARY:" -A5 | awk -F":" '{print $1 $2}'
i=$((i+1))
done
}

check_complexity(){
echo -e "\n\e[1;34mCHECK COMPLEXITY\e[0m\n"
i=0;
dir="time_check/*"
for file in $dir
do
start=$(($(date +%s%N)/1000000))
(./lem-in < $file) > /dev/null
end=$(($(date +%s%N)/1000000))
time=$((end-start))
if [ "$time" -le $"3000" ]
then
echo -en "TEST #$i: Execution time in miliseconds = \033[32m\033[32m$((end-start))\t OK \033[32m \033[32m  \033[0m\n"
else
echo -en "TEST #$i -> time more than 3000 milisec -> \033[31m \033[31m $((end-start)) milisec\033[0m\n"
fi
i=$((i+1));
done
}

chcek_accuracy(){
echo -e "\n\e[1;34mCHECK ACCURACY\e[0m\n"
i=0;
dir="accuracy_check/*"
for file in $dir
do
EXP=$(head -n2 $file | grep "#" |cut -d':' -f2)
GET=$(./lem-in < $file | grep L | wc -l)
if [ "$GET" -le "$EXP" ]
then
echo -en "test #$i shoud be: $EXP \033[32m\033[32m get from lem-in: $GET \033[32m\033[32m \033[0m\n"
else
echo -en "\033[31m \033[31m TEST NUMBER $i -> shoud be: $EXP get from lem-in: $GET \033[0m\n"
fi
i=$((i+1));
done
}

print_usage(){
echo "options:"
echo "-h    show options with brief descriptions"
echo "-a    check errors management"
echo "-b    check leak with invalid map"
echo "-c    check output is right format"
echo "-d    check leak with valid map"
echo "-e    check time complexity"
echo "-f    check accuracy"
exit 0
}

script_name="lem-in checker"

while getopts 'habcdef' flag; do
  case "${flag}" in
    a)  check_errors ;;
    b)  check_leak_errors ;;
    c)  check_ouput ;;
    d)  check_leak_valid ;;
    e)  check_complexity ;;
    f)  chcek_accuracy ;;
    h)  print_usage ;;
    *)  print_usage
    exit 1 ;;
  esac
done
