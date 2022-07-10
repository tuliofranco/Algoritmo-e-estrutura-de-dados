#include<stdio.h>
#include<stdlib.h>
 
// Aluno: Túlio Ferreira Franco Carvalho
// RA: 156743
// AED2 - Alvaro

typedef struct compose{
    int voucher_value, total_books, total_voucher;
} compose;
 
 
 
 
void work(compose *book){
    int voucher_temp = 0, resto = 0;
 
    if(book->total_voucher >= book->voucher_value){
        voucher_temp = book->total_voucher/book->voucher_value;
        resto = book->total_voucher%book->voucher_value;
 
        book->total_books = book->total_books + voucher_temp;
        book->total_voucher = voucher_temp + resto;
        return work(book);
    }
 
    printf("%d",book->total_books);
    printf("\n");
}
 
 
 
 
 
int main(){
 
    int N, i = 0;
    scanf("%d",&N);
 
    int money, price, voucher_value, pre_book = 0;
 
    while(i!=N){
        scanf("%d",&money);
        scanf("%d",&price);
        scanf("%d",&voucher_value);
 
 
        compose *book;
        book = malloc (sizeof(compose));
 
 
        book->voucher_value = voucher_value;
        book->total_books = money/price;
        book->total_voucher = book->total_books;
 
        work(book);
 
 
 
 
        free(book);
        i++;
 
    }
return 0;
 
}