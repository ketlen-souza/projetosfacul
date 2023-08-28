//  Ketlen Victoria Martins de Souza - nUSP 11.838.777
//  Leonardo Goncalves Carvalho - nUSP 11.837.672

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  MAX se refere a jogadas maximas permitidas (esse valor pode ser alterado pelo jogador
//quando atingido tal valor, caso ele queira mais rodadas disponíveis).
#define MAX 150
//  WIN se refere ao numero minimo de rodadas para se iniciar a vericacao da quantidade de
//gansos que ainda permanecem no tabuleiro.
#define WIN 20

//  Funcao que imprime o tabuleiro
void imprime_tabuleiro(char tabuleiro[7][7]){
  printf("\n\n\t     1   2   3   4   5   6   7\n");
  printf("\t  \n");
  printf("\t 1  \t     %c - %c - %c\n", tabuleiro[0][2],tabuleiro[0][3],tabuleiro[0][4]);
  printf("\t    \t     | \\ | / |\n");
  printf("\t 2  \t     %c - %c - %c\n", tabuleiro[1][2],tabuleiro[1][3],tabuleiro[1][4]);
  printf("\t    \t     | / | \\ | \n");
  printf("\t 3   %c - %c - %c - %c - %c - %c - %c\n",tabuleiro[2][0],tabuleiro[2][1],tabuleiro[2][2],tabuleiro[2][3],tabuleiro[2][4],tabuleiro[2][5],tabuleiro[2][6]);
  printf("\t     | \\ | / | \\ | / | \\ | / | \n");
  printf("\t 4   %c - %c - %c - %c - %c - %c - %c\n",tabuleiro[3][0],tabuleiro[3][1],tabuleiro[3][2],tabuleiro[3][3],tabuleiro[3][4],tabuleiro[3][5],tabuleiro[3][6]);
  printf("\t     | / | \\ | / | \\ | / | \\ | \n");
  printf("\t 5   %c - %c - %c - %c - %c - %c - %c\n",tabuleiro[4][0],tabuleiro[4][1],tabuleiro[4][2],tabuleiro[4][3],tabuleiro[4][4],tabuleiro[4][5],tabuleiro[4][6]);
  printf("\t    \t     | \\ | / | \n");
  printf("\t 6  \t     %c - %c - %c\n", tabuleiro[5][2],tabuleiro[5][3],tabuleiro[5][4]);
  printf("\t    \t     | / | \\ | \n");
  printf("\t 7  \t     %c - %c - %c\n\n", tabuleiro[6][2],tabuleiro[6][3],tabuleiro[6][4]);
}

//--------------------

//  Funcao que identifica em qual posicao a raposa (R) esta
void verifica_posicao_R(char tabuleiro[7][7], int *i, int *j){
  for(*i = 0; *i < 7; *i = *i + 1){
    for(*j = 0; *j < 7; *j = *j + 1){
      if(tabuleiro[*i][*j] == 'R'){
        return;
      }
    }
  }
}

//------------------------------

//  Funcao que verifica se o movimento desejado eh para uma casa valida,
//considerando diagonais possiveis, "paredes", e distancia do "salto".
//  Retorna valores que simbolizam a seguintes direcoes esquematicas:
//  7   8   9
//  4   X   6
//  1   2   3
int posicao_valida(int Lf, int Cf, int Li, int Ci){
  
  //condição para andar pra direita
  if(Lf == Li && Cf == Ci+1){
    if((Li == 1-1 && Ci == 5-1) || (Li == 2-1 && Ci == 5-1) || (Li == 3-1 && Ci == 7-1) || (Li == 4-1 && Ci == 7-1) || (Li == 5-1 && Ci == 7-1) || (Li == 6-1 && Ci == 5-1) || (Li == 7-1 && Ci == 5-1)){
      return(-1);
    }
    return(6);
  }

  //condição para andar pra esquerda
  if(Lf == Li && Cf == Ci-1){
    if((Li == 1-1 && Ci == 3-1) || (Li == 2-1 && Ci == 3-1) || (Li == 3-1 && Ci == 1-1) || (Li == 4-1 && Ci == 1-1) || (Li == 5-1 && Ci == 1-1) || (Li == 6-1 && Ci == 3-1) || (Li == 7-1 && Ci == 3-1)){
      return(-1);
    }
    return(4);
  }
  
  //condição para andar pra baixo
  if(Lf== Li+1 && Cf == Ci){
    if((Li == 5-1 && Ci == 1-1) || (Li == 5-1 && Ci == 2-1) || (Li == 7-1 && Ci == 3-1) || (Li == 7-1 && Ci == 4-1) || (Li == 7-1 && Ci == 5-1) || (Li == 5-1 && Ci == 6-1) || (Li == 5-1 && Ci == 7-1)){
      return(-1);
    }
    return(2);
  }
  
  //condição para andar pra cima
  if(Lf == Li-1 && Cf == Ci){
    if((Li == 3-1 && Ci == 1-1) || (Li == 3-1 && Ci == 2-1) || (Li == 1-1 && Ci == 3-1) || (Li == 1-1 && Ci == 4-1) || (Li == 1-1 && Ci == 5-1) || (Li == 3-1 && Ci == 6-1) || (Li == 3-1 && Ci == 7-1)){
      return(-1);
    }
    return(8);
  }
  
  //condição para andar pra diagonal superior direita
  if(Lf == Li-1 && Cf == Ci+1){
    if((Li == 2-1 && Ci == 4-1) || (Li == 3-1 && Ci == 3-1) || (Li == 4-1 && Ci == 2-1) || (Li == 5-1 && Ci == 1-1) || (Li == 4-1 && Ci == 4-1) || (Li == 5-1 && Ci == 3-1) || (Li == 4-1 && Ci == 6-1) || (Li == 5-1 && Ci == 5-1) || (Li == 6-1 && Ci == 4-1) || (Li == 7-1 && Ci == 3-1)){
    return(9); 
    }
  }
  
  //condição para andar pra diagonal superior esquerda
  if(Lf == Li-1 && Cf == Ci-1){
    if((Li == 2-1 && Ci == 4-1) || (Li == 3-1 && Ci == 5-1) || (Li == 4-1 && Ci == 6-1) || (Li == 5-1 && Ci == 7-1) || (Li == 4-1 && Ci == 4-1) || (Li == 5-1 && Ci == 5-1) || (Li == 4-1 && Ci == 2-1) || (Li == 5-1 && Ci == 3-1) || (Li == 6-1 && Ci == 4-1) || (Li == 7-1 && Ci == 5-1)){
      return(7);
    }
  }
  
  //condição para andar pra diagonal inferior direita
  if(Lf == Li+1 && Cf == Ci+1){
    if((Li == 1-1 && Ci == 3-1) || (Li == 2-1 && Ci == 4-1) || (Li == 3-1 && Ci == 5-1) || (Li == 4-1 && Ci == 6-1) || (Li == 3-1 && Ci == 3-1) || (Li == 4-1 && Ci == 4-1) || (Li == 3-1 && Ci == 1-1) || (Li == 4-1 && Ci == 2-1) || (Li == 5-1 && Ci == 3-1) || (Li == 6-1 && Ci == 4-1)){
      return(3);
    }
  }

  //condição para andar pra diagonal inferior esquerda
  if(Lf == Li+1 && Cf == Ci-1){
    if((Li == 1-1 && Ci == 5-1) || (Li == 2-1 && Ci == 4-1) || (Li == 3-1 && Ci == 3-1) || (Li == 4-1 && Ci == 2-1) || (Li == 3-1 && Ci == 5-1) || (Li == 4-1 && Ci == 4-1) || (Li == 3-1 && Ci == 7-1) || (Li == 4-1 && Ci  == 6-1) || (Li == 5-1 && Ci == 5-1) || (Li == 6-1 && Ci == 4-1)){
      return(1);
    }
  }
  return(-1);
}

//----------------------

//  Funcao que verifica se o movimento solicitado eh valido
int movimento_valido(char tabuleiro[7][7], int Lf, int Cf, int Li, int Ci){
  //  Verifica se a casa desejada esta vazia
  if(posicao_valida(Lf,Cf,Li,Ci) != -1 && tabuleiro[Lf][Cf] == '.'){
    return(1);
  }
  return(-1);
}

//-------------------

//  Funcao que utiliza a que realiza o movimento solicitado, apenas no caso de ele ser valido.
int realiza_movimento(char jogador, char tabuleiro[7][7], int Lf, int Cf, int Li, int Ci){
  if(movimento_valido(tabuleiro, Lf, Cf, Li, Ci) == 1){
    //  "Esvazia" a casinha inicial da peca a se mover.
    tabuleiro[Li][Ci] = '.';
    //  Troca a posição da R, caso essa seja a vez dela jogar.
    if(jogador == 'R'){
    tabuleiro[Lf][Cf] = 'R';
    }
    //  Troca a posição da O, caso essa seja a vez dela jogar.
    if(jogador == 'O'){
    tabuleiro[Lf][Cf] = 'O';
    }
    return(1);
  }
  return(-1);
}

//---------------------

//  Funcao que verifica a possibilidade da raposa comer um ganso, e retorna 1 para possivel -1 para não possivel
int verifica_come_ganso(char tabuleiro[7][7], int Lf, int Cf){
  int LRi, CRi;
  //  Localiza a posicao da Raposa
  verifica_posicao_R(tabuleiro,&LRi,&CRi);  
  int aux;
  aux = posicao_valida(Lf,Cf,LRi,CRi);

  //  Condicoes necessarias para que a Raposa tenha a possibilidade de comer, pelo menos, um ganso
  if((aux == 6 && tabuleiro[Lf][Cf] == 'O' && tabuleiro[Lf][Cf+1] == '.') || (aux == 4 && tabuleiro[Lf][Cf] == 'O' && tabuleiro[Lf][Cf-1] == '.') || (aux == 8 && tabuleiro[Lf][Cf] == 'O' && tabuleiro[Lf-1][Cf] == '.') || (aux == 2 && tabuleiro[Lf][Cf] == 'O' && tabuleiro[Lf+1][Cf] == '.') || (aux == 9 && tabuleiro[Lf][Cf] == 'O' && tabuleiro[Lf-1][Cf+1] == '.') || (aux == 7 && tabuleiro[Lf][Cf] == 'O' && tabuleiro[Lf-1][Cf-1] == '.') || (aux == 3 && tabuleiro[Lf][Cf] == 'O' && tabuleiro[Lf+1][Cf+1] == '.') || (aux == 1 && tabuleiro[Lf][Cf] == 'O' && tabuleiro[Lf+1][Cf-1] == '.')){
    return(1);
  }
  return(-1);
}

//------------------------

//  Funcao que realiza os movimentos da raposa, quando esta tem a possibilidade de comer um ganso
int come_ganso(char tabuleiro[7][7], int Lf, int Cf){
  int LRi, CRi;
  //  Localiza a posicao da Raposa
  verifica_posicao_R(tabuleiro,&LRi,&CRi);
  int aux;
  //  
  aux = posicao_valida(Lf,Cf,LRi,CRi);
  
  //  Verifica se a casa desejada esta ocupada e existe um espaco vago "atras" do ganso (direita)
  if(aux == 6 && tabuleiro[Lf][Cf] == 'O' && tabuleiro[Lf][Cf+1] == '.'){
    tabuleiro[Lf][Cf] = '.';
    tabuleiro[LRi][CRi] = '.';
    tabuleiro[Lf][Cf+1] = 'R';
    return(1);
  }
  
  //  Verifica se a casa desejada esta ocupada e existe um espaco vago "atras" do ganso (esquerda)
  if(aux == 4 && tabuleiro[Lf][Cf] == 'O' && tabuleiro[Lf][Cf-1] == '.'){
    tabuleiro[Lf][Cf] = '.';
    tabuleiro[LRi][CRi] = '.';
    tabuleiro[Lf][Cf-1] = 'R';
    return(1);
  }

  //  Verifica se a casa desejada esta ocupada e existe um espaco vago "atras" do ganso (cima)
  if(aux == 8 && tabuleiro[Lf][Cf] == 'O' && tabuleiro[Lf-1][Cf] == '.'){
    tabuleiro[Lf][Cf] = '.';
    tabuleiro[LRi][CRi] = '.';
    tabuleiro[Lf-1][Cf] = 'R';
    return(1);
  }

  //  Verifica se a casa desejada esta ocupada e existe um espaco vago "atras" do ganso (baixo)
  if(aux == 2 && tabuleiro[Lf][Cf] == 'O' && tabuleiro[Lf+1][Cf] == '.'){
    tabuleiro[Lf][Cf] = '.';
    tabuleiro[LRi][CRi] = '.';
    tabuleiro[Lf+1][Cf] = 'R';
    return(1);
  }

  //  Verifica se a casa desejada esta ocupada e existe um espaco vago "atras" do ganso (diagonal superior direita)
  if(aux == 9 && tabuleiro[Lf][Cf] == 'O' && tabuleiro[Lf-1][Cf+1] == '.'){
    tabuleiro[Lf][Cf] = '.';
    tabuleiro[LRi][CRi] = '.';
    tabuleiro[Lf-1][Cf+1] = 'R';
    return(1);
  }

  //  Verifica se a casa desejada esta ocupada e existe um espaco vago "atras" do ganso (diagonal superior esquerda)
  if(aux == 7 && tabuleiro[Lf][Cf] == 'O' && tabuleiro[Lf-1][Cf-1] == '.'){
    tabuleiro[Lf][Cf] = '.';
    tabuleiro[LRi][CRi] = '.';
    tabuleiro[Lf-1][Cf-1] = 'R';
    return(1);
  }

  //  Verifica se a casa desejada esta ocupada e existe um espaco vago "atras" do ganso (diagonal inferior direita)
  if(aux == 3 && tabuleiro[Lf][Cf] == 'O' && tabuleiro[Lf+1][Cf+1] == '.'){
    tabuleiro[Lf][Cf] = '.';
    tabuleiro[LRi][CRi] = '.';
    tabuleiro[Lf+1][Cf+1] = 'R';
    return(1);
  }

  //  Verifica se a casa desejada esta ocupada e existe um espaco vago "atras" do ganso (diagonal inferior esquerda)
  if(aux == 1 && tabuleiro[Lf][Cf] == 'O' && tabuleiro[Lf+1][Cf-1] == '.'){
    tabuleiro[Lf][Cf] = '.';
    tabuleiro[LRi][CRi] = '.';
    tabuleiro[Lf+1][Cf-1] = 'R';
    return(1);
  }
  return(-1);
}

//--------------------------

//  Funcao que verifica, a partir da MAX rodada, quantos gansos (O) ainda restam no tabuleiro.
int verifica_n_O(char tabuleiro[7][7]){
  int i, j, aux;
  aux = 0;
  for(i = 0; i < 7; i++){
    for(j = 0; j < 7; j++){
      if(tabuleiro[i][j] == 'O'){
        aux++;
      }
    }
  }
  return(aux);
}

//----------------------------

// Funcao que verifica se os gansos ganharam
int ganso_ganhou(char jogador, char tabuleiro[7][7], int Lf, int Cf){
  int LRi, CRi;
  // Localiza a posicao da raposa 
  verifica_posicao_R(tabuleiro, &LRi, &CRi);

  //  Apos localizar a raposa, eh chamada a funcao que verifica se eh possivel, esta, realizar um movimento
  //  seja apenas para mover-se ou para comer um ganso 
  if(movimento_valido(tabuleiro, LRi+1, CRi, LRi, CRi) == -1 && movimento_valido(tabuleiro, LRi-1, CRi, LRi, CRi) == -1 && movimento_valido(tabuleiro, LRi, CRi+1, LRi, CRi) == -1 && movimento_valido(tabuleiro, LRi, CRi-1, LRi, CRi) == -1 && movimento_valido(tabuleiro, LRi+1, CRi+1, LRi, CRi) == -1 && movimento_valido(tabuleiro, LRi+1, CRi-1, LRi, CRi) == -1 && movimento_valido(tabuleiro, LRi-1, CRi+1, LRi, CRi) == -1 && movimento_valido(tabuleiro, LRi-1, CRi-1, LRi, CRi) == -1){

    //  
    if(verifica_come_ganso(tabuleiro, LRi+1, CRi) == -1 && verifica_come_ganso(tabuleiro, LRi-1, CRi) == -1 && verifica_come_ganso(tabuleiro, LRi, CRi+1) == -1 && verifica_come_ganso(tabuleiro, LRi, CRi-1) == -1 && verifica_come_ganso(tabuleiro, LRi+1, CRi+1) == -1 && verifica_come_ganso(tabuleiro, LRi+1, CRi-1) == -1 && verifica_come_ganso(tabuleiro, LRi-1, CRi+1) == -1 && verifica_come_ganso(tabuleiro, LRi-1, CRi-1) == -1){
      return(1);
    }
  }
  return(-1);
}

//  Funcao que verifica se a coordenada digitada eh valida e devolve -1 pra invalida e 1 pra valida
int verifica_coord(char tabuleiro[7][7], char jogador, int Lf, int Cf, int LOi, int COi){ 
  int LRi, CRi;

  if(jogador == 'R'){

    //  Localiza a posicao da Raposa.
    verifica_posicao_R(tabuleiro,&LRi,&CRi);
    if(posicao_valida(Lf,Cf,LRi,CRi) != -1){ 
      
      //  Situacao em que a coordenada digitada é para realizar um movimento.
      if(tabuleiro[Lf][Cf] == '.' && realiza_movimento(jogador, tabuleiro, Lf, Cf, LRi, CRi) == 1){
        return(1);
      }
      //  Situacao em que a coordenada digitada é para comer uma peca dos gansos.
      if(tabuleiro[Lf][Cf] == 'O' && come_ganso(tabuleiro, Lf, Cf) == 1){
        return(2);
      }
    }
    return(-1);
  }

  if(jogador == 'O'){
    //  Situacao em que a coordenada digitada é para realizar um movimento.
    if(posicao_valida(Lf,Cf,LOi,COi) != -1 && realiza_movimento(jogador, tabuleiro, Lf, Cf, LOi, COi) == 1){
      return(1);
    }
  }
  return(-1);
}

//------------------------

//  Funcao que verifica se a jogada realizada pela raposa permite uma nova jogada, com a condicao de que seja para "comer" outra peca.
void R_nova_jogada(char tabuleiro[7][7], char jogador){
  int aux, Lf, Cf, LRi, CRi;
  
  //  Localiza a posicao  Raposa.
  verifica_posicao_R(tabuleiro, &LRi, &CRi);

  // Verifica se ha a possibilidade da raposa comer mais um ganso.
  for( ;verifica_come_ganso(tabuleiro, LRi+1, CRi) == 1 || verifica_come_ganso(tabuleiro, LRi-1, CRi) == 1 || verifica_come_ganso(tabuleiro, LRi, CRi+1) == 1 || verifica_come_ganso(tabuleiro, LRi, CRi-1) == 1 || verifica_come_ganso(tabuleiro, LRi+1, CRi+1) == 1 || verifica_come_ganso(tabuleiro, LRi+1, CRi-1) == 1 || verifica_come_ganso(tabuleiro, LRi-1, CRi+1) == 1 || verifica_come_ganso(tabuleiro, LRi-1, CRi-1) == 1; ){
    
    //  Pergunta ao jogador se este deseja comer ou nao mais um ganso.
    do{
      system("clear");
      imprime_tabuleiro(tabuleiro);
      printf("Você possui, pelo menos, mais uma peca disponivel para ''comer''. Deseja realizar tal movimento?\nDigite 1 para ''sim''.\nDigite 2 para ''nao''.\n");
      scanf("%d", &aux);
    }while((aux != 1 || aux == 2) && (aux == 1 || aux != 2));
    
    //  Caso o jogador escolher sim, este deve digitar a coordenada do ganso ao qual deseja comer.
    if(aux == 1){
      do{
        printf("Digite uma coordenada valida para casa que deseja realizar o movimento de apanhar a peca do ganso.\n");
        scanf("%d %d", &Lf, &Cf);
        Lf--;
        Cf--;
      }while(tabuleiro[Lf][Cf] != 'O' || come_ganso(tabuleiro,Lf,Cf) != 1);
    }

    //  Localiza a posicao da Raposa.
    verifica_posicao_R(tabuleiro, &LRi, &CRi);
    
    //  Caso a escolha seja nao, a funcao nao retorna nada e a jogada vai para os gansos.
    if(aux == 2){
      return;
    }
  }
  return;
}

//------------------------

int main(){
  //  Matrizes que formam o tabuleiro
  char tabuleiro[7][7] = {"  ...  ","  ...  ","O..R..O", "O.....O", "OOOOOOO","  OOO  ", "  OOO  "}; 
  char tabuleiro_reserva[7][7] = {"  ...  ","  ...  ","O..R..O","O.....O","OOOOOOO","  OOO  ","  OOO  "};

  //  Sumario das declaracoes:
  // Lf = Linha final; Cf = Coluna final; LOi = Linha inicial do ganso; COi = Coluna inicial do ganso; RMA = rodadas maximas atingidas
  //i e j = contadores; coord = variavel auxiliar.
  int tipo_jogo, Lf, Cf, LOi, COi, rodada, RMA, i, j, coord;
  
  //  Variavel que guarda qual jogador está jogando atualmente (R ou O).
  char jogador;
  
  //  Variavel que guarda o nome do jogador jogando atualmente ("a Raposa" ou "o Ganso").
  char nome_jogador[9];

  system("clear");
  printf("\t\t\tVoce esta jogando FOX AND GEESE!\n\tO jogo contem 17 gansos, representados por O, e uma raposa, apresentada como R.\n\tO objetivo principal para os gansos eh limitar os movimentos da raposa, e para a raposa eh eliminar, pelo menos, 13 gansos.\n\n\t\t\t"
  
  "REGRAS:\n\t1. Os movimentos validos sao aqueles feitos para casas adjacentes, vazias, e passando em cima das linhas demonstradas no tabuleiro abaixo.\n\t"
  "2. Somente para a raposa(R), é valido movimentos por cima dos gansos(O), se houver casa vazia ''do outro lado''.\n\t"
  "3. Para movimentar os gansos(O) no jogo, voce deve digitar a coordenada correspondente a peca (linhaXcoluna), e a coordenada para a casa desejada (linhaXcoluna), separadas por espaços.\n\t"
  "4. Para movimentar a raposa(R) digite a coordenada (linhaXcoluna) para a qual deseja move-la.\n\t"
  "5. Para realizar o movimento de ''comer'' pecas dos gansos, eh necessario digitar a casa do ganso ao qual se deseja ''comer''.\n");
  imprime_tabuleiro(tabuleiro);
  
  //  Escolha do tipo de jogo (contra amigo ou maquina).
  do{
    printf("Leia atentamente as regras do jogo e selecione um meio de jogar: \nDigite 1: contra amigo\nDigite 2: contra maquina - ainda nao disponivel\n");
    scanf("%d", &tipo_jogo);
  }while(tipo_jogo != 1);
  
  if(tipo_jogo == 1){
    system("clear");
    printf("\nTIPO ESCOLHIDO: CONTRA AMIGO\n");
    
    //  Enquanto nao atingir a quantidade de rodadas maximas, preh definidas, o jogo permanece rodando.
    for(rodada = 1; rodada < MAX; rodada++){

	    //  O Jogo inicia, as rodadas impares sao da raposa e as pares dos ganso.
      if(rodada % 2 == 1){
		    jogador = 'R';
        strcpy(nome_jogador, "a RAPOSA");
	    }
      else{
        strcpy(nome_jogador, "o GANSO");
		    jogador = 'O';
	    }
      
      //  Apos a vigesima jogada se inicia a contagem dos gansos, equanto houver mais que 4 gansos o jogo continua,
      //  caso houver exatamente 4 gansos, a raposa eh a vencedora.
	    if(jogador == 'R' && rodada > WIN && verifica_n_O(tabuleiro) < 5) {
		    system("clear");
		    imprime_tabuleiro(tabuleiro);
		    printf("\t\tPARABENS!! RAPOSA(R) EH A VENCEDORA!!\n");
		    return (0);
	    }

      //  Verifica se a Raposa nao possui mais jogadas e define os Gansos como vencedores.
	    if(jogador == 'R' && ganso_ganhou(jogador,tabuleiro,Lf,Cf) == 1) {
		    system("clear");
		    imprime_tabuleiro(tabuleiro);
		    printf("\t\tPARABENS!! GANSOS(O) SÃO OS VENCEDORES!!\n");
		    return (0);
	    } 

      //  Repeticao Do-While para realizar as jogadas dos Gansos e da Raposa
	    do{
		    system("clear");
		    imprime_tabuleiro(tabuleiro);

        //  Caso seja a vez dos Gansos, ele terah que digitar a coordenada de qual ganso deseja alterar a posicao.
		    if(jogador == 'O'){
			    printf("VEZ DA %c:\nDigite valores validos que correspondam, respectivamente, a linha e a coluna, do ganco que deseja alterar a posicao:\n", jogador);
			    scanf("%d", &LOi);
			    scanf("%d", &COi);
			    LOi--;
			    COi--;
		    }

        //  Solicitacao de digito para a coordenada final do movimento e realizacao do mesmo.
          printf("VEZ DA %c:\nDigite valores validos que correspondam, respectivamente, a linha e a coluna, para a qual deseja  mover %s:\n", jogador, nome_jogador);
		      scanf("%d", &Lf);
		      scanf("%d", &Cf);
		      Lf--;
		      Cf--;
		    coord = verifica_coord(tabuleiro, jogador, Lf, Cf, LOi, COi);

        //  Verificacao de caso a Raposa possua mais de uma jogada.
        if(jogador == 'R' && coord == 2){
          R_nova_jogada(tabuleiro,jogador);
        }

	    }while(coord == -1);
      
      //  Caso o numero maximo de rodadas permitidas tenha sido atingido.
	    if(rodada == MAX) {
		    system("clear");
		    imprime_tabuleiro(tabuleiro);
       
        //  Eh perguntado se os jogadores desejam continuar o jogo ou reiniciah-lo.
        do{
			    printf("Numero de rodadas maximas atingidas. Deseja continuar?\nDigite 1 para continuar.\nDigite 2 para reiniciar o jogo.\n");
			    scanf("%d", &RMA);
		    }while((RMA != 1 || RMA == 2) && (RMA == 1 || RMA != 2));
		    system("clear");

        //  Eh reiniciado o jogo, limpando o tabuleiro e reiniciando as jogadas
		    if(RMA == 2){
			    for(i = 0; i < 7; i++){
				    for(j = 0; j < 7; j++){
					    tabuleiro[i][j] = tabuleiro_reserva[i][j];
				    }
			    }
			    printf("\n\t\t\tJOGO REINICIADO!\n");
		    }
		    rodada = 1;
		    jogador = 'R';
	    }
    }
  }
  return(0);
} 