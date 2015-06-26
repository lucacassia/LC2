import numpy,math
from scipy.optimize import curve_fit
import argparse

parser = argparse.ArgumentParser(description='Fitting of files.')
parser.add_argument('-i', action="store", dest="path", type=str, required=True, nargs='+', help='read from PATH')
parser.add_argument('-o', action="store", default="output.dat", dest="output", type=str, help='place the output into OUTPUT')
args = parser.parse_args()

for infile in args.path:
    with open(infile,'r') as f:
        firstline = f.readline()
        data = numpy.loadtxt(f, usecols = (0,), skiprows=1000, unpack=True)

    print(firstline)

    step = 1
    if firstline.split()[3] == 'MH':
        step = 10

    mean = 0.0
    for t in range(data.size):
        mean += data[t]
    mean /= data.size
    variance = 0.0
    for t in range(data.size):
        variance += (data[t]-mean)**2
    variance /= data.size
    for t in range(data.size):
        data[t] -= mean;

    print("μ  =",mean,"\nσ² =",variance)

    new_path = infile[:-4]+".acr"

    with open(new_path,"w") as output:
        output.write(firstline)
        for k_max in range(0,100*step,step):
            autocorrelation_time = 0.5
            for k in range(k_max):
                autocorrelation = 0.0
                for t in range(data.size - k):
                    autocorrelation += data[t] * data[t+k]
                autocorrelation /= variance * (data.size - k)
                autocorrelation_time += autocorrelation
            output.write("{}\t{}\n".format(k_max, autocorrelation_time))
    
        print("\nFile saved to:",new_path)

