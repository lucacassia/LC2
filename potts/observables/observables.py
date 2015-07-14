import numpy,math,argparse
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

parser = argparse.ArgumentParser(description='Fitting.')
parser.add_argument('-i', action="store", dest="path", type=str, required=True, nargs='+', help='read from PATH')
parser.add_argument('-o', action="store", default="obs.fit", dest="output", type=str, help='place the output into OUTPUT')
args = parser.parse_args()

def func(x, x0, a, b, c):
    return c-a*(x-x0)**2+b*(x-x0)**3

with open(args.output,"w") as output:
    for path in args.path:
        print("Fitting: "+path)

        # specific heat
        with open(path, 'r') as f:
            data = numpy.loadtxt(f, usecols = (0, 2), unpack=True)
        lattice_size = path.split('_')[0].split('/')[1]
        data = data[:,numpy.logical_and(0.35 < data[0,:], data[0,:] < 0.5)]
        plt.plot(data[0], data[1], 'b-')
        plt.show()
        left  = float(input("enter left  extremum: "))
        right = float(input("enter right extremum: "))
        
        crop = data[:,numpy.logical_and(left < data[0,:], data[0,:] < right)]
        p0 = [  4.34689952e-01,   1.77684498e+05,   3.07106140e+06,   1.83096187e+02]
        popt, pcov = curve_fit(func, crop[0], crop[1], p0, maxfev=100000)

        y = func(crop[0],popt[0],popt[1],popt[2],popt[3])
        plt.xlabel(r'$\beta$')
        plt.ylabel(r'$C$')
        plt.title('{}x{} '.format(lattice_size,lattice_size)+path.split('_')[1])
        plt.text(popt[0]+0.025, popt[3], r'$\beta_c={0:.6f}\pm{1:.6f}$'.format(popt[0], numpy.sqrt(pcov[0][0]) ) )
        plt.plot(data[0], data[1], 'k-')
        plt.plot(crop[0], y, 'r', lw=2)
        plt.show()

        print(popt)
        output.write("{}\t{}\t{}\t".format( lattice_size, popt[0], numpy.sqrt(pcov[0][0])) )

        # susceptibility
        with open(path, 'r') as f:
            data = numpy.loadtxt(f, usecols = (0, 5), unpack=True)
        lattice_size = path.split('_')[0].split('/')[1]
        data = data[:,numpy.logical_and(0.35 < data[0,:], data[0,:] < 0.5)]
        plt.plot(data[0], data[1], 'b-')
        plt.show()
        left  = float(input("enter left  extremum: "))
        right = float(input("enter right extremum: "))
        
        crop = data[:,numpy.logical_and(left < data[0,:], data[0,:] < right)]
        p0 = [ 0.43, 2.00000000e+05,   3.00000000e+06,   2.00000000e+02]
        popt, pcov = curve_fit(func, crop[0], crop[1], p0, maxfev=100000)

        y = func(crop[0],popt[0],popt[1],popt[2],popt[3])
        plt.xlabel(r'$\beta$')
        plt.ylabel(r'$\chi$')
        plt.title('{}x{} '.format(lattice_size,lattice_size)+path.split('_')[1])
        plt.text(popt[0]+0.025, popt[3], r'$\beta_c={0:.6f}\pm{1:.6f}$'.format(popt[0], numpy.sqrt(pcov[0][0]) ) )
        plt.plot(data[0], data[1], 'k-')
        plt.plot(crop[0], y, 'r', lw=2)
        plt.show()


        print(popt)
        output.write("{}\t{}\n".format( popt[0], numpy.sqrt(pcov[0][0])) )

print("File saved to: "+args.output)

