#include"ising.h"

int main(){
    double b, start = 0, end = 1;
    for(b = start; b <= end; b += (end-start)/10)
        dump_data(4, b, SW, 1000000);
    return 0;
}
