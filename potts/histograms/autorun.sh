#!/usr/bin/sh

make

rm data/*

./example
time ./generator

./histograms data/*.bin

rm img/*
gnuplot histograms.gnu
