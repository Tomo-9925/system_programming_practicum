#include <stdio.h>
#include <stdlib.h>
#include <math.h>

extern double daikei_(double *, double *);

int main(int argc, char **argv) {
  double a = strtod(argv[1], NULL);
  double b = strtod(argv[2], NULL);
  double y;

  y = daikei_(&a, &b);

  printf("%.8lf\n", y);

  return 0;
}