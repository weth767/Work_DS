#ifndef TREE_H
#define TREE_H
/*ponteiro para a struct ramo*/
typedef struct BRANCH * branch;
/*estrutura ramo para montar a arvore*/
struct BRANCH{
    int value;
    branch right;
    branch left;
    int height;
};
/*funções da biblioteca*/
/*função de inserir um ramo na árvore, retorna a referência do nó raiz, recebe por parametro o nó raiz 
e o valor a ser inserido*/
branch insert_on_tree(branch root, int value);
/*função para mostrar os dados da árvore no percurso pré-ordem*/
void show_tree_preorder(branch root);
/*função para mostrar os dados da árvore no percurso em-ordem, recebe o nó*/
void show_tree_inorder(branch root);
/*função para mostrar os dados da árvore no percurso pós-ordem, recebe o nó*/
void show_tree_postorder(branch root);
/*função para calcular o grau de um nó da árvore, recebe o nó*/
int calculate_branch_degree(branch br);
/*função para calcular o nível de um nó, recebe por parametro o nó raiz e o nó a ser calculado*/
int calculate_level(branch root,branch br);
/*função para verificar se um valor está na árvore, se estiver retorna o nó, senão retorna NULL,
recebe por parametro o nó raiz e o valor*/
branch verify_value_on_tree(branch br, int value);
/*função de deletar um ramo na árvore, retorna a referência do nó raiz, recebe por parametro o nó raiz 
e o valor a ser removido*/
branch delete_value_on_tree(branch root, int value);
#endif