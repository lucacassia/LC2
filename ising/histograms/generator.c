#include"ising.h"

int main(){

    double b, start = 0.30f, end = 0.45f;
    for(b = start; b <= end; b += (end-start)/6.0f)
        dump_data(8, b, SW, 1000000);

    return 0;
}
