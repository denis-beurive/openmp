#include <omp.h>
#include <stdio.h>

// export OMP_NUM_THREADS=4

int main() {

    int result = 0;

    // Number of loop: 8
    // Number of thread: 4 (OMP_NUM_THREADS)
    // The text printed to STDOUT can be misleading.
    printf("==========================================================\n");
    #pragma omp parallel for reduction(+:result)
    for (int i=0; i<8; i++) {
        result += i;
        printf("[%d] result(%p): %d\n", omp_get_thread_num(), (void*)&result, result); fflush(stdout);
    }
    // result = 0 + 1 + 2 + 3 +... + 7
    printf("result=%d\n", result);


    // The previous code could be replaced by the following one.
    // Although it is not identical.
    // Mak sure to set export OMP_NUM_THREADS=4 !!!
    // 2 passes, 4 threads per pass.
    // WARNING: the loop bloc is totally within critical section!!!
    printf("==========================================================\n");
    result = 0;
    int delta = -1;
    #pragma omp parallel default(none) shared(result, delta)
    for (int i=0; i<2; i++) {
        #pragma omp atomic
        delta += 1;
        #pragma omp atomic
        result += delta;
        printf("[%d] result(%p): %d\n", omp_get_thread_num(), (void*)&result, result);
    }
    // result = 0 + 1 + 2 + 3 +... + 7
    printf("result=%d\n", result);

}
