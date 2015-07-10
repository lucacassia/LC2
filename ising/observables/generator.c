#include"ising.h"

int main(){
    double b, start = 0.4f, end = 1.5f;
    int lattice_size = 64;

    for(b = start; b <= end; b += (end-start)/(2048/lattice_size)){
        dump_data(lattice_size, b, MH, 100000);
    }
    return 0;
}
