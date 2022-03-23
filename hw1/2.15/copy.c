#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc,char *argv[]){
    FILE * fin;
    FILE * fout;
    int ch;
    char *f_read = argv[1];
    char *f_write = argv[2];

    fin = fopen(f_read,"rb");
    fout = fopen(f_write,"wb");
    ch = getc(fin);
    while(ch != EOF){
        putc(ch,fout);
        ch = getc(fin);
    }
    fclose(fin);
    fclose(fout);
    return 0;
}