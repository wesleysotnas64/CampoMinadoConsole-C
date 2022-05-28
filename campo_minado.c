#include <stdio.h>
#include <stdlib.h>

#define TAM 8

//Assinatura de funções
int dentro_do_campo(int linha, int coluna);
int tem_bomba(int linha, int coluna);

int campo[TAM][TAM];

int main(){
    return 0;
}

int dentro_do_campo(int linha, int coluna){
   int col_lim = ((coluna < 0) || (coluna >= TAM));
   int lin_lim = ((linha  < 0) || (linha  >= TAM));

   if(col_lim || lin_lim) return 1;

   return 0;
}

int tem_bomba(int linha, int coluna){
    return campo[linha][coluna];
}

