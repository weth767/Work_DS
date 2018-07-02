#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "tree.h"
/*função para contar as linhas de instrução do arquivo*/
/*como sempre tem uma instrução fim, a contagem iniciará em 0*/
int count_lines(FILE* file){
    /*variável que contará o número de linhas*/
    int count = 0;
    /*variáveis char para leitura e teste*/
    char end = '\n',read_letter;
    /*um laço de repetição que vai até o fim do arquivo para ler todas as linhas*/
    while(!(feof(file))){
        /*le cada caractere*/
        read_letter = fgetc(file);
        /*se for o final da linha, conta mais um*/
        if(read_letter == end){
            /*aumenta o contador*/
            count++;
        }
    }
    /*no final retorna a quantidade de linhas*/
    return (count); 
}
/*função para leitura do arquivo texto*/
read* read_file(char path[]){
    /*coloca o ponteiro para apontar para o arquivo aberto*/
    FILE* file = fopen(path,"r");
    /*variáveis necessárias para a leitura do arquivo*/
    char helper[25];
    int control = 1;
    int size = count_lines(file);
    char order[25];
    /*cria um vetor da estruturas*/
    read * r = (read*)malloc((size + 1) * sizeof(read));
    /*coloca o ponteiro de arquivo de volta no inicio do arquivo*/ 
    fseek(file,0,0);
    /*verifica a não nulidade do ponteiro*/
    if(file != NULL){
        /*senão estiver null, continua a leitura*/
        /*laço de repetição que vai executar até o final do arquivo*/
        while(!(feof(file))){
            /*leitura da instrução*/
            fscanf(file,"%[^ ]s",r[control].command);
            /*verifica qual a instrução lida e caso necessário pega o valor*/
            /*verifica se é a instrução inclui*/
            if(strcmp(r[control].command,"INCLUI") == 0){
                /*se for, pula o próximo caractere, o espaço*/
                getc(file);
                /*lê o valor a ser incluido*/
                fscanf(file,"%i",&r[control].value);
            }
            /*verifica se a instrução é exclui*/
            else if(strcmp(r[control].command,"EXCLUI") == 0){
                /*se for, pula o próximo caractere, o espaço*/
                getc(file);
                /*e lê o valor a ser excluido*/
                fscanf(file,"%i",&r[control].value);
            }
            /*verifica se a instrução é busca*/
            else if(strcmp(r[control].command,"BUSCA") == 0){
                /*pula o caractere espaço*/
                getc(file);
                /*lẽ o valor a ser buscado*/
                fscanf(file,"%i",&r[control].value);
            }
            /*verifica se a instrução é imprime*/
            else if(strcmp(r[control].command,"IMPRIME") == 0){
                /*pula o espaço*/
                getc(file);
                /*lê a forma de ser impresso os valores da árvore*/
                fscanf(file,"%s",order);
                /*verifica a ordem de impressão dos dados da árvore*/
                /*se for preordem*/
                if(strcmp(order,"PREORDEM") == 0){
                    /*valor 1*/
                    r[control].value = 1;
                }
                /*se for inordem*/
                else if(strcmp(order,"INORDEM") == 0){
                    /*valor 2*/
                    r[control].value = 2;
                }
                /*se for posordem*/
                else if(strcmp(order,"POSORDEM") == 0){
                    /*valor 3*/
                    r[control].value = 3;
                }
            }
            /*e no fim das verificações e lê até o final da linha*/
            fscanf(file,"%[^\n]s",helper);
            /*para depois pular para próxima*/
            getc(file);
            /*soma o controle para controlar o vetor*/
            control++;   
        }
    }
    /*no fim a posição 0 do vetor de instruções será a quantidade de instruções*/
    strcpy(r[0].command,"AMOUNT");
    r[0].value = size;
    /*fecha o arquivo*/
    fclose(file);
    /*e retorna o ponteiro*/
    return r;
}
/*função para salvar os valores da árvore em pre ordem*/
void save_preorder(branch node, FILE* file){
    /*verifica se o nó não é null e o ponteiro do arquivo também*/
    if(node != NULL && file != NULL){
        /*senão estiver, salva o percurso no arquivo*/
        fprintf(file,"(%i)",node->value);
        save_preorder(node->left,file);
        save_preorder(node->right,file);
    }
}
/*função para salvar os valores da árvore em ordem*/
void save_inorder(branch node, FILE* file){
     /*verifica se o nó não é null e o ponteiro do arquivo também*/
     if(node != NULL && file != NULL){
        /*senão estiver, salva o percurso no arquivo*/
        save_inorder(node->left,file);
        fprintf(file,"(%i)",node->value);
        save_inorder(node->right,file);
    }
}
/*função para salvar os valores da árvore em pos ordem*/
void save_postorder(branch node, FILE* file){
    /*verifica se o nó não é null e o ponteiro do arquivo também*/
    if(node != NULL && file != NULL){
        /*senão estiver, salva o percurso no arquivo*/
        save_postorder(node->left,file);
        save_postorder(node->right,file);
        fprintf(file,"(%i)",node->value);
    }
}