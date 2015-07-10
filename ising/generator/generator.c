#include"ising.h"

int main(){
    dump_data(32, get_beta_critical(), MH, 1000);
    dump_data(32, get_beta_critical(), SW, 1000);
    return 0;
}
