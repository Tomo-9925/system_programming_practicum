#include <stdio.h>
#include <stdlib.h>
#include <math.h>

extern double kaiseki_(double *, double *);

int main(int argc, char **argv) {
  double a = strtod(argv[1], NULL);
  double b = strtod(argv[2], NULL);
  double a1;

  a1 = kaiseki_(&a, &b);

  printf("%.8lf\n", a1);

  return 0;
}