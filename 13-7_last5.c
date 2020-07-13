#include <stdio.h>
#include <stdlib.h>
#include <math.h>

extern double daikei_(double *, double *, long *);
double kaiseki(double *a, double *b);

int main(int argc, char **argv) {
  long div_num = strtol(argv[3], NULL, 10);
  double a = strtod(argv[1], NULL);
  double b = strtod(argv[2], NULL);
  double a1, a2, a3;

  if(a>=b || fabs(a-b)<1.0/10000) {
    fprintf(stderr, "引数の値を変更してください．\n");
    return 1;
  }

  a1 = kaiseki(&a, &b);
  a2 = daikei_(&a, &b, &div_num);
  a3 = fabs(a1-a2);

  printf("%ld\t", div_num);
  printf("%.8lf\t", a1);
  printf("%.8lf\t", a2);
  printf("%.8lf\n", a3);

  return 0;
}

double kaiseki(double *a, double *b) {
  return ( -2 * cos((*b)/2) + 0.5 * sin(2*(*b)) ) - ( -2 * cos((*a)/2) + 0.5 * sin(2*(*a)) );
}