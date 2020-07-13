#include <stdio.h>

extern float logistic_(float *);

int main(void)
{
  float x = 0.1415926535, y;

  y = logistic_(&x);

  printf("%.9f\n", y);

  return 0;
}