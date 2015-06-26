#include"ising.h"

void dump_data(int lattice_size, double beta_value, void (*algorithm)(), int run_time)
{
    if( algorithm != MH && algorithm != SW ){ printf("\nInvalid Algorithm!\n"); }
    else{
        char filename[50];
        sprintf(filename, "data/%d_%f_%s_%d.dat", lattice_size, beta_value, get_algorithm_string(algorithm), run_time);
        FILE *f = fopen(filename, "w");
        printf("\nExecuting %s : L = %d : β = %f : time = %d\n\n", get_algorithm_string(algorithm), lattice_size, beta_value, run_time);
        init(lattice_size, beta_value);
        printf("Gathering Data..."); fflush(stdout);
        int t; for(t = 0; t < run_time; t++){
            algorithm();
            fprintf(f, "%d\t%d\t%f\t%s", t, lattice_size, beta_value, get_algorithm_string(algorithm));
            fprintf(f, "\t%f", get_energy() / (lattice_size * lattice_size));
            fprintf(f, "\t%f", get_magnetization() / (lattice_size * lattice_size));
            fprintf(f, "\t%f", (get_largest_cluster() * 1.0f) / (lattice_size * lattice_size));
            fprintf(f, "\n");
        }
        printf(" DONE!\n\n");
        fclose(f);
        clear();
    }
}

int main(){
    dump_data(32, get_beta_critical(), MH, 1000);
    return 0;
}
