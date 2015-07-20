#!/usr/bin/python

from subprocess import call

eta = 0.3
stop = 0.68
step = 0.05

while eta <= stop:
    call(["./multi",str(eta),"50"])
    eta += step

eta = 0.68
stop = 0.72
step = (stop-eta)/11

while eta < stop+0.001:
    call(["./multi",str(eta),"50"])
    eta += step

eta = 0.735
stop = 0.785
step = 0.015

while eta <= stop:
    call(["./multi",str(eta),"50"])
    eta += step

