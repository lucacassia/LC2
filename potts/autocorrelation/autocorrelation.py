import numpy,math
from scipy.optimize import curve_fit
import argparse

parser = argparse.ArgumentParser(description='Fitting of files.')
parser.add_argument('-i', action="store", dest="path", type=str, required=True, nargs='+', help='read from PATH')
parser.add_argument('-o', action="store", default="acr.fit", dest="output", type=str, help='place the output into OUTPUT')
args = parser.parse_args()

def func(x, a, b):
    return a*(1-(2*b/(2*b+1))*numpy.exp(-x/b))

with open(args.output,"w") as output:

    for path in args.path:
        print("Fitting: "+path)
        with open(path, 'r') as f:
            beta = float(f.readline().split()[2])
            data = numpy.loadtxt(f,unpack=True)
        popt, pcov = curve_fit(func, data[0], data[1])
        output.write("{}\t{}\t{}\n".format( (beta-1.00505254)/1.00505254, popt[0], popt[1] ) )

print("File saved to: "+args.output)

