import numpy,math
from scipy.optimize import curve_fit
import argparse
from pylab import *

parser = argparse.ArgumentParser(description='Fitting.')
parser.add_argument('-i', action="store", dest="path", type=str, required=True, nargs='+', help='read from PATH')
parser.add_argument('-o', action="store", default="obs.fit", dest="output", type=str, help='place the output into OUTPUT')
args = parser.parse_args()

def func(x, a, b, c):
    return -a*(x-b)**2+c

with open(args.output,"w") as output:
    for path in args.path:
        print("Fitting: "+path)

        with open(path, 'r') as f:
            data = numpy.loadtxt(f, usecols = (0, 2), unpack=True)
        lattice_size = path.split('_')[0].split('/')[1]
        data = data[:,numpy.logical_and(0.40 < data[0,:], data[0,:] < 0.45)]
        p0 = [15000,0.43,150]
        popt, pcov = curve_fit(func, data[0], data[1], p0)

        y = func(data[0],popt[0],popt[1],popt[2])
        plot(data[0],y)
        plot(data[0],data[1])
        show()

        val = popt[1]
        err = numpy.sqrt(pcov[1][1])
        output.write("{}\t{}\t{}\t".format( lattice_size, val, err) )

        with open(path, 'r') as f:
            data = numpy.loadtxt(f, usecols = (0, 4), unpack=True)
        lattice_size = path.split('_')[0]
        data = data[:,numpy.logical_and(0.4 < data[0,:], data[0,:] < 0.45)]
        p0 = [15000,0.43,150]
        popt, pcov = curve_fit(func, data[0], data[1], p0)

        y = func(data[0],popt[0],popt[1],popt[2])
        plot(data[0],y)
        plot(data[0],data[1])
        show()

        val = popt[1]
        err = numpy.sqrt(pcov[1][1])
        output.write("{}\t{}\n".format( val, err) )

print("File saved to: "+args.output)

