#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#define space 5

/*função que retorna o maior valor entre dois inteiros passados por parametro*/
int bigger(int a, int b){
    /*retorna o maior entre a e b*/
    return (a > b)? a : b;
}
/*função para retornar a altura do ramo*/
int height(branch br){
    /*se o nó for nulo, não há altura*/
    if (br == NULL){
        /*então retorna 0*/
        return 0;
    }
    if(height(br->left) < height(br->right)){
        return height(br->right) + 1;
    }
    else{
        return height(br->left) + 1;
    }  
    /*senão retorna a altura*/
    return br->height;
}
/*função para girar o ramo para direita*/
branch right_rotate(branch br){
    /*guarda os endereços da direita e da esquerda do ramo*/
    branch a = br->left;
    branch b = a->right;
    /*realiza a troca dos valores*/
    a->right = br;
    br->left = b;
    /*atualiza as alturas*/
    br->height = bigger(height(br->left),height(br->right)) + 1;
    a->height = bigger(height(a->left),height(a->right)) + 1;
    /*retorna o ponteiro para a rotação realizada*/
    return a;
}
/*função para girar o ramo para esquerda*/
branch left_rotate(branch br){
    /*guarda os endereços da direita e da esquerda do ramo*/
    branch a = br->right;
    branch b = a->left;
    /*realiza a troca dos valores*/
    a->left = br;
    br->right = b;
    /*atualiza as alturas*/
    br->height  = bigger(height(br->left),height(br->right)) + 1;
    a->height = bigger(height(a->left),height(a->right)) + 1;
    /*retorna o ponteiro para a rotação realizada*/
    return a;
}
/*retorna o fator de balenceamento do ramo*/
int balance_factor(branch br){
    if (br == NULL)
        return 0;
    return height(br->left) - height(br->right);
}
/*função para inserir um ramo na árvore*/
branch insert_on_tree(branch node, int value){
    /*se não há ramos ligados a raiz*/
    if(node == NULL){
        /*aloca uma nova posição para o novo ramo*/
        branch br = (branch)malloc(sizeof(struct BRANCH));
        /*insere o valor*/
        br->value = value;
        /*seta os direita e esquerda como NULL, pois não há nada*/
        br->left = NULL;
        br->right = NULL;
        /*e coloca a altura como 1*/
        br->height = 0;
        /*retorna o ponteiro do nó*/
        return(br);
    }
    /*para um valor menor do que o o valor do ramo raiz, insere na esquerda*/
    else if(value < node->value){
        /*vai para esquerda*/
        node->left = insert_on_tree(node->left,value);
    }
    /*para um valor maior que o valor do ramo raiz, insere na direita*/
    else if(value > node->value){
        /*vai para direita*/
        node->right = insert_on_tree(node->right,value);
    }
    /*valores iguais não são usados em árvore*/
    else{
        /*retorna o nó*/
        return node;
    }
    /*atualiza a altura do nó raiz*/
    node->height = bigger(height(node->left),height(node->right)) + 1;
    /*guarda o balanceamento do nó*/
    int balance = balance_factor(node);
    /*agora vem a parte do balenceamento da árvore*/
    /*primeiro caso, dois fatores a direita*/
    if(balance > 1 && value < node->left->value){
        /*retoção para direita*/
        return right_rotate(node);
    }
    /*segundo caso, dois fatores a esqueda*/
    else if(balance < -1 && value > node->right->value){
        /*rotação para esquerda*/
        return left_rotate(node);
    }
    /*terceiro caso, um fator a esquerda outro a direita*/
    else if(balance_factor(node) > 1 && value > node->left->value){
        /*rotação para esquerda*/
        node->left = left_rotate(node->left);
        /*depois para direita*/
        return right_rotate(node);
    }
    /*quarto caso, um fator a direita e outra a esquerda*/
    else if(balance_factor(node) < -1 && value < node->right->value){
        /*rotação para direita*/
        node->right = right_rotate(node->right);
        /*depois para esquerda*/
        return left_rotate(node);
    }
    /*retorna a referência do nó*/
    return node;
}
/*mostra os valores na árvore no percurso preordem*/
/*indo de nó em nó, recebe por parametro o nó*/
void show_tree_preorder(branch node){
    /*verifica se o nó não está null*/
    if(node != NULL){
        /*senão tiver vai mostrando os valores em recursão, até que seja null*/
        printf("%i ",node->value);
        show_tree_preorder(node->left);
        show_tree_preorder(node->right); 
    }
}
/*mostra os valores na árvore no percurso inordem*/
/*indo de nó em nó, recebe por parametro o nó*/
void show_tree_inorder(branch node){
     /*verifica se o nó não está null*/
    if(node != NULL){
        /*senão tiver vai mostrando os valores em recursão, até que seja null*/
        show_tree_inorder(node->left);
        printf("%i ",node->value);
        show_tree_inorder(node->right); 
    }
}
/*mostra os valores na árvore no percurso posordem*/
/*indo de nó em nó, recebe por parametro o nó*/
void show_tree_postorder(branch node){
     /*verifica se o nó não está null*/
    if(node != NULL){
         /*senão tiver vai mostrando os valores em recursão, até que seja null*/
        show_tree_postorder(node->left);
        show_tree_postorder(node->right);
        printf("%i ",node->value); 
    }
}
/*função para calcular o grau do ramo*/
int calculate_branch_degree(branch br){
    /*primeiro caso, direita e esquerda como null, grau 0*/
    if(br->left == NULL & br->right == NULL){
        return 0;
    }
    /*segundo caso, esquerda como null e direita não, grau 1*/
    else if(br->left == NULL && br->right != NULL){
        return 1;
    }
    /*terceiro caso, direita como null e esquerda não, grau 1*/
    else if(br->right == NULL && br->left != NULL){
        return 1;
    } 
    /*quarto caso, nenhum como null, grau 2*/
    else{
        return 2;
    }
}
/*função para calcular o nível de determinado nó da árvore*/
int calculate_level(branch node, branch br){
    int level = 0;
    /*um auxiliar guarda o root*/
    branch helper = node;
    /*vai até o helper ser igual ao ramo passado por parametro*/
    while(helper != br){
        /*se o valor do ramo, for maior que o nó atual, vai para direita*/
        if(br->value > helper->value){
            helper = helper->right;
        }
        /*se o valor for menor, vai para esquerda*/
        else if(br->value < helper->value){
            helper = helper->left;
        }
        /*incrementa o nível*/
        level++;
    }
    /*retorna o nível*/
    return level;
}
/*função para verificar se um valor está na árvore*/
branch verify_value_on_tree(branch br, int value){
	/*se o a raiz já estiver em NULL, já retorna null direto*/
	if(br == NULL){
		return NULL;	
	}
	/*se o valor da raiz for maior que o valor passado por parâmetro*/
	else if(br->value > value){
		/*vai para a esquerda da árvore*/
		return verify_value_on_tree(br->left,value);
	}
	/*já se o valor for menor que o valor passado por parâmetro*/
	else if(br->value < value){
		/*vai para o lado direito da árvore*/
		return verify_value_on_tree(br->right,value);
	}
	/*e por fim se não entrou em nenhuma das condições retorna o próprio galho*/
	else{
		return br;
	}
}
/*função para retornar o menor valor na esquerda da árvore*/
branch left_value(branch br){
    branch current = br;
    /*fica no enquanto até que o auxiliar seja nulo*/
    while (current->left != NULL)
        current = current->left;
    /*no fim retorna o menor valor da extrema esquerda*/
    return current;
}
/*função para deletar valores da árvore e rebalance-la depois da exclusão*/
branch delete_value_on_tree(branch node, int value){
    /*primeiro caso, árvore vazia*/
    if(node == NULL){
        return node;
    }
    /*segundo caso, o valor a ser deletado é menor que o valor da raiz*/
    else if (value < node->value){
        node->left = delete_value_on_tree(node->left, value);
    }
    /*terceiro caso, o valor a ser deletado é maior que o valor da raiz*/
    else if(value > node->value){
        node->right = delete_value_on_tree(node->right, value);
    }
    /*valor a ser deletado encontrado*/
    else{
        /*valor a ser deletado*/
        if( (node->left == NULL) || (node->right == NULL)){
            branch temp = node->left ? node->left : node->right;
            /*se o nó não tiver filhos*/
            if (temp == NULL){
                /*guarda o valor*/
                temp = node;
                /*e anula o raiz*/
                node = NULL;
            }
            /*caso de um filho só do nó*/
            else{
                /*faz a troca dos valores*/
                *node = *temp;      
            } 
            /*limpa o espaço de memória*/
            free(temp);
        }
        /*entra nos casos de remoção de dois filhos*/
        else{
            /*pega o valor mais a esquerda, e o primeiro a direita dele*/
            branch temp = left_value(node->right);
            /*troca esse valor com o temporario*/
            node->value = temp->value;
            /*deleta o valor que foi trocado*/
            node->right = delete_value_on_tree(node->right, temp->value);
        }
    }
    /*verifica se essa remoção já deixou a árvore vazia, se sim*/
    if(node == NULL){
        /*retorna o ponteiro e sai da função*/
        return node;
    }
    /*guarda o fator de balanceamento do nó para utiliza-lo*/
    int balance = balance_factor(node);
    /*agora atualiza a altura*/
    node->height = 1 + bigger(height(node->left),height(node->right));
    /*agora vem a parte do balenceamento da árvore*/
    /*primeiro caso, dois fatores a direita*/
    if(balance > 1 && balance_factor(node->left) >= 0){
        return right_rotate(node);
    }
    /*segundo caso, dois fatores a esqueda*/
    else if(balance < -1 && balance_factor(node->right) <= 0){
        return left_rotate(node);
    }
    /*terceiro caso, um fator a esquerda outro a direita*/
    else if(balance_factor(node) > 1 && value > node->left->value){
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }
    /*quarto caso, um fator a direita e outra a esquerda*/
    else if(balance_factor(node) < -1 && value < node->right->value){
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }
    /*retorna o ponteiro da raiz*/
    return node;
}
/*função para destruir a árvore*/
/*recebe por parametro o nó raiz*/
branch destroy_tree(branch root){
    /*enquanto o nó raiz diferente de NULL*/
    /*executa o laço*/
    while(root != NULL){
        /*vai deletando os valores da árvore um a um e trocando as raizes*/
        root = delete_value_on_tree(root,root->value);
    }
    /*quando sair do laço e a raiz for igual a null*/
    /*da um free no ponteiro por garantia*/
    free(root);
    /*coloca o ponteiro para null*/
    root = NULL;
    /*e retorna ele*/
    return root;
}
void draw_horizontal_tree(branch node,int depth, char *path, int right){
    // stopping condition
    if (node == NULL){
        return;
    }
    // increase spacing
    depth++;
    // start with direita no
    draw_horizontal_tree(node->right, depth, path, 1);
    // set | draw map
    path[depth-2] = 0;
    if(right){
        path[depth-2] = 1;
    }
    if(node->left){
        path[depth-1] = 1;
    }
    // print root after spacing
    printf("\n");
    for(int i=0; i<depth-1; i++){
        if(i == depth-2){
            printf("╬");
        }
        else if(path[i]){
            printf("║");
        }
        else{
            printf(" ");
        }
        for(int j=1; j<space; j++){
            if(i < depth-2){
                printf(" ");
            }
            else{
                printf("═");
            }
        }
    }
    printf("%d\n", node->value);
    // vertical espacors below
    for(int i=0; i<depth; i++){
        if(path[i]){
            printf("║");
        }
        else{
            printf(" ");
        }
        for(int j=1; j<space; j++){
            printf(" ");
        }
    }
    // go to esquerda no
    draw_horizontal_tree(node->left,depth, path, 0);
}
//primary fuction
void draw_tree(branch node){
    // should check if we don't exceed this somehow..
    char path[255] = {};
    //initial depth is 0
    draw_horizontal_tree(node, 0, path, 0);
}