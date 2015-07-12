#include"ising.h"

int main(){

    double b;
    for(b = 0.32; b <= 0.40; b += 0.005f)
        dump_data(8, b, SW, 1000000);

    return 0;
}
