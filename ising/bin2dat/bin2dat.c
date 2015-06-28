#include"ising.h"

int main ( int argc, char *argv[] )
{
    if( argc < 2 ){
        printf( "usage: %s <input.bin> [<input.bin>]\n", argv[0] );
        return 0;
    }
    int k;
    for( k = 1; k < argc; k++ ){
        FILE *fin;
        if( !( fin = fopen( argv[k], "rb") ) ){
            printf( "Error opening file: %s\n", argv[k] );
            break;
        }
        header hdr = get_header(fin);
        printf( "\nHeader:\n#\t%d\t%f\t%s\n\n", hdr.l, hdr.b, hdr.algorithm);
        printf( "Columns:  %d\n", hdr.cols );
        printf( "Rows:     %d\n\n", hdr.size );
        fseek(fin, 0L, SEEK_SET);

        char output[50];
        sprintf( output, "%d_%f_%s_%d.dat", hdr.l, hdr.b, hdr.algorithm, hdr.size );
        FILE *fout = fopen( output, "w" );
        fprintf( fout, "#\t%d\t%f\t%s\n", hdr.l, hdr.b, hdr.algorithm );

        int i,j;
        raw *content = (raw*)malloc( hdr.cols * sizeof(raw) );
        for( j = 0; j < hdr.cols; j++ )
            content[j] = load_data( fin, j, 0 );
        fclose(fin);

        for( i = 0; i < hdr.size; i++ ){
            for( j = 0; j < hdr.cols - 1; j++ ){
                fprintf( fout, "%e\t", content[j].data[i] );
            }
            fprintf( fout, "%e\n", content[hdr.cols-1].data[i] );
        }
        printf( "Written to:\t%s\n\n", output );
        fclose(fout);

        for( j = 0; j < hdr.cols; j++ )
            raw_close(&content[j]);
        free(content);
    }
    return 0;
}
