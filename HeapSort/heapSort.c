#include <stdio.h>
#include <stdlib.h>
 
// Aluno: Túlio Ferreira Franco Carvalho
// RA: 156743
// AED2 - Alvaro
 
void SWAP_STRING(char *vet[], int a, int b){    //Função que troca de posição duas strings no vetor
    char aux;
    int i=0;
    for(i=0; i<20; i++){
    aux = vet[a][i];
    vet[a][i] = vet[b][i];
    vet[b][i] = aux;
    }
}
 
void MAX_HEAPIFY(char *A[], int n, int i){      //Função que encontra a string de ordem maior entre a raiz e seus filhos
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int max = i;
    int j=0;
    int aux=0;
    do{
    if(l<n && A[max][j] < A[l][j] && A[max][j]>=97 && A[max][j]<=122 && A[l][j]>=97 && A[l][j]<=122){
        max = l;
        aux = 1;
        }
        j++;
        }while(aux!=1 && j>20 && (A[max][j]!=0 || A[l][j]!=0));
    j=0;
    aux=0;
    do{
        if(l<n && A[max][j] < A[l][j] && A[max][j]>=97 && A[max][j]<=122 && A[l][j]>=97 && A[l][j]<=122){
            max = r;
            aux = 1;
        }
        j++;
        }while(aux!=1 && j>20 && (A[max][j]!=0 || A[l][j]!=0));
 
    if (max != i) {
        SWAP_STRING(A, i, max);
        MAX_HEAPIFY(A, n, max);
    }
}
 
void BUILD_MAX_HEAP(char *A[], int n){          //Função que coloca na raiz topo a string de maior ordem
    int i;
    for (i = n - 1; i >= 0; i--) {
        MAX_HEAPIFY(A, i, 0);
    }
}
 
void EXTRACT_MAX_HEAP(char *A[], int n){        //Função que extrai da arvore a string de maior ordem e coloca a string de maior ordem entre a raiz e seus filhos na raiz novamente
    int i;
    for (i = n - 1; i >= 0; i--) {
        SWAP_STRING(A, 0, i);
        MAX_HEAPIFY(A, i, 0);
    }
}
 
void HEAPSORT(char *A[], int n){                //Função que faz a ordenação heapsort do vetor de strings
    BUILD_MAX_HEAP(A, n);
    EXTRACT_MAX_HEAP(A, n);
}
 
int main(){
    int N_total, N_separadas, i=0,  vet_indices_separadas[999], indice_palavra_fora_da_regra=9999, j=0;
    char *vet_string_total[999], *vet_string_separadas[999];
    scanf("%d", &N_total);                                                                  //Leitura do número de palavras totais
    for(i=0; i<N_total; i++){
        vet_string_total[i] = (char*) malloc(20*sizeof(char));                               //Alocação de memória da string no vetor
        scanf("%s", vet_string_total[i]);                                                   //Leitura de todas as palavras
        }
 
    for(int i = 0; i < N_total; i++ ){                                                               //Verificação de caracteres fora da regra na string
        j=0;
        do{
            if((vet_string_total[i][j]<97 || vet_string_total[i][j]>122) && vet_string_total[i][j]!=32 && indice_palavra_fora_da_regra==9999)
                indice_palavra_fora_da_regra=i;
                j++;
            } while(vet_string_total[i][j]!=0);
        }
 
    scanf("%d", &N_separadas);                                                              //Leitura do número de palavras selecionadas
    for(int i = 0; i < N_separadas; i++ ){
        scanf("%d", &vet_indices_separadas[i]);                                             //Leitura do índice das palavras selecionadas
        vet_string_separadas[i] = vet_string_total[vet_indices_separadas[i]];               //Transferência das strings selecionadas para um vetor exclusivo
        }
 
    if(indice_palavra_fora_da_regra!=9999){
        printf("a palavra %s eh invalida", vet_string_total[indice_palavra_fora_da_regra]); //Se há algum caractere fora da regra imprime a primeira string que contém
        } else {
            printf("build_heap:");
            for(int i=0; i < N_separadas; i++ ){                                                       //Impressão das strings selecionadas fora de ordem
                printf(" %s", vet_string_separadas[i]);
                }
            HEAPSORT(vet_string_separadas, N_separadas);                                        //Ordenação das strings
 
            printf("\npalavras:");
            for(int i=0; i < N_separadas; i++ ){                                                        //Impressão das strings selecionadas em ordem
                printf(" %s", vet_string_separadas[i]);
            }
        }
 
    for(int i = 0; i < N_total; i++ ){                                                               //Liberação de memória alocada
        free(vet_string_total[i]);
    }
    for(int i = 0; i < N_separadas; i++ ){                                                           //Liberação de memória alocada
        free(vet_string_separadas[i]);
    }
    return 0;
}