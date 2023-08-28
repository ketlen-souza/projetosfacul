//  Ketlen Victoria Martins de Souza - nUSP 11.838.777
//  Leonardo Goncalves Carvalho - nUSP 11.837.672

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

//  MAX se refere a jogadas maximas permitidas (a contagem pode ser reiniciada pelo jogador,
//quando atingido tal valor, caso ele queira mais rodadas).
#define MAX 200
//  WIN se refere ao numero minimo de rodadas para se iniciar a vericacao da quantidade de
//gansos que ainda permanecem no tabuleiro.
#define WIN 15

//------------------------

//  Funcao que dah uma pausa no jogo.
void espera(double segundos) {
  clock_t agora, limite;

  // Verifica o horario no momento da execucao e o armazena em "agora".
  agora  = clock();

  // Calcula o horario depois de "segundos", a partir do valor de "agora", e armazena em "limite".
  limite = agora + segundos*CLOCKS_PER_SEC;

  // Enquanto nao chega no horario "limite", continua verificando qual o horario corrente.
  while (limite > agora) {
    agora  = clock();
  }

  return;
}

//------------------------

//  Funcao que imprime o tabuleiro
void imprime_tabuleiro(char tabuleiro[9][9]){
  int i,j;
  printf("\n\n\t     1   2   3   4   5   6   7\n");
  printf("\t  \n");
  printf("\t 1  \t     %c - %c - %c\n", tabuleiro[1][3],tabuleiro[1][4],tabuleiro[1][5]);
  printf("\t    \t     | \\ | / |\n");
  printf("\t 2  \t     %c - %c - %c\n", tabuleiro[2][3],tabuleiro[2][4],tabuleiro[2][5]);
  printf("\t    \t     | / | \\ | \n");
  printf("\t 3   %c - %c - %c - %c - %c - %c - %c\n",tabuleiro[3][1],tabuleiro[3][2],tabuleiro[3][3],tabuleiro[3][4],tabuleiro[3][5],tabuleiro[3][6],tabuleiro[3][7]);
  printf("\t     | \\ | / | \\ | / | \\ | / | \n");
  printf("\t 4   %c - %c - %c - %c - %c - %c - %c\n",tabuleiro[4][1],tabuleiro[4][2],tabuleiro[4][3],tabuleiro[4][4],tabuleiro[4][5],tabuleiro[4][6],tabuleiro[4][7]);
  printf("\t     | / | \\ | / | \\ | / | \\ | \n");
  printf("\t 5   %c - %c - %c - %c - %c - %c - %c\n",tabuleiro[5][1],tabuleiro[5][2],tabuleiro[5][3],tabuleiro[5][4],tabuleiro[5][5],tabuleiro[5][6],tabuleiro[5][7]);
  printf("\t    \t     | \\ | / | \n");
  printf("\t 6  \t     %c - %c - %c\n",tabuleiro[6][3],tabuleiro[6][4],tabuleiro[6][5]);
  printf("\t    \t     | / | \\ | \n");
  printf("\t 7  \t     %c - %c - %c\n\n",tabuleiro[7][3],tabuleiro[7][4],tabuleiro[7][5]);
}

//------------------------

//  Imprime as regras e o tabuleiro
void regras(char tabuleiro[9][9]){
  system("clear");
  printf("\t\t\tVoce esta jogando FOX AND GEESE!\n\tO jogo contem 17 gansos, representados por O, e uma raposa, apresentada como R.\n\tO objetivo principal para os gansos eh limitar os movimentos da raposa, e para a raposa eh eliminar, pelo menos, 13 gansos.\n\n\t\t\t"
  
  "REGRAS:\n\t1. Os movimentos validos sao aqueles feitos para casas adjacentes, vazias, e passando em cima das linhas demonstradas no tabuleiro abaixo.\n\t"
  "2. Somente para a raposa(R), é valido movimentos por cima dos gansos(O), se houver casa vazia ''do outro lado''.\n\t"
  "3. Para movimentar os gansos(O) no jogo, voce deve digitar a coordenada correspondente a peca (linhaXcoluna), e a coordenada para a casa desejada (linhaXcoluna), separadas por espaços.\n\t"
  "4. Durante o jogo contra amigo, digite a coordenada (linhaXcoluna) para a qual deseja mover a raposa(R).\n\t"
  "5. Para realizar o movimento de ''comer'' pecas dos gansos, eh necessario digitar a casa do ganso ao qual se deseja ''comer''.\n");
  imprime_tabuleiro(tabuleiro);
  
  return;
}

//--------------------

//  Funcao que identifica em qual posicao a raposa (R) estah.
void verifica_posicao_R(char tabuleiro[9][9], int *i, int *j){
  for(*i = 1; *i < 8; *i = *i + 1){
    for(*j = 1; *j < 8; *j = *j + 1){
      if(tabuleiro[*i][*j] == 'R'){
        return;
      }
    }
  }
}

//------------------------------

//  Funcao que 'monta' o vetor para avaliar as posicoes validas.
int isonLC(int pL[], int pC[], int L, int C){
  int i,x;
  //  Descobre o tamanho do vetor.
  for(x = 0; pL[x] != -1 && pC[x] != -1; x++);
  for(i = 0; i < x; i++){
    if(L == pL[i] && C == pC[i]){
      return(1);
    }
  }
  return(0);
}

//------------------------------

//  Funcao que recebe um vetor e os valores que se deseja colocar nele. 
void altera_vetor(int vetor[], int a, int b, int c, int d, int e, int f, int g, int h, int j, int k, int l){
  int i;
  int aux[] = {a,b,c,d,e,f,g,h,j,k,l};
  for(i = 0; aux[i] != -1; i++){
    vetor[i] = aux[i];
  }
  return;
}

//------------------------------

/*  Funcao que verifica se o movimento desejado eh para uma casa valida, considerando
 diagonais possiveis, "paredes", e distancia do "salto".
  Retorna valores que simbolizam a seguintes direcoes esquematicas:
  7   8   9
  4   X   6
  1   2   3*/
int direcao_valida(int Lf, int Cf, int Li, int Ci){
  int dvL[] = {1,2,3,4,5,6,7,-1,-1,-1,-1};
  int dvC[] = {5,5,7,7,7,5,5,-1,-1,-1,-1};
  
  //  Condição para andar pra direita.
  if(Lf == Li && Cf == Ci+1){
    if(isonLC(dvL,dvC,Li,Ci) == 1){
      return(-1);
    }
    return(6);
  }

  //  Condição para andar pra esquerda.
  if(Lf == Li && Cf == Ci-1){
    altera_vetor(dvL, 1, 2, 3, 4, 5, 6, 7, -1, -1, -1, -1);
    altera_vetor(dvC, 3, 3, 1, 1, 1, 3, 3, -1, -1, -1, -1);
    if(isonLC(dvL,dvC,Li,Ci) == 1){
      return(-1);
    }
    return(4);
  }
  
  //  Condição para andar pra baixo.
  if(Lf== Li+1 && Cf == Ci){
    altera_vetor(dvL, 5, 5, 7, 7, 7, 5, 5, -1, -1, -1, -1);
    altera_vetor(dvC, 1, 2, 3, 4, 5, 6, 7, -1, -1, -1, -1);
    if(isonLC(dvL,dvC,Li,Ci) == 1){
      return(-1);
    }
    return(2);
  }
  
  //  Condição para andar pra cima.
  if(Lf == Li-1 && Cf == Ci){
    altera_vetor(dvL, 3, 3, 1, 1, 1, 3, 3, -1, -1, -1, -1);
    altera_vetor(dvC, 1, 2, 3, 4, 5, 6, 7, -1, -1, -1, -1);
    if(isonLC(dvL,dvC,Li,Ci) == 1){
      return(-1);
    }
    return(8);
  }
  
  //  Condição para andar pra diagonal superior direita.
  if(Lf == Li-1 && Cf == Ci+1){
    altera_vetor(dvL, 2, 3, 4, 5, 4, 5, 4, 5, 6, 7, -1);
    altera_vetor(dvC, 4, 3, 2, 1, 4, 3, 6, 5, 4, 3, -1);
    if(isonLC(dvL,dvC,Li,Ci)){
      return(9);
    }
    return(-1);
  }

  //  Condição para andar pra diagonal superior esquerda.
  if(Lf == Li-1 && Cf == Ci-1){
    altera_vetor(dvL, 2, 3, 4, 5, 4, 5, 4, 5, 6, 7, -1);
    altera_vetor(dvC, 4, 5, 6, 7, 4, 3, 2, 3, 4, 5, -1);
    if(isonLC(dvL,dvC,Li,Ci)){
      return(7);
    }
    return(-1);
  }
  
  //  Condição para andar pra diagonal inferior direita.
  if(Lf == Li+1 && Cf == Ci+1){
    altera_vetor(dvL, 1, 2, 3, 4, 3, 4, 3, 4, 5, 6, -1);
    altera_vetor(dvC, 3, 4, 5, 6, 3, 4, 1, 2, 3, 4, -1);
    if(isonLC(dvL,dvC,Li,Ci)){
      return(3);
    }
    return(-1);
  }

  //  Condição para andar pra diagonal inferior esquerda.
  if(Lf == Li+1 && Cf == Ci-1){
    altera_vetor(dvL, 1, 2, 3, 4, 3, 4, 3, 4, 5, 6, -1);
    altera_vetor(dvC, 5, 4, 3, 2, 5, 4, 7, 6, 5, 4, -1);
    if(isonLC(dvL,dvC,Li,Ci)){
      return(1);
    }
  }
  return(-1);
}

//----------------------

//  Funcao que verifica se o movimento solicitado eh valido (casa vazia e direcao valida)
int movimento_valido(char tabuleiro[9][9], int Lf, int Cf, int Li, int Ci){
  if(direcao_valida(Lf, Cf, Li, Ci) != -1 && tabuleiro[Lf][Cf] == '.'){
    return(1);
  }
  return(-1);
}

//-------------------

//  Funcao que utiliza a que realiza o movimento solicitado, apenas no caso de ele ser valido.
int realiza_movimento(char jogador, char tabuleiro[9][9], int Lf, int Cf, int Li, int Ci){
  if(movimento_valido(tabuleiro, Lf, Cf, Li, Ci) == 1){
    tabuleiro[Li][Ci] = '.';
    tabuleiro[Lf][Cf] = jogador;
    return(1);
  }
  return(-1);
}

//---------------------

//  Funcao que verifica a possibilidade da raposa comer um ganso, e retorna 1 para possivel -1
//para não possivel - utilizada para o jogo contra amigo.
int verifica_come_ganso(char tabuleiro[9][9], int Lf, int Cf, int *i, int *j){
  int LRi, CRi, aux, k;

  //  Vetor que possui as direcoes possiveis, em que a ordem acompanha a variacao do for.
  int direcoes[] = {7, 8, 9, 4, -1, 6, 1, 2, 3};  

  //  Localiza a posicao da Raposa
  verifica_posicao_R(tabuleiro,&LRi,&CRi);

  //  Auxiliar que verifica se a direcao do movimento é valida
  aux = direcao_valida(Lf,Cf,LRi,CRi);

  //  Condicoes necessarias para que a Raposa tenha a possibilidade de comer, pelo menos, um ganso.
  if(tabuleiro[Lf][Cf] == 'O'){
    k = 0;
    for(*i = -1; *i <= 1; *i = *i + 1){
      for(*j = -1; *j <= 1; *j = *j + 1){
        if(direcoes[k] == aux && tabuleiro[Lf+*i][Cf+*j] == '.'){
          return(1);
        }
        k++;
      }
    }
  }
  return(-1);
}

//------------------------

//  Funcao que realiza os movimentos da raposa, quando esta tem a possibilidade de comer
//um ganso - utilizada para o jogo contra amigo.
int come_ganso(char tabuleiro[9][9], int Lf, int Cf){
  int LRi, CRi, i, j;

  //  Localiza a posicao da Raposa
  verifica_posicao_R(tabuleiro,&LRi,&CRi);

  //  Verifica a direcao do movimento, se esta eh valida, se a posicao "atras" do ganso estah vazia e
  //realiza o movimento, se possivel. 
  if(verifica_come_ganso(tabuleiro, Lf, Cf, &i, &j) == 1){
    tabuleiro[Lf][Cf] = '.';
    tabuleiro[LRi][CRi] = '.';
    tabuleiro[Lf+i][Cf+j] = 'R';
    return(1);
  }

  return(-1);
}

//--------------------------

//  Funcao que verifica, a partir da MAX rodada, quantos gansos (O) ainda restam no tabuleiro.
int verifica_n_O(char tabuleiro[9][9]){
  int i, j, qnt_gansos;
  qnt_gansos = 0;
  for(i = 1; i < 8; i++){
    for(j = 1; j < 8; j++){
      if(tabuleiro[i][j] == 'O'){
        qnt_gansos++;
      }
    }
  }
  return(qnt_gansos);
}

//----------------------------

// Funcao que verifica se os gansos ganharam, com base na incapacidade da Raposa de se movimentar.
int ganso_ganhou(char jogador, char tabuleiro[9][9], int Lf, int Cf){
  int LRi, CRi, i, j;
  int aux = 0;
  int aux2 = 0;
  int x, y; // variaveis descartaveis

  // Localiza a posicao da raposa 
  verifica_posicao_R(tabuleiro, &LRi, &CRi);

  //  Condicao para que a Raposa nao seja capaz de se mover.
  for(i = -1; i <= 1; i++){
    for(j = -1; j <= 1; j++){
      if(movimento_valido(tabuleiro, LRi+i, CRi+j, LRi, CRi) == -1){
        aux++;
      }
    }
  }

  //  Caso todos os movimentos sejam invalidos.
  if(aux == 9){

    //  Condicao para que a Raposa nao seja capaz de comer ganso(s).
    for(i = -1; i <= 1; i++){
      for(j = -1; j <= 1; j++){
        if(verifica_come_ganso(tabuleiro, LRi+i, CRi+j, &x, &y) == -1){
          aux2++;
        }
      }
    }
    //  Caso todas as posicoes sejam invalidas
    if(aux2 == 9){
      return(1);
    }
  }
  return(-1);
}

//------------------------

//  Funcao que verifica se a coordenada digitada eh valida e devolve -1 pra invalida e 1 pra valida.
int verifica_coord(char tabuleiro[9][9], char jogador, int Lf, int Cf, int LOi, int COi){ 
  int LRi, CRi;

  if(jogador == 'R'){

    //  Localiza a posicao da Raposa.
    verifica_posicao_R(tabuleiro,&LRi,&CRi);
    if(direcao_valida(Lf,Cf,LRi,CRi) != -1){ 
      
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
    if(tabuleiro[Lf][Cf] != 'R' && tabuleiro[LOi][COi] != 'R'){
      //  Situacao em que a coordenada digitada é para realizar um movimento.
      if(direcao_valida(Lf,Cf,LOi,COi) != -1 && realiza_movimento(jogador, tabuleiro, Lf, Cf, LOi, COi) == 1){
        return(1);
      }
    }
  }
  return(-1);
}

//------------------------

//  Funcao que verifica se a jogada realizada pela raposa permite uma nova jogada, com a condicao de
//que seja para "comer" outra peca.
void R_nova_jogada(char tabuleiro[9][9], char jogador){
  int aux, Lf, Cf, LRi, CRi, i, j;
  int x, y; //  variaveis descartaveis
  int k; // contabilizador de gansos possiveis de comer

  //  Localiza a posicao  Raposa.
  verifica_posicao_R(tabuleiro, &LRi, &CRi);

  // Verifica se ha a possibilidade da raposa comer mais um ganso.
  do{
    k = 0;
    for(i = -1; i <= 1; i++){
      for(j = -1; j <=1; j++){
        if(verifica_come_ganso(tabuleiro, LRi+i, CRi+j, &x, &y) == 1){
          k++;
        }
      }
    }

    if(k != 0){
      //  Pergunta ao jogador se este deseja comer ou nao mais um ganso, caso seja possivel.
      do{
        system("clear");
        imprime_tabuleiro(tabuleiro);
        printf("Eh possivel comer mais ganso(s), deseja comer?\nDigite 1 para 'sim' e 2 para 'nao'.\n");
        scanf("%d", &aux);
      }while(aux != 1 && aux != 2);
    
      //  Caso o jogador escolher sim, este deve digitar a coordenada do ganso ao qual deseja comer.
      if(aux == 1){
        do{
          printf("Digite a casinha do ganso.\n");
          scanf("%d %d", &Lf, &Cf);
        }while(tabuleiro[Lf][Cf] != 'O' || come_ganso(tabuleiro,Lf,Cf) != 1);
      }

      //  Localiza a posicao da Raposa.
      verifica_posicao_R(tabuleiro, &LRi, &CRi);
    
      //  Caso a escolha seja nao, a funcao nao retorna nada e a jogada vai para os gansos.
      if(aux == 2){
        return;
      }
    }
  }while(k != 0);

  return;
}

//------------------------

//  Funcao que verifica se ha gansos a serem comidos - utilizada para o jogo contra maquina.
int verif_come_ganso_tipo2(char tabuleiro[9][9]){
  int LRi, CRi, aux = 0;
  int i, j, k, h, x = 0; //  variaveis contabilizadoras dos fors

  //  Vetor que possui as direcoes possiveis, em que a ordem acompanha a variacao do for.
  int direcoes[] = {7, 8, 9, 4, -1, 6, 1, 2, 3};

  verifica_posicao_R(tabuleiro, &LRi, &CRi); // Localiza a Raposa

  // Loops com a condicao para que a direcao do movimento seja valido (verificacao feita para todas as
  //casas ao redor da Raposa), caso lah possua um ganso, e atras dele um espaco vago ('.').
  for(i = -1; i <= 1; i++){
    for(j = -1; j <= 1; j++){
      k = (abs(i)+1) * i;
      h = (abs(j)+1) * j;
      if((direcao_valida(LRi+i,CRi+j,LRi,CRi) == direcoes[x] && tabuleiro[LRi+i][CRi+j]  == 'O' && tabuleiro[LRi+k][CRi+h] == '.')){
        aux++; // contabiliza os gansos disponiveis para comer.
      }
      x++;
    }
  }

  //  Caso haja gansos disponiveis para se comer.
  if(aux != 0){
    return(1);
  }
  // Caso contrario.
  return(0);
}

//------------------------

//  Funcao que realiza os movimentos da raposa, quando esta tem a possibilidade de comer um
//ganso - utilizada para o jogo contra maquina.
//  OBS: as coordenadas finais (Lf, Cf) sao selecionadas de acordo com a posicao inicial da Raposa.
int come_ganso_tipo2(char tabuleiro[9][9]){
  int LRi, CRi, Lf, Cf;
  int i, j, k, h, x = 0; //  variaveis utilizadas nos fors

  //  Vetor que possui as direcoes possiveis, em que a ordem acompanha a variacao do for.
  int direcoes[] = {7, 8, 9, 4, -1, 6, 1, 2, 3};

  //  Localiza a Raposa.
  verifica_posicao_R(tabuleiro, &LRi, &CRi);
  // Loops que verificam a possibilidade da Raposa comer um ou mais gansos (de acordo com a direcao que
  //o ganso estah em relacao a Raposa) e realiza este movimento.
  for(i = -1; i <= 1; i++){
    for(j = -1; j <= 1; j++){
      k = (abs(i)+1) * i;
      h = (abs(j)+1) * j;
      if((direcao_valida(LRi+i,CRi+j,LRi,CRi) == direcoes[x] && tabuleiro[LRi+i][CRi+j]  == 'O' && tabuleiro[LRi+k][CRi+h] == '.')){
        tabuleiro[LRi][CRi] = '.';
        tabuleiro[LRi+i][CRi+j] = '.';
        tabuleiro[LRi+k][CRi+h] = 'R';
        espera(0.4); // pausa para poder enxergar a Raposa comendo um ou mais gansos.
        system("clear");
        imprime_tabuleiro(tabuleiro);
        return(1);
      }
      x++;
    }
  }

  //  Caso nao haja nenhum ganso disponivel para comer.
  return(-1);
}

//------------------------

// Funcao que verifica se em jogadas futuras havera a possibilidade de comer um ou mais gansos e devolve a quantidade possivel.
int procura_ganso(char tabuleiro[9][9], int Lf, int Cf, int gansos_validos[8][3]){
  int i, j, k, direcao;
  k = 0;  //  Contabilizador de quantidade de gansos.
  
  //  Loop que verifica se ha gansos ao redor da possivel nova casa da Raposa, e se houver, salva as coordenadas destes 
  //gansos e a direcao para qual a Raposa ira se mover para comer o ganso, caso esteja em sua possivel nova casa.
  for(i = -1; i <= 1; i++){
    for(j = -1; j <= 1; j++){
      if(tabuleiro[Lf+i][Cf+j] == 'O'){
        direcao = direcao_valida(Lf+i, Cf+j, Lf, Cf);
        if(direcao != -1){
          gansos_validos[k][0] = Lf+i;
          gansos_validos[k][1] = Cf+j;
          gansos_validos[k][2] = direcao;
          k++;
        }
      }
    }
  }

  return(k);
}

//------------------------

/*  Funcao que aleatoriza as posicoes proximas a posicao inicial da Raposa, procura gansos proximos
 que poderao ser comidos em futuros movimentos, verifica a possibilidade de come-los, se ha mais de 
 uma possibilidade para comer, e informa a melhor posicao para realizar o movimento, realizando ele
 logo em seguida.
  PRIORIDADES PARA O MOVIMENTO DA RAPOSA:
 1 _ casinha que futuramente poderah comer, pelo menos, um ganso (ha dois gansos que podem ser 'comidos').
 2 _ casinha que ha um ganso que futuramente poderah ser comido, caso nao seja movido.
 3 _ casinha em que ha um ganso por perto - centralizada no tabuleiro.
 4 _ casinha em que ha um ganso por perto - qualquer uma das boas posicoes.
 5 _ sorteio com probabilidade de 70% para casinhas centralizadas no tabuleiro e 30% para casinhas da ponta.*/
int estrategias_raposa(char tabuleiro[9][9]){
  int Lf, Cf, LRi, CRi, i, j, k, h, gansos_validos[8][3], qnt_gansos, L, C, posicoes_nao_comiveis[56][2], posicoes_boas[56][2];
  float sorteio;
  j = 0;
  k = 0;
  h = 0;

  //  Localiza a Raposa
  verifica_posicao_R(tabuleiro, &LRi, &CRi);

  //  Loop que aleatoriza posicoes vazias proximas a posicao inicial da Raposa.
  for(Lf = LRi - 1; Lf <= LRi + 1; Lf++){
    for(Cf = CRi - 1; Cf <= CRi + 1; Cf++){
      
      //  Condicao para que uma possivel posicao final seja valida em relacao a posicao final (da Raposa).
      if(tabuleiro[Lf][Cf] == '.' && movimento_valido(tabuleiro, Lf, Cf, LRi, CRi) == 1){

        //  Procura gansos proximos a posicao referente ao loop.
        qnt_gansos = procura_ganso(tabuleiro, Lf, Cf, gansos_validos);
        //  Verifica se a quantidade de gansos proximos, a posicao em questao, eh diferente de zero.
        if(qnt_gansos != 0){

          //  Loop que verifica se atras do ganso, proximo a posicao em questao, eh passivel de ser comido
          //(ha uma casa vazia "atras" dele) e adiciona a posicao desse ganso a uma lista.
          for(i = 0; i < qnt_gansos; i++){
            L = gansos_validos[i][0];
            C = gansos_validos[i][1];

            if((gansos_validos[i][2] == 8 && tabuleiro[L-1][C] == '.') || (gansos_validos[i][2] == 2 && tabuleiro[L+1][C] == '.') || (gansos_validos[i][2] == 4 && tabuleiro[L][C-1] == '.') || (gansos_validos[i][2] == 6 && tabuleiro[L][C+1] == '.') || (gansos_validos[i][2] == 7 && tabuleiro[L-1][C-1] == '.') || (gansos_validos[i][2] == 9 && tabuleiro[L-1][C+1] == '.') || (gansos_validos[i][2] == 3 && tabuleiro[L+1][C+1] == '.') || (gansos_validos[i][2] == 1 && tabuleiro[L+1][C-1] == '.')){
              posicoes_boas[j][0] = Lf;
              posicoes_boas[j][1] = Cf;
              j++;
            }
            else{
              posicoes_nao_comiveis[h][0] = Lf;
              posicoes_nao_comiveis[h][1] = Cf;
              h++;
            }
          }
        }
      }
    }
  }

  //  Caso nao existam posicoes boas que possuam possibilidade de futuramente comer ganso(s), serah avaliada
  //as posicoes que apenas estao perto de um ou mais gansos.
  if(j == 0){
    for(k = 0; k < h; k++){
      posicoes_boas[k][0] = posicoes_nao_comiveis[k][0];
      posicoes_boas[k][1] = posicoes_nao_comiveis[k][1];
    }
    j = h;
  }

  //  Caso a posicao boa se refira a posicao da Raposa, ela serah descartada e a matriz com as posicoes boas eh reordenada.
  for(k = 0; k < j; k++){
    if(posicoes_boas[k][0] == LRi && posicoes_boas[k][1] == CRi){
      i = k;
      for(h = k + 1; h < j; h++){
        posicoes_boas[i][0] = posicoes_boas[h][0];
        posicoes_boas[i][1] = posicoes_boas[h][1];
        i++;
      }
      j = i;
    }
  }

  //  Loop que verifica se ha posicoes repetidas na listagem de gansos possiveis de serem comidos em
  //futuras jogadas. Se dois delas forem iguais essa se torna uma boa posicao para se mover.
  //  OBS: o loop só serah realizado se houver gansos em alguma posicao ao redor da Raposa (j != 0).
  for(i = 0; i < j; i++){
    for(k = i+1; k < j; k++){
      if(posicoes_boas[i][0] == posicoes_boas[k][0] && posicoes_boas[i][1] == posicoes_boas[k][1]){
        Lf = posicoes_boas[i][0];
        Cf = posicoes_boas[i][1];
        realiza_movimento('R', tabuleiro, Lf, Cf, LRi, CRi);
        return(1);
      }
    }
  }

  //  Caso não haja repeticoes de posicoes, eh escolhida uma da lista, com base na preferência em
  //permanecer no centro do tabuleiro.
  //  OBS: o loop soh serah realizado se houver gansos em alguma posicao ao redor da Raposa.
  for(i = 0; i < j; i++){
    if(posicoes_boas[i][0] >= 3 && posicoes_boas[i][0] <= 5 && posicoes_boas[i][1] >= 3 && posicoes_boas[i][1] <= 5){
      Lf = posicoes_boas[i][0];
      Cf = posicoes_boas[i][1];
      realiza_movimento('R', tabuleiro, Lf, Cf, LRi, CRi);
      return(1);
    }
  }

  //  Caso não haja repeticoes de posicoes, eh escolhida uma da lista, de forma aleatoria.
  //  OBS: soh serah realizado se houver gansos em alguma posicao ao redor da Raposa (j != 0).
  if(j != 0){
    i = rand() % j;  
    Lf = posicoes_boas[i][0];
    Cf = posicoes_boas[i][1];
    realiza_movimento('R', tabuleiro, Lf, Cf, LRi, CRi);
    return(1);
  }
  
  //  Caso nao exista nenhum ganso nas casas adjascentes, será feito um sorteio para casas aleatorias,
  //com probabilidade maior para o centro (entre 2 e 6).
  sorteio = rand() % 1;

  do{
    if(1 < LRi && LRi < 7 && 1 < CRi && CRi < 7){
      //  Caso de movimento aleatorio no centro do tabuleiro.
      if(sorteio <= 0.7){
        do{
          Lf = rand() % 6;
          Cf = rand() % 6;
        } while(Lf < 3 && Cf < 3);
      }
    
      //  Caso a propabilidade menor seja sorteada a Raposa se moverah para qualquer casa valida das pontas do tabuleiro.
      else{
        do{
          Lf = rand() % 8;
          Cf = rand() % 8;
        } while(Lf > 2 && Lf < 6 && Cf > 2 && Cf < 6);
      }
    }

    else{
      do{
        Lf = rand() % 7;
        Cf = rand() % 7;
      } while(Lf < 2 && Cf < 2);
    }
    
  }while(movimento_valido(tabuleiro, Lf, Cf, LRi, CRi) != 1);
  
  //  Realiza o movimento sorteado. 
  realiza_movimento('R', tabuleiro, Lf, Cf, LRi, CRi);
  return(1);
}

//------------------------

//  Funcao principal.
int main(){
  //  Nas matrizes que formam o tabuleiro, acrescentamos duas linhas e colunas a mais, preenchidas com " ", para 
  //que durante as verificacoes, não sejam considerados movimentos validos, aqueles feitos para linhas e colunas 
  //no lado oposto do tabuleiro. Como, por exemplo, uma Raposa que na casinha 3 7 quer comer um ganso na 4 1, 
  //mesmo ele estando do outro lado.
  char tabuleiro[9][9] = {"         ","   ...   ","   ...   "," O..R..O ", " O.....O ", " OOOOOOO ","   OOO   ", "   OOO   ","         "}; 
  char tabuleiro_reserva[9][9] = {"         ","   ...   ","   ...   "," O..R..O ", " O.....O ", " OOOOOOO ","   OOO   ", "   OOO   ","         "};

  //  Sumario das declaracoes:
  // Lf = Linha final; Cf = Coluna final; LOi = Linha inicial do ganso; COi = Coluna inicial do ganso;
  //RMA = rodadas maximas atingidas; i e j = contadores; coord e aux = variaveis auxiliares.
  int tipo_jogo, Lf, Cf, LOi, COi, rodada, RMA, i, j, coord, aux;
  
  //  Variaveis que guardam, respectivamente, qual jogador da partida (O ou R) e seu nome:
  char jogador;
  char nome_jogador[10];

  //Chama a funcao que imprime as regras do jogo
  regras(tabuleiro); 

  //  Escolha do tipo de jogo (contra amigo ou maquina).
  do{
    printf("Leia atentamente as regras do jogo e selecione um meio de jogar: \nDigite 1: contra amigo\nDigite 2: contra maquina\n");
    scanf("%d", &tipo_jogo);
  }while(tipo_jogo != 1 && tipo_jogo != 2);

  // Jogo contra amigo
  if(tipo_jogo == 1){
    system("clear");
    printf("\nTIPO ESCOLHIDO: CONTRA AMIGO\n");
    espera(1);
    
    //  Enquanto nao atingir a quantidade de rodadas maximas, preh definidas, o jogo permanece rodando.
    for(rodada = 1; rodada < MAX; rodada++){

	    //  O Jogo inicia, as rodadas impares sao da raposa e as pares dos ganso.
      if(rodada % 2 == 1){
		    jogador = 'R';
        strcpy(nome_jogador, "DA RAPOSA");
	    }
      else{
        strcpy(nome_jogador, "DO GANSO");
		    jogador = 'O';
	    }
      
      //  Apos a vigesima jogada se inicia a contagem dos gansos, equanto houver mais que 4 gansos o jogo continua,
      //  caso houver exatamente 4 gansos, ou menos, a raposa eh a vencedora.
	    if(jogador == 'O' && rodada > WIN && verifica_n_O(tabuleiro) < 5) {
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
			    printf("\t    \t    VEZ %s\nDigite os valores para a casinha inicial:\n", nome_jogador);
			    scanf("%d", &LOi);
			    scanf("%d", &COi);
			    LOi--;
			    COi--;
          printf("Agora para a casinha final:\n");
		    }

        //  Solicitacao de digito para a coordenada final do movimento e realizacao do mesmo.
          if(jogador == 'R'){
            printf("\t    \t    VEZ %s:\nDigite os valores para a casinha final:\n", nome_jogador);
          }
		      scanf("%d", &Lf);
		      scanf("%d", &Cf);
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

  // Jogo contra a maquina
  if(tipo_jogo == 2){
    
    // Gerar um numero aleatorio todas as vezes que abrir o programa.
    srand(time(NULL));

    system("clear");
    printf("\nTIPO ESCOLHIDO: CONTRA A MAQUINA\n");
    espera(1);

    //  Enquanto nao atingir a quantidade de rodadas maximas, preh definidas, o jogo permanece rodando.
    for(rodada = 1; rodada <= MAX; rodada++){

	    //  O Jogo inicia, as rodadas impares sao da raposa e as pares dos gansos.
      if(rodada % 2 == 1){
		    jogador = 'R';
	    }
      else{
        strcpy(nome_jogador, "DO GANSO");
		    jogador = 'O';
	    }
      
      //  Apos a vigesima jogada se inicia a contagem dos gansos, equanto houver mais que 4 gansos o jogo continua,
      //  caso houver exatamente 4 gansos, a raposa eh a vencedora.
	    if(jogador == 'O' && rodada > WIN && verifica_n_O(tabuleiro) < 5) {
		    system("clear");
		    imprime_tabuleiro(tabuleiro);
		    printf("VOCE PERDEU, TENTE NOVAMENTE!!\n");
		    return(0);
	    }

      //  Verifica se a Raposa nao possui mais jogadas e define os Gansos como vencedores.
	    if(jogador == 'R' && ganso_ganhou(jogador,tabuleiro,Lf,Cf) == 1) {
		    system("clear");
		    imprime_tabuleiro(tabuleiro);
		    printf("\t\tPARABENS!! VOCE GANHOU!!\n");
		    return(0);
	    } 

      system("clear");
		  imprime_tabuleiro(tabuleiro);

      //  Caso seja a vez dos Gansos, ele terah que digitar a coordenada de qual ganso deseja alterar a posicao.
	    if(jogador == 'O'){
  	    do{
			    printf("\t    \t    VEZ %s\nDigite os valores para a casinha inicial:\n", nome_jogador);
			    scanf("%d", &LOi);
			    scanf("%d", &COi);
          
          printf("Agora para a casinha final:\n");
		      scanf("%d", &Lf);
		      scanf("%d", &Cf);  
          
          //  Verificacao da coordenada (valida = 1, invalida = -1).
  		    coord = verifica_coord(tabuleiro, jogador, Lf, Cf, LOi, COi);
	      }while(coord == -1);
      }

      //  Vez da Raposa - serah feitas verificacoes (funcoes) para realizar a jogada.
      if(jogador == 'R'){

        //  Auxiliar para saber se a Raposa realizou o movimento de comer um ganso.
        aux = 0;

        //  Condicao para a Raposa poder comer um ganso.
        if(verif_come_ganso_tipo2(tabuleiro) == 1){
          aux = 1;

          //  Condicao do-while para que a Raposa coma quantos gansos estiverem disponiveis.
          do{
            come_ganso_tipo2(tabuleiro);
          }while(verif_come_ganso_tipo2(tabuleiro) == 1 && come_ganso_tipo2(tabuleiro) == 1);
        }
        //  Caso não seja possivel comer, ira realizar um movimento em alguma direcao, utilizando de estrategias.
        if(aux == 0){
          coord = estrategias_raposa(tabuleiro);
        }
      }

      //  Caso o numero maximo de rodadas permitidas tenha sido atingido.
	    if(rodada == MAX){
		    system("clear");
		    imprime_tabuleiro(tabuleiro);
       
        //  Eh perguntado se o jogador deseja continuar o jogo ou reiniciah-lo.
        do{
			    printf("Numero de rodadas maximas atingidas. Deseja continuar?\nDigite 1 para continuar.\nDigite 2 para reiniciar o jogo.\n");
			    scanf("%d", &RMA);
		    }while((RMA != 1 || RMA == 2) && (RMA == 1 || RMA != 2));
		    system("clear");
		    rodada = 1;
		    jogador = 'R';

        //  Eh reiniciado o jogo, limpando o tabuleiro e reiniciando as jogadas
		    if(RMA == 2){
			    for(i = 0; i < 7; i++){
				    for(j = 0; j < 7; j++){
					    tabuleiro[i][j] = tabuleiro_reserva[i][j];
				    }
			    }
			    printf("\n\t\t\tJOGO REINICIADO!\n");
          espera(1);
   		    rodada = 2;
        }
      }
    }
  }

  return(0);
}