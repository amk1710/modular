/***************************************************************************
*  $MCI Módulo de implementação: INT Controlador da Interface do Usuário
*
*  Arquivo gerado:              INTERFACE.c
*  Letras identificadoras:      INT
*
*  Nome da base de software:    Implementação de jogo de truco
*  Arquivo da base de software: \Fontes\INTERFACE.BSW
*
*  Projeto: INF 1301 / T2 Programação Modular
*  Gestor:  LES/DI/PUC-Rio
*  Autores: ausm
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       ausm  21/JUN/2016  Início desenvolvimento
***************************************************************************/

#include "LISTA.h"
#include "CONTROLADOR.h"
#include "BARALHO.h"

#include <stdlib.h>
#include <stdio.h>

#define INTERFACE_OWN
#include "INTERFACE.h"
#undef INTERFACE_OWN

/***** Protótipos das funções encapuladas no módulo *****/

   static void ExibeTitulo() ;
   static void MostraCartas( LIS_tppLista cartas ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: INT  &Inicializa Jogo
*****/

   void INT_InicializaJogo( LIS_tppLista jogadores , 
                           CON_tpEquipe equipeA , 
                           CON_tpEquipe equipeB )
   {
      LIS_tpCondRet condRet;

      int quantidadeJogadores,
          equipes;

      CON_tpMaoJogador jogador;

      printf("Informe o número de jogadores:\n");
      while( quantidadeJogadores == NULL )
      {
         scanf("%u", quantidadeJogadores);
         if( (quantidadeJogadores%2) != 0 || quantidadeJogadores > 6 )
         {
            printf("O número de jogadores deve ser 2, 4 ou 6\n");
            quantidadeJogadores = NULL;
         } else if( quantidadeJogadores == 0 )
         {
            return;
         } /* if */
      } /* while */

      equipes = 0;
      while( equipes < 2 )
      {
         if( equipes == 0 )
         {
            printf("Informe o nome da equipe A:\n");
            scanf("%s", equipeA->Nome);
         } else
         {
            printf("Informe o nome da equipe B:\n");
            scanf("%s", equipeB->Nome);
         } /* if */
         printf("Informe os nomes dos jogadores (devem ser %d jogadores):\n", (quantidadeJogadores/2));
         for( int i = 0; i < (quantidadeJogadores / 2); i++ )
         {
            jogador = (CON_tpMaoJogador*) malloc(sizeof(CON_tpMaoJogador));
            scanf("%s", jogador->Nome);
            jogador->Equipe = ( equipes == 0 )?equipeA->Nome:equipeB->Nome;
            condRet = LIS_InserirElementoApos( jogadores, jogador );
            if( condRet != LIS_CondRetOK )
            {
               return;
            } /* if */
         } /* for */
         equipes++;
      } /* while */

      equipeA->Pontuacao = 0;
      equipeB->Pontuacao = 0;
   }  /* Fim função: INT  &Inicializa Jogo */

/***************************************************************************
*
*  Função: INT  &Exibir Mesa
*****/

   void INT_ExibirMesa( LIS_tppLista Descarte )
   {
      printf("|************************************************************|\n|                           MESA                             |\n ************************************************************\n");

      MostraCartas( Descarte );
   } /* Fim Função: INT &Exibir Mesa */

/***************************************************************************
*
*  Função: INT  &Exibe Mão
*****/

   void INT_ExibeMao( LIS_tppLista jogadores )
   {
      CON_tpMaoJogador jogadorAtual;

      jogadorAtual = LIS_ObterValor( jogadores );
      printf("|************************************************************|\n|                           %s\n ************************************************************\n", jogadorAtual->Nome );
      MostraCartas( jogadorAtual->Cartas );

   } /* Fim Função: INT &Exibe Mão */

/***************************************************************************
*
*  Função: INT  &Faz Jogada
*****/

   BAR_tpCarta * INT_Fazjogada( LIS_tppLista jogadores )
   {
      int quantidadeCartas, 
          escolhida;

      CON_tpMaoJogador jogador;


      jogador = LIS_ObterValor( jogadores );

      quantidadeCartas = LIS_NumerodeElementos( jogador->Cartas );

      printf("Digite o número correspondente à ordem em que a carta aparece na tela:\n");
      while( escolhida == NULL )
      {
         scanf("%d", escolhida);
         if( escolhida > quantidadeCartas + 1 )
         {
            printf("Você informou um número maior que a quantidade de cartas!\n");
            escolhida = NULL;
         } /* if */
      } /* while */

      IrInicioLista( jogador->Cartas );
      LIS_AvancarElementoCorrente( jogador->Cartas, escolhida - 1 );
      return LIS_ObterValor( jogador->Cartas );
   } /* Fim Função: INT &Faz Jogada */
 

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: INT - Mostra Cartas
*
*  $ED Descrição da função
*     Recebe uma cabeça de lista com elementos do tipo BAR__tpCarta
*     e imprime na tela de maneira padronizada.
*
***********************************************************************/
   void MostraCartas( LIS_tppLista Cartas )
   {
      BAR_tpCarta * carta;
      int quatindade;
      char * output;

      quantidade = LIS_NumerodeElementos( Cartas );
      IrInicioLista( Cartas );

      output = (char *) malloc( 62 * sizeof(char) );
      for( int i = 0; i < quantidade; i++ )
      {
         carta = LIS_ObterValor( Cartas );

         switch( carta->valor)
         {
            case BAR_As:
               strcpy( output, "Ás" );
               break;
            case BAR_Dois:
               strcpy( output, "2" );
               break;
            case BAR_Tres:
               strcpy( output, "3" );
               break;
            case BAR_Quatro:
               strcpy( output, "4" );
               break;
            case BAR_Cinco:
               strcpy( output, "5" );
               break;
            case BAR_Seis:
               strcpy( output, "6" );
               break;
            case BAR_Sete:
               strcpy( output, "7" );
               break;
            case BAR_Valete:
               strcpy( output, "Valete" );
               break;
            case BAR_Rainha:
               strcpy( output, "Rainha" );
               break;
            case BAR_Rei:
               strcpy( output, "Rei" );
               break;
         } /* switch */
         strcat( output, " de " );
         switch( carta->naipe )
         {
            case BAR_Paus:
               strcat( output, "Paus" );
               break;
            case BAR_Copas:
               strcat( output, "Copas" );
               break;
            case BAR_Espadas:
               strcat( output, "Espadas" );
               break;
            case BAR_Ouros:
               strcat( output, "Ouros" );
               break;
         } /* switch */
         printf( " || %s ||", output ); // no máximo 23 caracteres
         if( i % 2 == 0 )
         {
            printf("\n");
         } /* if */
         LIS_AvancarElementoCorrente( Cartas, 1 );
      } /* for */
   } /* Fim Função: INT &Mostra Cartas