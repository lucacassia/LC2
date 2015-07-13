#include"potts.h"

int main()
{
    double b;
    for(b = 0.5; b < 1.6; b += 0.25){
        dump_data(32, b, MH, 500);
        dump_data(32, b, SW, 500);
        dump_data(64, b, MH, 500);
        dump_data(64, b, SW, 500);
    }
    return 0;
}
