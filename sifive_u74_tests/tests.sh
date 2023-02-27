#! /bin/bash
# Compile test files
echo $(make)

#################################################
echo "### PERF TESTS ###" >>$1
echo "init - 100 executions" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(time ./perf_init_time) &>>$1
done

echo "start - 100 executions" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(time ./perf_start_time) &>>$1
done

echo "end - 100 executions" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(time ./perf_end_time) &>>$1
done

echo "close - 100 executions" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(time ./perf_close_time) &>>$1
done

echo "count - 40 executions" >>$1
for ((i = 0; i < 40; i++)); do
    echo $(time ./perf_count_time) &>>$1
done

echo "total - 40 executions" >>$1
for ((i = 0; i < 40; i++)); do
    echo $(time ./perf_total_time) &>>$1
done

#################################################
echo "### PAPI TESTS ###" >>$1
echo "init - 100 executions" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(time ./papi_init_time) &>>$1
done

echo "start - 100 executions" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(time ./papi_start_time) &>>$1
done

echo "end - 100 executions" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(time ./papi_end_time) &>>$1
done

echo "close - 100 executions" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(time ./papi_close_time) &>>$1
done

echo "count - 40 executions" >>$1
for ((i = 0; i < 40; i++)); do
    echo $(time ./papi_count_time) &>>$1
done

echo "total - 40 executions" >>$1
for ((i = 0; i < 40; i++)); do
    echo $(time ./papi_total_time) &>>$1
done

#################################################
echo "### GENERAL TESTS ###" >>$1
echo "kernel_time - 40 executions" >>$1
for ((i = 0; i < 40; i++)); do
    echo $(time ./kernel_time) &>>$1
done

echo "gettime_time - 100 executions" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(time ./gettime_time) &>>$1
done
