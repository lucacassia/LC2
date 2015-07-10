#include"ising.h"

int main()
{
    double b;
    for(b = 0.39; b <= 0.49; b += 0.01){
        dump_data(32, b, SW, 100000 );
/*        dump_data(32, b, MH, 1000000 );*/
    }
    return 0;
}
