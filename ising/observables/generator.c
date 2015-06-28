#include"ising.h"

int main(){
    double b;
    for(b = 0.0f; b <= 1.0f; b += 1.0f/100){
        dump_data(32, b, SW, 100000);
    }
    return 0;
}
