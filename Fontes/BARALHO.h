#if ! defined( BARALHO_ )
#define BARALHO_
/***************************************************************************
*
*  $MCD Módulo de definição: BAR Controlador do Tipo Baralho
*
*  Arquivo gerado:              BARALHO.h
*  Letras identificadoras:      BAR
*
*  Nome da base de software:    Implementação de jogo de truco
*  Arquivo da base de software: \Fontes\BARALHO.h
*
*  Projeto: INF 1301 / T2 Programação Modular
*  Gestor:  LES/DI/PUC-Rio
*  Autores: ausm
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data      Observações
*     1       ausm  07/mai/2016  início desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa o tipo de dados carta, e gera uma variável do tipo lista
*        que será preenchida por variáveis do tipo carta.
*
*     O baralho não será embaralhado, mas retornará uma carta aleatória 
*        quando for pedido, e a mesma será retirada da lista.
*
***************************************************************************/
 
#if defined( BARALHO_OWN )
   #define BARALHO_EXT
#else
   #define BARALHO_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/***********************************************************************
*
*  $TC Tipo de dados: BAR Naipes do Baralho
*
*
*  $ED Descrição do tipo
*     Uma contante para cada naipe do baralho francês
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
*  $ED Descrição do tipo
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
*  $ED Descrição do tipo
*     Um atributo para o naipe e um para o valor. Cartas com o naipe 
*        nulo serão reconhecidas como coringas.
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
*  $FC Função: BAR  &Criar Baralho
*
*  $ED Descrição da função
*     Cria uma lista duplamente encadeada vazia.
*
*  $EP Parâmetros
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído.
*                     Ver descrição do módulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista.
*     Este ponteiro será utilizado pelas funções que manipulem o baralho.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/
   LIS_tppLista BAR_CriarBaralho(
             void   ( * ExcluirValor ) ( void * pDado ) ) ;

/***********************************************************************
*
*  $FC Função: BAR  &Pedir Carta
*
*  $ED Descrição da função
*     Retoorna um elemento aleatório na lista informada e o retira do baralho
*
*  $EP Parâmetros
*     Baralho  - Um ponteiro para uma lista de cartas.
*
*  $FV Valor retornado
*     Se executou corretamente retorna um ponteiro para uma carta.
*
*     Se ocorreu algum erro ou o baralho estiver vazio, retornará NULL.
*
***********************************************************************/
   BAR_tpCarta BAR_PedirCarta( LIS_tppLista * Baralho ) ;

/***********************************************************************
*
*  $FC Função: BAR  &Devolver Carta
*
*  $ED Descrição da função
*     Devolve uma carta ao baralho.
*
*  $EP Parâmetros
*     LIS_tppLista - Ponteiro para a cabeça da lista baralho
*
*     BAR_tpCarta - Variável do tipo carta
*
*  $FV Valor retornado
*     Retorna um uma condição de retorno global do módulo lista, 
*        LIS_CondRetOK se tudo ocorreu bem, 
*        LIS_CondRetFaltouMemoria se ocorrer algum erro por falta de memória.
*
*     Essa função não impede que uma carta já existente no baralho seja 
*        inserida novamente.
*
***********************************************************************/
   LIS_tpCondRet BAR_DevolverCarta( LIS_tppLista * Baralho ,
	                           BAR_tpCarta Carta       ) ;

/***********************************************************************
*
*  $FC Função: BAR  &Setar Baralho
*
*  $ED Descrição da função
*     Preenche uma lista do tipo LIS_tppLista com as 54 cartas convencionais 
*        do baralho, incluindo dois coringas.
*
*  $EP Parâmetros
*     LIS_tppLista - Ponteiro para a cabeça da lista baralho
*
*  $FV Valor retornado
*     Retorna um uma condição de retorno global do módulo lista, 
*        LIS_CondRetOK se tudo ocorreu bem, 
*        LIS_CondRetFaltouMemoria se ocorrer algum erro por falta de memória.
*
*     Se o baralho não estiver vazio será limpo antes de iniciar o preenchimento.
*
***********************************************************************/
   LIS_tpCondRet BAR_SetarBaralho( LIS_tppLista * Baralho ) ;

/***********************************************************************
*
*  $FC Função: BAR  &Setar Baralho Truco
*
*  $ED Descrição da função
*     Preenche uma lista do tipo LIS_tppLista com as 40 cartas do jogo 
*        de truco.
*
*  $EP Parâmetros
*     LIS_tppLista - Ponteiro para a cabeça da lista baralho
*
*  $FV Valor retornado
*     Retorna um uma condição de retorno global do módulo lista, 
*        LIS_CondRetOK se tudo ocorreu bem, 
*        LIS_CondRetFaltouMemoria se ocorrer algum erro por falta de memória.
*
*     Se o baralho não estiver vazio será limpo antes de iniciar o preenchimento.
*
***********************************************************************/
   LIS_tpCondRet BAR_SetarBaralhoTruco( LIS_tppLista * Baralho ) ;

/***********************************************************************
*
*  $FC Função: BAR  &Destruir Baralho
*
*  $ED Descrição da função
*     Destroi o baralho
*
*  $EP Parâmetros
*     LIS_tppLista - Ponteiro para a cabeça da lista baralho
*
*  $FV Valor retornado
*     Libera a memória de cada carta do baralho e da própria estrutura ao final.
*
***********************************************************************/
   void BAR_DestruirBaralho( LIS_tppLista * Baralho ) ;

