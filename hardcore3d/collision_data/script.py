#!/usr/bin/python

from subprocess import call

eta = 0.3
stop = 0.681
step = 0.02

while eta <= stop:
    call(["./multi",str(eta),"10"])
    eta += step

