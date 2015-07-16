#!/usr/bin/sh

make

rm data/*

./levels
time ./generator

./histograms data/*.bin

rm img/*
gnuplot histograms.gnu
