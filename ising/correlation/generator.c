#include"ising.h"

int main(){
    double b;
    for(b = 0.42f; b < 0.43f; b += 0.01f/15)
        dump_data(128, b, SW, 100000);
    return 0;
}
