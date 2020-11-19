#include <omp.h>
#include <stdio.h>
#include <unistd.h>

int main() {

    int i = 0;
    int j = 0;

    printf("==========================================================\n");

    printf("i | j   | thread\n");
    #pragma omp parallel for num_threads(4) default(none) shared(i) private(j) schedule(static, 2)
    for (i = 0; i < 4; i++)
        for (j = 0; j <= 6; j++) {
            printf("%d | %03d | #%d\n", i, j, omp_get_thread_num());
        }

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