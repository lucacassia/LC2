#include"ising.h"

int main(){
    dump_data(32, 0.43, MH, 100000);
    dump_data(32, 0.43, SW, 100000);

    FILE *f = fopen("data/32_0.430000_MH_100000.bin", "rb");
    raw content = load_data(f,3);
    fclose(f);
    f = fopen("test.dat","w");
    fprintf(f,"#\t%d\t%f\t%s\n",content.l,content.b,content.algorithm);
    int t;for(t = 0; t < content.size; t++) fprintf(f,"%f\n",content.data[t]);
    raw_close(&content);
    fclose(f);
    return 0;
}
