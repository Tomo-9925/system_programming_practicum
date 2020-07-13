#include <stdio.h>
#include <math.h>

float logistic(float x)
{
  float y;

  y = 3.8 * x * (1 - x);
  return y;
}