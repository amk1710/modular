/***************************************************************************
*  $MCI Módulo de implementação: BAR  Controlador do Tipo Baralho
*
*  Arquivo gerado:              BARALHO.c
*  Letras identificadoras:      BAR
*
*  Nome da base de software:    Implementação de jogo de truco
*  Arquivo da base de software: \Fontes\ARCABOUC.BSW
*
*  Projeto: INF 1301 / T2 Programação Modular
*  Gestor:  LES/DI/PUC-Rio
*  Autores: ausm
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       ausm  07/mai/2016  Início desenvolvimento
***************************************************************************/
#include <LISTA.h>
#include <GERAALT.h>

#define BARALHO_OWN
#include "BARALHO.h"
#undef BARALHO_OWN

/***** Protótipos das funções encapuladas no módulo *****/

   static void LimparBaralho( LIS_tppLista Baralho );
   static void PlaceholderLista( BAR_tpCarta * carta );
   static void ExcluirCarta( BAR_tpCarta * carta );

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: BAR  &Criar Baralho
*  ****/

   LIS_tppLista BAR_CriarBaralho( )
   {
	   LIS_tppLista baralho = NULL;

	   baralho = LIS_CriarLista( & ExcluirCarta );
	   if( baralho == NULL )
	   {
		   return NULL;
	   } /* if */

	   return baralho;
   }  /* Fim função: BAR  &Criar Baralho */

/***************************************************************************
*
*  Função: BAR  &Pedir Carta
*  ****/

   BAR_tpCarta BAR_PedirCarta( LIS_tppLista Baralho )
   {
	   BAR_tpCarta * carta = NULL;
	   int numeroAleatorio = NULL ,
		   tamanhoBaralho = NULL   ;

	   tamanhoBaralho = Baralho.numElem;

	   ALT_Inicializar( 0 );
	   numeroAleatorio = ALT_GerarDistUniforme( 0, tamanhoBaralho );

	   IrInicioLista( Baralho );
	   LIS_AvancarElementoCorrente( Baralho, numeroAleatorio );
	   carta = LIS_ObterValor( Baralho );

	   if( carta != NULL )
	   {
		   LIS_ExcluirElemento( Baralho );
	   }

	   return carta;
   } /* Fim função: BAR &Pedir Carta */

/***************************************************************************
*
*  Função: BAR  &Devolver Carta
*  ****/

   LIS_tpCondRet BAR_DevolverCarta( LIS_tppLista Baralho ,
	                                BAR_tpCarta Carta     )
   {
	   LIS_tpCondRet * condRet = NULL;
	   int numeroAleatorio = NULL ,
		   tamanhoBaralho = NULL   ;

	   tamanhoBaralho = Baralho.numElem;

	   ALT_Inicializar( 0 );
	   numeroAleatorio = ALT_GerarDistUniforme( 0, tamanhoBaralho );

	   IrInicioLista( Baralho );
	   LIS_AvancarElementoCorrente( Baralho, numeroAleatorio );
	   condRet = LIS_InserirElementoApos( Baralho, Carta );

	   return condRet;
   } /* Fim função: BAR &Devolver Carta */

/***************************************************************************
*
*  Função: BAR  &Setar Baralho
*  ****/

   LIS_tpCondRet BAR_SetarBaralho( LIS_tppLista Baralho )
   {
	   BAR_tpNaipe naipe = NULL;
	   BAR_tpValores valor = NULL;

	   IrInicioLista( Baralho );
	   if( Baralho.numElem > 0 ){
		   LimparBaralho( Baralho );
	   }

	   for( naipe = BAR_Paus; naipe <= BAR_Ouros; naipe++ )
	   {
		   for( valor = BAR_As; valor <= BAR_Coringa; valor++ )
		   {
			   LIS_tpCondRet resultado = NULL;
			   BAR_tpCarta novaCarta = NULL;

			   novaCarta = ( BAR_tpCarta * ) malloc( sizeof( BAR_tpCarta )) ;
			   if( novaCarta == NULL )
			   {
				   return LIS_CondRetFaltouMemoria;
			   } /* if */
			   novaCarta.naipe = naipe;
			   novaCarta.valor = valor;
			   resultado = LIS_InserirElementoApos( Baralho, novaCarta );
			   if( resultado == LIS_CondRetFaltouMemoria )
			   {
			       return LIS_CondRetFaltouMemoria;
			   }
		   } /* for */
	   } /* for */

	   return LIS_CondRetOK;
   } /* Fim função: BAR &Setar Baralho */

/***************************************************************************
*
*  Função: BAR  &Setar Baralho Truco
*  ****/

   LIS_tpCondRet BAR_SetarBaralhoTruco( LIS_tppLista Baralho )
   {
	   BAR_tpNaipe naipe = NULL;
	   BAR_tpValores valor = NULL;

	   IrInicioLista( Baralho );
	   if( Baralho.numElem > 0 ){
		   LimparBaralho( Baralho );
	   }

	   for( naipe = BAR_Paus; naipe <= BAR_Ouros; naipe++ )
	   {
		   for( valor = BAR_As; valor <= BAR_Rei; valor++ )
		   {
			   if( valor != BAR_Oito && valor != BAR_Nove && valor != BAR_Dez )
			   {
				   LIS_tpCondRet resultado = NULL;
				   BAR_tpCarta novaCarta = NULL;

				   novaCarta = ( BAR_tpCarta * ) malloc( sizeof( BAR_tpCarta )) ;
				   if( novaCarta == NULL )
				   {
					   return LIS_CondRetFaltouMemoria;
				   } /* if */
				   novaCarta.naipe = naipe;
				   novaCarta.valor = valor;
				   resultado = LIS_InserirElementoApos( Baralho, novaCarta );
				   if( resultado == LIS_CondRetFaltouMemoria )
				   {
					   return LIS_CondRetFaltouMemoria;
				   }
			   }
		   } /* for */
	   } /* for */
	   return LIS_CondRetOK;
   } /* Fim função: BAR &Setar Baralho Truco */

/***************************************************************************
*
*  Função: BAR  &Destruir Baralho
*  ****/

   void BAR_DestruirBaralho( LIS_tppLista Baralho )
   {
	   Baralho.ExcluirValor = & ExcluirCarta;
	   LIS_DestruirLista( Baralho );
	   free( Baralho );
   } /* Fim função: BAR &Destruir Baralho

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: BAR - Limpar Baralho
*
*  $ED Descrição da função
*     Recebe um ponteiro para uma lista, atribui a função ExcluirCarta
*        ao atributo ExcluirValor e chama a LIS_EsvaziarLista. Depois, 
*        volta a atribuir a PlaceholderLista ao ExcluirValor.
*
***********************************************************************/

   void LimparBaralho( LIS_tppLista Baralho )
   {
	   Baralho.ExcluirValor = & ExcluirCarta;
	   LIS_EsvaziarLista( Baralho );
	   Baralho.ExcluirValor = & PlaceholderLista;
   }

/***********************************************************************
*
*  $FC Função: BAR - Placeholder Lista
*
*  $ED Descrição da função
*     Recebe um ponteiro para uma carta e não faz nada. Serve
*        para ser passada à função BAR_CriaLista e é chamada pelo módulo
*        lista sempre que um elemento é removido.
*
***********************************************************************/

   void PlaceholderLista( BAR_tpCarta * carta )
   {
	   return 0;
   } /* Fim função: BAR - Placeholder Lista

/***********************************************************************
*
*  $FC Função: BAR - Excluir Carta
*
*  $ED Descrição da função
*     Libera espaço de memória ocupado por uma carta.
*        Só deve ser passada ao tipo LIS_tppLista quando o baralho for 
*        destruído.
*
***********************************************************************/

   void ExcluirCarta( BAR_tpCarta * carta )
   {
	   free( carta );
   } /* Fim função: BAR - Excluir Carta