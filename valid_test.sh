#!/bin/bash
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

cp lem-in 42_lem-in_tools
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
