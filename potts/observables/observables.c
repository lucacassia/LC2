#include"potts.h"

int main ( int argc, char *argv[] )
{
    if( argc < 2 ){
        printf( "usage: %s <input.bin> [<input.bin>]\n", argv[0] );
        return 0;
    }
    int i;
    for(i = 1; i < argc; i++){

        /* read from input */
        FILE *fin;
        if( !(fin = fopen(argv[i], "rb") ) ){
            printf("Error opening file: %s\n", argv[i]);
            break;
        }

        /*** energy ***/
        raw storage = load_data(fin,0,1000);

        int t;
        int n_states = storage.hdr.q;
        int lattice_size = storage.hdr.l;
        double beta_value = storage.hdr.b;
        int bin_size = 50;
        double n_bins = storage.hdr.size / bin_size;
        double *binned_data, mean, error;

        /* open output and write header */
        char output[50];
        sprintf(output, "data/%d_%s.obs", lattice_size, storage.hdr.algorithm );
        FILE *fout = fopen(output,"a");
        fprintf(fout, "%e\t", beta_value );         /* header */

        /* mean */
        binned_data = jackknife(storage.data, storage.hdr.size, bin_size );
        mean = 0.0f;
        for(t = 0; t < n_bins; t++)
            mean += binned_data[t];
        mean /= n_bins;
        free(binned_data);
        fprintf(fout, "%e\t", mean );               /* energy */

        /* variance */
        for(t = 0; t < storage.hdr.size; t++)
            storage.data[t] = (storage.data[t]-mean)*(storage.data[t]-mean);

        binned_data = jackknife(storage.data, storage.hdr.size, bin_size );
        raw_close(&storage);

        mean = 0.0f;
        for(t = 0; t < n_bins; t++)
            mean += binned_data[t];
        mean /= n_bins;

        error = 0.0f;
        for(t = 0; t < n_bins; t++)
            error += (binned_data[t]-mean)*(binned_data[t]-mean);
        error *= (n_bins-1.0f)/n_bins;
        free(binned_data);

        mean *= beta_value * beta_value * lattice_size * lattice_size;
        error = beta_value * beta_value * lattice_size * lattice_size * sqrt(error);
        fprintf(fout, "%e\t%e\t", mean,  error );   /* heat capacity w error */

        /*** magnetization ***/
        storage = load_data(fin,1+n_states,1000);

        /* mean */
        binned_data = jackknife(storage.data, storage.hdr.size, bin_size );
        mean = 0.0f;
        for(t = 0; t < n_bins; t++)
            mean += binned_data[t];
        mean /= n_bins;
        free(binned_data);
        fprintf(fout, "%e\t", mean );               /* magnetization */

        /* variance */
        for(t = 0; t < storage.hdr.size; t++)
            storage.data[t] = (storage.data[t]-mean)*(storage.data[t]-mean);

        binned_data = jackknife(storage.data, storage.hdr.size, bin_size );
        raw_close(&storage);

        mean = 0.0f;
        for(t = 0; t < n_bins; t++)
            mean += binned_data[t];
        mean /= n_bins;

        error = 0.0f;
        for(t = 0; t < n_bins; t++)
            error += (binned_data[t]-mean)*(binned_data[t]-mean);
        error *= (n_bins-1.0f)/n_bins;
        free(binned_data);

        mean *= beta_value * lattice_size * lattice_size;
        error = beta_value * lattice_size * lattice_size * sqrt(error);

        fprintf(fout, "%e\t%e\n", mean,  error );   /* susceptibility w error */


        printf("Written to: %s\t\tβ -> %f\n", output, beta_value);
        fclose(fout);
    }
    return 0;
}

