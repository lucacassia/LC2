#include"ising.h"

int main(){
    double b, start = 0.3f, end = 0.6f;
    for(b = start; b <= end; b += (end-start)/100){
        dump_data(32, b, MH, 100000);
    }
    return 0;
}
