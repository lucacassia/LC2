#include"ising.h"

int main(){
    void (*algorithm)() = MH;
    dump_data(32, 0.3, algorithm, 500);
    dump_data(32, 0.4, algorithm, 500);
    dump_data(32, get_beta_critical(), algorithm, 1000);

    algorithm = SW;
    dump_data(32, 0.3, algorithm, 500);
    dump_data(32, 0.4, algorithm, 500);
    dump_data(32, get_beta_critical(), algorithm, 1000);
    return 0;
}
