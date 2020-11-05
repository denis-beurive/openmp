#include <omp.h>
#include <stdio.h>
#include <unistd.h>

// export OMP_NUM_THREADS=4

int task1() {
    static int v = 0;
    // Put a sleep here, so we see the 2 threads working simultaneously.
    usleep(1000);
    return 2*v + 1;
}

int task2() {
    static int v = 0;
    // Put a sleep here, so we see the 2 threads working simultaneously.
    usleep(1000);
    return 3*v + 1;
}


int main() {

    int t1 = 0;
    int t2 = 0;

    // Task1 and Task2 are totally decoupled.
    // One thread will be assigned to Task1.
    // One thread will be assigned to Task2.

    #pragma omp parallel sections
    {
        // Task 1
        #pragma omp section
        for (int i=0; i<50; i++) { printf("#1 %d\n", omp_get_thread_num()); t1 += task1(); }

        // Task 2
        #pragma omp section
        for (int i=0; i<50; i++) { printf("#2 %d\n", omp_get_thread_num()); t2 += task2(); }
    }

    printf("t1=%d, t2=%d, t1+t2=%d\n", t1, t2, t1+t2);
    return 0;
}