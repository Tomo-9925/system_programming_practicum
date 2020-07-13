#!/bin/bash

echo "  |  1  2  3  4  5  6  7  8  9"
echo "--+---------------------------"
i=1
while [ $i -lt 10 ]
do
  echo -n "$i |"
  j=1
  while [ $j -lt 10 ]
  do
    seki=$((i*j))
    printf "%3d" $seki
    ((j++))  # j=$((j+1))
  done
  echo ""
  ((i++))
done
echo "--+---------------------------"