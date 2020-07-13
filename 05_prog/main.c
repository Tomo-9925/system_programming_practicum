#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int sec, usec;

    srand((unsigned)time(NULL));

    printf("%d\n", rand());

    return 0;
}
