#include"ising.h"

int n_samples(void (*algorithm)())
{
    if(algorithm == SW) return 10000;
    if(algorithm == MH) return 100000;
    return 0;
}

int main(){
    double b, start = 0.4f, end = 0.475f;
    int lattice_size = 64;
    void (*algoritm)() = MH;

    for(b = start; b <= end; b += (end-start)/(2048/lattice_size)){
        dump_data(lattice_size, b, algoritm, n_samples( algoritm ) );
    }
    return 0;
}
