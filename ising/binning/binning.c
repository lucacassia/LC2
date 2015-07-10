#include "ising.h"

int main ( int argc, char *argv[] )
{
    if( argc < 2 ){
        printf( "usage: %s <input.bin> [<input.bin>]\n", argv[0] );
        return 0;
    }
    int i;
    for(i = 1; i < argc; i++){

        /*read from input */
        FILE *fin;
        if( !(fin = fopen(argv[i], "rb") ) ){
            printf("Error opening file: %s\n", argv[i]);
            break;
        }
        raw storage = load_data(fin,0,1000);
        fclose(fin);
        printf( "\nReading: %s\n", argv[i]);

        /* reading k_max step */
        int step = 1;
        if( storage.id == 0 ){
            printf( "Insert <step> parameter: " );
            scanf( "%d", &step );
            if( step < 1){
                printf("Invalid value for <step> !\n");
                return 0;
            }
        }

        /* global mean and variance */
        int t, k;
        double old_mean = 0.0f;
        for(t = 0; t < storage.size; t++)
            old_mean += storage.data[t];
        old_mean /= storage.size;
        double old_variance = 0.0f;
        for(t = 0; t < storage.size; t++)
            old_variance += (storage.data[t] - old_mean) * (storage.data[t] - old_mean);
        old_variance /= storage.size;

        /* open output file and write header */
        char output[50];
        sprintf(output, "data/%d_%f_%s_%d.var", storage.l, storage.b, storage.algorithm, storage.size );
        FILE *fout = fopen(output,"w");
        fprintf(fout , "#\t%d\t%f\t%s\t%d\n", storage.l, storage.b, storage.algorithm, storage.size );

        /* binnin analysis */
        double *binned_data;
        for(k = 1; k < 100 * step; k += step){
            binned_data = bin_data(storage.data, storage.size, k);
            double mean = 0.0f;
            for(t = 0; t < storage.size/k; t++)
                mean += binned_data[t];
            mean /= (storage.size/k);
            double variance = 0.0f;
            for(t = 0; t < storage.size/k; t++)
                variance += (binned_data[t] - mean) * (binned_data[t] - mean);
            variance /= (storage.size/k);
            fprintf( fout, "%d\t%e\n", k, k * variance / old_variance );
            free(binned_data);
        }

        /* close and clear memory */
        fclose(fout);
        raw_close(&storage);
        printf( "Written to: %s\n", output );
    }
    return 0;
}

