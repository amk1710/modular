/***************************************************************************
Módulo de implementação dos testes do módulo baralho
***************************************************************************/

#include    <stdio.h>
#include    <string.h>
#include    <stdlib.h>
#include    <math.h>

#include    "TST_ESPC.H"

#include    "generico.h"
#include    "LerParm.h"

#include    "LISTA.h"
#include    "BARALHO.h"


#define   ERRO_LER       ">>>"


static char CriarBaralho [ ] = "=criarbaralho" ;
static char TestarSetarBaralho[ ] = "=testarsetarbaralho" ;
static char TestarSetarBaralhoTruco [ ] = "=testarsetarbaralhotruco" ;
static char CompararCompra [ ] = "=compararcompra" ;
static char TestarCompra[ ]  = "=testarcompra" ;
static char TestarDevolucao[ ]  = "=testardevolucao" ;
static char TestarDestruir[ ] = "=testardestruir" ;

/***********************************************************************
*
*  $FC Função: TBAR &Testar baralho
*
*  $ED Descrição da função
*     Realiza testes em cima de um baralho.
*
*     Comandos disponíveis:
*
*     =criarbaralho
*     =testarsetarbaralho           CondRetEsp
*     =testarsetarbaralhotruco      CondRetEsp
*     =compararcompra               Naipe     Valor
*     =testarcompra					CondretEsp
*     =testardevolucao              Naipe     Valor   CondRetEsp
*     =testardestruir               
*
***********************************************************************/





/***********************************************************************
*
*  $FC Função: TALT &Efetuar o teste de função do módulo aleatorio
*
***********************************************************************/


LIS_tppLista baralho;
//baralho usado pelos testes


   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int numLidos = -1;
	  int valorCarta;
	  int naipeCarta;

	  BAR_tpCarta* carta;
	  BAR_tpCarta cartaNaoP;

	  int CondRetEsp = -1  ;
	  int ValEsp = -1 ;
	  TST_tpCondRet CondRet ;


      /* Testar criar baralho*/

		 if ( strcmp( ComandoTeste , CriarBaralho ) == 0 )
         {
			 baralho = BAR_CriarBaralho();
			 return TST_CompararPonteiroNulo( 1 , baralho ,
               "Erro em ponteiro de novo baralho."  ) ;

         } /* fim ativa: Testar criar baralho */

		/* Testar setar baralho*/

         else if ( strcmp( ComandoTeste , TestarSetarBaralho ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &CondRetEsp ) ;

            if (  numLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRet = BAR_SetarBaralho(baralho);

			return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno ao setar baralho"                   ) ;


         } /* fim ativa: Testar setar baralho */

      /* Testar setar baralho de truco */

         else if ( strcmp( ComandoTeste , TestarSetarBaralhoTruco ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &CondRetEsp ) ;

            if (  numLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRet = BAR_SetarBaralhoTruco(baralho);

			return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno ao setar baralho de truco"                   ) ;

         } /* fim ativa: Testar setar baralho truco */

		 /* Testar comparar compra */

         else if ( strcmp( ComandoTeste , CompararCompra ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                               &naipeCarta, &valorCarta ) ;

            if (  numLidos != 2 || naipeCarta > 3 || naipeCarta < 0 || valorCarta < 0 || valorCarta > 13 )
            {
               return TST_CondRetParm ;
            } /* if */

			carta = BAR_PedirCarta(baralho);

			if(carta->naipe != naipeCarta || carta->valor != valorCarta)
			{
				return TST_CondRetErro;
			}

			else return TST_CondRetOK;

         } /* fim ativa: Testar comparar compra */


		 /* Testar comprar carta */

         else if ( strcmp( ComandoTeste , TestarCompra ) == 0 )
         {

			numLidos = LER_LerParametros( "i" ,
                       &ValEsp ) ;

            if ( numLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

			carta = BAR_PedirCarta(baralho);
			
			if((carta != NULL) && carta->valor != BAR_Coringa)
			{		
				fprintf( TST_ObterArqLog( ) , "Naipe: %d Valor: %d \n", carta->naipe, carta->valor) ;
				return TST_CondRetOK;
			}
			else if	(carta != NULL)
			{
				fprintf( TST_ObterArqLog( ) , "Naipe: Coringa Valor: %d \n", carta->valor);
				return TST_CondRetOK;
			}
			else return TST_CondRetErro;


         } /* fim ativa: Testar compra */

		 
		 /* Testar devolução de cartas*/

         else if ( strcmp( ComandoTeste , TestarDevolucao ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" ,
					&naipeCarta, &valorCarta, &CondRetEsp ) ;

            if (  numLidos != 3 || naipeCarta > 3 || naipeCarta < 0 || valorCarta < 0 || valorCarta > 13 )
            {
               return TST_CondRetParm ;
            } /* if */

			carta = (BAR_tpCarta*) malloc(sizeof(BAR_tpCarta));

			
			if(carta == NULL)
			{
				return TST_CondRetMemoria;
			}

			carta->naipe =  naipeCarta;
			carta->valor =  valorCarta;

			


			CondRet = BAR_DevolverCarta(baralho, carta);

			return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno ao setar baralho de truco"                   ) ;


         } /* fim ativa: Testar destruir */


		 else if ( strcmp( ComandoTeste , TestarDestruir ) == 0 )
         {

           BAR_DestruirBaralho(baralho);
		   return TST_CondRetOK;



         } /* fim ativa: Testar destruir */

		 

      return TST_CondRetNaoConhec ;


   } /* Fim função: TBAR &Efetuar o teste do módulo baralho */





/********** Fim do módulo de implementação: TBAR Teste do módulo Baralho **********/

