#include <stdio.h>

int main(int argc, char **argv){
  int i;

  printf("文字列の個数 %d\n",argc);
  for(i=0;i<argc;i++)
    printf("%d 番目の文字列 %s\n",i,argv[i]);
  return 0;
}
