#! /bin/bash
# Compile test files
echo $(make)
TIMEFORMAT=%R

echo "no_count_no_time - 40 executions" >> $1
for ((i=0; i<40;i++))
do
    time {
        echo $(time ./no_count_no_time) &>> $1
    } &>> $1
done

echo "Perf_no_time - 40 executions" >> $1
for ((i=0; i<40;i++))
do
    time {
        echo $(time ./perf_no_time) &>> $1
    } &>> $1
done

echo "PAPI_no_time - 40 executions" >> $1
for ((i=0; i<40;i++))
do
    time {
        echo $(time ./papi_no_time) &>> $1
    } &>> $1
done

echo "no_count_time - 40 executions" >> $1
for ((i=0; i<40;i++))
do
    time {
        echo $(time ./no_count_time) &>> $1
    } &>> $1
done

echo "Perf_time - 40 executions" >> $1
for ((i=0; i<40;i++))
do
    time {
        echo $(time ./perf_time) &>> $1
    } &>> $1
done

echo "PAPI_time - 40 executions" >> $1
for ((i=0; i<40;i++))
do
    time {
        echo $(time ./papi_time) &>> $1
    } &>> $1
done

echo $(unset TIMEFORMAT)
