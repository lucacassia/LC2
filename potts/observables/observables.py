import numpy,math,argparse
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

parser = argparse.ArgumentParser(description='Fitting.')
parser.add_argument('-i', action="store", dest="path", type=str, required=True, nargs='+', help='read from PATH')
args = parser.parse_args()

def func(x, x0, a, b, c):
    return c-a*(x-x0)**2+b*(x-x0)**3

for path in args.path:
    print("Fitting: "+path)

    # specific heat
    with open(path, 'r') as f:
        data = numpy.loadtxt(f, usecols = (0, 2), unpack=True)
    lattice_size = path.split('_')[0].split('/')[1]
    plt.plot(data[0], data[1], 'bo')
    plt.show()
    left  = float(input("enter left  extremum: "))
    right = float(input("enter right extremum: "))

    crop = data[:,numpy.logical_and(left < data[0,:], data[0,:] < right)]
    p0 = [ 1.0, 2.00000000e+05,   3.00000000e+06,   2.00000000e+02]
    popt, pcov = curve_fit(func, crop[0], crop[1], p0, maxfev=100000)

    y = func(crop[0],popt[0],popt[1],popt[2],popt[3])
    plt.xlabel(r'$\beta$')
    plt.ylabel(r'$C$')
    plt.title('{}x{} '.format(lattice_size,lattice_size)+path.split('_')[1])
    plt.text(popt[0]+0.005, popt[3], r'$\beta_c={0:.6f}\pm{1:.6f}$'.format(popt[0], numpy.sqrt(pcov[0][0]) ) )
    plt.plot(data[0], data[1], 'k-')
    plt.plot(crop[0], y, 'r', lw=2)
    plt.show()
    print(popt)

    # susceptibility
    with open(path, 'r') as f:
        data = numpy.loadtxt(f, usecols = (0, 5), unpack=True)
    lattice_size = path.split('_')[0].split('/')[1]
    plt.plot(data[0], data[1], 'bo')
    plt.show()
    left  = float(input("enter left  extremum: "))
    right = float(input("enter right extremum: "))

    crop = data[:,numpy.logical_and(left < data[0,:], data[0,:] < right)]
    p0 = [ 1.0, 2.00000000e+05,   3.00000000e+06,   2.00000000e+02]
    popt, pcov = curve_fit(func, crop[0], crop[1], p0, maxfev=100000)

    y = func(crop[0],popt[0],popt[1],popt[2],popt[3])
    plt.xlabel(r'$\beta$')
    plt.ylabel(r'$\chi$')
    plt.title('{}x{} '.format(lattice_size,lattice_size)+path.split('_')[1])
    plt.text(popt[0]+0.005, popt[3], r'$\beta_c={0:.6f}\pm{1:.6f}$'.format(popt[0], numpy.sqrt(pcov[0][0]) ) )
    plt.plot(data[0], data[1], 'k-')
    plt.plot(crop[0], y, 'r', lw=2)
    plt.show()
    print(popt)
