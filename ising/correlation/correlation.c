#include "ising.h"

int get_bin_size(int ID)
{
    if(ID == 0) return 1000;
    if(ID == 1) return 50;
    return 0;
}

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
        header hdr = get_header(fin);
        printf( "\nReading: %s\n", argv[i]);
        printf( "\nHeader:\n#\t%d\t%f\t%s\n\n", hdr.l, hdr.b, hdr.algorithm);
        fseek(fin, 0L, SEEK_SET);

        double **binned_data = (double**)malloc( (hdr.l/2) * sizeof(double*) );
        int k; for(k = 0; k < hdr.l/2; k++){
            raw storage = load_data( fin, 3+k, 1000 );
            binned_data[k] = jackknife(storage.data, storage.size, get_bin_size(storage.id) );
            raw_close(&storage);
        }
        fclose(fin);

        char output[50];
        sprintf(output, "data/%d_%f_%s_%d.cor", hdr.l, hdr.b, hdr.algorithm, hdr.size );
        FILE *fout = fopen(output,"w");

        int t;
        int n_bins = hdr.size / get_bin_size(hdr.id);

        fprintf(fout, "#\t%d\t%f\t%s\t%d\n", hdr.l, hdr.b, hdr.algorithm, n_bins );

        for(k = 0; k < hdr.l/2; k++){
            double sum = 0.0f;
            fprintf(fout, "%d\t", k);
            for(t = 0; t < n_bins; t++){
                sum += binned_data[k][t];
                fprintf(fout, "%e\t", binned_data[k][t]);
            }
            fprintf(fout, "%e\n", sum/n_bins);
            free(binned_data[k]);
        }
        fclose(fout);
        printf("Written to: %s\tbeta = %f\n", output, hdr.b);
    }
    return 0;
}

