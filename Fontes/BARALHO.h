#if ! defined( BARALHO_ )
#define BARALHO_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: BAR Controlador do Tipo Baralho
*
*  Arquivo gerado:              BARALHO.h
*  Letras identificadoras:      BAR
*
*  Nome da base de software:    Implementa��o de jogo de truco
*  Arquivo da base de software: \Fontes\BARALHO.h
*
*  Projeto: INF 1301 / T2 Programa��o Modular
*  Gestor:  LES/DI/PUC-Rio
*  Autores: ausm
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data      Observa��es
*     1       ausm  07/mai/2016  in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Implementa o tipo de dados carta, e gera uma vari�vel do tipo lista
*        que ser� preenchida por vari�veis do tipo carta.
*
*     O baralho n�o ser� embaralhado, mas retornar� uma carta aleat�ria 
*        quando for pedido, e a mesma ser� retirada da lista.
*
***************************************************************************/
 
#if defined( BARALHO_OWN )
   #define BARALHO_EXT
#else
   #define BARALHO_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/***********************************************************************
*
*  $TC Tipo de dados: BAR Naipes do Baralho
*
*
*  $ED Descri��o do tipo
*     Uma contante para cada naipe do baralho franc�s
*
***********************************************************************/

   typedef enum {

         BAR_Paus ,

         BAR_Copas ,

         BAR_Espadas ,

         BAR_Ouros

   } BAR_tpNaipes ;

/***********************************************************************
*
*  $TC Tipo de dados: BAR Valores das Cartas
*
*
*  $ED Descri��o do tipo
*     Valores de dois a dez, Coringa, As, Valete, Rainha e Rei.
*
***********************************************************************/

   typedef enum {

         BAR_As ,

         BAR_Dois ,

         BAR_Tres ,

         BAR_Quatro ,

		 BAR_Cinco ,

		 BAR_Seis ,

		 BAR_Sete ,

		 BAR_Oito ,

		 BAR_Nove ,
		 
		 BAR_Dez ,

		 BAR_Valete ,

		 BAR_Rainha ,

		 BAR_Rei ,

		 BAR_Coringa

   } BAR_tpValores ;

/***********************************************************************
*
*  $TC Tipo de dados: BAR Carta de Baralho
*
*
*  $ED Descri��o do tipo
*     Um atributo para o naipe e um para o valor. Cartas com o naipe 
*        nulo ser�o reconhecidas como coringas.
*
***********************************************************************/

   typedef struct tagCarta {
	   BAR_tpNaipes naipe ;
	         /* Naipe da carta */

	   BAR_tpValores valor ;
	         /* Valor da carta */

   } BAR_tpCarta ;

/***********************************************************************
*
*  $FC Fun��o: BAR  &Criar Baralho
*
*  $ED Descri��o da fun��o
*     Cria uma lista duplamente encadeada vazia.
*
*  $EP Par�metros
*     ExcluirValor  - ponteiro para a fun��o que processa a
*                     exclus�o do valor referenciado pelo elemento
*                     a ser exclu�do.
*                     Ver descri��o do m�dulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista.
*     Este ponteiro ser� utilizado pelas fun��es que manipulem o baralho.
*
*     Se ocorreu algum erro, por exemplo falta de mem�ria ou dados errados,
*     a fun��o retornar� NULL.
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
***********************************************************************/
   LIS_tppLista BAR_CriarBaralho(
             void   ( * ExcluirValor ) ( void * pDado ) ) ;

/***********************************************************************
*
*  $FC Fun��o: BAR  &Pedir Carta
*
*  $ED Descri��o da fun��o
*     Retoorna um elemento aleat�rio na lista informada e o retira do baralho
*
*  $EP Par�metros
*     Baralho  - Um ponteiro para uma lista de cartas.
*
*  $FV Valor retornado
*     Se executou corretamente retorna um ponteiro para uma carta.
*
*     Se ocorreu algum erro ou o baralho estiver vazio, retornar� NULL.
*
***********************************************************************/
   BAR_tpCarta BAR_PedirCarta( LIS_tppLista * Baralho ) ;

/***********************************************************************
*
*  $FC Fun��o: BAR  &Devolver Carta
*
*  $ED Descri��o da fun��o
*     Devolve uma carta ao baralho.
*
*  $EP Par�metros
*     LIS_tppLista - Ponteiro para a cabe�a da lista baralho
*
*     BAR_tpCarta - Vari�vel do tipo carta
*
*  $FV Valor retornado
*     Retorna um uma condi��o de retorno global do m�dulo lista, 
*        LIS_CondRetOK se tudo ocorreu bem, 
*        LIS_CondRetFaltouMemoria se ocorrer algum erro por falta de mem�ria.
*
*     Essa fun��o n�o impede que uma carta j� existente no baralho seja 
*        inserida novamente.
*
***********************************************************************/
   LIS_tpCondRet BAR_DevolverCarta( LIS_tppLista * Baralho ,
	                           BAR_tpCarta Carta       ) ;

/***********************************************************************
*
*  $FC Fun��o: BAR  &Setar Baralho
*
*  $ED Descri��o da fun��o
*     Preenche uma lista do tipo LIS_tppLista com as 54 cartas convencionais 
*        do baralho, incluindo dois coringas.
*
*  $EP Par�metros
*     LIS_tppLista - Ponteiro para a cabe�a da lista baralho
*
*  $FV Valor retornado
*     Retorna um uma condi��o de retorno global do m�dulo lista, 
*        LIS_CondRetOK se tudo ocorreu bem, 
*        LIS_CondRetFaltouMemoria se ocorrer algum erro por falta de mem�ria.
*
*     Se o baralho n�o estiver vazio ser� limpo antes de iniciar o preenchimento.
*
***********************************************************************/
   LIS_tpCondRet BAR_SetarBaralho( LIS_tppLista * Baralho ) ;

/***********************************************************************
*
*  $FC Fun��o: BAR  &Setar Baralho Truco
*
*  $ED Descri��o da fun��o
*     Preenche uma lista do tipo LIS_tppLista com as 40 cartas do jogo 
*        de truco.
*
*  $EP Par�metros
*     LIS_tppLista - Ponteiro para a cabe�a da lista baralho
*
*  $FV Valor retornado
*     Retorna um uma condi��o de retorno global do m�dulo lista, 
*        LIS_CondRetOK se tudo ocorreu bem, 
*        LIS_CondRetFaltouMemoria se ocorrer algum erro por falta de mem�ria.
*
*     Se o baralho n�o estiver vazio ser� limpo antes de iniciar o preenchimento.
*
***********************************************************************/
   LIS_tpCondRet BAR_SetarBaralhoTruco( LIS_tppLista * Baralho ) ;

/***********************************************************************
*
*  $FC Fun��o: BAR  &Destruir Baralho
*
*  $ED Descri��o da fun��o
*     Destroi o baralho
*
*  $EP Par�metros
*     LIS_tppLista - Ponteiro para a cabe�a da lista baralho
*
*  $FV Valor retornado
*     Libera a mem�ria de cada carta do baralho e da pr�pria estrutura ao final.
*
***********************************************************************/
   void BAR_DestruirBaralho( LIS_tppLista * Baralho ) ;

