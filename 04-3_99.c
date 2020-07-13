#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
  char c;
  long i=0, j=0;

  while((c = getopt(argc, argv, "i:j:")) != -1) {
    switch(c) {
    case 'i':
      i=strtol(optarg, NULL, 10);
      break;
    case 'j':
      j=strtol(optarg, NULL, 10);
      break;
    }
  }

  if(i<=0 || j<=0) {
    fprintf(stderr, "i or j is equal or less than 0.\n");
    exit(1);
  }

  /* multiply i and j, then return the value */
  return i*j;
}