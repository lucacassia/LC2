import numpy,math
from scipy.optimize import curve_fit
import argparse

parser = argparse.ArgumentParser(description='Fitting of files.')
parser.add_argument('paths', metavar='path', type=str, nargs='+', help='path of the file(s) containing the data to fit')
parser.add_argument('-o', action="store", default="py_fit.dat", dest="output_path", type=str, help='output file')
args = parser.parse_args()

print(args)

def func(x, a, b):
    return a*(1-(2*b/(2*b+1))*numpy.exp(-x/b))

output = open(args.output_path,"w")

for path in args.paths:
    print("Fitting: "+path)
    f = open(path, 'r')
    data = numpy.loadtxt(f,unpack=True)
    f.close()
    popt, pcov = curve_fit(func, data[1], data[2])
    output.write(str((data[0][0]-0.4406868)/0.4406868)+"\t"+str(popt[0])+"\n")

output.close()
