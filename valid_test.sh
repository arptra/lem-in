#!/bin/bash

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
echo -en "\t\033[32m \033[32m TEST NUMBER $i OK \033[32m \033[32m  \033[0m\n"
echo -en "\t\033[32m \033[32m Execution time in miliseconds: $((end-start)) \033[32m \033[32m  \033[0m\n"
else
echo -en "\033[31m \033[31m TEST NUMBER $i -> time more than 3000 milisec -> $((end-start)) milisec\033[0m\n"
fi
i=$((i+1));
done


i=0;
dir="accuracy_check/*"
for file in $dir
do
EXP=$(head -n2 $file | grep "#" |cut -d':' -f2)
GET=$(./lem-in < $file | grep L | wc -l)
if [ "$GET" -le "$EXP" ]
then
echo -en "\t\033[32m \033[32m TEST NUMBER $i OK \033[32m \033[32m  \033[0m\n"
echo -en "\t\033[32m \033[32m shoud be: $EXP get from lem-in: $GET \033[32m \033[32m  \033[0m\n"
else
echo -en "\033[31m \033[31m TEST NUMBER $i -> shoud be: $EXP get from lem-in: $GET \033[0m\n"
fi
i=$((i+1));
done

cp lem-in 42_lem-in_tools
dir="maps/validation_errs/*"
i=1;
for file in $dir
do
err=$(./lem-in 2>&1 < $file)
if [ "$err" = $"ERROR" ]
then
echo -en "test #:$i PASS: \033[32m \033[32m OK \033[0m\n"
else
echo -en "test #:$i NOT PASS filename: $file;\033[31m \033[31m KO \033[0m\n"
fi
i=$((i+1))
done

cd 42_lem-in_tools
bash check_invalid_map.sh ./lem-in
cd ../

dir="maps/validation_errs/*"
i=1
if [ "$1" = $"--leak-invalid" ]
then
echo -en "\t\033[32m \033[32m LOOK FOR LEAK \033[32m \033[32m  \033[0m\n"
for file in $dir
do
echo -en "\t\033[32m \033[32m TEST NUMBER $i $file \033[32m \033[32m  \033[0m\n"
valgrind 2>&1 --leak-check=full --show-leak-kinds=all ./lem-in < $file | grep "LEAK SUMMARY:" -A5 | awk -F":" '{print $1 $2}'
i=$((i+1))
done
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

i=1
if [ "$2" = $"--leak-valid" ]
then
echo -en "\t\033[32m \033[32m LOOK FOR LEAK \033[32m \033[32m  \033[0m\n"
for file in $dir
do
echo -en "\t\033[32m \033[32m TEST NUMBER $i $file \033[32m \033[32m  \033[0m\n"
valgrind 2>&1 --leak-check=full --show-leak-kinds=all ./lem-in < $file | grep "LEAK SUMMARY:" -A5 | awk -F":" '{print $1 $2}'
i=$((i+1))
done
fi
cd ../
