#include "stdio.h"
#include "stdlib.h"
#include <math.h>
#include "ListaPecas.h"
#include "ListasJogadas.h"

#define PEAO    1
#define CAVALO  2
#define BISPO   3
#define TORRE   4
#define RAINHA  5
#define REI     6
#define MAX_NIVEL 4

typedef struct Posicao{
    int qtdBrancas;
    struct Peca *brancas;
    int qtdPretas;
    struct Peca *pretas;
    int jogVez;
    struct Peca *tab[8][8];
}Posicao;

void ResetCor(){
    printf("\033[0m");
}

void AjustaCor(int peca){
    switch(abs(peca)){
    case PEAO: printf("\033[0;36m");break;
    case CAVALO: printf("\033[1;33m");break;
    case BISPO: printf("\033[0;35m");break;
    case TORRE: printf("\033[0;32m");break;
    case RAINHA: printf("\033[0;34m");break;
    case REI: printf("\033[1;31m");break;
    }
}

void DesenhaTabuleiro(Posicao pos){
    int i,j;
    system("clear");

    printf("    +---+---+---+---+---+---+---+---+\n");
    for (i=7;i>=0;i--){
        printf("%d   |",i+1);
        for (j=0;j<8;j++){
            if (pos.tab[i][j]){ //se tem pe?a nessa casa
                AjustaCor(pos.tab[i][j]->codigo);
                if (pos.tab[i][j]->codigo>0)
                    printf(" %d",pos.tab[i][j]->codigo);
                else printf("%d",pos.tab[i][j]->codigo);
                ResetCor();
            }else printf("  ");//se n?o tem pe?a, deixa em vazio o printf
            printf(" |");
        }
        printf("\n    +---+---+---+---+---+---+---+---+\n");
    }
    printf("      1   2   3   4   5   6   7   8 \n");
}

void CalculaPeao(Posicao pos,int linha,int coluna,struct Jogada *lista){
    int peca = pos.tab[linha][coluna]->codigo;

    if (linha+peca>=0 && linha+peca<=7){//n?o est? na primeira nem na ?ltima linha
    if((linha==1 && peca==1) || (linha==6 && peca==-1)){
      if (pos.tab[linha+2*peca][coluna]==NULL){
        InsereJogada(lista,linha,coluna,linha+2*peca,coluna);
        }
    }
        if (pos.tab[linha+peca][coluna]==NULL){ //pode avancar
            InsereJogada(lista,linha,coluna,linha+peca,coluna);
        }
        if (coluna>0 && pos.tab[linha+peca][coluna-1]!=NULL && pos.tab[linha+peca][coluna-1]->codigo*peca<0){ //verificar captura na esquerda
            InsereJogada(lista,linha,coluna,linha+peca,coluna-1);
            pos.tab[linha+peca][coluna-1]->ataques++;
        }
        if (coluna<7 && pos.tab[linha+peca][coluna+1]!=NULL && pos.tab[linha+peca][coluna+1]->codigo*peca<0){
            InsereJogada(lista,linha,coluna,linha+peca,coluna+1);
            pos.tab[linha+peca][coluna+1]->ataques++;
        }
    }
}

void CalculaCavalo(Posicao pos, int linha, int coluna, struct Jogada *lista){
    int peca = pos.tab[linha][coluna]->codigo;

    if (linha<6){ //duas linhas acima
        if (coluna<7 && (pos.tab[linha+2][coluna+1]==NULL || pos.tab[linha+2][coluna+1]->codigo*peca<0)){ //direita
            InsereJogada(lista,linha,coluna,linha+2,coluna+1);
            if (pos.tab[linha+2][coluna+1]!=NULL)
                pos.tab[linha+2][coluna+1]->ataques++;
        }
        if (coluna>0 && (pos.tab[linha+2][coluna-1]==NULL || pos.tab[linha+2][coluna-1]->codigo*peca<0)){ //esquerda
            InsereJogada(lista,linha,coluna,linha+2,coluna-1);
            if (pos.tab[linha+2][coluna-1]!=NULL)
                pos.tab[linha+2][coluna-1]->ataques++;
        }
    }
    if (linha<7){//uma linha acima
        if (coluna<6 && (pos.tab[linha+1][coluna+2]==NULL || pos.tab[linha+1][coluna+2]->codigo*peca<0)){ //duas casas ? direita
            InsereJogada(lista,linha,coluna,linha+2,coluna-1);
            if (pos.tab[linha+1][coluna+2]!=NULL)
                pos.tab[linha+1][coluna+2]->ataques++;
        }
        if (coluna>1 && (pos.tab[linha+1][coluna-2]==NULL || pos.tab[linha+1][coluna-2]->codigo*peca<0)){ //duas casas ? esquerda
            InsereJogada(lista,linha,coluna,linha+1,coluna-2);
            if (pos.tab[linha+1][coluna-2]!=NULL)
                pos.tab[linha+1][coluna-2]->ataques++;
        }
    }
    if (linha>1){ //duas linhas abaixo
        if (coluna<7 && (pos.tab[linha-2][coluna+1]==NULL || pos.tab[linha-2][coluna+1]->codigo*peca<0)){ //direita
            InsereJogada(lista,linha,coluna,linha-2,coluna+1);
            if (pos.tab[linha-2][coluna+1]!=NULL)
                pos.tab[linha-2][coluna+1]->ataques++;
        }
        if (coluna>0 && (pos.tab[linha-2][coluna-1]==NULL || pos.tab[linha-2][coluna-1]->codigo*peca<0)){ //esquerda
            InsereJogada(lista,linha,coluna,linha-2,coluna-1);
            if (pos.tab[linha-2][coluna-1]!=NULL)
                pos.tab[linha-2][coluna-1]->ataques++;
        }
    }
    if (linha>0){//uma linha abaixo
        if (coluna<6 && (pos.tab[linha-1][coluna+2]==NULL || pos.tab[linha-1][coluna+2]->codigo*peca<0)){ //duas casas ? direita
            InsereJogada(lista,linha,coluna,linha-1,coluna+2);
            if (pos.tab[linha-1][coluna+2]!=NULL)
                pos.tab[linha-1][coluna+2]->ataques++;
        }
        if (coluna>1 && (pos.tab[linha-1][coluna-2]==NULL || pos.tab[linha-1][coluna-2]->codigo*peca<0)){ //duas casas ? esquerd
            InsereJogada(lista,linha,coluna,linha-1,coluna-2);
            if (pos.tab[linha-1][coluna-2]!=NULL)
                pos.tab[linha-1][coluna-2]->ataques++;
        }
    }
}

void CalculaBispo(Posicao pos, int linha, int coluna, struct Jogada *lista){
    int peca = pos.tab[linha][coluna]->codigo;

    int k=0;

    do{//diagonal superior direita
        k++;
        if (linha+k<8 && coluna+k<8 && (pos.tab[linha+k][coluna+k]==NULL||pos.tab[linha+k][coluna+k]->codigo*peca<0)){
            InsereJogada(lista,linha,coluna,linha+k,coluna+k);
            if (pos.tab[linha+k][coluna+k]!=NULL)
                pos.tab[linha+k][coluna+k]->ataques++;
        }
    }while (linha+k<8 && coluna+k<8 && pos.tab[linha+k][coluna+k]==NULL);

    k=0;
    do{//diagonal superior esquerda
        k++;
        if (linha+k<8 && coluna-k>=0 && (pos.tab[linha+k][coluna-k]==NULL||pos.tab[linha+k][coluna-k]->codigo*peca<0)){
            InsereJogada(lista,linha,coluna,linha+k,coluna-k);
            if (pos.tab[linha+k][coluna-k]!=NULL)
                pos.tab[linha+k][coluna-k]->ataques++;
        }
    }while (linha+k<8 && coluna-k>=0 && pos.tab[linha+k][coluna-k]==NULL);

    k=0;
    do{//diagonal inferior direita
        k++;
        if (linha-k>=0 && coluna+k<8 && (pos.tab[linha-k][coluna+k]==NULL||pos.tab[linha-k][coluna+k]->codigo*peca<0)){
            InsereJogada(lista,linha,coluna,linha-k,coluna+k);
            if (pos.tab[linha-k][coluna+k]!=NULL)
                pos.tab[linha-k][coluna+k]->ataques++;
        }
    }while (linha-k>=0 && coluna+k<8 && pos.tab[linha-k][coluna+k]==NULL);

    k=0;
    do{//diagonal inferior direita
        k++;
        if (linha-k>=0 && coluna-k>=0 && (pos.tab[linha-k][coluna-k]==NULL||pos.tab[linha-k][coluna-k]->codigo*peca<0)){
            InsereJogada(lista,linha,coluna,linha-k,coluna-k);
            if (pos.tab[linha-k][coluna-k]!=NULL)
                pos.tab[linha-k][coluna-k]->ataques++;
        }
    }while (linha-k>=0 && coluna+k>=0 && pos.tab[linha-k][coluna-k]==NULL);
}

void CalculaTorre(Posicao pos, int linha, int coluna, struct Jogada *lista){
    int peca=pos.tab[linha][coluna]->codigo;

    int k=0;

    do{//coluna acima
        k++;
        if (linha+k<8 && (pos.tab[linha+k][coluna]==NULL||pos.tab[linha+k][coluna]->codigo*peca<0)){
            InsereJogada(lista,linha,coluna,linha+k,coluna);
            if (pos.tab[linha+k][coluna]!=NULL)
                pos.tab[linha+k][coluna]->ataques++;
        }
    }while(linha+k<8 && pos.tab[linha+k][coluna]==NULL);

    k=0;
    do{//coluna abaixo
        k++;
        if (linha-k>=0 && (pos.tab[linha-k][coluna]==NULL||pos.tab[linha-k][coluna]->codigo*peca<0)){
            InsereJogada(lista,linha,coluna,linha-k,coluna);
            if (pos.tab[linha-k][coluna]!=NULL)
                pos.tab[linha-k][coluna]->ataques++;
        }
    }while(linha-k>=0 && pos.tab[linha-k][coluna]==NULL);

    k=0;
    do{//linha direita
        k++;
        if (coluna+k<8 && (pos.tab[linha][coluna+k]==NULL||pos.tab[linha][coluna+k]->codigo*peca<0)){
            InsereJogada(lista,linha,coluna,linha,coluna+k);
            if (pos.tab[linha][coluna+k]!=NULL)
                pos.tab[linha][coluna+k]->ataques++;
        }
    }while(coluna+k<8 && pos.tab[linha][coluna+k]==NULL);

    k=0;
    do{//linha esquerda
        k++;
        if (coluna-k>=0 && (pos.tab[linha][coluna-k]==NULL||pos.tab[linha][coluna-k]->codigo*peca<0)){
            InsereJogada(lista,linha,coluna,linha,coluna-k);
            if (pos.tab[linha][coluna-k]!=NULL)
                pos.tab[linha][coluna-k]->ataques++;
        }
    }while(coluna-k>=0 && pos.tab[linha][coluna-k]==NULL);
}

void CalculaRei(Posicao pos, int linha, int coluna,struct Jogada *lista){
    int peca=pos.tab[linha][coluna]->codigo;

    if (linha<7){//linha de cima
        if (pos.tab[linha+1][coluna]==NULL||pos.tab[linha+1][coluna]->codigo*peca<0){//mesma coluna
            InsereJogada(lista,linha,coluna,linha+1,coluna);
            if (pos.tab[linha+1][coluna]!=NULL)
                pos.tab[linha+1][coluna]->ataques++;
        }
        if (coluna<7 && (pos.tab[linha+1][coluna+1]==NULL||pos.tab[linha+1][coluna+1]->codigo*peca<0)){//superior direita
            InsereJogada(lista,linha,coluna,linha+1,coluna+1);
            if (pos.tab[linha+1][coluna+1]!=NULL)
                pos.tab[linha+1][coluna+1]->ataques++;
        }
        if (coluna>0 && (pos.tab[linha+1][coluna-1]==NULL||pos.tab[linha+1][coluna-1]->codigo*peca<0)){//superior esquerda
            InsereJogada(lista,linha,coluna,linha+1,coluna-1);
            if (pos.tab[linha+1][coluna-1]!=NULL)
                pos.tab[linha+1][coluna-1]->ataques++;
        }
    }

    if (linha>0){//linha de baixo
        if (pos.tab[linha-1][coluna]==NULL||pos.tab[linha-1][coluna]->codigo*peca<0){//mesma coluna
            InsereJogada(lista,linha,coluna,linha-1,coluna);
            if (pos.tab[linha-1][coluna]!=NULL)
                pos.tab[linha-1][coluna]->ataques++;
        }
        if (coluna<7 && (pos.tab[linha-1][coluna+1]==NULL||pos.tab[linha-1][coluna+1]->codigo*peca<0)){//inferior direita
            InsereJogada(lista,linha,coluna,linha-1,coluna+1);
            if (pos.tab[linha-1][coluna+1]!=NULL)
                pos.tab[linha-1][coluna+1]->ataques++;
        }
        if (coluna>0 && (pos.tab[linha-1][coluna-1]==NULL||pos.tab[linha-1][coluna-1]->codigo*peca<0)){//inferior esquerda
            InsereJogada(lista,linha,coluna,linha-1,coluna-1);
            if (pos.tab[linha-1][coluna-1]!=NULL)
                pos.tab[linha-1][coluna-1]->ataques++;
        }
    }

    if (coluna<7 && (pos.tab[linha][coluna+1]==NULL||pos.tab[linha][coluna+1]->codigo*peca<0)){ //mesma linha, casa da direita
        InsereJogada(lista,linha,coluna,linha+1,coluna);
            if (pos.tab[linha][coluna+1]!=NULL)
                pos.tab[linha][coluna+1]->ataques++;
    }

    if (coluna>0 && (pos.tab[linha][coluna-1]==NULL||pos.tab[linha][coluna-1]->codigo*peca<0)){ //mesma linha, casa da esquerda
        InsereJogada(lista,linha,coluna,linha,coluna-1);
            if (pos.tab[linha][coluna-1]!=NULL)
                pos.tab[linha][coluna-1]->ataques++;
    }
}

//inicia o tabuleiro, colocando as pe?as e criando as listas
struct Posicao IniciaTabuleiro(){
    struct Posicao pos;
    pos.qtdBrancas = pos.qtdPretas = 16;
    pos.jogVez = 1;
    pos.brancas = CriaListaPeca();
    pos.pretas = CriaListaPeca();

    int i,j;
    for (i=2;i<6;i++)
        for (j=0;j<8;j++)
            pos.tab[i][j] = NULL;

    for (j=0;j<8;j++){
        pos.tab[1][j] = InserePeca(pos.brancas,PEAO,1,j);
        pos.tab[6][j] = InserePeca(pos.pretas,-PEAO,6,j);
    }

    pos.tab[0][0] = InserePeca(pos.brancas,TORRE,0,0);
    pos.tab[0][7] = InserePeca(pos.brancas,TORRE,0,7);

    pos.tab[7][0] = InserePeca(pos.pretas,-TORRE,7,0);
    pos.tab[7][7] = InserePeca(pos.pretas,-TORRE,7,7);

    pos.tab[0][1] = InserePeca(pos.brancas,CAVALO,0,1);
    pos.tab[0][6] = InserePeca(pos.brancas,CAVALO,0,6);

    pos.tab[7][1] = InserePeca(pos.pretas,-CAVALO,7,1);
    pos.tab[7][6] = InserePeca(pos.pretas,-CAVALO,7,6);

    pos.tab[0][2] = InserePeca(pos.brancas,BISPO,0,2);
    pos.tab[0][5] = InserePeca(pos.brancas,BISPO,0,5);

    pos.tab[7][2] = InserePeca(pos.pretas,-BISPO,7,2);
    pos.tab[7][5] = InserePeca(pos.pretas,-BISPO,7,5);

    pos.tab[0][3] = InserePeca(pos.brancas,RAINHA,0,3);
    pos.tab[7][3] = InserePeca(pos.pretas,-RAINHA,7,3);

    pos.tab[0][4] = InserePeca(pos.brancas,REI,0,4);
    pos.tab[7][4] = InserePeca(pos.pretas,-REI,7,4);

    return pos;
}

struct Posicao CopiaPosicao(struct Posicao pos){
    struct Posicao copiapos;

    copiapos.qtdPretas = pos.qtdPretas;
    copiapos.qtdBrancas = pos.qtdBrancas;
    copiapos.jogVez = pos.jogVez;

    copiapos.brancas = CriaListaPeca();
    copiapos.pretas = CriaListaPeca();
    int i,j;
    for(i = 0; i < 8; i++){
      for(j = 0; j < 8; j++){
        if(pos.tab[i][j] == NULL){
          copiapos.tab[i][j] = NULL;
        }else if(pos.tab[i][j]->codigo < 0){
          copiapos.tab[i][j] = InserePeca(copiapos.pretas, pos.tab[i][j]->codigo, pos.tab[i][j]->linha, pos.tab[i][j]->coluna);
        }else if(pos.tab[i][j]->codigo > 0){
          copiapos.tab[i][j] = InserePeca(copiapos.brancas, pos.tab[i][j]->codigo, pos.tab[i][j]->linha, pos.tab[i][j]->coluna);
        }
      }
    }

    return copiapos;
}

void CalculaJogadas(Posicao pos,int linha, int coluna, struct Jogada *lista){
    int peca = pos.tab[linha][coluna]->codigo;
    switch (abs(peca)){
    case PEAO:   CalculaPeao(pos,linha,coluna,lista);break;//peoes
    case CAVALO: CalculaCavalo(pos,linha,coluna,lista);break;//cavalos
    case BISPO:  CalculaBispo(pos,linha,coluna,lista);break;//bispos
    case TORRE:  CalculaTorre(pos,linha,coluna,lista);break;//torres
    case RAINHA: CalculaBispo(pos,linha,coluna,lista);
                 CalculaTorre(pos,linha,coluna,lista);break;
    case REI:    CalculaRei(pos,linha,coluna,lista);break;//rei
    }
}

struct Jogada *CalculaMovimentosPossiveis(Posicao pos){
    struct Jogada *jogadas = CriaListaJogada();
    struct Peca *aux;

    ZeraAtaques(pos.brancas);
    ZeraAtaques(pos.pretas);

    if (pos.jogVez==1){
        aux = pos.brancas->prox;
        while (aux!=pos.brancas){
            CalculaJogadas(pos,aux->linha,aux->coluna,jogadas);
            aux=aux->prox;
        }
    }else{
        aux = pos.pretas->prox;
        while (aux!=pos.pretas){
            CalculaJogadas(pos,aux->linha,aux->coluna,jogadas);
            aux=aux->prox;
        }
    }
    return jogadas;
}

struct Jogada *EscolheJogada(struct Jogada *jogadas){
    int deLinha,deColuna,paraLinha, paraColuna;
    struct Jogada *jog=NULL;
    do{
        printf("Digite a linha e a coluna da peca a ser movida:");
        scanf("%d %d",&deLinha,&deColuna);
        deLinha--;deColuna--;//na matriz a contagem come?a com 0

        printf("Digite a linha e a coluna para onde a peca deve ser movida:");
        scanf("%d %d",&paraLinha,&paraColuna);
        paraLinha--;paraColuna--;//na matriz a contagem come?a com 0

        jog = jogadas->prox;
        while (jog!=jogadas&&(jog->deLinha!=deLinha||jog->deColuna!=deColuna||jog->paraLinha!=paraLinha||jog->paraColuna!=paraColuna)){
            jog = jog->prox;
        }
    }while (jog==jogadas);
    return jog;
}

int ExecutaJogada(Posicao *pos,struct Jogada jog){
    int resp=0;
    if ((pos->tab[jog.deLinha][jog.deColuna]->codigo==PEAO && jog.paraLinha==7) || (pos->tab[jog.deLinha][jog.deColuna]->codigo==-PEAO && jog.paraLinha == 0)){
		pos->tab[jog.deLinha][jog.deColuna]->codigo *= RAINHA;
	}
    struct Peca *peca = pos->tab[jog.deLinha][jog.deColuna];

    pos->tab[jog.deLinha][jog.deColuna] = NULL; //retira a pe?a do ligar

    if (pos->tab[jog.paraLinha][jog.paraColuna]!=NULL){ //a pe?a far? uma captura
        if (abs(pos->tab[jog.paraLinha][jog.paraColuna]->codigo)==REI) //rei capturado
            resp=1;

        RemovePeca(pos->tab[jog.paraLinha][jog.paraColuna]); //retira a pe?a que foi capturada da sua lista
        if (pos->jogVez==1)
            pos->qtdPretas--; //capturou pe?a preta
        else pos->qtdBrancas--;//capturou pe?a branca
    }
    pos->tab[jog.paraLinha][jog.paraColuna] = peca;
    peca->linha = jog.paraLinha;
    peca->coluna = jog.paraColuna;

    pos->jogVez = -pos->jogVez;

    return resp;
}

double avaliaPosicao (struct Posicao pos){

  struct Peca *aux, *aux2;
  int avaliaBranca,avaliaPreta;

  //avalia brancas
  aux = pos.brancas -> prox;

  while(aux != pos.brancas)
  {
    if(pos.brancas->codigo == PEAO)
    {
      avaliaBranca += 1;
      if(pos.brancas->ataques > 0)
      {
        avaliaBranca -= pos.brancas->ataques * 0.5;
      }
    }
    else
      if(pos.brancas->codigo == CAVALO)
      {
       avaliaBranca += 3;
        if(pos.brancas->ataques > 0)
        {
         avaliaBranca -= pos.brancas->ataques * 0.5;
        }
      } else
        if(pos.brancas->codigo == BISPO)
      {
       avaliaBranca += 3;
        if(pos.brancas->ataques > 0)
        {
         avaliaBranca -= pos.brancas->ataques * 0.5;
        }
      } else
      if(pos.brancas->codigo == TORRE)
      {
       avaliaBranca += 3;
        if(pos.brancas->ataques > 0)
        {
         avaliaBranca -= pos.brancas->ataques * 0.5;
        }
      } else
      if(pos.brancas->codigo == RAINHA)
      {
       avaliaBranca += 4;
        if(pos.brancas->ataques > 0)
        {
         avaliaBranca -= pos.brancas->ataques * 0.5;
        }
      } else
      if(pos.brancas->codigo == REI)
      {
        if(pos.brancas->ataques > 0)
        {
         avaliaBranca -= pos.brancas->ataques * 2;
        }
      }
  }
  //avalia pretas
  aux = pos.pretas -> prox;

  while(aux != pos.pretas) {
    if(pos.pretas->codigo == PEAO)
    {
      avaliaPreta += 1;
      if(pos.pretas->ataques > 0)
      {
        avaliaPreta -= pos.pretas->ataques * 0.5;
      }
    }
    else if(pos.pretas->codigo == CAVALO){
       avaliaBranca += 3;
        if(pos.pretas->ataques > 0)
        {
         avaliaPreta -= pos.pretas->ataques * 0.5;
        }
        }else if(pos.pretas->codigo == BISPO){
       avaliaPreta += 3;
        if(pos.brancas->ataques > 0)
        {
         avaliaPreta -= pos.pretas->ataques * 0.5;
        }
        }else if(pos.pretas->codigo == TORRE){
       avaliaPreta += 3;
        if(pos.pretas->ataques > 0)
        {
         avaliaPreta -= pos.pretas->ataques * 0.5;
        }
        }else if(pos.pretas->codigo == RAINHA){
       avaliaBranca += 4;
        if(pos.pretas->ataques > 0)
        {
         avaliaPreta -= pos.pretas->ataques * 0.5;
        }
        }else if(pos.pretas->codigo == REI){
        if(pos.pretas->ataques > 0)
        {
         avaliaPreta -= pos.pretas->ataques * 2;
        }
        }
  }
  return avaliaPreta - avaliaBranca;
}

void liberamemoria(struct Posicao pos){
   DestroiPecas(pos.brancas);
   DestroiPecas(pos.pretas);
}

struct Jogada ExecutaIA(struct Posicao pos, int nivel, double alfa, double beta){
    struct Jogada *lista,*jogadaAux,*listaBrancas,*listaPretas;

    double melhorValor, valorJogada;
		struct Jogada melhorjogada;
		struct Jogada jogadaIA;
		struct Posicao posCopia;

		if(nivel % 2 == 0)
        melhorValor = -INFINITY;
    else
        melhorValor = INFINITY;

    int podado = 0;

    ///calcular as poss?veis jogadas das pe?as brancas e pretas (item 2 do exerc?cio)
        if(pos.jogVez == -1){
        listaPretas = CalculaMovimentosPossiveis(pos);
        pos.jogVez = 1;
        listaBrancas = CalculaMovimentosPossiveis(pos);
        pos.jogVez = -1;
    }else{
        listaBrancas = CalculaMovimentosPossiveis(pos);
        pos.jogVez = -1;
        listaPretas = CalculaMovimentosPossiveis(pos);
        pos.jogVez = 1;
    }
    ///fazer com que a vari?vel "lista" receba a lista de jogadas das pe?as brancas ou das pretas, dependendo do valor de n?vel (item 3 do exerc?cio)

			if(nivel % 2 == 0){
        lista = CriaListaJogada();
        lista = listaPretas;
    }else{
        lista = CriaListaJogada();
        lista = listaBrancas;
    }

    jogadaAux = lista->prox;

    while (jogadaAux != lista && podado==0){
			///aqui vamos percorrer a lista de jogadas poss?veis (ou da sbrancas ou das pretas) enquanto ainda for bom continuar avaliando a posi??o

        ///copiar o par?metro "posAtual" para "posCopia" (item 4 do exerc?cio)
					posCopia = CopiaPosicao(pos);
        ///executar a jogada "jogadaAux" em "posCopia" (item 4 do exerc?cio)
				ExecutaJogada(&posCopia,*jogadaAux);
        ///verificar se "nivel" ? menor do que "MAX_NIVEL" (item 5 do exerc?cio)
				if(nivel < MAX_NIVEL)
        {
            ///verificar se "nivel" ? par (item 5a do exerc?cio)
						if(nivel%2 == 0)

                ///chamar a fun??o recursivamente e guardar a jogada retornada em "jogadaIA" (item 5a do exerc?cio)
							 jogadaIA = ExecutaIA(posCopia, nivel +1, melhorValor, beta);

            ///verificar se "nivel" ? ?mpar (item 5b do exerc?cio) - pode ser usado "else" em rela??o ao item 5a
						else
            {
								jogadaIA = ExecutaIA(posCopia, nivel +1, alfa, melhorValor);
                ///chamar a fun??o recursivamente e guardar a jogada retornada em "jogadaIA" (item 5b do exerc?cio)
            }
						ExecutaJogada(&posCopia, jogadaIA);
            ///executar "jogadaIA" sobre "posCopia" (item 5a do exerc?cio)
        }

        ///avaliar a posi??o "posCopia" (item 6 do exerc?cio)
				 valorJogada = avaliaPosicao(posCopia);
        ///verificar se houve poda (item 6 do exerc?cio)

					if(valorJogada < alfa || valorJogada > beta)
					podado = 1;
        ///verificar "jogadaIA" ? a melhor jogada encontrada at? o momento (item 7 do exerc?cio)
					if(nivel % 2 == 0 && valorJogada >= melhorValor){
						melhorValor = valorJogada;
						melhorjogada = *jogadaAux;
					}else if(nivel % 2 != 0 && valorJogada <= melhorValor){
						melhorValor = valorJogada;
						melhorjogada = *jogadaAux;
					}
        ///liberar a mem?ria de "posCopia" (item 8 do exerc?cio)
				jogadaAux = jogadaAux -> prox;
	    	liberamemoria(posCopia);
    }

    ///liberar a mem?ria alocada nas listas de poss?veis jogadas das pe?as brancas e pretas (item 9 do exerc?cio)
		DestroiJogadas(listaPretas);
    DestroiJogadas(listaBrancas);

    ///retornar a melhor jogada encontrada "melhorJogada" (item 9 do exerc?cio).

		return melhorjogada;
}

void SalvaJogada(const char *nome, struct Jogada *jogada){
    FILE *arq;
    if(jogada == NULL){
			arq = fopen(nome, "wb");
			fclose(arq);
		}else{
			arq = fopen(nome, "ab");
			fwrite(&jogada->deLinha,sizeof(int),1,arq);
			fwrite(&jogada->deColuna,sizeof(int),1,arq);
			fwrite(&jogada->paraLinha,sizeof(int),1,arq);
			fwrite(&jogada->paraColuna,sizeof(int),1,arq);
		}

		fclose(arq);
    ///fechar o arquivo
}

int main(){
    int vencedor=0;

    struct Posicao posAux = IniciaTabuleiro();
    struct Jogada *jogadasPossiveis=NULL,jogadaEscolhida;

		SalvaJogada("jogada.bin", NULL);

    while (vencedor==0){
        DesenhaTabuleiro(posAux);
        if (posAux.jogVez==1){
            jogadasPossiveis = CalculaMovimentosPossiveis(posAux);
            jogadaEscolhida = *EscolheJogada(jogadasPossiveis); ///eu modifiquei aqui para retornar um struct ao inv?s de um ponteiro
            DestroiJogadas(jogadasPossiveis);
        }else{
            jogadaEscolhida = ExecutaIA(posAux,0,-INFINITY,INFINITY);
        }

        SalvaJogada("jogada.bin",  &jogadaEscolhida);

        vencedor = ExecutaJogada(&posAux,jogadaEscolhida);
    }
    if (posAux.jogVez==-1){ //a fun??o ExecutaJogada j? trocou o jogador da vez
        printf("Brancas venceram!");
    }else printf("Pretas venceram!");

    DestroiPecas(posAux.brancas);
    DestroiPecas(posAux.pretas);
}

