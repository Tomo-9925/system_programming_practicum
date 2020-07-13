/*
  このプログラムは，pthread_create() 関数のオンラインマニュアルから
  引用したものをベースに，実習用に作り替えています．
*/

/*
#define _REENTRANT
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
/*
#include <thread.h>
*/

#define NUM_THREADS 10
#define SLEEP_TIME 1500000

void *sleeping(void *);   /* thread routine */
int i;
pthread_t tid[NUM_THREADS];      /* array of thread IDs */

int main(int argc, char *argv[])
{
    for ( i = 0; i < NUM_THREADS; i++)
	pthread_create(&tid[i], NULL, sleeping,
			(void *)SLEEP_TIME);
    fprintf(stderr,"\n");
    for ( i = 0; i < NUM_THREADS; i++)
	pthread_join(tid[i], NULL);

    printf("main() reporting that all %d threads have terminated\n", i);
    return (0);
}  /* main */

void * sleeping(void *arg)
{
    int sleep_time = (int)arg;
    pthread_t  thr;

    thr=pthread_self();
    printf("thread %p sleeping %d seconds ...\n",
					thr, sleep_time);
    usleep(sleep_time);
    printf("thread %p awakening\n", thr);
    return (NULL);
}
