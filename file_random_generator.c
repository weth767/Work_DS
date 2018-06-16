#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[]){
    /*verifica se o formato de entrada do programa está correto*/
    if(argc == 2 && argv[1] != NULL){ 
        /*variável para guardar o caminho do arquivo a ser criado*/
        char path[100];
        strcpy(path,argv[1]);
        /*abre o arquivo*/
        FILE* file = fopen(path,"w");
        /*verifica se o arquivo foi aberto corretamente*/
        if(file != NULL){
            /*se foi aberto, seta a semente para os números pseudo-aleatórios*/
            srand(time(NULL));
            /*contador de instruções, que vai de 1 a 100*/
            int counter_instructions = rand() % 100 + 1;
            /*vetor que guarda as instruções, as instruções são 6 tipos, inclui, exclui, busca, e 
            os 3 tipos de imprime*/
            /*1 - inclui*/
            /*2 - exclui*/
            /*3 - busca*/
            /*4 - imprime préordem*/
            /*5 - imprime emordem*/
            /*6 - imprime pósordem*/
            int type_instructions[counter_instructions];
            /*primeira instrução como insere para não dar problemas no programa*/
            type_instructions[0] = 1;
            /*vetor que guarda os valores adicionados para serem usados para ser excluido*/
            int add_numbers[counter_instructions];
            /*variavel de controle do vetor*/
            int control = 0;
            /*variavel para guardar os valores*/
            int value;
            /*for para preencher o vetor de instruções*/
            for(int i = 1; i < counter_instructions; i++){
                type_instructions[i] = rand() % 6 + 1;
            }
            /*agora só escrever no arquivo, se for funções de 1 a 3, deve ser gerado um número
            aleatório de 1 a 1000 para ser escrito junto com a função*/
            for(int i = 0; i < counter_instructions; i++){
                /*switch para verificar as instruções*/
                switch(type_instructions[i]){
                    /*caso 1, inclui valores*/
                    case 1:
                        /*recebe um valor aleatório de 1 a 1000*/
                        value = rand() % 1000 + 1;
                        /*guarda no vetor de valores adicionados*/
                        add_numbers[control] = value;
                        /*incrementa o controle do vetor*/
                        control++;
                        /*e salva no arquivo*/
                        fprintf(file,"INCLUI %i\n",value);
                    break;
                    /*caso 2, exclui valores*/
                    case 2:
                        /*salva no arquivo um valor a ser excluido dentro do vetor dos adicionados*/
                        fprintf(file,"EXCLUI %i\n",add_numbers[rand() % control]);
                    break;
                    /*caso 3, busca de valores*/
                    case 3:
                        /*teste rápido para ver se vai pegar um dos valores do vetor ou um valor aleatorio*/
                        if((rand() % 2) == 1){
                            /*se for rand igual 1, busca um dos valores do vetor*/
                            fprintf(file,"BUSCA %i\n",add_numbers[rand() % control]);
                        }
                        /*senão*/
                        else{
                            /*busca um valor aleatório*/
                            fprintf(file,"BUSCA %i\n",rand() % 1000 + 1);
                        }
                    break;
                    /*caso 4, imprime o percurso preordem*/
                    case 4:
                        fprintf(file,"IMPRIME PREORDEM\n");
                    break;
                    /*caso 5, imprime o percurso inordem*/
                    case 5:
                        fprintf(file,"IMPRIME INORDEM\n");
                    break;
                    /*caso 6, imprime o percurso posordem*/
                    case 6:
                        fprintf(file,"IMPRIME POSORDEM\n");
                    break;
                }
            }
            /*salva no arquivo o fim*/
            fprintf(file,"FIM");
            /*fecha o arquivo*/
            fclose(file);
        }   
    }
    /*senão*/
    else{
        /*formato de inicialização errado*/
        printf("Formato de inicialização do aplicativo errada!\n");
        printf("O aplicativo deve ser iniciado com o programa e o nome do arquivo a ser criado!\n");
        printf("Seguindo o exemplo: frg.exe saida.txt\n");
    }
}