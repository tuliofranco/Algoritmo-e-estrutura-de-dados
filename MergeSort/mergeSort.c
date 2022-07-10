#include <stdio.h>
#include <stdlib.h>
 
// Aluno: Túlio Ferreira Franco Carvalho
// RA: 156743
// AED2 - Alvaro
// DATA: 11/05/2022
 
 
void merge(int* vector, int e, int m, int d) {
    int i, j, k;
    int n1 = m - e + 1;
    int n2 = d - m;
 
    // Cria dois arrays temporários, para os sub arrays, esquerda,E, e direita,D;
    int E[n1], D[n2];
 
    // Copia os dados para um array temporário L e R;
    for (i = 0; i < n1; i++)
        E[i] = vector[e + i];
    for (j = 0; j < n2; j++)
        D[j] = vector[m + 1 + j];
 
    // faz o merge das matrizes temporárias de volta em no ponteiro;
 
 
    // Index inicial do primeiro subarray;
    i = 0;
 
    // Index inicial do segundo subarray;
    j = 0;
 
    // Index inicial do subarray que vai fazer o merge;
    k = e;
 
 
    while (i < n1 && j < n2) {
        if (E[i] <= D[j]) {
            vector[k] = E[i];
            i++;
        }
        else {
            vector[k] = D[j];
            j++;
        }
        k++;
    }
 
    // Copia os elementos restantes do array L, se possuir algum;
    while (i < n1) {
        vector[k] = E[i];
        i++;
        k++;
    }
 
    // Copia os elementos restantes do array R, se possuir algum;
    while (j < n2) {
        vector[k] = D[j];
        j++;
        k++;
    }
}
 
//  E é para o index da esqueda e d para o index da direita do subarray do ponteiro arr que será ordenado;
void mergeSort(int* vector, int e, int d) {
    if (e < d) {
 
        int m = e + (d - e) / 2;
 
        // Ordena a primeira e segunda metade;
        mergeSort(vector, e, m);
        mergeSort(vector, m + 1, d);
 
        merge(vector, e, m, d);
    }
}
 
int main(){
 
    int N;
    scanf("%d", &N);
 
    int* vector;
 
    // Separa a memória para o trabalho;
    vector = malloc(N * sizeof(int));
 
    // Ler todos os valores e colocar no ponteiro;
    for(int i = 0; i < N; i++){
        scanf("%d", &vector[i]);
    }
 
    // Chama a função;
    mergeSort(vector, 0, N - 1);
 
    // Imprime os valores finais;
    for(int i = 0; i < N; i++) {
        printf("%d ", vector[i]);
    }
    free(vector);
return 0;
}