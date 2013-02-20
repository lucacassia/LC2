#include "ising.h"

int main(){
    int i;
    FILE *f = fopen("sigma.dat","w");
    init(); for(i = 0; i < 100 + memlen; i++) run();
    for(i = 0; i < 100; i++) fprintf(f,"%d\t%e\n",i,get_sigma(i));
    fclose(f);
    return 0;
}
