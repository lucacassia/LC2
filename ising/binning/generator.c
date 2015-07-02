#include"ising.h"

int main(){
/*
    dump_data(32, 0.35, MH, 1000000);
    dump_data(32, 0.40, MH, 1000000);
    dump_data(32, 0.43, MH, 1000000);
    dump_data(32, BETA_CRITICAL, MH, 1000000);
    dump_data(32, 0.45, MH, 1000000);
    dump_data(32, 0.50, MH, 1000000);

    dump_data(32, 0.35, SW, 1000000);
    dump_data(32, 0.40, SW, 1000000);
    dump_data(32, 0.43, SW, 1000000);
    dump_data(32, BETA_CRITICAL, SW, 1000000);
    dump_data(32, 0.45, SW, 1000000);
    dump_data(32, 0.50, SW, 1000000);
*/

    dump_data(8  , 0.435, SW, 1000000);
    dump_data(16 , 0.435, SW, 1000000);
    dump_data(32 , 0.435, SW, 1000000);
    dump_data(64 , 0.435, SW, 1000000);
    dump_data(128, 0.435, SW, 1000000);

    return 0;
}
