#include <omp.h>
#include <stdio.h>

// export OMP_NUM_THREADS=4

int main() {



    // This variable is shared between threads.
    int value_shared = 100;
    int value_private = 10;

    printf("=============================================================\n");
    printf("value_shared=%d, value_private=%d\n", value_shared, value_private);
    printf("=============================================================\n");

    // By default:
    // (1) the variables from the outer scope are shared in the parallel region
    // (2) any private variables need to be declared explicitly

    #pragma omp parallel private(value_private) // <=> #pragma omp parallel default(none) private(value_private)
    {
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
    printf("value_shared=%d, value_private=%d\n", value_shared, value_private);
    printf("=============================================================\n");

    // ----------------------------------------------------------------------------
    // ----------------------------------------------------------------------------

    #pragma omp parallel default(shared) private(value_private)
    {
        // The value "value_private" within this block is not the same than the one
        // declared without the bloc. "value_private" value is initialized to 0.
        value_shared += 1;  // This, de facto, points the the homonymous variable declared ou
        value_private += 1; // This, de facto, is a local variable.
        // By default, local variables in the parallel region are private. "x" is private (to threads).
        int x;
        printf("thread ID %d is running. value_shared=%d, value_private=%d, x=%d\n",
               omp_get_thread_num(),
               value_shared,
               value_private,
               x);
    }
    printf("=============================================================\n");
    printf("value_shared=%d, value_private=%d\n", value_shared, value_private);
    printf("=============================================================\n");
}