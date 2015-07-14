#include"potts.h"

int main(){

    double b, start = 0.8f, end = 1.2f;
    int lattice_size = 8;
    while( lattice_size <= 64){
        for(b = start; b <= end; b += (end-start)/(10))
            dump_data(lattice_size, b, SW, 50000 );
        lattice_size *= 2;
    }
    return 0;
}
