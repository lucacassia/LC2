#include"potts.h"

int main(){
/*
    double b, start = 0.4f, end = 1.2f;
    int lattice_size = 4;
    while( lattice_size <= 32){
        for(b = start; b <= end; b += (end-start)/(100))
            dump_data(lattice_size, b, SW, 50000 );
        lattice_size *= 2;
    }
*/
    double b;
    for(b=0.97;b<1.021;b+=(1.02-0.98)/25)
        dump_data(64, b, SW, 20000 );
    return 0;
}
