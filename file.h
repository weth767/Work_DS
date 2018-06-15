#ifndef FILE_H
#define FILE_H
/*estrutura para leitura do arquivo*/
typedef struct READ{
    int value;
    char command[25];
}read;
/*funções da biblioteca*/
/*função de ler o arquivo, recebe por parametro o caminho do arquivo*/
read* read_file(char path[]);
/*função para salvar os percursos no arquivo*/
void save_preorder(branch root,FILE* file);
void save_inorder(branch root,FILE* file);
void save_postorder(branch root,FILE* file);
#endif