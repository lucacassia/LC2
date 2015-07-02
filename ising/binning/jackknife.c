#include "ising.h"

int main ( int argc, char *argv[] )
{
    if( argc < 2 ){
        printf( "usage: %s <input.bin> [<input.bin>]\n", argv[0] );
        return 0;
    }
    int i;
    for(i = 1; i < argc; i++){
        FILE *fin;

        if( !(fin = fopen(argv[i], "rb") ) ){
            printf("Error opening file: %s\n", argv[i]);
            break;
        }
        raw storage = load_data(fin,0,1000);
        fclose(fin);
        printf( "\nReading: %s\n", argv[i]);
        printf( "\nHeader:\n#\t%d\t%f\t%s\n\n", storage.l, storage.b, storage.algorithm);

        int step = 1;
        if( storage.id == 0 ){
            printf( "Insert <step> parameter: " );
            scanf( "%d", &step );
            if( step < 1){
                printf("Invalid value for <step> !\n");
                return 0;
            }
        }

        int t, k;
        double old_mean = 0.0f;
        for(t = 0; t < storage.size; t++)
            old_mean += storage.data[t];
        old_mean /= storage.size;
        double old_variance = 0.0f;
        for(t = 0; t < storage.size; t++)
            old_variance += (storage.data[t] - old_mean) * (storage.data[t] - old_mean);
        old_variance /= storage.size;

        printf("Binning.............."); fflush(stdout);

        char output[50];
        sprintf(output, "data/%d_%f_%s_%d.var", storage.l, storage.b, storage.algorithm, storage.size );
        FILE *fout = fopen(output,"w");
        fprintf(fout , "#\t%d\t%f\t%s\t%d\n", storage.l, storage.b, storage.algorithm, storage.size );

        double *binned_data;
        for(k = 1; k < 100 * step; k += step){
            binned_data = jackknife(storage.data, storage.size, k);
            double mean = 0.0f;
            for(t = 0; t < storage.size/k; t++)
                mean += binned_data[t];
            mean /= (storage.size/k);
            double variance = 0.0f;
            for(t = 0; t < storage.size/k; t++)
                variance += (binned_data[t] - mean) * (binned_data[t] - mean);
            variance *= (storage.size/k-1)/(storage.size/k-1);
            fprintf( fout, "%d\t%e\n", k, variance / old_variance );
            free(binned_data);
        }
        printf( " DONE!\n" );
        printf( "Written to: %s\n", output );
        fclose(fout);
        raw_close(&storage);
    }
    return 0;
}

