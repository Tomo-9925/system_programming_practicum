#!/bin/sh

gnuplot << EOF
pi=3.141592653589
set grid
set xrange [-pi:pi]
set terminal postscript eps
set output 'sin.eps'
plot sin(x)
quit
EOF
