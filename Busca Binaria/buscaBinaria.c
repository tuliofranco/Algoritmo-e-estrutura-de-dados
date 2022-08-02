#include<stdio.h>
#include <stdlib.h>
 
 // Túlio Ferreira Franco Carvalho;
 
void recursive_binary_search(int *vector, int begin, int end, int item, int recursao){
    int i = (begin + end)/2;
 
    // If the beginning is greater than the end
    if (begin > end ) {
        return printf("%d nao foi encontrado",item);
    }
    // If the value in the vector is equal to the item;
    if (vector[i] == item) {
        return printf("%d",recursao);
    }
 
    // If the item value is greater than the vector value;
    if (item > vector[i]) {
        recursao +=+1;
        return recursive_binary_search( vector, i+1, end, item, recursao);
    } else {  // If the item value is less than the vector value;
        recursao +=1;
        return recursive_binary_search(vector, begin, i-1, item, recursao);
    }
 
}
 
int main (int argc, char* argv[]){
 
 
    int recursao = 0, VECTOR_SIZE;
    scanf("%i",&VECTOR_SIZE);
    VECTOR_SIZE = VECTOR_SIZE - 1;
    int* vector;
    vector = malloc (VECTOR_SIZE * sizeof(int));
 
    for(int a = 0; a <= VECTOR_SIZE; a++){ scanf("%i",&vector[a]);}
 
    int target;
    scanf("%i",&target);
 
    int begin = 0;
    recursive_binary_search( vector, 0, VECTOR_SIZE, target, recursao);
    
    free(vector);
 
return 0;
}