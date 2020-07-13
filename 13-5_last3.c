#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define A (M_PI/6)
#define B (3*M_PI/8)

double kaiseki();
double daikei(long div_num);

int main(int argc, char **argv) {
  long div_num = strtol(argv[1], NULL, 10);
  double a1 = kaiseki();
  double a2 = daikei(div_num);
  double a3 = fabs(a1-a2);

  printf("%ld\t", div_num);
  printf("%.8lf\t", a2);
  printf("%.8lf\n", a3);

  return 0;
}

double kaiseki() {
  return sin(B)-sin(A);
}

double daikei(long div_num) {
  int i;
  double h = (B-A)/div_num;
  double ans = 0;

  for(i=0; i<div_num; i++) {
    ans += ( cos(A+h*i) + cos(A+h*i+h) ) * h / 2;
  }

  return ans;
}