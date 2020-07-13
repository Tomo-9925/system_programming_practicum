#include <stdio.h>

union bytes {
  float f;
  unsigned int i;
  unsigned short s[2];
  unsigned char c[4];
};

union bytes swap(union bytes *original) {
  int i;
  union bytes swapped;

  for(i=0; i<sizeof(*original); i++) {
    swapped.c[i] = original->c[sizeof(*original)-i-1];
  }

  return swapped;
}

int main() {
  union bytes test, swapped;
  test.f = 170.079;

  printf("## バイト数の確認\n\n");

  printf("bytesのバイト数: %lu\n", sizeof(union bytes));
  printf("floatのバイト数: %lu\n", sizeof(float));
  printf("intのバイト数: %lu\n", sizeof(int));
  printf("shortのバイト数: %lu\n", sizeof(short));
  printf("ucharのバイト数: %lu\n\n", sizeof(unsigned char));

  printf("## 値の確認\n\n");

  printf("実際の数値: %f\n", test.f);
  printf("格納内容(int): %08X\n", test.i);
  printf("格納内容(short): %04X, %04X\n", test.s[0], test.s[1]);
  printf("格納内容(uchar): %02X, %02X, %02X, %02X\n\n", test.c[0], test.c[1], test.c[2], test.c[3]);

  swapped = swap(&test);

  printf("## 変換後の値の確認\n\n");

  printf("実際の数値: %f\n", swapped.f);
  printf("格納内容(int): %08X\n", swapped.i);
  printf("格納内容(short): %04X, %04X\n", swapped.s[0], swapped.s[1]);
  printf("格納内容(uchar): %02X, %02X, %02X, %02X\n", swapped.c[0], swapped.c[1], swapped.c[2], swapped.c[3]);

  return 0;
}