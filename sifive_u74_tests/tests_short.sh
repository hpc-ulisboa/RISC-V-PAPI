#! /bin/bash
# Compile test files
echo $(make)

#################################################
echo "### PERF TESTS ###" >>$1
echo "overhead" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(sudo nice --19 ./perf_overhead) &>>$1
done
echo "total gemm 10s" >>$1
for ((i = 0; i < 40; i++)); do
    echo $(sudo nice --19 ./perf_total_time 450 500 550 0 0) &>>$1
done
echo "total gemm 30s" >>$1
for ((i = 0; i < 40; i++)); do
    echo $(sudo nice --19 ./perf_total_time 650 700 750 0 0) &>>$1
done
echo "total gemm 60s" >>$1
for ((i = 0; i < 40; i++)); do
    echo $(sudo nice --19 ./perf_total_time 850 900 950 0 0) &>>$1
done

#################################################
echo "### PAPI TESTS ###" >>$1
eecho "overhead" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(sudo nice --19 ./papi_overhead) &>>$1
done
echo "total gemm 10s" >>$1
for ((i = 0; i < 40; i++)); do
    echo $(sudo nice --19 ./papi_total_time 450 500 550 PAPI_TOT_CYC) &>>$1
done
echo "total gemm 30s" >>$1
for ((i = 0; i < 40; i++)); do
    echo $(sudo nice --19 ./papi_total_time 650 700 750 PAPI_TOT_CYC) &>>$1
done
echo "total gemm 60s" >>$1
for ((i = 0; i < 40; i++)); do
    echo $(sudo nice --19 ./papi_total_time 850 900 950 PAPI_TOT_CYC) &>>$1
done

#################################################
echo "### GENERAL TESTS ###" >>$1
echo "clock_gettime overhead" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(./gettime_time) &>>$1
done
