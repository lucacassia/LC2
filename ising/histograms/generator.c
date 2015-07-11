#include"ising.h"

int main(){

    double b, start = 0.0f, end = 1.0f;
    for(b = start; b <= end; b += (end-start)/10.0f)
        dump_data(8, b, MH, 1000000);

    return 0;
}
