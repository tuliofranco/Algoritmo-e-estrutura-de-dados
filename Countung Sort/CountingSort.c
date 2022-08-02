#include <string.h>
#include <stdio.h>
#include <ctype.h>
 
// Túlio Ferreira Franco Carvalho

typedef char word[21];
typedef word list[100000];
 
char toLower(char c){
    if('A'<=c && c<='Z'){
        c += 32;
    }
    return c;
}
 
int decode(char c){
    if(isalnum(c))c -=96;
    else c = 0;
    return (int)c;
}
 
void countingSort(list ml, list sl,int Tam, int col){
    int map[27];
    int aux;
 
    memset(map,0,sizeof(int) * 27);
 
    for(aux = 0; aux < Tam; aux++){
 
        map[decode(ml[aux][col])]++;
    }
    for(aux = 1; aux < 27; aux++){
        map[aux] += map[aux-1];
    }
 
 
    for(int i = 0; i < 27; i++){
        printf("%d ", map[i]);
    }
    printf("\n");
 
    for(aux = Tam-1; aux > -1; aux--){
        int n = strlen(sl[map[decode(ml[aux][col])]-1]) > strlen(ml[aux]) ? strlen(sl[map[decode(ml[aux][col])]-1]) : strlen(ml[aux]);
        strncpy(sl[map[decode(ml[aux][col])]-1],ml[aux],n);
        map[decode(ml[aux][col])]--;
    }
}
 
void radixSort(list ml, int Tam,int maxCol){
    list sl;
    int col,aux;
    int _aux = 0;
 
    for(col = maxCol-1; col > -1; col--){
        if(!_aux){
 
            countingSort(ml,sl,Tam,col);
 
        }
        else{
 
            countingSort(sl,ml,Tam,col);
 
        }
        _aux = !_aux;
 
    }
 
    if(_aux){
        for(aux = 0; aux < Tam; aux++){
 
            strcpy(ml[aux],sl[aux]);
        }
    }
}
 
int main(){
    word palavra;
    list Listaprincipal,ListaAux;
    int N, P, M, aux;
    int t = 0;
    int Tam = 0;
 
    scanf("%d",&N);
 
    if(0<= N && N <= 100000){
        for(aux = 0; aux < N; aux++){
            int _aux = 0;
            memset(palavra,0,21 * sizeof(char));
            scanf("%s",palavra);
 
            for ( _aux = 0; _aux < strlen(palavra); _aux++){
                palavra[_aux] = toLower(palavra[_aux]);
            }
            strcpy(Listaprincipal[aux],palavra);
            t++;
            if (Tam < strlen(palavra)) Tam = strlen(palavra);
        }
 
        for(int i = 0; i <  N; i++){
            printf("%s",Listaprincipal[i]);
            if(1) printf(".");
            printf("\n");
        }
 
        printf("%d\n", Tam);
 
        radixSort(Listaprincipal,N,Tam);
 
        scanf("%d",&P);
        scanf("%d",&M);
    
        for(int i = P-1; i < P+M-1; i++){
            printf("%s",Listaprincipal[i]);
            if(0) printf(".");
            printf("\n");
        }
    }
    return 0;
}