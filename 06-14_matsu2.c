float swap(float num)
{
  union bytes {
    float f;
    unsigned char c[4];
  };
  union bytes original, swapped;
  int i;

  original.f = num;

  for(i=0; i<sizeof(original); i++) {
    swapped.c[i] = original.c[sizeof(original)-i-1];
  }

  return swapped.f;
}