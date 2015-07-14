import numpy,math
from scipy.optimize import curve_fit
import argparse

parser = argparse.ArgumentParser(description='Fitting of files.')
parser.add_argument('-i', action="store", dest="path", type=str, required=True, nargs='+', help='read from PATH')
parser.add_argument('-o', action="store", default="cor.fit", dest="output", type=str, help='place the output into OUTPUT')
args = parser.parse_args()

def func(x, a, b):
    return a*(numpy.exp(-x/b)+numpy.exp((x-lattice_size)/b))

with open(args.output,"w") as output:
    for path in args.path:
        print("Fitting: "+path)
        with open(path, 'r') as f:
            firstline = f.readline().split()
            lattice_size = int(firstline[1])
            beta = float(firstline[2])
            n_bins = int(firstline[4])
            data = numpy.loadtxt(f, usecols = (0, 1+n_bins), unpack=True)
        popt, pcov = curve_fit(func, data[0], data[1])
        mean = numpy.log(popt[1])
        error = 0.0
        for k in range(n_bins):
            with open(path, 'r') as f:
                data = numpy.loadtxt(f, skiprows = 1, usecols = (0,1+k), unpack=True)
            popt, pcov = curve_fit(func, data[0], data[1])
            error += (numpy.log(popt[1])-mean)**2
        error *= (n_bins - 1) / n_bins
        output.write("{}\t{}\t{}\n".format( numpy.log((0.44-beta)/0.44), mean, error ) )

print("File saved to: "+args.output)

