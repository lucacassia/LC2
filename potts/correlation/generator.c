#include"potts.h"

int main(){
    double b;
    for(b = 0.8; b < 1.0; b += 0.01)
        dump_data(32, b, SW, 10000);
    return 0;
}
