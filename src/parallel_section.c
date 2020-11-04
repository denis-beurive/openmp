#include <omp.h>
#include <stdio.h>

// export OMP_NUM_THREADS=4

int main() {

    // This variable is shared between threads.
    int value_shared = 100; // The value wil change
    int value_other_shared = 200; // The value wil change
    int value_private = 10; // The value will never change

    // ----------------------------------------------------------------------------
    // The default scope is not specified.
    // ----------------------------------------------------------------------------

    printf("=============================================================\n");
    printf("value_shared=%d, value_private=%d\n", value_shared, value_private);
    printf("=============================================================\n");

    // By default:
    // (1) the variables from the outer scope are shared in the parallel region.
    // (2) any variables declared as "private" need to be declared explicitly.

    #pragma omp parallel private(value_private) // <=> #pragma omp parallel default(none) private(value_private)
    {
        value_private = 0;
        value_other_shared = 0;

        value_shared += 1;   // This, de facto, points the the homonymous variable from the outer scope.
                             // This variable if shared between all threads.
        value_private += 1;  // This, de facto, is a local variable.
                             // Each thread has its own "clone" of this variable.
        int x;
        printf("thread ID %d is running. value_shared=%d, value_private=%d, x=%d\n",
               omp_get_thread_num(),
               value_shared,
               value_private,
               x);
    }
    printf("=============================================================\n");
    printf("value_shared=%d (expected 104), value_private=%d,  value_other_shared=%d (expected 0)\n", value_shared, value_private, value_other_shared);
    printf("=============================================================\n");

    // ----------------------------------------------------------------------------
    // The default scope is specified to "none" - default(none)
    // ----------------------------------------------------------------------------

    // By specifying "default(none)", you must declare the scope of **ALL** variables
    // from the outer scope (value_private, value_other_shared, value_shared).

    #pragma omp parallel default(none) private(value_private, value_other_shared) shared(value_shared) // <=> #pragma omp parallel default(none) private(value_private)
    {
        value_private = 0;
        value_other_shared = 0;

        value_shared += 1;   // This, de facto, points the the homonymous variable from the outer scope.
                             // This variable is shared between all threads.
        value_private += 1;  // This, de facto, is a local variable.
        value_other_shared += 1;
        // Each thread has its own "clone" of this variable.
        int x = 1000;
        printf("thread ID %d is running. value_shared=%d, value_private=%d, value_other_shared=%d, x=%d\n",
               omp_get_thread_num(),
               value_shared,
               value_private,
               value_other_shared,
               x);
    }
    printf("=============================================================\n");
    printf("value_shared=%d (expected 108), value_private=%d, value_other_shared=%d (expected 0)\n", value_shared, value_private, value_other_shared);
    printf("=============================================================\n");

    // ----------------------------------------------------------------------------
    // The default scope is specified to "shared" - default(shared)
    // ----------------------------------------------------------------------------

    // shared: the data declared outside a parallel region is shared, which means visible
    // and accessible by all threads simultaneously. By default, all variables in the work
    // sharing region are shared except the loop iteration counter.

    #pragma omp parallel default(shared) private(value_private)
    {
        value_private = 0;

        // The value "value_private" within this block is not the same than the one
        // declared without the bloc. "value_private" value is initialized to 0.
        value_shared += 1;  // This, de facto, points the the homonymous variable from the outer scope.
                            // This variable is shared between all threads.
        value_private += 1; // This, de facto, is a local variable.
        // By default, local variables in the parallel region are private. "x" is private (to threads).
        int x = 5;
        printf("thread ID %d is running. value_shared=%d, value_private=%d, x=%d\n",
               omp_get_thread_num(),
               value_shared,
               value_private,
               x);
    }
    printf("=============================================================\n");
    printf("value_shared=%d (expected 112), value_private=%d (expected 10), value_other_shared=%d\n", value_shared, value_private, value_other_shared);
    printf("=============================================================\n");


    // WARNING: 4 threads per loop.
    //          each loop modify one entry (and only one) entry in the array.
    //          => for a given "i", "array[i] += 1" is executed 4 times per loop!
    //          => for a given "i", "array[i]" will be incremented by 4.
    printf("\n==========================================================\n");
    int array[3] = {0, 10, 20};
    #pragma omp parallel default(shared)
    for (int i=0; i<3; i++) { // "i" represents the index in the array "array".
        #pragma omp atomic
        array[i] += 1;
    }
    // Expected: 0+4, 10+4, 20+4 => 4, 14, 24
    printf("[%d, %d, %d]\n", array[0], array[1], array[2]);

}