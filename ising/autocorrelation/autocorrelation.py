import numpy,math
from scipy.optimize import curve_fit
import argparse

parser = argparse.ArgumentParser(description='Fitting of files.')
parser.add_argument('-i', action="store", dest="path", type=str, required=True, nargs='+', help='read from PATH')
parser.add_argument('-o', action="store", default="py_fit.dat", dest="output", type=str, help='place the output into OUTPUT')
args = parser.parse_args()

def func(x, a, b):
    return a*(1-(2*b/(2*b+1))*numpy.exp(-x/b))

output = open(args.output,"w")

for path in args.path:
    print("Fitting: "+path)
    f = open(path, 'r')
    data = numpy.loadtxt(f,unpack=True)
    f.close()
    popt, pcov = curve_fit(func, data[1], data[2])
    output.write(str((data[0][0]-0.4406868)/0.4406868)+"\t"+str(popt[0])+"\n")

output.close()
print("File saved to: "+args.output)

