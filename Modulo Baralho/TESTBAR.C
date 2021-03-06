/***************************************************************************
M�dulo de implementa��o dos testes do m�dulo baralho
***************************************************************************/

#include    <stdio.h>
#include    <string.h>
#include    <stdlib.h>
#include    <math.h>

#include    "TESTBAR.H"

#include    "generico.h"
#include    "LerParm.h"

#include    "LISTA.h"
#include    "BARALHO.h"


#define   ERRO_LER       ">>>"

static int Vet[ DIM_VET + 1 ] ;

static char InicializarTeste [ ] = "=inicializar" ;
static char TestarSetarBaralho[ ] = "=testarsetarbaralho" ;
static char TestarSetarBaralhoTruco [ ] = "=testarsetarbaralhotruco" ;
static char TestarCompra[ ]  = "=testarcompra" ;
static char TestarDevolucao[ ]  = "=testardevolucao" ;
static char TestarDestruir[ ] = "=testardestruir" ;

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/



/*****  C�digo das fun��es exportadas pelo m�dulo  *****/





/*
Comandos de Teste:					Parametros:
=inicializar						
=testarsetarbaralho
=testarsetarbaralhotruco
=testarcompra						
=testardevolucao					int, int


=inicializar - inicializa o modulo baralho e cria o baralho usado nos testes
=testarsetarbaralho - seta o baralho para um baralho convencional
=testarsetarbaralhotruco - seta o baralho para um baralho de truco
=testarcompra - usa um baralho setado. Compra uma carta e registra seu valor no log de teste
=testardevolucao - devolve a carta passada para o baralho



*/

/***********************************************************************
*
*  $FC Fun��o: TALT &Efetuar o teste de fun��o do m�dulo aleatorio
*
***********************************************************************/


LIS_tppLista baralho;
//baralho usado pelos testes


   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int numLidos ;
	  int valorCarta;
	  int naipeCarta;
	  tagCarta* carta;

      /* Testar Inicializar modulo baralho */

         if ( strcmp( ComandoTeste , TestarInicializarCmd ) == 0 )
         {

            
            BAR_Inicializar() ;

			baralho = BAR_CriarBaralho();

            return TST_CondRetOK ;

         } /* fim ativa: Testar Inicializar modulo baralho */

      /* Testar  setar baralho*/

         else if ( strcmp( ComandoTeste , TestarSetarBaralho ) == 0 )
         {

            if(BAR_SetarBaralho(baralho) == LIS_CondRetOK) return TST_CondRetOK;
			else return TST_CondRetMemoria;

         } /* fim ativa: Testar setar baralho */

      /* Testar setar baralho de truco */

         else if ( strcmp( ComandoTeste , TestarSetarBaralhoTruco ) == 0 )
         {

            if(BAR_SetarBaralhoTruco(baralho) == LIS_CondRetOK) return TST_CondRetOK;
			else return TST_CondRetMemoria;

         } /* fim ativa: Testar setar baralho truco */

		 /* Testar comprar carta */

         else if ( strcmp( ComandoTeste , TestarCompra ) == 0 )
         {

            carta = BAR_PedirCarta(baralho);
			if(carta == NULL) return TST_CondRetErro;
			else
			{
				if(carta->naipe != NULL) fprintf( TST_ObterArqLog( ) , "Naipe: %d Valor: %d \n", carta->naipe, carta->valor) ;
				else fprintf( TST_ObterArqLog( ) , "Naipe: Joker Valor: %d \n", carta->valor) ;
			}
			return TST_CondRetOK;


         } /* fim ativa: Testar compra */

		 
		 /* Testar devolu��o de cartas*/

         else if ( strcmp( ComandoTeste , TestarDevolucao ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" , &naipeCarta, &valorCarta ) ;

            if (  numLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

			carta = (tagCarta*) malloc(sizeof(tagCarta));

			carta->naipe = naipeCarta;
			valor->carta = valorCarta;

			if(BAR_DevolverCarta(baralho, carta) == LIS_CondRetFaltouMemoria) return TST_CondRetMemoria;
			else return TST_CondRetOK;



         } /* fim ativa: Testar destruir */


		 else if ( strcmp( ComandoTeste , TestarDestruir ) == 0 )
         {

           BAR_DestruirBaralho(baralho);
		   return TST_CondRetOK;



         } /* fim ativa: Testar destruir */

		 

      return TST_CondRetNaoConhec ;


   } /* Fim fun��o: TALT &Efetuar o teste de fun��o do m�dulo aleatorio */


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/










/********** Fim do m�dulo de implementa��o: TBAR Teste do m�dulo Baralho **********/

