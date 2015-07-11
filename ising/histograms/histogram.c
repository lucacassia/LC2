#include"ising.h"

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

        raw storage;
        storage = load_data(fin,1,1000);     /* m */

        /* bin data */
        int i, m, n_bins = storage.l*storage.l/2+1;
        int *histogram = (int*)malloc(n_bins*sizeof(int));
        for(m = 0; m < n_bins; m++)
            histogram[m] = 0;
        for(i = 0; i < storage.size; i++)
            histogram[(int)(storage.data[i]*(n_bins-1))]++;

        /* write to output */
        char output[50];
        sprintf(output, "data/%d_%f_%s_%d.hist", storage.l, storage.b, storage.algorithm, storage.size );
        FILE *fout = fopen(output,"w");
        for(m = 0; m < n_bins; m++)
            fprintf(fout, "%e\t%d\n", m*1.0f/(n_bins-1), histogram[m] );
        fclose(fout);

        printf("Written to: %s\t\tβ -> %f\n", output, storage.b);
    }
    return 0;
}

