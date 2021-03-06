/***************************************************************************
*  $MCI M�dulo de implementa��o: TALT Teste do gerador de n�meros aleat�rios
*
*  Arquivo gerado:              TESTALT.c
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: C:\AUTOTEST\PROJETOS\ARCABOUC.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     4       avs   01/fev/2006 criar linguagem script simb�lica
*     3       avs   08/dez/2004 uniformiza��o dos exemplos
*     2       avs   07/jul/2003 unifica��o de todos os m�dulos em um s� projeto
*     1       avs   16/abr/2003 in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Testa e exemplifica o uso do gerador de n�meros aleat�rios
*
***************************************************************************/

#include    <stdio.h>
#include    <string.h>
#include    <math.h>

#include    "TESTALT.H"

#include    "generico.h"
#include    "LerParm.h"

#include    "GERAALT.h"

#define   NUM_POR_LINHA  5
#define   NUM_GERA       10000000
#define   NUM_GERA_FLOAT 10000000.0
#define   DIM_VET   100

#define   ERRO_LER       ">>>"

static int Vet[ DIM_VET + 1 ] ;

static char TestarInicializarCmd[ ] = "=inicializar" ;
static char ExibirUniformeCmd[   ]  = "=exibiruniforme" ;
static char ExibirFrequenciaCmd[ ]  = "=exibirfrequencia" ;
static char TestarPermutacaoCmd[ ]  = "=exibirpermutacao" ;

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   static TST_tpCondRet ExibirPermutacao( ) ;

   static void ExibirDistribuicao( double numGera ,  int Inf , int Sup , char * Mensagem ) ;

   static void ZerarVetor( void ) ;

   static TST_tpCondRet ExibirUniforme( void ) ;

   static TST_tpCondRet ExibirFrequencia( void ) ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/





/*
Comandos de Teste:					Parametros:
=inicializar						int
=exibir uniforme
=exibirfrequencia
=exibirpermuta��o






*/

/***********************************************************************
*
*  $FC Fun��o: TALT &Efetuar o teste de fun��o do m�dulo aleatorio
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      unsigned int Semente ;
      int      numLidos ;

      /* Testar Inicializar gerador de n�meros aleat�rios */

         if ( strcmp( ComandoTeste , TestarInicializarCmd ) == 0 )
         {

            numLidos = LER_LerParametros( "i" , &Semente ) ;
            if ( numLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            ALT_Inicializar( Semente ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar Inicializar gerador de n�meros aleat�rios */

      /* Testar distribui��o uniforme */

         else if ( strcmp( ComandoTeste , ExibirUniformeCmd ) == 0 )
         {

            return ExibirUniforme( ) ;

         } /* fim ativa: Testar distribui��o uniforme */

      /* Testar distribui��o freq��ncias */

         else if ( strcmp( ComandoTeste , ExibirFrequenciaCmd ) == 0 )
         {

            return ExibirFrequencia( ) ;

         } /* fim ativa: Testar distribui��o freq��ncias */

      /* Testar permuta��o rand�mica */

         else if ( strcmp( ComandoTeste , TestarPermutacaoCmd ) == 0 )
         {

            return ExibirPermutacao( ) ;

         } /* fim ativa: Testar permuta��o rand�mica */

      return TST_CondRetNaoConhec ;

   } /* Fim fun��o: TALT &Efetuar o teste de fun��o do m�dulo aleatorio */


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TALT -Exibir permuta��o rand�mica uniformemente distribu�da
*
***********************************************************************/

   TST_tpCondRet ExibirPermutacao( )
   {

      int Vetor[ DIM_VET ] ;

      int numGera  = -1 ,
          numLidos = -1 ,
          numElem  = -1  ;

      int i ;

      /* Ler par�metros do vetor */

         numLidos = LER_LerParametros( "ii" , &numGera , &numElem ) ;
         if ( ( numLidos != 2 )
           || ( numGera  <  1 )
           || ( numElem  <  2 )
           || ( numElem  >  DIM_VET ))
         {
            return TST_CondRetParm ;
         } /* if */

      /* Embaralhar vetor */

         for( i = 0 ; i < numElem ; i++ )
         {
            Vetor[ i ] = i ;
         } /* for */

         ALT_GerarPermutacao( numElem , Vetor ) ;

      /* Exibir Permuta��o */

         fprintf( TST_ObterArqLog( ) , "\n\nPermuta��o" ) ;

         for( i = 0 ; i < numElem ; i ++ )
         {
            fprintf( TST_ObterArqLog( ) , " %4d" , Vetor[ i ] ) ;
         } /* for */
         fprintf( TST_ObterArqLog( ) , "\n" ) ;

      return TST_CondRetOK ;

   } /* Fim fun��o: TALT -Exibir permuta��o rand�mica uniformemente distribu�da */


/***********************************************************************
*
*  $FC Fun��o: TALT -Exibir distribuicao
*
***********************************************************************/

   void ExibirDistribuicao( double numGera ,  int Inf , int Sup , char * Mensagem )
   {

      int i ,
          j ;

      double A ;


      fprintf( TST_ObterArqLog( ) , "\n\n%s, contagem\n" , Mensagem ) ;

      j = 0 ;

      for ( i = Inf ; i <= Sup ; i++ )
      {
         if ( j % NUM_POR_LINHA == 0 )
         {
            fprintf( TST_ObterArqLog( ) , "\n" ) ;
         }
         j++ ;
         fprintf( TST_ObterArqLog( ) , " %4d = %6d" , i , Vet[ i ] ) ;
      } /* for */

      fprintf( TST_ObterArqLog( ) , "\n\n%s, fra��o do total gerado\n" , Mensagem ) ;

      j = 0 ;

      for ( i = Inf ; i <= Sup ; i++ )
      {
         if ( j % NUM_POR_LINHA == 0 )
         {
            fprintf( TST_ObterArqLog( ) , "\n" ) ;
         }
         j++ ;
         A = Vet[ i ] ;
         A = A / numGera ;
         fprintf( TST_ObterArqLog( ) , " %4d= %7lf" , i , A ) ;
      } /* for */

      fprintf( TST_ObterArqLog( ) , "\n\n" ) ;

   } /* Fim fun��o: TALT -Exibir distribuicao */


/***********************************************************************
*
*  $FC Fun��o: TALT -Zerar vetor de n�meros gerados
*
***********************************************************************/

   void ZerarVetor( void )
   {

      int i ;

      for ( i = 0 ; i <= DIM_VET ; i++ )
      {
         Vet[ i ] = 0 ;
      } /* for */

   } /* Fim fun��o: TALT -Zerar vetor de n�meros gerados */


/***********************************************************************
*
*  $FC Fun��o: TALT -Exibir distribui��o uniforme
*
***********************************************************************/

   TST_tpCondRet ExibirUniforme( void )
   {

      int numLidos = 0  ,
          numGera  = 0  ,
          Inf      = -1 ,
          Sup      = -1 ,
          i ;

      double DesvioEsp  = 0. ,
             Tolerancia = 0.  ;


      double MediaEsperada,
             Desvio       ,
             A             ;

      /* Ler par�metros distribui��o uniforme */

         numLidos = LER_LerParametros( "iiiff" , &numGera , &Inf , &Sup ,
                                       &DesvioEsp , &Tolerancia ) ;

         if ( ( numLidos != 5 )
           || ( numGera < 2   )
           || ( Inf     < 0   )
           || ( Inf     > Sup )
           || ( Sup     > DIM_VET ))

         {
            return TST_CondRetParm ;
         } /* if */

      /* Gerar distribui��o uniforme */

         ZerarVetor( ) ;

         for ( i = 0 ; i < numGera ; i++ )
         {
            Vet[ ALT_GerarDistUniforme( Inf , Sup ) ] ++ ;
         } /* for */

      /* Calcular m�dia e desvio padr�o uniforme */

         MediaEsperada = ( 1. / ( Sup - Inf + 1 )) ;

         Desvio        = 0. ;

         for( i = Inf ; i <= Sup ; i ++ )
         {
            A = Vet[ i ] ;
            A = A / numGera ;

            Desvio      += pow( ( A - MediaEsperada ) , 2 ) ;
         } /* for */

         Desvio        = sqrt( Desvio ) ;

         fprintf( TST_ObterArqLog( ) , "\n\n   Desvio: %8lf" ,
                  Desvio ) ;

      /* Exibir distribui��o uniforme */

         ExibirDistribuicao( numGera , Inf , Sup , "Distribui��o uniforme." ) ;

         return TST_CompararFloat( DesvioEsp , Desvio , Tolerancia ,
                  "Desvio discrepa muito." ) ;

   } /* Fim fun��o: TALT -Exibir distribui��o uniforme */


/***********************************************************************
*
*  $FC Fun��o: TALT -Exibir distribui��o de freq��ncias
*
***********************************************************************/

   TST_tpCondRet ExibirFrequencia( void )
   {

      int numLidos = -1 ,
          numGera  = -1 ,
          numElem  = -1 ,
          Anterior ,
          Limite   ,
          i ;

      int vetElem[ DIM_VET + 1 ]  ;

      /* Ler par�metros freq��ncias */

         numLidos = LER_LerParametros( "ii" , &numGera , &Limite ) ;
         if ( ( numLidos != 2 )
           || ( numGera  < 10 )
           || ( Limite   < 10 ))
         {
            return TST_CondRetParm ;
         } /* if */

         numElem  = 0 ;

         Anterior = 0 ;

         while ( LER_LerParmInt( &( vetElem[ numElem ] )))
         {
            if ( vetElem[ numElem ] < 0 )
            {
               break ;
            } /* if */

            if ( vetElem[ numElem ] <= Anterior )
            {
               TST_ExibirPrefixo( ERRO_LER , "Par�metro freq��ncia fora de ordem" ) ;
               return TST_CondRetParm ;
            } /* if */

            Anterior = vetElem[ numElem ] ;
            numElem ++ ;

         } /* while */

      /* Gerar tabela de freq��ncias */

         ZerarVetor( ) ;

         for ( i = 0 ; i < numGera ; i++ )
         {
            Vet[ ALT_GerarFrequencia( numElem , vetElem , Limite ) ] ++ ;
         } /* for */

         ExibirDistribuicao( numGera , 0 , numElem , "Distribui��o de freq��ncia." ) ;

      return TST_CondRetOK ;

   } /* Fim fun��o: TALT -Exibir distribui��o de freq��ncias */

/********** Fim do m�dulo de implementa��o: TALT Teste do gerador de n�meros aleat�rios **********/

