 /* **************************************************************************
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
************************************************************************** */

#include "LISTA.h"
#include "GERAALT.h"

#include <stdlib.h>

#define BARALHO_OWN
#include "BARALHO.h"
#undef BARALHO_OWN

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   static void LimparBaralho( LIS_tppLista Baralho );
   static void PlaceholderLista( BAR_tpCarta * carta );
   static void ExcluirCarta( void* carta );
   static BAR_tpNaipes BAR_IncrementarNaipe(BAR_tpNaipes Naipe);
   static BAR_tpValores BAR_IncrementarValor(BAR_tpValores Valor);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: BAR  &Criar Baralho
*  ****/

   LIS_tppLista BAR_CriarBaralho( )
   {
	   LIS_tppLista baralho;

	   baralho = LIS_CriarLista( ExcluirCarta );
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
	   BAR_tpCarta * carta;
	   int numeroAleatorio,
		   tamanhoBaralho;

	   tamanhoBaralho = LIS_NumerodeElementos(Baralho);

	   ALT_Inicializar( 1 );
	   numeroAleatorio = ALT_GerarDistUniforme( 0, tamanhoBaralho );

	   IrInicioLista( Baralho );
	   LIS_AvancarElementoCorrente( Baralho, numeroAleatorio );
	   carta = (BAR_tpCarta*) LIS_ObterValor( Baralho );

	   if( carta != NULL )
	   {
		   LIS_ExcluirElemento( Baralho );
	   }

	   return *carta;
   } /* Fim fun*��o: BAR &Pedir Carta */

/***************************************************************************
*
*  Fun��o: BAR  &Devolver Carta
*  ****/

   LIS_tpCondRet BAR_DevolverCarta( LIS_tppLista Baralho ,
	                                BAR_tpCarta Carta     )
   {
	   LIS_tpCondRet condRet;
	   int numeroAleatorio ,
		   tamanhoBaralho;

	   tamanhoBaralho = LIS_NumerodeElementos(Baralho);

	   ALT_Inicializar( 1 );
	   numeroAleatorio = ALT_GerarDistUniforme( 0, tamanhoBaralho );

	   IrInicioLista( Baralho );
	   LIS_AvancarElementoCorrente( Baralho, numeroAleatorio );
	   condRet = LIS_InserirElementoApos( Baralho, &Carta );

	   return condRet;
   } /* Fim fun��o: BAR &Devolver Carta */

/***************************************************************************
*
*  Fun��o: BAR  &Setar Baralho
*  ****/

   LIS_tpCondRet BAR_SetarBaralho( LIS_tppLista Baralho )
   {
	   BAR_tpNaipes naipe;
	   BAR_tpValores valor;
	   LIS_tpCondRet resultado;
	   BAR_tpCarta* novaCarta ;

	   IrInicioLista( Baralho );
	   if( LIS_NumerodeElementos(Baralho) > 0 ){
		   LimparBaralho( Baralho );
	   }

	   for( naipe = BAR_Paus; naipe <= BAR_Ouros; naipe++)
	   {
		   for( valor = BAR_As; valor < BAR_Coringa; valor++ )
		   {
			   

			   novaCarta = ( BAR_tpCarta * ) malloc( sizeof( BAR_tpCarta )) ;
			   if( novaCarta == NULL )
			   {
				   return LIS_CondRetFaltouMemoria;
			   } /* if */
			   novaCarta->naipe = naipe;
			   novaCarta->valor = valor;
			   resultado = LIS_InserirElementoApos( Baralho, novaCarta );
			   if( resultado == LIS_CondRetFaltouMemoria )
			   {
			       return LIS_CondRetFaltouMemoria;
			   }
		   } /* for */
	   } /* for */

	   // Primeiro Joker
	   novaCarta = ( BAR_tpCarta * ) malloc( sizeof( BAR_tpCarta )) ;
	   if( novaCarta == NULL )
		{
				   return LIS_CondRetFaltouMemoria;
		} /* if */
	   novaCarta->naipe = BAR_Paus;
	   novaCarta->valor = BAR_Coringa;
	   resultado = LIS_InserirElementoApos( Baralho, novaCarta );
		if( resultado == LIS_CondRetFaltouMemoria )
		{
			return LIS_CondRetFaltouMemoria;
		} /* if */

		// segundo Joker
		novaCarta = ( BAR_tpCarta * ) malloc( sizeof( BAR_tpCarta )) ;
	   if( novaCarta == NULL )
		{
				   return LIS_CondRetFaltouMemoria;
		} /* if */
	   novaCarta->naipe = BAR_Paus;
	   novaCarta->valor = BAR_Coringa;
	   resultado = LIS_InserirElementoApos( Baralho, novaCarta );
		if( resultado == LIS_CondRetFaltouMemoria )
		{
			return LIS_CondRetFaltouMemoria;
		} /* if */

		// fim jokers 

	   return LIS_CondRetOK;
   } /* Fim fun��o: BAR &Setar Baralho */

/***************************************************************************
*
*  Fun��o: BAR  &Setar Baralho Truco
*  ****/

   LIS_tpCondRet BAR_SetarBaralhoTruco( LIS_tppLista Baralho )
   {
	   BAR_tpNaipes naipe;
	   BAR_tpValores valor;

	   LIS_tpCondRet resultado;
	   BAR_tpCarta* novaCarta;

	   IrInicioLista( Baralho );
	   if( LIS_NumerodeElementos(Baralho) > 0 ){
		   LimparBaralho( Baralho );
	   }

	   for( naipe = BAR_Paus; naipe <= BAR_Ouros; naipe++)
	   {
		   for( valor = BAR_As; valor <= BAR_Rei; valor++ )
		   {
			   if( valor != BAR_Oito && valor != BAR_Nove && valor != BAR_Dez )
			   {
				   

				   novaCarta = ( BAR_tpCarta * ) malloc( sizeof( BAR_tpCarta )) ;
				   if( novaCarta == NULL )
				   {
					   return LIS_CondRetFaltouMemoria;
				   } /* if */
				   novaCarta->naipe = naipe;
				   novaCarta->valor = valor;
				   resultado = LIS_InserirElementoApos( Baralho, novaCarta );
				   if( resultado == LIS_CondRetFaltouMemoria )
				   {
					   return LIS_CondRetFaltouMemoria;
				   }
			   }
		   } /* for */
	   } /* for */
	   return LIS_CondRetOK;
   } /* Fim fun��o: BAR &Setar Baralho Truco */

/***************************************************************************
*
*  Fun��o: BAR  &Destruir Baralho
*  ****/

   void BAR_DestruirBaralho( LIS_tppLista Baralho )
   {
	   LIS_DestruirLista( Baralho );
	   free( Baralho );
   } /* Fim fun��o: BAR &Destruir Baralho
/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

/***********************************************************************
*
*  $FC Fun��o: BAR - Limpar Baralho
*
*  $ED Descri��o da fun��o
*     Recebe um ponteiro para uma lista, atribui a fun��o ExcluirCarta
*        ao atributo ExcluirValor e chama a LIS_EsvaziarLista. Depois, 
*        volta a atribuir a PlaceholderLista ao ExcluirValor.
*
***********************************************************************/

   void LimparBaralho( LIS_tppLista Baralho )
   {
	   LIS_EsvaziarLista( Baralho );
   }

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
	   return ;
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

   void ExcluirCarta( void * carta )
   {
	   free( carta );
   } /* Fim fun��o: BAR - Excluir Carta */

/***********************************************************************
*
*  $FC Fun��o: BAR - Incrementar Naipe
*
*  $ED Descri��o da fun��o
*     Incrementa naipe segundo a ordem: paus->copas->espadas->ouros->paus
*
***********************************************************************/


   static BAR_tpNaipes BAR_IncrementarNaipe(BAR_tpNaipes Naipe)
   {
	   if(Naipe == BAR_Paus) return BAR_Copas;
	   if(Naipe == BAR_Copas) return BAR_Espadas;
	   if(Naipe == BAR_Espadas) return BAR_Ouros;
	   if(Naipe == BAR_Ouros) return BAR_Paus;
   }

   /***********************************************************************
*
*  $FC Fun��o: BAR - Incrementar valor
*
*  $ED Descri��o da fun��o
*     incrementa valor de carta segundo a ordem As->...->10->J->Q->K->A
*		Joker se incrementa para si mesmo.
*
***********************************************************************/



   static BAR_tpValores BAR_IncrementarValor(BAR_tpValores Valor)
   {
	   if(Valor == BAR_Coringa) return BAR_Coringa;
	   if(Valor == BAR_Rei) return BAR_As;
	   if(Valor == BAR_As) return BAR_Dois;
	   if(Valor == BAR_Dois) return BAR_Tres;
	   if(Valor == BAR_Tres) return BAR_Quatro;
	   if(Valor == BAR_Quatro) return BAR_Cinco;
	   if(Valor == BAR_Cinco) return BAR_Seis;
	   if(Valor == BAR_Seis) return BAR_Sete;
	   if(Valor == BAR_Sete) return BAR_Oito;
	   if(Valor == BAR_Oito) return BAR_Nove;
	   if(Valor == BAR_Nove) return BAR_Dez;
	   if(Valor == BAR_Dez) return BAR_Valete;
	   if(Valor == BAR_Valete) return BAR_Rainha;
	   if(Valor == BAR_Rainha) return BAR_Rei;

   }

   //fim baralho.c