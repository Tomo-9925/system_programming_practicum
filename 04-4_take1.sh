#!/bin/bash

# 見出し
echo -n "    |"
for i in `seq 1 $1`
do
  printf "%4d" $i
done
echo ""

# 罫線
echo -n "----+"
for i in `seq 1 $1`
do
  echo -n "----"
done
echo ""

# 本体
for i in `seq 1 $1`
do
  printf "%4d|" $i  # 見出し + 罫線
  for j in `seq 1 $1`
  do
    ./04-3_99.out -i $i -j $j  # 99.cの実行ファイルを実行
    printf "%4d" $?  # プログラムの計算結果を出力
  done
  echo ""
done

# 罫線
echo -n "----+"
for i in `seq 1 $1`
do
  echo -n "----"
done
echo ""
