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
        int i, e, n_bins = 100;
        int *histogram = (int*)malloc(n_bins*sizeof(int));
        for(e = 0; e < n_bins; e++)
            histogram[e] = 0;
        for(i = 0; i < storage.size; i++)
            for(e = 0; e < n_bins; e++)
                if((storage.data[i]>-2.0+e*2.0f/n_bins)&&(storage.data[i]<=-2.0+(e+1)*2.0f/n_bins))
                    histogram[i]++;

        /* write to output */
        char output[50];
        sprintf(output, "data/%d_%s_%d.hist", storage.l, storage.algorithm, storage.size );
        FILE *fout = fopen(output,"w");
        for(e = 0; e < n_bins; e++)
            fprintf(fout, "%e\t%d\n", -2.0+(e+0.5f)*2.0f/n_bins, histogram[e] );
        fclose(fout);

        printf("Written to: %s\t\tβ -> %f\n", output, storage.b);
    }
    return 0;
}

