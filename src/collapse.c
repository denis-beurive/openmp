#include <omp.h>
#include <stdio.h>
#include <unistd.h>

int main() {

    int i = 0;
    int j = 0;

    // ==========================================================
    // i | j   | thread
    // 0 | 000 | #0
    // 0 | 001 | #0
    // 0 | 002 | #0
    // 0 | 003 | #0
    // 2 | 000 | #1
    // 2 | 001 | #1
    // 2 | 002 | #1
    // 2 | 003 | #1
    // 2 | 004 | #1
    // 2 | 005 | #1
    // 2 | 006 | #1
    // 3 | 000 | #1
    // 3 | 001 | #1
    // 3 | 002 | #1
    // 3 | 003 | #1
    // 3 | 004 | #1
    // 3 | 005 | #1
    // 3 | 006 | #1
    // 0 | 004 | #0
    // 0 | 005 | #0
    // 0 | 006 | #0
    // 1 | 000 | #0
    // 1 | 001 | #0
    // 1 | 002 | #0
    // 1 | 003 | #0
    // 1 | 004 | #0
    // 1 | 005 | #0
    // 1 | 006 | #0

    printf("==========================================================\n");

    printf("i | j   | thread\n");
    #pragma omp parallel for num_threads(4) default(none) shared(i) private(j) schedule(static, 2)
    for (i = 0; i < 4; i++)
        for (j = 0; j <= 6; j++) {
            printf("%d | %03d | #%d\n", i, j, omp_get_thread_num());
        }

    // ==========================================================
    // i | j   | thread
    // 0 | 002 | #1
    // 0 | 004 | #2
    // 0 | 003 | #1
    // 0 | 005 | #2
    // 1 | 003 | #1
    // 1 | 005 | #2
    // 1 | 004 | #1
    // 1 | 006 | #2
    // 2 | 004 | #1
    // 2 | 006 | #2
    // 2 | 005 | #1
    // 3 | 000 | #2
    // 3 | 005 | #1
    // 3 | 006 | #1
    // 0 | 000 | #0
    // 0 | 001 | #0
    // 1 | 001 | #0
    // 1 | 002 | #0
    // 2 | 002 | #0
    // 2 | 003 | #0
    // 3 | 003 | #0
    // 3 | 004 | #0
    // 0 | 006 | #3
    // 1 | 000 | #3
    // 2 | 000 | #3
    // 2 | 001 | #3
    // 3 | 001 | #3
    // 3 | 002 | #3

    printf("==========================================================\n");

    // Collapse(<number of loops>)
    // Note: if execution of any associated loop changes any of the values used
    //       to compute any of the iteration counts, then the behavior is unspecified.

    printf("i | j   | thread\n");
    #pragma omp parallel for num_threads(4) default(none) shared(i) private(j) collapse(2) schedule(static, 2)
    for (i = 0; i < 4; i++)
        for (j = 0; j <= 6; j++) {
            printf("%d | %03d | #%d\n", i, j, omp_get_thread_num());
        }
}