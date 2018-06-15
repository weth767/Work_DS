#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

/*enumeração para simular o tipo boolean*/
enum boolean {
    true = 1, false = 0
};
/*criando o tipo bool*/
typedef  enum boolean  bool;

/*função que retorna o maior valor entre dois inteiros passados por parametro*/
int bigger(int a, int b){
    return (a > b)? a : b;
}
/*função para retornar a altura do ramo*/
int height(branch br){
    if (br == NULL)
        return 0;
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
branch insert_on_tree(branch root, int value){
    /*se não há ramos ligados a raiz*/
    if(root == NULL){
        /*aloca uma nova posição para o novo ramo*/
        branch br = (branch)malloc(sizeof(struct BRANCH));
        /*insere o valor*/
        br->value = value;
        /*seta os direita e esquerda como NULL, pois não há nada*/
        br->left = NULL;
        br->right = NULL;
        /*e coloca a altura como 1*/
        br->height = 0;
        return(br);
    }
    /*para um valor menor do que o o valor do ramo raiz, insere na esquerda*/
    else if(value < root->value){
        root->left = insert_on_tree(root->left,value);
    }
    /*para um valor maior que o valor do ramo raiz, insere na direita*/
    else if(value > root->value){
        root->right = insert_on_tree(root->right,value);
    }
    /*valores iguais não são usados em árvore*/
    else{
        return root;
    }
    /*atualiza a altura do nó raiz*/
    root->height = bigger(height(root->left),height(root->right)) + 1;
    /*agora vem a parte do balenceamento da árvore*/
    /*primeiro caso, dois fatores a direita*/
    if(balance_factor(root) > 1 && value < root->left->value){
        return right_rotate(root);
    }
    /*segundo caso, dois fatores a esqueda*/
    else if(balance_factor(root) < -1 && value > root->right->value){
        return left_rotate(root);
    }
    /*terceiro caso, um fator a esquerda outro a direita*/
    else if(balance_factor(root) > 1 && value > root->left->value){
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }
    /*quarto caso, um fator a direita e outra a esquerda*/
    else if(balance_factor(root) < -1 && value < root->right->value){
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }
    return root;
}
/*mostra os valores na árvore no percurso preordem*/
void show_tree_preorder(branch root){
    if(root != NULL){
        printf("%i ",root->value);
        show_tree_preorder(root->left);
        show_tree_preorder(root->right); 
    }
}
/*mostra os valores na árvore no percurso inordem*/
void show_tree_inorder(branch root){
    if(root != NULL){
        show_tree_inorder(root->left);
        printf("%i ",root->value);
        show_tree_inorder(root->right); 
    }
}
/*mostra os valores na árvore no percurso posordem*/
void show_tree_postorder(branch root){
    if(root != NULL){
        show_tree_postorder(root->left);
        show_tree_postorder(root->right);
        printf("%i ",root->value); 
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
int calculate_level(branch root,branch br){
    int level = 0;
    /*um auxiliar guarda o root*/
    branch helper = root;
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
branch delete_value_on_tree(branch root, int value){
    /*primeiro caso, árvore vazia*/
    if (root == NULL){
        return root;
    }
    /*segundo caso, o valor a ser deletado é menor que o valor da raiz*/
    else if (value < root->value){
        root->left = delete_value_on_tree(root->left, value);
    }
    /*terceiro caso, o valor a ser deletado é maior que o valor da raiz*/
    else if(value > root->value){
        root->right = delete_value_on_tree(root->right, value);
    }
    /*valores iguais não são aceitos em uma árvore binária*/
    else{
        /*valor a ser deletado*/
        if( (root->left == NULL) || (root->right == NULL)){
            branch temp = root->left ? root->left : root->right;
            /*se o nó não tiver filhos*/
            if (temp == NULL){
                /*guarda o valor*/
                temp = root;
                /*e anula o raiz*/
                root = NULL;
            }
            /*caso de um filho só do nó*/
            else{
                /*limpa o valor*/
                *root = *temp;
                /*limpa o espaço de memória*/
                free(temp);
            } 
        }
        /*entra nos casos de remoção de dois filhos*/
        else{
            /*pega o valor mais a esquerda, e o primeiro a direita dele*/
            branch temp = left_value(root->right);
            /*troca esse valor com o temporario*/
            root->value = temp->value;
            /*deleta o valor que foi trocado*/
            root->right = delete_value_on_tree(root->right, temp->value);
        }
    }
    /*agora atualiza a altura*/
    root->height = 1 + bigger(height(root->left),height(root->right));
    /*agora vem a parte do balenceamento da árvore*/
    /*primeiro caso, dois fatores a direita*/
    if(balance_factor(root) > 1 && value < root->left->value){
        return right_rotate(root);
    }
    /*segundo caso, dois fatores a esqueda*/
    else if(balance_factor(root) < -1 && value > root->right->value){
        return left_rotate(root);
    }
    /*terceiro caso, um fator a esquerda outro a direita*/
    else if(balance_factor(root) > 1 && value > root->left->value){
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }
    /*quarto caso, um fator a direita e outra a esquerda*/
    else if(balance_factor(root) < -1 && value < root->right->value){
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }
    /*retorna o ponteiro da raiz*/
    return root;
}