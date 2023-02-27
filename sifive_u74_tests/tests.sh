#! /bin/bash
# Compile test files
echo $(make)

#################################################
echo "### PERF TESTS ###" >>$1
echo "init - 100 executions" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(./perf_init_time) &>>$1
done

echo "start - 100 executions" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(./perf_start_time) &>>$1
done

echo "end - 100 executions" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(./perf_end_time) &>>$1
done

echo "close - 100 executions" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(./perf_close_time) &>>$1
done

echo "count - 40 executions" >>$1
for ((i = 0; i < 40; i++)); do
    echo $(./perf_count_time) &>>$1
done

echo "total - 40 executions" >>$1
for ((i = 0; i < 40; i++)); do
    echo $(./perf_total_time) &>>$1
done

#################################################
echo "### PAPI TESTS ###" >>$1
echo "init - 100 executions" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(./papi_init_time) &>>$1
done

echo "start - 100 executions" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(./papi_start_time) &>>$1
done

echo "end - 100 executions" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(./papi_end_time) &>>$1
done

echo "close - 100 executions" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(./papi_close_time) &>>$1
done

echo "count - 40 executions" >>$1
for ((i = 0; i < 40; i++)); do
    echo $(./papi_count_time) &>>$1
done

echo "total - 40 executions" >>$1
for ((i = 0; i < 40; i++)); do
    echo $(./papi_total_time) &>>$1
done

#################################################
echo "### GENERAL TESTS ###" >>$1
echo "kernel_time - 40 executions" >>$1
for ((i = 0; i < 40; i++)); do
    echo $(./kernel_time) &>>$1
done

echo "gettime_time - 100 executions" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(./gettime_time) &>>$1
done
