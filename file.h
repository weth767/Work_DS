#ifndef FILE_H
#define FILE_H
/*estrutura para leitura do arquivo*/
typedef struct READ{
    int value;
    char command[25];
}read;
/*funções da biblioteca*/
int read_file(char path[]);
#endif