#! /bin/bash
# Compile test files
echo $(make)
TIMEFORMAT=%R

echo "no_count_no_time - 20 executions" >> $1
for ((i=0; i<20;i++))
do
    time {
        echo $(./no_count_no_time) &>> $1
    } &>> $1
done

echo "Perf_no_time - 20 executions" >> $1
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

echo "no_count_time - 20 executions" >> $1
for ((i=0; i<20;i++))
do
    time {
        echo $(./no_count_time) &>> $1
    } &>> $1
done

echo "Perf_time - 20 executions" >> $1
for ((i=0; i<20;i++))
do
    time {
        echo $(./perf_time) &>> $1
    } &>> $1
done

echo "PAPI_time - 20 executions" >> $1
for ((i=0; i<20;i++))
do
    time {
        echo $(./papi_time) &>> $1
    } &>> $1
done

echo $(unset TIMEFORMAT)
