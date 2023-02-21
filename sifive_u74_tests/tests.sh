#! /bin/bash
# Compile test files
echo $(make)
echo $(TIMEFORMAT=%R)
echo "Perf_no_time" >> $1
# Do 20 executions of perf_no_time test
for ((i=0; i<20;i++))
do
    echo $(./perf_no_time) >> $1
done
echo $(unset TIMEFORMAT)

