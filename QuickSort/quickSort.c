#include <stdio.h>
#include <stdlib.h>
 
// Aluno: Túlio Ferreira Franco Carvalho
// RA: 156743
// AED2 - Alvaro
 
void QuickSort(int* A, int p, int r, int elemento) {
    int q;
 
    if( p < r ){
        q = Particiona(A, p, r, elemento);
 
        if( A[q-1] > A[q] && A[q+1] < A[q] ){
            exit;
        }
 
        if( q > elemento ){
            QuickSort(A, p, q-1, elemento);
        }
        if ( q < elemento ){
            QuickSort(A, q+1, r, elemento);
        }
    }
}
 
int Particiona(int* A, int p, int r) {
    int i, j, x, aux1, aux2;
    i = p - 1;
    x = A[r];
    for( j = p; j <= r-1; j++ ) {
        if( A[j] <= x ){
            i++;
            aux1 = A[i];
            A[i] = A[j];
            A[j] = aux1;
        }
    }
    aux2 = A[i+1];
    A[i+1] = A[r];
    A[r] = aux2;
return (i+1);
}
 
 
 
int main(){
 
    int N, elemento;
    int* vector;
 
    // elemento
    scanf("%d", &elemento);
 
    // Quantidade de elementos no vetor;
    scanf("%d", &N);
 
    // Separa a memória para o trabalho;
    vector = malloc(N * sizeof(int));
 
    // Ler todos os valores e colocar no ponteiro;
    for(int i = 0; i < N; i++){
        scanf("%d", &vector[i]);
    }
 
 
    QuickSort(vector, 0, N-1, elemento-1);
 
 
 
    printf("%do menor elemento eh o ",elemento);
    elemento = elemento-1;
    printf("%d", vector[elemento]);
    printf("\n");
    for(int i = 0; i < N; i++){
        printf("%d ", vector[i]);
    }
 
    free(vector);
return 0;
}