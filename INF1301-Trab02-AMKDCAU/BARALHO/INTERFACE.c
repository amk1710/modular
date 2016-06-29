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

#include <stdlib.h>
#include <stdio.h>

#define INTERFACE_OWN
#include "INTERFACE.h"
#undef INTERFACE_OWN

/***** Protótipos das funções encapuladas no módulo *****/

   static void ExibeTitulo() ;

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
            printf("Informe os jogadores da equipe A:\n");
         } else
         {
            printf("Informe os jogadores da equipe B\n");
         } /* if */
         printf("(devem ser %d jogadores", (quantidadeJogadores/2));
         for( int i = 0; i < (quantidadeJogadores / 2); i++ )
         {
            jogador = (CON_tpMaoJogador*) malloc(sizeof(CON_tpMaoJogador));
            scanf("%s", jogador->Nome);
            jogador->Equipe = ( equipes == 0 )?'A':'B';
            condRet = LIS_InserirElementoApos( jogadores, jogador );
            if( condRet != LIS_CondRetOK )
            {
               return;
            } /* if */
         } /* for */
      } /* while */
      equipeA->Nome = 'A';
      equipeA->Pontuacao = 0;

      equipeB->Nome = 'B';
      equipeB->Pontuacao = 0;
   }  /* Fim função: INT  &Inicializa Jogo