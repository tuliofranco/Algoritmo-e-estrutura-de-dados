#include<stdio.h>
#include<stdlib.h>
 
// Túlio Ferreira Franco Carvalho

void insertion_sort(int *vector, int N, int recursao){
    int i, j, tmp, position;
 
    for(i = 1; i < N; i++){
        tmp = vector[i];
        printf("%d ", recursao);
        printf("%d ", vector[i]);
        recursao -= 1;
        for(j = i-1; j >= 0 && tmp < vector[j]; j--){
            vector[j+1] = vector[j];
            }
        printf("%d",j+1);
        printf("\n");
        vector[j+1] = tmp;
        }
 
    for(int i = 0; i < N; i++){
        printf("%d ",vector[i]);
    }
}

int main(){
 
    int N;
    scanf("%d",&N);
    int recursao = N - 1;
    int* vector;
 
    vector = malloc ( N * sizeof(int));
 
 
    for(int i = 0; i < N; i++){
        scanf("%d",&vector[i]);
    }
    insertion_sort(vector, N, recursao);
 
    free(vector);
return 0;
}