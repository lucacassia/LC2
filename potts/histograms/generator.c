#include"potts.h"

int main()
{
    double b;
    for(b = 0.8; b <= 1.0; b += 0.033 )
        dump_data(8, b, SW, 1000000);

    return 0;
}
