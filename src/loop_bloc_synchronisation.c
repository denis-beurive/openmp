#include <omp.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// export OMP_NUM_THREADS=4

int function(int x) {
    static int n = 0;
    n = n + 1;
    printf("function: (%i) n=%d\n", x, n); fflush(stdout);
    return 2*x + n;
}

int function_synchronized(int x) {
    static int n = 0;
    #pragma omp atomic
    n = n + 1;
    printf("function: (%i) n=%d\n", x, n); fflush(stdout);
    return 2*x + n;
}

int main() {

    int value_private = 10; // The value will never change
    int counter = 0;
    int result = 0;

    // Execute 3*4=12 loops (3 loops per thread).
    // Access to the function "function" is not synchronized.

    printf("==========================================================\n");
    #pragma omp parallel default(none) private(value_private) shared(counter, result)
    for (int i=0; i<3; i++) {
        result = function(i);
        printf("go [%d] counter:%d result:%d, i:%d\n", omp_get_thread_num(), counter, result, i);
        counter += 1;
    }

    // Example of output:
    //
    //    function: (0) n=2
    //    go [0] counter:0 result:3, i:0
    //    function: (1) n=4
    //    go [0] counter:1 result:6, i:1
    //    function: (2) n=5
    //    go [0] counter:2 result:9, i:2
    //    function: (0) n=3
    //    go [2] counter:3 result:5, i:0
    //    function: (1) n=6
    //    go [2] counter:4 result:8, i:1
    //    function: (2) n=7
    //    go [2] counter:5 result:11, i:2
    //    function: (0) n=1
    //    go [3] counter:6 result:7, i:0
    //    function: (1) n=8
    //    go [3] counter:7 result:10, i:1
    //    function: (2) n=9
    //    go [3] counter:8 result:13, i:2
    //    function: (0) n=1
    //    go [1] counter:9 result:9, i:0
    //    function: (1) n=10
    //    go [1] counter:10 result:12, i:1
    //    function: (2) n=11
    //    go [1] counter:11 result:15, i:2
    //    counter=12 (expected 12)
    //
    // As we can see, 2 threads may execute the function simultaneously:
    //
    //    go [2] counter:5 result:11, i:2
    //    function: (0) n=1
    //    go [3] counter:8 result:13, i:2
    //    function: (0) n=1
    //
    // Threads 2 and 3 accessed the static variable "n" simultaneously.

    printf("counter=%d (expected 12)\n", counter);

    // Execute 3*4=12 loops (3 loops per thread).
    // Access to the function "function" is synchronized.

    printf("==========================================================\n");
    #pragma omp parallel default(none) private(value_private) shared(counter, result)
    for (int i=0; i<3; i++) {
        // Synchronized the access to the function "function".
        #pragma omp critical
        result = function(i);
        printf("go [%d] counter:%d result:%d, i:%d\n", omp_get_thread_num(), counter, result, i);
        counter += 1;
    }

    // Execute 3*4=12 loops (3 loops per thread).
    // Access to the function "function_synchronized" is not synchronized.
    // However, "function_synchronized" contains critical sections.

    printf("==========================================================\n");
    #pragma omp parallel default(none) private(value_private) shared(counter, result)
    for (int i=0; i<3; i++) {
        // Synchronized the access to the function "function".
        result = function_synchronized(i);
        printf("go [%d] counter:%d result:%d, i:%d\n", omp_get_thread_num(), counter, result, i);
        counter += 1;
    }
    printf("==========================================================\n");

}
