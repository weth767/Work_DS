#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

int main(int argc, char *argv[]){
    char path_input_file[100];
    char path_output_file[100];
    strcpy(path_input_file," ");
    strcpy(path_output_file," "); 
    if(argv[1] != NULL && argv[2] != NULL && argc == 3){
        /*se está tudo ok, salva os arquivos nas strings*/ 
        strcpy(path_input_file,argv[1]);
        strcpy(path_output_file,argv[2]);
        read_file(path_input_file);
    }
    return 0;
}