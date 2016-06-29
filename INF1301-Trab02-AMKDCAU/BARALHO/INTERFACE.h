#if ! defined( INTERFACE_ )
#define INTERFACE_

/***************************************************************************
*
*  $MCD Módulo de definição: INT Controlador da Interface do Usuário
*
*  Arquivo gerado:              INTERFACE.h
*  Letras identificadoras:      INT
*
*  Nome da base de software:    Implementação de jogo de truco
*  Arquivo da base de software: \Fontes\INTERFACE.h
*
*  Projeto: INF 1301 / T2 Programação Modular
*  Gestor:  LES/DI/PUC-Rio
*  Autores: ausm
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data      Observações
*     1       ausm  20/JUN/2016  início desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa a interface do usuário.
*
***************************************************************************/
 
#if defined( INTERFACE_OWN )
   #define INTERFACE_EXT
#else
   #define INTERFACE_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/***********************************************************************
*
*  $FC Função: INT  &Inicializa Jogo
*
*  $ED Descrição da função
*     Inicializa a estrutura com as equipes, lista de jogadores e pontuação.
*
*  $FV Valor retornado
*     
*
***********************************************************************/
   void INT_InicializaJogo( LIS_tppLista jogadores , 
   								CON_tpEquipe equipeA , 
   								CON_tpEquipe equipeB ) ;

/***********************************************************************
*
*  $FC Função: INT  &Exibir Mesa
*
*  $ED Descrição da função
*     Exibe as cartas que foram jogadas na mesa e por quais jogadores até então.
*
*  $FV Valor retornado
*     Exibido na tela
*
***********************************************************************/
   void INT_ExibirMesa( LIS_tppLista Descarte ) ;

/***********************************************************************
*
*  $FC Função: INT  &Exibe Mão
*
*  $ED Descrição da função
*     Exibe as cartas da mão do jogador
*
*  $FV Valor retornado
*     Exibido na tela
*
***********************************************************************/
   void INT_ExibeMao( LIS_tppLista jogadores ) ;

/***********************************************************************
*
*  $FC Função: INT  &Faz Jogada
*
*  $ED Descrição da função
*     Dá ao jogador a opção de escolher a carta que irá jogar
*
*  $FV Valor retornado
*     Ponteiro para a carta escolhida.
*
***********************************************************************/
   Carta* INT_Fazjogada( LIS_tppLista jogadores ) ;

/***********************************************************************
*
*  $FC Função: INT  &Pedir Truco
*
*  $ED Descrição da função
*     Exibe a opção de Pedir Truco ou Prosseguir com a jogada.
*
*  $FV Valor retornado
*     Valor de retorno: 1 para caso tenho pedido truco, 
*        0 para caso tenha prosseguido com a jogada.
*
***********************************************************************/
   int INT_PedirTruco() ;

/***********************************************************************
*
*  $FC Função: INT  &Responder Truco
*
*  $ED Descrição da função
*     Recebe a escolha do jogador: Aceitar, Recusar ou Retrucar.
*
*  $FV Valor retornado
*     1 caso tenha aceitado, 
*        retorna 2 caso tenha recusado,
*        retorna 3 caso tenha retrucado.
*
***********************************************************************/
   int INT_ResponderTruco() ;

/***********************************************************************
*
*  $FC Função: INT  &Terminar Rodada
*
*  $ED Descrição da função
*     Exibe o nome do jogador que ganhou aquela rodada, e a sua equipe. Em
*	      casos de empate exibe que aquela rodada não teve vencedor.
*
*  $FV Valor retornado
*     
*
***********************************************************************/
   void INT_TerminarRodada( LIS_tppLista jogadores ) ;

/***********************************************************************
*
*  $FC Função: INT  &Terminar Mão
*
*  $ED Descrição da função
*     Exibe a equipe que venceu aquela mão, e quantos pontos ela marcou.
*
*  $FV Valor retornado
*     
*
***********************************************************************/
   void INT_TerminarMao( CON_tpEquipe equipe, int * pontuacao ) ;

/***********************************************************************
*
*  $FC Função: INT  &Terminar Jogo
*
*  $ED Descrição da função
*     Exibe a equipe que venceu aquela mão, e quantos pontos ela marcou.
*
*  $FV Valor retornado
*     
*
***********************************************************************/
   void INT_TerminarJogo( CON_tpEquipe equipeVenceu, CON_tpEquipe equipePerdeu ) ;

#undef INTERFACE_EXT

/********** Fim do módulo de definição: INT Controlador da Interface do Usuário **********/

#else
#endif