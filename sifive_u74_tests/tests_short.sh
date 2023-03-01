#! /bin/bash
# Compile test files
echo $(make)

#################################################
echo "### PERF TESTS ###" >>$1
echo "count - 40 executions" >>$1
for ((i = 0; i < 40; i++)); do
    echo $(./perf_count_time) &>>$1
done

#################################################
echo "### PAPI TESTS ###" >>$1
echo "count - 40 executions" >>$1
for ((i = 0; i < 40; i++)); do
    echo $(./papi_count_time) &>>$1
done

#################################################
echo "### GENERAL TESTS ###" >>$1
echo "kernel_time - 40 executions" >>$1
for ((i = 0; i < 40; i++)); do
    echo $(./kernel_time) &>>$1
done
