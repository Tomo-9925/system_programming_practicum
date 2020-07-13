#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double kaiseki(double *a, double *b);

int main(int argc, char **argv) {
  double a = strtod(argv[1], NULL);
  double b = strtod(argv[2], NULL);
  double a1;

  a1 = kaiseki(&a, &b);

  printf("%.8lf\n", a1);

  return 0;
}

double kaiseki(double *a, double *b) {
  return ( -2 * cos((*b)/2) + 0.5 * sin(2*(*b)) ) - ( -2 * cos((*a)/2) + 0.5 * sin(2*(*a)) );
}