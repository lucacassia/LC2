#include"ising.h"

int main(){

    double b, start = 0.35f, end = 0.40f;
    for(b = start; b <= end; b += (end-start)/10.0f)
        dump_data(8, b, MH, 1000000);

    return 0;
}
