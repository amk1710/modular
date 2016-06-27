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
*     Implementa o tipo de dados carta, e gera uma variável do tipo lista
*        que será preenchida por variáveis do tipo carta.
*
*     O baralho não será embaralhado, mas retornará uma carta aleatória 
*        quando for pedido, e a mesma será retirada da lista.
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
   void INT_InicializaJogo( tpElemLista* jogadores , 
   								Equipe* equipeA , 
   								Equipe* equipeB ) ;

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
   void INT_ExibirMesa( tpElemLista* Descarte ) ;

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
*     0 para caso tenha prosseguido com a jogada.
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
*     retorna 2 caso tenha recusado,
*     retorna 3 caso tenha retrucado.
*
***********************************************************************/
   int INT_ResponderTruco() ;