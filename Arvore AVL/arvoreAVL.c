#include<stdio.h>
#include<stdlib.h>
 
// Túlio Ferreira Franco Carvalho

typedef struct{
    int info, altura;
    struct AVL* esquerda;
    struct AVL* direita;
} AVL;

int Altura(AVL* node){
    int h_esq, h_dir;
 
    if (node == NULL)
        return 0;
    else{
        h_esq = Altura(node->esquerda);
        h_dir = Altura(node->direita);
        if (h_esq < h_dir){
            return h_dir+1;
        }
        else{
            return h_esq+1;
        }
    }
}

void Rotacao_direita(AVL** node_a){
    AVL* node_b;
 
    if((*node_a)->esquerda == NULL){
        return;
    }
    node_b = (*node_a)->esquerda;
    (*node_a)->esquerda = node_b->direita;
    node_b->direita = (*node_a);
    (*node_a)->altura = Altura(*node_a);
    node_b->altura = Altura(node_b);
    *node_a = node_b;
}

void Rotacao_esquerda(AVL** node_a){
    AVL* node_b;
 
    if((*node_a)->direita == NULL){
        return;
    }
    node_b = (*node_a)->direita;
    (*node_a)->direita = node_b->esquerda;
    node_b->esquerda = (*node_a);
    (*node_a)->altura = Altura(*node_a);
    node_b->altura = Altura(node_b);
    *node_a = node_b;
}
 
int altura(AVL* node_a){                                             //Função que retorna a informação altura da estrutura de um nó nao nulo
    if(node_a!=NULL){
        return node_a->altura;
    }
    else{
        return 0;
    }
}
 
void Balanceamento(AVL** node_a){                                    //Função que realiza rotações quando a diferença das alturas é maior que 1
    int diferenca_altura;
    AVL* temp;
 
    diferenca_altura = altura((*node_a)->esquerda) - altura((*node_a)->direita);
    if(diferenca_altura >= 2){
        temp = (*node_a)->esquerda;
        diferenca_altura = altura(temp->esquerda) - altura(temp->direita);
        if(diferenca_altura < 0){
            Rotacao_esquerda(&((*node_a)->esquerda));
        }
        Rotacao_direita(node_a);
    }
    else if (diferenca_altura <= -2){
        temp = (*node_a)->direita;
        diferenca_altura = altura(temp->esquerda) - altura(temp->direita);
        if (diferenca_altura > 0){
            Rotacao_direita(&((*node_a)->direita));
        }
        Rotacao_esquerda(node_a);
    }
}
 
void Insere(AVL** node_a, int item){                                 //Função recursiva que insere um novo nó e balanceia a AVL
    AVL* temp;
 
    if((*node_a) == NULL){                                           //caso o nó chave seja nulo cria novo nó
        temp = (AVL*)malloc(sizeof(AVL));
        temp->esquerda = NULL;
        temp->direita = NULL;
        temp->info = item;
        *node_a = temp;
    }
    else if(item < (*node_a)->info){                                 //caso a informação for menor que a informação do nó chave insere à esquerda
        Insere(&((*node_a)->esquerda), item);
    }
    else if(item > (*node_a)->info){                                 //caso a informação for maior que a informação do nó chave insere à direita
        Insere(&((*node_a)->direita), item);
    }
    (*node_a)->altura = Altura(*node_a);                             //calcula e insere a altura na estrutura do nó
    Balanceamento(node_a);                                           //balanceamento da AVL
}
 
AVL* Busca_menor(AVL* node_a){                                       //Função recursiva que busca o menor nó da subárvore
    if(node_a->esquerda == NULL){
        return node_a;
    }
    else{
        return Busca_menor(node_a->esquerda);
    }
}
 
AVL* Busca(AVL* node_a, int item){                                   //Função recursiva que busca um nó e retorna-o
    if (node_a == NULL)
        return 0;
    else{
        if (item == node_a->info){
            return node_a;
        }
        else if (Busca(node_a->esquerda, item)){
            return Busca(node_a->esquerda, item);
        }
        else{
            return Busca(node_a->direita, item);
        }
    }
}
 
void Exclui(AVL** node_a,int item){                                  //Função recursiva que exclui um nó e rebalanceia a AVL
    AVL* temp;
 
    if((*node_a) == NULL){                                           //caso a raiz seja nula apenas retorna
        return;
    }
    if(item < (*node_a)->info){                                      //caso o nó a ser excluido for menor que a raiz ele será excluido na subarvore esquerda
        Exclui(&((*node_a)->esquerda), item);
    }
    else if(item > (*node_a)->info){                                 //caso o nó a ser excluido for maior que a raiz ele será excluido na subarvore direita
        Exclui(&((*node_a)->direita), item);
    }
    else{                                                            //caso o nó for o mesmo da raiz então será deletado
        if((*node_a)->esquerda == NULL){
            temp = (*node_a)->direita;
            free(*node_a);
            *node_a = temp;
            return;
        }
        else if((*node_a)->direita == NULL){
            temp = (*node_a)->esquerda;
            free(*node_a);
            *node_a = temp;
            return;
        }
        temp = Busca_menor((*node_a)->direita);
        (*node_a)->info = temp->info;
        Exclui(&((*node_a)->direita), temp->info);
    }
    (*node_a)->altura = Altura(*node_a);
    Balanceamento(node_a);
}
 
void Libera(AVL* node_a){                                            //Função que libera o espaço de memória da AVL
    if(node_a!= NULL){
        Libera(node_a->esquerda);
        Libera(node_a->direita);
        free(node_a);                                                //libera a raiz
    }
    return NULL;
}
 
int main(){
    AVL* root = NULL;
    int vet[100000], vet_busca[1000], no_busca;
    int aux1, aux2, i=0, j=0, k=0, l=0;
 
    while(aux1!= -1){                                                //Leitura da sequência de números dos nós da AVL
        scanf("%d", &vet[i]);
        aux1 = vet[i];
        i++;
    }
 
    while(aux2!= -1){                                                //Leitura da sequência de números a serem pesquisados: caso contido excluir, caso não-contido inserir na AVL
        scanf("%d", &vet_busca[j]);
        aux2 = vet_busca[j];
        j++;
    }
 
    scanf("%d", &no_busca);                                          //Leitura do inteiro a ser pesquisado na AVL
 
    while(vet[k]!=-1){                                               //Inserção da sequência de números lidos nos nós da AVL
        Insere(&root, vet[k]);
        k++;
 
    }
    int alt = Altura(root)-1;                                        //Verificação da altura da AVL apartir do nó raiz
    int alt_esq = Altura(root->esquerda);                            //Verificação da altura da subárvore à esquerda apartir do nó raiz
    int alt_dir = Altura(root->direita);                             //Verificação da altura da subárvore à direita apartir do nó raiz
    printf("%d, %d, %d", alt, alt_esq, alt_dir);
    printf("\n");
    while(vet_busca[l]!=-1){                                         //Pesquisa da sequência de números: caso contido exclui, caso não-contido insere na AVL
        if(Busca(root, vet_busca[l])==NULL){
           Insere(&root, vet_busca[l]);
           l++;
        }
        else{
            Exclui(&root, vet_busca[l]);
            l++;
        }
    }
    if(Busca(root, no_busca)==NULL){                                 //Pesquisa do inteiro: caso contido imprime as alturas, caso não-contido imprime "Valor nao encontrado"
        printf("Valor nao encontrado");
    }
    else{
        alt = Altura(Busca(root, no_busca))-1;
        alt_esq = Altura(Busca(root, no_busca)->esquerda);
        alt_dir = Altura(Busca(root, no_busca)->direita);
        printf("%d, %d, %d", alt, alt_esq, alt_dir);
    }
    Libera(root);
}