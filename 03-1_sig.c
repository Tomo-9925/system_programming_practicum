#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <limits.h>
#include <sys/time.h>
#include <sys/param.h>

const static char *file = "save-data.dat";
double x, y;

void sig_save(int args /* UNUED */)
{
  char filepath[PATH_MAX];
  char *timestr;
  char *homedir = getenv("HOME");
  time_t nowtime;
  FILE *fp;

  if(strlen(homedir)+strlen(file)+1 > PATH_MAX) {
    fprintf(stderr, "Path to %s is too long.\n", file);
    exit(1);
  }

  sprintf(filepath, "%s/%s", homedir, file);
  fp = fopen(filepath, "w");
  if(fp==NULL) {
    fprintf(stderr, "File %s can't be opened.\n", file);
    exit(1);
  }

  nowtime = time(NULL);
  fprintf(fp, "Date/Time: %s", ctime(&nowtime));
  fprintf(fp, "X(n) = %lf, X(n+1) = %lf\n", x, y);
  fclose(fp);

  signal(SIGINT, sig_save);
}

double logistic(double x)
{
  double y = 3.8 * x * (1 - x);

  return y;
}

void sig_print(int sigid)
{
  printf("x = %lf\n", x);
  printf("y = %lf\n", y);

  signal(SIGUSR1, sig_print);
}

void sig_exit(int sigid)
{
  exit(0);
}

int main(void)
{
  struct timeval tv;
  int ret;

  if( (ret = fork()) == -1 ) {
    perror("can't exec subprocess\n");
    exit(1);
  }
  if(ret) {
    exit(0);
  }

  srand((unsigned)time((time_t *)NULL));

  tv.tv_sec = 1;
  tv.tv_usec = 0;

  printf("このプログラムは，無限ループのプログラムです．\n");
  printf("適当な間隔で，CTRL-Cを押してシグナルを発生させて\n");
  printf("ください．\n");
  printf("完全に終了するときは，killコマンドで終了してください．\n");
  printf("このプログラムは，CTRL-Cでは止まりません．\n");

  signal(SIGINT, sig_save);
  signal(SIGUSR1, sig_print);
  signal(SIGUSR2, sig_exit);

  x = 0.1 + rand()/(double)RAND_MAX*0.001-0.0005;
  while(1) {
    y = logistic(x);
    select(0, NULL, NULL, NULL, &tv);
    x = y;
  }
}