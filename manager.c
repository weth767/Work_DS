#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "tree.h"

int main(int argc, char *argv[]){
    /*variáveis para os arquivos de entrada e saída*/
    char path_input_file[100];
    char path_output_file[100];
    /*seta as variáveis com vazias*/
    strcpy(path_input_file," ");
    strcpy(path_output_file," "); 
    /*verifica se os valores de entrada da execução da aplicação estão completos*/
    /*se estiver continua a execução*/
    if(argv[1] != NULL && argv[2] != NULL && argc == 3){
        /*se está tudo ok, salva os arquivos nas strings*/ 
        strcpy(path_input_file,argv[1]);
        strcpy(path_output_file,argv[2]);
        read* r = read_file(path_input_file);
        /*pega a quantidade de instruções a serem executas*/
        int amount = r[0].value;
        /*cria o nó raiz*/
        branch root = NULL;
        /*laço para executar as instruções */
        for(int i = 1; i <= amount; i++){
            /*verifica se é a função de incluir*/
            if(strcmp(r[i].command,"INCLUI") == 0){
                /*se for, chama a função de inserir*/
                root = insert_on_tree(root,r[i].value);
            }
            /*verifica se é a função de excluir*/
            else if(strcmp(r[i].command,"EXCLUI") == 0){
                /*se for, chama a função de excluir*/
                root = delete_value_on_tree(root,r[i].value);
            }
            /*verifica se é a função de imprimir*/
            else if(strcmp(r[i].command,"IMPRIME") == 0){
                /*se for, verifica a ordem de impressão*/
                /*1, preordem*/
                if(r[i].value == 1){
                    save_preorder(root,path_output_file);
                    show_tree_preorder(root);
                    printf("\n");
                }
                /*2, inordem*/
                else if(r[i].value == 2){
                    save_inorder(root,path_output_file);
                    show_tree_inorder(root);
                    printf("\n");
                }
                /*3, posordem*/
                else if(r[i].value == 3){
                    save_postorder(root,path_output_file);
                    show_tree_postorder(root);
                    printf("\n");
                }
            }
            /*verifica se a instrução é busca, se for*/
            else if(strcmp(r[i].command,"BUSCA") == 0){
                /*chama a função de busca de um valor*/
                if(verify_value_on_tree(root,r[i].value) != NULL){
                    printf("%i\n",r[i].value);
                }
                else{
                    printf("elemento %i não encontrado\n",r[i].value);
                }
            }
        }
        /*executa */
    }
    /*senão mostra erro*/
    else{
        printf("Formato de entrada da aplicação está incorreto, deve ser a aplicação e os arquivos de entrada e saída!\n");
    }
    return 0;
}