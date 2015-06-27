#include"ising.h"

int main(){

    void (*algorithm)() = MH;
    dump_data(32, 0.35, algorithm, 1000000);
    dump_data(32, 0.40, algorithm, 1000000);
    dump_data(32, 0.43, algorithm, 1000000);
    dump_data(32, BETA_CRITICAL, algorithm, 1000000);
    dump_data(32, 0.45, algorithm, 1000000);
    dump_data(32, 0.50, algorithm, 1000000);

    return 0;
}
