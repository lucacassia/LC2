#!/usr/bin/sh

make

#rm data/*
#time ./generator
./observables data/*.bin

rm img/*
gnuplot observables.gnu
