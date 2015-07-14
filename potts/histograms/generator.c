#include"potts.h"

int main()
{
    double b;
    for(b = 0.75; b < 0.951; b += 0.02 )
        dump_data(8, b, SW, 1000000);

    return 0;
}
