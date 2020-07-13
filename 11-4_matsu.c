#include <stdio.h>
#include <math.h>
#include "mpi.h"

#define RANGE (2.0/5.0*M_PI)

int main(int argc, char **argv)
{
  int me, np, n;
  double b_sec, a_sec;
  double cnt_lmt;  // 1区間の計算回数
  MPI_Status stat;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &np);
  MPI_Comm_rank(MPI_COMM_WORLD, &me);

  if (me == 0){
    n = atoi(argv[1]);
    cnt_lmt = (double)n/np;
  }

  b_sec = MPI_Wtime();
  MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&cnt_lmt, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  if (me == 0){
    int i;
    double x[2]={0.0,0.0}, o_x[50][2];  // 2次元配列で50台分の結果を格納可能に
    double tmp = 0;  // 各スレーブノードの計算結果を足し合わせるための仮の変数
    for(i=0;i<cnt_lmt;i++)  // 範囲の変更
      x[0]+=sin(RANGE*i/n)*(RANGE/n);
    a_sec = MPI_Wtime();
    x[1] = a_sec - b_sec;
    for(i=1;i<np;i++) {
      MPI_Recv(&o_x[i][0], 2, MPI_DOUBLE, i, 11, MPI_COMM_WORLD, &stat);  // 各スレーブノードからの処理結果取得
      printf("[S] Elapsed time(s): %lf\n", o_x[i][1]);  // 各スレーブノードの処理時間を出力
      tmp += o_x[i][0];  // 各スレーブノードの処理結果を足し合わせる
    }
    printf("[M] Elapsed time(s): %lf\n", x[1]);
    printf("Result: %25.15lf\n", x[0] + tmp);
  }
  else{
    int cnt;
    double x[2]={0.0,0.0}, b_sec, a_sec;
    double i = n/np*me;
    b_sec = MPI_Wtime();
    for(cnt=0;cnt<cnt_lmt;cnt++) { // ノードの番号によって計算箇所を変更
      x[0]+=sin(RANGE*i/n)*(RANGE/n);
      i++;
    }
    a_sec = MPI_Wtime();
    x[1] = a_sec - b_sec;
    MPI_Send(x, 2, MPI_DOUBLE, 0, 11, MPI_COMM_WORLD);
  }

  MPI_Finalize();

  if (me==0)
    printf("area  : %25.15lf\n", 1.0-cos(RANGE));
}