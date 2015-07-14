#!/usr/bin/sh

make

rm data/*

time ./generator
cd data
./../../bin2dat/bin2dat *.bin
cd ..

rm img/*
gnuplot thermalization.gnu
