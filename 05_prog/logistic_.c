float logistic_(float *x)
{
  float y;

  y = 3.8 * (*x) * (1- (*x));
  return y;
}