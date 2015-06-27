#include"ising.h"

int main(){

    dump_data(32, 0.43, SW, 100000);
    double x;
    for(x = -0.1; x <= 0.1; x += 0.004)
        dump_data(32, (x+1) * BETA_CRITICAL, SW, 100000 );

    return 0;
}
