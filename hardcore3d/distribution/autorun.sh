#!/usr/bin/sh

rm data/* img/*
make

./distribution

gnuplot distribution.gnu
