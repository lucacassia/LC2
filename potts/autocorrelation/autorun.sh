#!/usr/bin/sh

rm data/*
rm img/*

make

time ./generator
./autocorrelation data/*.bin
cat data/*.acr > data/SW.3d
python autocorrelation.py -i data/*.acr -o data/SW.fit
gnuplot autocorrelation.gnu

