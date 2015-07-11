#include"ising.h"

int main(){
    double x;
    double start = -3.75;
    double  end  = -0.25;
    for(x = start; x <= end; x += (end-start)/10)
        dump_data(128, (1-exp(x))*BETA_CRITICAL, MH, 100000);
    return 0;
}
