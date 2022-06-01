#include <stdio.h>
#include <stdlib.h>

#define TAM 5

//Assinatura de funções
int dentro_do_campo (int linha, int coluna);
int tem_bomba       (int linha, int coluna);
int localizacao     (int linha, int coluna);
int conta_adjacencia(int linha, int coluna);

void inserir(int linha, int coluna);
void inicializar();
void marcar(int linha, int coluna);
void cavar(int linha, int coluna);
void imprime();
void imprime_minas(); //apenas para testes

int sup_esq();
int sup_dir();
int inf_dir();
int inf_esq();
int esq(int linha);
int sup(int coluna);
int dir(int linha);
int inf(int coluna);
int mid(int linha, int coluna);

int  campo[TAM][TAM];
char campo_aux[TAM][TAM];

int main(){

    inicializar();

    inserir(0,0);
    cavar(1,1);
    

    imprime();
    imprime_minas();

    return 0;
}

//Usada para cavar e marcar
int dentro_do_campo(int linha, int coluna){
   int col_lim = ((coluna < 0) || (coluna >= TAM));
   int lin_lim = ((linha  < 0) || (linha  >= TAM));

   if(col_lim || lin_lim) return 0;

   return 1;
}

//Usada para a função cavar
int tem_bomba(int linha, int coluna){
    return campo[linha][coluna];
}

//Usada para a função cavar
int localizacao(int linha, int coluna){
    /* RETORNO
     - 1: Canto superior esquerdo [0]    [0]
     - 2: Canto superior direito  [0]    [TAM-1]
     - 3: Canto inferior direito  [TAM-1][TAM-1]
     - 4: Canto inferior esquerdo [TAM-1][0]
     - 5: Borda esquerda [n]    [0]
     - 6: Borda superior [0]    [n]
     - 7: Borda direita  [n]    [TAM-1]
     - 8: Borda inferior [TAM-1][n]
     - 9: Não está nas bordas
    */
    //Cantos
    if(linha == 0 && coluna == 0)     return 1;
    if(linha == 0 && coluna == TAM-1) return 2;
    if(linha == TAM-1 && coluna == TAM-1) return 3;
    if(linha == TAM-1 && coluna == 0)     return 4;

    //Bordas
    if(coluna == 0) return 5;
    if(linha  == 0) return 6;
    if(coluna == TAM-1) return 7;
    if(linha  == TAM-1) return 8;

    return 9;
}

int conta_adjacencia(int linha, int coluna){
    if(dentro_do_campo(linha, coluna)){
        int posicao = localizacao(linha, coluna);
        switch (posicao){
        case 1:
            return sup_esq();
            break;
        
        case 2:
            return sup_dir();
            break;
        
        case 3:
            return inf_dir();
            break;

        case 4:
            return inf_esq();
            break;

        case 5:
            return esq(linha);
            break;

        case 6:
            return sup(coluna);
            break;

        case 7:
            return dir(linha);
            break;

        case 8:
            return inf(coluna);
            break;
        
        default:
            return mid(linha, coluna); 
            break;
        }
    }
}

//Insere uma bomba na posição indicada
void inserir(int linha, int coluna){
    campo[linha][coluna] = 1;
}

void inicializar(){
    for(int i = 0; i < TAM; i++){
        for(int j = 0; j < TAM; j++){
            campo[i][j] = 0;
            campo_aux[i][j] = '-';
        }
    }

    //inserir(0,0);
}

void marcar(int linha, int coluna){
    if(dentro_do_campo(linha, coluna)){
        if(campo_aux[linha][coluna] == 'B') campo_aux[linha][coluna] = '-';
        else campo_aux[linha][coluna] = 'B';
    } 
}

void cavar(int linha, int coluna){
    if(dentro_do_campo(linha, coluna)){
        if(tem_bomba(linha, coluna)){
            printf("FIM DE JOGO! VOCÊ PERDEU!\n");
        } else{
            int qtd_adjacentes = conta_adjacencia(linha, coluna);
            if(qtd_adjacentes != 0){
                campo_aux[linha][coluna] = (char)(qtd_adjacentes)+'0';
                //campo_aux[linha][coluna] = '1';
            }
        }
    }
}

void imprime(){
    for(int i = 0; i < TAM; i++){
        for(int j = 0; j < TAM; j++){
            printf("[%c]", campo_aux[i][j]);
        }
        printf("\n");
    }
}

//Usado apenas para testes
void imprime_minas(){
    for(int i = 0; i < TAM; i++){
        for(int j = 0; j < TAM; j++){
            printf("[%d]", campo[i][j]);
        }
        printf("\n");
    }
}

int sup_esq(){
    return (campo[0][1] + campo[1][1] + campo[1][0]);
}

int sup_dir(){
    return (campo[0][TAM-2] + campo[1][TAM-2] + campo[1][TAM-1]);
}

int inf_dir(){
    return (campo[TAM-2][TAM-1] + campo[TAM-2][TAM-2] + campo[TAM-1][TAM-2]);
}

int inf_esq(){
    return (campo[TAM-1][1] + campo[TAM-2][1] + campo[TAM-2][0]);
}

int esq(int linha){
    int c = 0;

    c+= (campo[linha-1][0] + campo[linha+1][0]);

    for(int i = linha-1; i <= linha +1; i++) c += campo[i][1];

    return c;
}

int sup(int coluna){
    int c = 0;

    c += (campo[0][coluna-1] + campo[0][coluna+1]);

    for(int j = coluna-1; j <= coluna+1; j++) c += campo[1][coluna];

    return c;
}

int dir(int linha){
    int c = 0;

    c+= (campo[linha-1][TAM-1] + campo[linha+1][TAM-1]);

    for(int i = linha-1; i <= linha +1; i++) c += campo[i][TAM-2];

    return c;
}

int inf(int coluna){
    int c = 0;

    c += (campo[TAM-1][coluna-1] + campo[TAM-1][coluna+1]);

    for(int j = coluna-1; j <= coluna+1; j++) c += campo[TAM-2][coluna];

    return c;
}

int mid(int linha, int coluna){
    int c = 0;

    for(int j = coluna-1; j <= coluna+1; j++) c += campo[linha-1][j];

    c += (campo[linha][coluna-1] + campo[linha][coluna+1]);

    for(int j = coluna-1; j <= coluna+1; j++) c += campo[linha+1][j];
}