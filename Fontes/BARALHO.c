/***************************************************************************
*  $MCI M�dulo de implementa��o: BAR  Controlador do Tipo Baralho
*
*  Arquivo gerado:              BARALHO.c
*  Letras identificadoras:      BAR
*
*  Nome da base de software:    Implementa��o de jogo de truco
*  Arquivo da base de software: \Fontes\ARCABOUC.BSW
*
*  Projeto: INF 1301 / T2 Programa��o Modular
*  Gestor:  LES/DI/PUC-Rio
*  Autores: ausm
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1       ausm  07/mai/2016  In�cio desenvolvimento
***************************************************************************/
#include <LISTA.h>
#include <GERAALT.h>

#define BARALHO_OWN
#include "BARALHO.h"
#undef BARALHO_OWN

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   static void LimparBaralho( LIS_tppLista Baralho );
   static void PlaceholderLista( BAR_tpCarta * carta );
   static void ExcluirCarta( BAR_tpCarta * carta );

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: BAR  &Criar Baralho
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
   }  /* Fim fun��o: BAR  &Criar Baralho */

/***************************************************************************
*
*  Fun��o: BAR  &Pedir Carta
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
   } /* Fim fun��o: BAR &Pedir Carta */

/***************************************************************************
*
*  Fun��o: BAR  &Pedir Carta
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
   }

/***************************************************************************
*
*  Fun��o: BAR  &Setar Baralho
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
		   for( valor = BAR_As; valor <= BAR_Rei; valo++ )
		   {

		   }
	   }

   }

/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

/***********************************************************************
*
*  $FC Fun��o: BAR - Placeholder Lista
*
*  $ED Descri��o da fun��o
*     Recebe um ponteiro para uma carta e n�o faz nada. Serve
*        para ser passada � fun��o BAR_CriaLista e � chamada pelo m�dulo
*        lista sempre que um elemento � removido.
*
***********************************************************************/

   void PlaceholderLista( BAR_tpCarta * carta )
   {
	   return 0;
   } /* Fim fun��o: BAR - Placeholder Lista

/***********************************************************************
*
*  $FC Fun��o: BAR - Excluir Carta
*
*  $ED Descri��o da fun��o
*     Libera espa�o de mem�ria ocupado por uma carta.
*        S� deve ser passada ao tipo LIS_tppLista quando o baralho for 
*        destru�do.
*
***********************************************************************/

   void ExcluirCarta( BAR_tpCarta * carta )
   {
	   free( carta );
   } /* Fim fun��o: BAR - Excluir Carta