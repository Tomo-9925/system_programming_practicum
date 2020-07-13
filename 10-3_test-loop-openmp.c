#if 0

  on tcs05 only

  % gcc -fopenmp test-loop-openmp.c -o test-loop-openmp  -lm

#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define N	10000000

int main(void)
{
    double y1, y2;
    int x1, x2;

    y1=0.0;
#pragma omp parallel for reduction (+:y1)
    for(x1=0;x1<N;x1++){
	y1 = y1 + sin(2.0*M_PI*x1/N);
    }

    y2=0.0;
#pragma omp parallel for reduction (+:y2)
    for(x2=0;x2<N;x2++){
	y2 = y2 + cos(2.0*M_PI*x2/N);
    }

    printf("y1=%25.15lf\n", y1);
    printf("y2=%25.15lf\n", y2);

    return 0;
}
