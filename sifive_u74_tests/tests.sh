#! /bin/bash

# Test usage:
#   - perf_overhead prints 4 measurements to stdout, being the delays to: get a perf_events file descriptor, start the count, stop and retrieve the count and close the file descriptor.
#   - papi_overhead prints 4 measurements to stdout, being the delays to: initialize the PAPI library, start the count, stop and retrieve the count and terminate the PAPI library.
#   - perf_total_time takes 5 inputs: the first 3 are the dimensions of the matrixes, the 4th  is the perf_event type field and the 5th is the perf_event config field (check https://web.eece.maine.edu/~vweaver/projects/perf_events/perf_event_open.html#lbAN),
#       and prints 2 measurements to stdout: the event count and the total time the test ran four.
#   - papi_total_time takes 4 inputs: the first 3 are the dimensions of the matrixes and the 4th  is the event name to be measured by PAPI,
#       and prints 2 measurements to stdout: the event count and the total time the test ran four.

# Compile test files
echo $(make)

#################################################
echo "### PERF TESTS ###" >>$1
echo "overhead" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(sudo nice --19 ./perf_overhead) &>>$1
done
echo "cycles gemm 10s" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(sudo nice --19 ./perf_total_time 450 500 550 0 0) &>>$1
done
echo "cycles gemm 30s" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(sudo nice --19 ./perf_total_time 650 700 750 0 0) &>>$1
done
echo "cycles gemm 60s" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(sudo nice --19 ./perf_total_time 850 900 950 0 0) &>>$1
done
echo "fp_load gemm 10s" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(sudo nice --19 ./perf_total_time 450 500 550 4 524288) &>>$1
done
echo "fp_store gemm 10s" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(sudo nice --19 ./perf_total_time 450 500 550 4 1048576) &>>$1
done
echo "fp_madd gemm 10s" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(sudo nice --19 ./perf_total_time 450 500 550 4 8388608) &>>$1
done
echo "d-cache_busy gemm 10s" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(sudo nice --19 ./perf_total_time 450 500 550 4 4097) &>>$1
done
echo "br_target_miss gemm 10s" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(sudo nice --19 ./perf_total_time 450 500 550 4 16385) &>>$1
done
echo "fp_interlock gemm 10s" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(sudo nice --19 ./perf_total_time 450 500 550 4 262145) &>>$1
done
echo "i-cache_miss gemm 10s" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(sudo nice --19 ./perf_total_time 450 500 550 4 258) &>>$1
done
echo "d-cache_miss gemm 10s" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(sudo nice --19 ./perf_total_time 450 500 550 4 514) &>>$1
done
echo "d-cache_wb gemm 10s" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(sudo nice --19 ./perf_total_time 450 500 550 4 1026) &>>$1
done

#################################################
echo "### PAPI TESTS ###" >>$1
echo "overhead" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(sudo nice --19 ./papi_overhead) &>>$1
done
echo "cycles gemm 10s" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(sudo nice --19 ./papi_total_time 450 500 550 PAPI_TOT_CYC) &>>$1
done
echo "cycles gemm 30s" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(sudo nice --19 ./papi_total_time 650 700 750 PAPI_TOT_CYC) &>>$1
done
echo "cycles gemm 60s" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(sudo nice --19 ./papi_total_time 850 900 950 PAPI_TOT_CYC) &>>$1
done
echo "fp_load gemm 10s" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(sudo nice --19 ./perf_total_time 450 500 550 FP_LOAD_RETIRED) &>>$1
done
echo "fp_store gemm 10s" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(sudo nice --19 ./perf_total_time 450 500 550 FP_STORE_RETIRED) &>>$1
done
echo "fp_madd gemm 10s" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(sudo nice --19 ./perf_total_time 450 500 550 FP_FUSEDMADD_RETIRED) &>>$1
done
echo "d-cache_busy gemm 10s" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(sudo nice --19 ./perf_total_time 450 500 550 DCACHE_DTIM_BUSY) &>>$1
done
echo "br_target_miss gemm 10s" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(sudo nice --19 ./perf_total_time 450 500 550 BRANCH_TARGET_MISPREDICTION) &>>$1
done
echo "fp_interlock gemm 10s" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(sudo nice --19 ./perf_total_time 450 500 550 FP_INTERLOCK) &>>$1
done
echo "i-cache_miss gemm 10s" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(sudo nice --19 ./perf_total_time 450 500 550 ICACHE_RETIRED) &>>$1
done
echo "d-cache_miss gemm 10s" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(sudo nice --19 ./perf_total_time 450 500 550 DCACHE_MISS_MMIO_ACCESSES) &>>$1
done
echo "d-cache_wb gemm 10s" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(sudo nice --19 ./perf_total_time 450 500 550 DCACHE_WRITEBACK) &>>$1
done

#################################################
echo "### GENERAL TESTS ###" >>$1
echo "clock_gettime overhead" >>$1
for ((i = 0; i < 100; i++)); do
    echo $(./gettime_time) &>>$1
done
