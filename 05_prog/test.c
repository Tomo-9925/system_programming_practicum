#include <stdio.h>
#include "logistic.h"

int main(void) {
  float x;

  for(x=0; x<1.1; x+=0.1) {
    printf("x=%.2f, y=%.2f\n", x, logistic_(&x));
  }

  return 0;
}
