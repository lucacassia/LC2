#include"ising.h"

int main ( int argc, char *argv[] ){
    if( argc != 2 ){ printf( "usage: %s file.bin\n", argv[0] ); }
    else{
        FILE *fin = fopen( argv[1], "rb" );
        if( fin == 0 ){ printf( "Could not open file\n" ); }
        else{
            FILE *fout = fopen( "out.dat", "w" );
            header hdr = get_header(fin);
            printf("cols = %d\n",hdr.cols);
            fseek(fin, 0L, SEEK_SET);
            fprintf( fout, "#\t%d\t%f\t%s\n", hdr.l, hdr.b, hdr.algorithm );
            raw *content = (raw*)malloc( hdr.cols * sizeof(raw) );
            int i,j; for( j = 0; j < hdr.cols; j++ ){ content[j] = load_data( fin, j, 0 ); }
            for( i = 0; i < hdr.size; i++ ){
                for( j = 0; j < hdr.cols - 1; j++ ){
                    fprintf( fout, "%f\t", content[j].data[i] );
                }
                fprintf( fout, "%f\n", content[hdr.cols-1].data[i] );
            }
            fclose(fin);
            fclose(fout);
        }
    }
    return 0;
}
