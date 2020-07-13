int kaijo_(int *n)
{
  int tmp = *n - 1;

  if(*n<=1) {
    return 1;
  } else {
    return *n * kaijo_(&tmp);
  }
}