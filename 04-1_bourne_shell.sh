#!/bin/sh

echo "# for文"
echo ""

echo "  |  1  2  3  4  5  6  7  8  9"
echo "--+---------------------------"
for i in 1 2 3 4 5 6 7 8 9;
do
  echo "$i |\c"
  for j in 1 2 3 4 5 6 7 8 9;
  do
    seki=`expr $i \* $j`
    printf "%3d" $seki
  done
  echo ""
done
echo "--+---------------------------"

echo ""
echo "# while文"
echo ""

echo "  |  1  2  3  4  5  6  7  8  9"
echo "--+---------------------------"
i=1
while [ `expr $i \< 10` = 1 ]
do
  echo "$i |\c"
  j=1
  while [ `expr $j \< 10` = 1 ]
  do
    seki=`expr $i \* $j`
    printf "%3d" $seki
    j=`expr $j + 1`
  done
  echo ""
  i=`expr $i + 1`
done
echo "--+---------------------------"