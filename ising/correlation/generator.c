#include"ising.h"

int main(){
    double x;
    for(x = -0.1; x < 0; x += 0.002){
        dump_data(128, (x+1)*BETA_CRITICAL, MH, 100000);
        dump_data(128, (x+1)*BETA_CRITICAL, SW, 100000);
    }
    return 0;
}
