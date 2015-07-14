#include"potts.h"

int main()
{
    double b;
    for(b = 0.7; b <= 1.35; b += 0.05){
        dump_data(8, b, SW, 100000 );
    }
    return 0;
}
