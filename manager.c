#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "tree.h"
/*função principal*/
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
        /*remove o arquivo anterior para não sobreescrever*/
        remove(path_output_file);
        /*lê o arquivo e recebe os dados na struct*/
        read* r = read_file(path_input_file);
        /*pega a quantidade de instruções a serem executas*/
        int amount = r[0].value;
        /*cria o nó raiz*/
        branch root = NULL;
        /*abre o arquivo de saída*/
        FILE* out_file = fopen(path_output_file,"a+");;
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
                    /*printa o <*/
                    fprintf(out_file,"<");
                    /*chama a função para salvar na ordem 1*/
                    save_preorder(root,out_file);
                    /*fecha com > e um pulo de linha*/
                    fprintf(out_file,">\n");
                    /*mostra no console a árvore na ordem*/
                   //show_tree_preorder(root);
                    /*e um pula linha*/
                    //printf("\n");
                }
                /*2, inordem*/
                else if(r[i].value == 2){
                    /*printa o <*/
                    fprintf(out_file,"<");
                    /*chama a função para salvar na ordem 2*/
                    save_inorder(root,out_file);
                    /*fecha com > e um pulo de linha*/
                    fprintf(out_file,">\n");
                    /*mostra no console a árvore na ordem*/
                    //show_tree_inorder(root);
                    /*e um pula linha*/
                    //printf("\n");
                }
                /*3, posordem*/
                else if(r[i].value == 3){
                    /*printa o <*/
                    fprintf(out_file,"<");
                    /*chama a função para salvar na ordem 3*/
                    save_postorder(root,out_file);
                    /*fecha com > e um pulo de linha*/
                    fprintf(out_file,">\n");
                    /*mostra no console a árvore na ordem*/
                    //show_tree_postorder(root);
                    /*e um pula linha*/
                    //printf("\n");
                }
            }
            /*verifica se a instrução é busca, se for*/
            else if(strcmp(r[i].command,"BUSCA") == 0){
                /*chama a função de busca de um valor*/
                /*se o valor for diferente de NULL*/
                if(verify_value_on_tree(root,r[i].value) != NULL){
                    /*printa no arquivo*/
                    fprintf(out_file,"%i\n",r[i].value);
                    /*e no console*/
                    //printf("%i\n",r[i].value);
                }
                /*senão*/
                else{
                    /*mostra que o elemento não foi encontrado no console e no arquivo*/
                    fprintf(out_file,"Elemento %i não encontrado\n",r[i].value);
                    //printf("Elemento %i não encontrado\n",r[i].value);
                }
            }
        }
        draw_tree(root);
        printf("\n");
        /*fecha o arquivo de saída*/
        fclose(out_file);
        /*destroi a árvore*/
        root = destroy_tree(root);
    }
    /*senão mostra erro*/
    else{
        /*Erro para formato errado de entrada de arquivos*/
        printf("Formato de entrada da aplicação está incorreto, deve ser a aplicação e os arquivos de entrada e saída!\n");
    }
    return 0;
}