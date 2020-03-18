#!/bin/bash
dir="maps/validation_errs/*"
i=0;
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

i=0
if [ "$1" = $"-leak" ]
then
echo -en "\t\033[32m \033[32m LOOK FOR LEAK \033[32m \033[32m  \033[0m\n"
for file in $dir
do
err=$(valgrind --leak-check=full --show-leak-kinds=all ./lem-in < $file)
echo -en "\t\033[32m \033[32m TEST NUMBER $i \033[32m \033[32m  \033[0m\n"
echo $err
i=$((i+1))
done
fi

# to test for right path
#
#for file in $dir; do echo $file;  bash checker.sh lem-in $file; done
#
#run in dir 42_lem-in_tools
#