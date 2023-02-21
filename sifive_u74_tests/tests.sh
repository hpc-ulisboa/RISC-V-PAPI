#! /bin/bash
# Compile test files
echo $(make)
TIMEFORMAT=%R
echo "Perf_no_time - 20 executions" >> $1
# Do 20 executions of perf_no_time test
for ((i=0; i<20;i++))
do
    time {
        echo $(./perf_no_time) &>> $1
    } &>> $1
done

echo "PAPI_no_time - 20 executions" >> $1
for ((i=0; i<20;i++))
do
    time {
        echo $(./papi_no_time) &>> $1
    } &>> $1
done

echo $(unset TIMEFORMAT)

