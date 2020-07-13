#!/bin/bash

arg=${1:-Italy}  # 引数取得．引数がない場合は"Italy"を代入．
n=0  # 九九の大きさ

if [ $arg = "Italy" ]
then
  n=10
elif [ $arg = "Australia" ]
then
  n=12
elif [ $arg = "India" ]
then
  n=20
else
  echo "Invalid argument"
  exit 1
fi


# 見出し
echo -n "    |"
for i in `seq 1 $n`
do
  printf "%4d" $i
done
echo ""

# 罫線
echo -n "----+"
for i in `seq 1 $n`
do
  echo -n "----"
done
echo ""

# 本体
for i in `seq 1 $n`
do
  printf "%4d|" $i  # 見出し + 罫線
  for j in `seq 1 $n`
  do
    ./04-3_99.out -i $i -j $j
    tmp=$?
    if [ $i -ge 13 ] && [ $j -ge 13 ]
    then
      if [ $tmp -lt 169 ]
      then
        (( tmp += 256 ))
      fi
    fi
    printf "%4d" $tmp  # プログラムの計算結果を出力
  done
  echo ""
done

# 罫線
echo -n "----+"
for i in `seq 1 $n`
do
  echo -n "----"
done
echo ""
