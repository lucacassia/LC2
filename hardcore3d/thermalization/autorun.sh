#!/usr/bin/sh

rm data/* img/*
make

./thermalization

gnuplot thermalization.gnu
