#include <stdio.h>
#include <stdlib.h>
 
// Túlio Ferreira Franco Carvalho

 
void merge(int* vector, int e, int m, int d) {
    int i, j, k;
    int n1 = m - e + 1;
    int n2 = d - m;

    int E[n1], D[n2];

    for (i = 0; i < n1; i++)
        E[i] = vector[e + i];
    for (j = 0; j < n2; j++)
        D[j] = vector[m + 1 + j];
 
    i = 0;
    j = 0;
 
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
 
    while (i < n1) {
        vector[k] = E[i];
        i++;
        k++;
    }
 
    while (j < n2) {
        vector[k] = D[j];
        j++;
        k++;
    }
}
 
void mergeSort(int* vector, int e, int d) {
    if (e < d) {
 
        int m = e + (d - e) / 2;

        mergeSort(vector, e, m);
        mergeSort(vector, m + 1, d);
 
        merge(vector, e, m, d);
    }
}
 
int main(){
 
    int N;
    scanf("%d", &N);
 
    int* vector;

    vector = malloc(N * sizeof(int));
 
    for(int i = 0; i < N; i++){
        scanf("%d", &vector[i]);
    }
 
    mergeSort(vector, 0, N - 1);
 
    for(int i = 0; i < N; i++) {
        printf("%d ", vector[i]);
    }
    free(vector);
return 0;
}