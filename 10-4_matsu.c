#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS 16  // 使用スレッド数
#define A 0  // 解1
#define B 2  // 解2
#define P 10000000  // 分割数

void *calc(void *);  // 計算を行う関数
pthread_t tid[NUM_THREADS];  // スレッドIDの管理
double x_range = (double)(B-A) / NUM_THREADS;  // 1スレッドが計算する区間
double h = (double)(B-A) / P;  // 四角形の面積を計算するときに使うxの幅
int cnt_lmt = P / NUM_THREADS;  // 1スレッドあたりの計算回数
double sum = 0;  // 合計値

int main(int argc, char *argv[])
{
  int i, tmp[NUM_THREADS];

  for ( i = 0; i < NUM_THREADS; ++i ) {
    tmp[i] = i;  // スレッドに割り振られた番号
    pthread_create(&tid[i], NULL, &calc, &tmp[i]);
  }
  for ( i = 0; i < NUM_THREADS; i++ ) {
    pthread_join(tid[i], NULL);
  }

  printf("%.10f\n", sum);  // 結果の出力

  return (0);
}

void *calc(void *arg)
{
  int num = *((int*)arg);  // 何番目の区間を計算するか
  int cnt;  // 現在の計算回数
  double x_0 = A + x_range * num;  // 区間のはじめのxの数値
  double x = x_0;
  double tmp = 0;  // 合計値を一時的に確保する場所

  for( cnt = 0 ; cnt < cnt_lmt ; cnt++ ) {
    tmp += (-pow((x-1),2)+1) * h;
    x += h;
  }

  sum += tmp;

  return (NULL);
}
