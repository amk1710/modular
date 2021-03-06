/***************************************************************************
*  $MCI M�dulo de implementa��o: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
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
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#define LISTA_OWN
#include "LISTA.H"
#undef LISTA_OWN

//inclui interfaces para uso em modo _DEBUG

#ifdef _DEBUG
   #include   "GENERICO.H"
   #include   "Conta.h"
   #include   "cespdin.h"
	#include "IdTiposEspaco.def"
#endif

/********************************************************
*
*  typedef's da cabe�a e elemento da lista
*
*********************************************************/

typedef struct tagElemLista tpElemLista;

typedef struct LIS_tagLista LIS_tpLista;





/***********************************************************************
*
*  $TC Tipo de dados: LIS Elemento da lista
*
*
***********************************************************************/

   struct tagElemLista {

         void * pValor ;
               /* Ponteiro para o valor contido no elemento */

         struct tagElemLista * pAnt ;
               /* Ponteiro para o elemento predecessor */

         struct tagElemLista * pProx ;
               /* Ponteiro para o elemento sucessor */
		
		#ifdef _DEBUG

		 LIS_tpLista * ponteiroCabeca;
				/* ponteiro para a cabe�a da lista */
		 int posicaoElementoLista;
				/* a posi��o do elemento na lista */
		#endif
   } ;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabe�a de lista
*
*
***********************************************************************/

   struct LIS_tagLista {

         tpElemLista * pOrigemLista ;
               /* Ponteiro para a origem da lista */

         tpElemLista * pFimLista ;
               /* Ponteiro para o final da lista */

         tpElemLista * pElemCorr ;
               /* Ponteiro para o elemento corrente da lista */

         int numElem ;
               /* N�mero de elementos da lista */

         void ( * ExcluirValor ) ( void * pValor ) ;
               /* Ponteiro para a fun��o de destrui��o do valor contido em um elemento */
		
		#ifdef _DEBUG

		 int numCorrente ;
				/* a posi��o na lista do elemento corrente*/
		#endif


   } ;

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   static void LiberarElemento( LIS_tppLista   pLista ,
                                tpElemLista  * pElem   ) ;

   static tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                       void *       pValor  ) ;

   static void LimparCabeca( LIS_tppLista pLista ) ;

	#ifdef _DEBUG
		void IncrementarAPartirde(tpElemLista* Elem);

		void DecrementarAPartirde(tpElemLista* Elem);

		LIS_tpCondRet LIS_VerificarElem(LIS_tpLista* pLista, tpElemLista* Elem);

	#endif

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: LIS  &Criar lista
*  ****/

   LIS_tppLista LIS_CriarLista(
             void   ( * ExcluirValor ) ( void * pDado ) )
   {

	LIS_tpLista * pLista = NULL ;

      pLista = ( LIS_tpLista * ) malloc( sizeof( LIS_tpLista )) ;

	#ifdef _DEBUG
	  CNT_CONTAR( "LIS_CriarLista_a" ) ;
	#endif

      if ( pLista == NULL )
      {
        #ifdef _DEBUG
			CNT_CONTAR( "LIS_CriarLista_b" ) ;
		#endif
		 return NULL ;
      } /* if */

      LimparCabeca( pLista ) ;

      pLista->ExcluirValor = ExcluirValor ;

	#ifdef _DEBUG
	  CNT_CONTAR( "LIS_CriarLista_c" ) ;
	  pLista->numCorrente = -1;
	  CED_DefinirTipoEspaco( pLista , LIS_TipoEspacoCabeca ) ;
	#endif

	  return pLista ;

   } /* Fim fun��o: LIS  &Criar lista */

/***************************************************************************
*
*  Fun��o: LIS  &Destruir lista
*  ****/

   void LIS_DestruirLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
		 assert( pLista != NULL ) ;
		 CNT_CONTAR( "LIS_DestruirLista_a" ) ;
      #endif

      LIS_EsvaziarLista( pLista ) ;

      free( pLista ) ;

   } /* Fim fun��o: LIS  &Destruir lista */

/***************************************************************************
*
*  Fun��o: LIS  &Esvaziar lista
*  ****/

   void LIS_EsvaziarLista( LIS_tppLista pLista )
   {
	  tpElemLista * pElem ;
      tpElemLista * pProx ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
		 CNT_CONTAR( "LIS_EsvaziarLista_a" ) ;
      #endif

      pElem = pLista->pOrigemLista ;
      while ( pElem != NULL )
      {
        #ifdef _DEBUG
			CNT_CONTAR( "LIS_EsvaziarLista_b" ) ;
		#endif
		 pProx = pElem->pProx ;
         LiberarElemento( pLista , pElem ) ;
         pElem = pProx ;
      } /* while */

	#ifdef _DEBUG
			CNT_CONTAR( "LIS_EsvaziarLista_c" ) ;
	#endif
      LimparCabeca( pLista ) ;

   } /* Fim fun��o: LIS  &Esvaziar lista */

/***************************************************************************
*
*  Fun��o: LIS  &Inserir elemento antes
*  ****/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
                                           void * pValor        )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
		 CNT_CONTAR( "LIS_InserirElementoAntes_i" ) ;
      #endif

      /* Criar elemento a inserir antes */

         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL )
         {
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_InserirElementoAntes_p" ) ;
			#endif
            return LIS_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento antes do elemento corrente */

         if ( pLista->pElemCorr == NULL ) /* se a lista � vazia: */
         {
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_InserirElementoAntes_b" ) ;
				pLista->numCorrente = 0;
				pElem->posicaoElementoLista = 0;
			#endif
         } else /* sen�o...*/
         {
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_InserirElementoAntes_a" ) ;
			#endif
            if ( pLista->pElemCorr->pAnt != NULL ) /* nao � o primeiro da lista */
            {
				#ifdef _DEBUG
					CNT_CONTAR( "LIS_InserirElementoAntes_c" ) ;
				#endif
				pElem->pAnt  = pLista->pElemCorr->pAnt ;
               pLista->pElemCorr->pAnt->pProx = pElem ;
				
            } else /* � o primeiro da lista */
            {
				#ifdef _DEBUG
					CNT_CONTAR( "LIS_InserirElementoAntes_d" ) ;
				#endif
               pLista->pOrigemLista = pElem ;
            } /* if */

            pElem->pProx = pLista->pElemCorr ;
            pLista->pElemCorr->pAnt = pElem ;
			#ifdef _DEBUG
					CNT_CONTAR( "LIS_InserirElementoAntes_e" ) ;
					pElem->posicaoElementoLista = pLista->pElemCorr->posicaoElementoLista ;
					IncrementarAPartirde(pLista->pElemCorr); /* incrementa a posi��o de cada elemento a partir deste */
			#endif
         } /* if */

         pLista->pElemCorr = pElem ;
		#ifdef _DEBUG
		 pLista->numCorrente = pElem->posicaoElementoLista;
		 CNT_CONTAR( "LIS_InserirElementoAntes_f" ) ;
		#endif

         return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Inserir elemento antes */

/***************************************************************************
*
*  Fun��o: LIS  &Inserir elemento ap�s
*  ****/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor        )
      
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
		 CNT_CONTAR( "LIS_InserirElementoApos_i" ) ;
      #endif

      /* Criar elemento a inserir ap�s */

         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL )
         {
            #ifdef _DEBUG
				CNT_CONTAR( "LIS_InserirElementoApos_p" ) ;
				//passagem proibida
			#endif
			 return LIS_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento ap�s o elemento */

         if ( pLista->pElemCorr == NULL ) /* se a lista � vazia */
         {
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_InserirElementoApos_b" ) ;
				pLista->numCorrente = 0;
				pElem->posicaoElementoLista = 0;
			#endif
         } else /* sen�o... */
         {
            #ifdef _DEBUG
				CNT_CONTAR( "LIS_InserirElementoApos_a" ) ;
			#endif
			if ( pLista->pElemCorr->pProx != NULL ) /* elemento n�o � o �ltimo */ 
            {
				#ifdef _DEBUG
				CNT_CONTAR( "LIS_InserirElementoApos_c" );
				#endif
				pElem->pProx  = pLista->pElemCorr->pProx ;
				pLista->pElemCorr->pProx->pAnt = pElem ;
            } else
            {
				#ifdef _DEBUG
					CNT_CONTAR( "LIS_InserirElementoApos_d" ) ;
				#endif
				pLista->pFimLista = pElem ;
            } /* if */

            pElem->pAnt = pLista->pElemCorr ;
            pLista->pElemCorr->pProx = pElem ;
			#ifdef _DEBUG
					CNT_CONTAR( "LIS_InserirElementoApos_e" ) ;
					pElem->posicaoElementoLista = pLista->pElemCorr->posicaoElementoLista + 1;
					IncrementarAPartirde(pElem->pProx); /* incrementa a posi��o de cada elemento a partir deste */
			#endif
         } /* if */
                  
         pLista->pElemCorr = pElem ;
		 #ifdef _DEBUG
			CNT_CONTAR( "LIS_InserirElementoApos_f" ) ;
			pLista->numCorrente = pElem->posicaoElementoLista;
		 #endif
                  
         return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Inserir elemento ap�s */

/***************************************************************************
*
*  Fun��o: LIS  &Excluir elemento
*  ****/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista )
   {

      tpElemLista * pElem ;

      if ( pLista->pElemCorr == NULL )
      {
         return LIS_CondRetListaVazia ;
      } /* if */

      pElem = pLista->pElemCorr ;

      

	  //Decrementa posi��es
	#ifdef _DEBUG
		CNT_CONTAR( "LIS_ExcluirElemento_a" ) ;
		DecrementarAPartirde(pElem->pProx);
	#endif

	/* Desencadeia � esquerda */
         if ( pElem->pAnt != NULL )
         {
            #ifdef _DEBUG
				CNT_CONTAR( "LIS_ExcluirElemento_b" ) ;
			#endif
			pElem->pAnt->pProx   = pElem->pProx ;
            pLista->pElemCorr    = pElem->pAnt ;
         } 
		 else 
		 {
            #ifdef _DEBUG
				CNT_CONTAR( "LIS_ExcluirElemento_c" ) ;
			#endif
			pLista->pElemCorr    = pElem->pProx ;
            pLista->pOrigemLista = pLista->pElemCorr ;
         } /* if */

      /* Desencadeia � direita */

         if ( pElem->pProx != NULL )
         {
            #ifdef _DEBUG
				CNT_CONTAR( "LIS_ExcluirElemento_d" ) ;
			#endif
			pElem->pProx->pAnt = pElem->pAnt ;
         } 
		 else
         {
            #ifdef _DEBUG
				CNT_CONTAR( "LIS_ExcluirElemento_e" ) ;
			#endif
			pLista->pFimLista = pElem->pAnt ;
         } /* if */

      LiberarElemento( pLista , pElem ) ;

	#ifdef _DEBUG
		if(pLista->pElemCorr) pLista->numCorrente = pLista->pElemCorr->posicaoElementoLista; /*lista n�o ficou vazia */
		else pLista->numCorrente = -1; /* lista ficou vazia */
		CNT_CONTAR( "LIS_ExcluirElemento_f" ) ;
	#endif 

      return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Excluir elemento */

/***************************************************************************
*
*  Fun��o: LIS  &Obter refer�ncia para o valor contido no elemento
*  ****/
   

   
   void * LIS_ObterValor( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
		 CNT_CONTAR( "LIS_ObterValor_a" ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
		#ifdef _DEBUG
				CNT_CONTAR( "LIS_ObterValor_c" ) ;
		#endif
		 return NULL ;
      } /* if */

		#ifdef _DEBUG
				CNT_CONTAR( "LIS_ObterValor_b" ) ;
		#endif
      return pLista->pElemCorr->pValor ;

   } /* Fim fun��o: LIS  &Obter refer�ncia para o valor contido no elemento */

/***************************************************************************
*
*  Fun��o: LIS  &Ir para o elemento inicial
*  ****/

   void IrInicioLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
		 CNT_CONTAR( "IrInicioLista_a" ) ;
		 pLista->numCorrente = 0;
      #endif

      pLista->pElemCorr = pLista->pOrigemLista ;


   } /* Fim fun��o: LIS  &Ir para o elemento inicial */

/***************************************************************************
*
*  Fun��o: LIS  &Ir para o elemento final
*  ****/

   void IrFinalLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
		 CNT_CONTAR( "IrFinalLista_a" ) ;
		 pLista->numCorrente = pLista->numElem - 1;
      #endif

      pLista->pElemCorr = pLista->pFimLista ;

   } /* Fim fun��o: LIS  &Ir para o elemento final */

/***************************************************************************
*
*  Fun��o: LIS  &Avan�ar elemento
*  ****/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem )
   {

      int i ;

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
		 CNT_CONTAR( "LIS_AvancarElementoCorrente_a" ) ;
      #endif

      /* Tratar lista vazia */

         if ( pLista->pElemCorr == NULL )
         {
			#ifdef _DEBUG
         		CNT_CONTAR( "LIS_AvancarElementoCorrente_b" ) ;
			#endif
            return LIS_CondRetListaVazia ;

         } /* fim ativa: Tratar lista vazia */

      /* Tratar avan�ar para frente */

		#ifdef _DEBUG
         		CNT_CONTAR( "LIS_AvancarElementoCorrente_c" ) ;
		#endif

         if ( numElem > 0 )
         {

            #ifdef _DEBUG
         		CNT_CONTAR( "LIS_AvancarElementoCorrente_d" ) ;
			#endif
			pElem = pLista->pElemCorr ;
            for( i = numElem ; i > 0 ; i-- )
            {
               if ( pElem == NULL )
               {
					#ifdef _DEBUG
         				CNT_CONTAR( "LIS_AvancarElementoCorrente_f" ) ;
					#endif
				   break ;
               } /* if */
				#ifdef _DEBUG
         			CNT_CONTAR( "LIS_AvancarElementoCorrente_e" ) ;
				#endif
               pElem    = pElem->pProx ;
            } /* for */

            if ( pElem != NULL )
            {
               pLista->pElemCorr = pElem ;
				#ifdef _DEBUG
					pLista->numCorrente = pLista->pElemCorr->posicaoElementoLista;
					CNT_CONTAR( "LIS_AvancarElementoCorrente_h" ) ;
				#endif
               return LIS_CondRetOK ;
            } /* if */

            pLista->pElemCorr = pLista->pFimLista ;
			#ifdef _DEBUG
				pLista->numCorrente = pLista->pElemCorr->posicaoElementoLista;
				CNT_CONTAR( "LIS_AvancarElementoCorrente_g" ) ;
			#endif
            return LIS_CondRetFimLista ;

         } /* fim ativa: Tratar avan�ar para frente */

      /* Tratar avan�ar para tr�s */

         else if ( numElem < 0 )
         {

            #ifdef _DEBUG
         			CNT_CONTAR( "LIS_AvancarElementoCorrente_i" ) ;
			#endif
			pElem = pLista->pElemCorr ;
            for( i = numElem ; i < 0 ; i++ )
            {
               if ( pElem == NULL )
               {
					#ifdef _DEBUG
         				CNT_CONTAR( "LIS_AvancarElementoCorrente_j" ) ;
					#endif
				   break ;
               } /* if */
               pElem    = pElem->pAnt ;
				#ifdef _DEBUG
         			CNT_CONTAR( "LIS_AvancarElementoCorrente_k" ) ;
				#endif
            } /* for */

			#ifdef _DEBUG
         			CNT_CONTAR( "LIS_AvancarElementoCorrente_l" ) ;
			#endif

            if ( pElem != NULL )
            {
               pLista->pElemCorr = pElem ;
				#ifdef _DEBUG
					pLista->numCorrente = pElem->posicaoElementoLista;
					CNT_CONTAR( "LIS_AvancarElementoCorrente_m" ) ;
				#endif
               return LIS_CondRetOK ;
            } /* if */

            pLista->pElemCorr = pLista->pOrigemLista ;
			#ifdef _DEBUG
				pLista->numCorrente = pLista->pElemCorr->posicaoElementoLista;
				CNT_CONTAR( "LIS_AvancarElementoCorrente_n" ) ;
			#endif
            return LIS_CondRetFimLista ;

         } /* fim ativa: Tratar avan�ar para tr�s */

      /* Tratar n�o avan�ar */
		#ifdef _DEBUG
         			CNT_CONTAR( "LIS_AvancarElementoCorrente_o" ) ;
		#endif
         return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Avan�ar elemento */

/***************************************************************************
*
*  Fun��o: LIS  &Procurar elemento contendo valor
*  ****/
//
   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    void * pValor        )
   {

      tpElemLista * pElem;

      #ifdef _DEBUG
         assert( pLista  != NULL ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
         return LIS_CondRetListaVazia ;
      } /* if */
// pq pLista->pElemCorr, e n�o o primeiro elem???
      for ( pElem  = pLista->pOrigemLista ;
            pElem != NULL ;
            pElem  = pElem->pProx )
      {
         if ( pElem->pValor == pValor )
         {
            pLista->pElemCorr = pElem ;
			#ifdef _DEBUG
			pLista->numCorrente = pElem->posicaoElementoLista;
			#endif
            return LIS_CondRetOK ;
         } /* if */
      } /* for */

      return LIS_CondRetNaoAchou ;

   } 
   
   /* Fim fun��o: LIS  &Procurar elemento contendo valor */


//******************************************************
   /* Fun��o: LIS &Numero de Elementos */

    int LIS_NumerodeElementos( LIS_tppLista pLista)
	{
		#ifdef _DEBUG
			assert(pLista != NULL);
         	CNT_CONTAR( "LIS_NumerodeElementos_a" ) ;
		#endif
		return pLista->numElem;
	}


	
	
/***********************************************************************
*
*  $FC Fun��o: LIS  - Verificar corretude das estruturas de lista atrav�s das redund�ncias. S� dispon�vel no modo _DEBUG
*
***********************************************************************/
#ifdef _DEBUG

   LIS_tpCondRet LIS_VerificarLista(LIS_tppLista pLista)
   {
	   
	   LIS_tpCondRet ret;
	   tpElemLista *aux, *ant;
	   int i, corrOk = 0;
	    tpElemLista* Elem = pLista->pOrigemLista;
	   // Verificar cabe�a
		CNT_CONTAR( "LIS_VerificarLista_a" ) ;
	   if(pLista == NULL)
	   {
		    TST_NotificarFalha( "Cabe�a da lista recebida � nula" ) ;
            CNT_CONTAR( "LIS_VerificarLista_E1" ) ;
			return LIS_CondRetDeturpacao ;
	   }
	   CNT_CONTAR( "LIS_VerificarLista_b" ) ;
		if ( ! CED_VerificarEspaco( pLista , NULL ) )
         {
            TST_NotificarFalha( "Controle do espa�o acusou erro." ) ;
            CNT_CONTAR( "LIS_VerificarLista_E2" ) ;
			return LIS_CondRetDeturpacao ;
         } /* if */
		CNT_CONTAR( "LIS_VerificarLista_c" ) ;
		if (CED_ObterTipoEspaco(pLista) != LIS_TipoEspacoCabeca)
		{
			TST_NotificarFalha( "Cabe�a da Lista n�o foi definida como LIS_TipoEspacoCabeca. " ) ;
			CNT_CONTAR( "LIS_VerificarLista_E3" ) ;
			return LIS_CondRetDeturpacao;
		} /* if */
		CNT_CONTAR( "LIS_VerificarLista_d" ) ;
		if (CED_ObterTamanhoValor(pLista) != sizeof(LIS_tpLista))
		{
			TST_NotificarFalha( "Cabe�a da Lista n�o tem o tamanho certo. " ) ;
			CNT_CONTAR( "LIS_VerificarLista_E4" ) ;
			return LIS_CondRetDeturpacao;
		}
		CNT_CONTAR( "LIS_VerificarLista_e" ) ;
		if( pLista->pOrigemLista == NULL || pLista->pFimLista == NULL || pLista->pElemCorr == NULL)
		{
			CNT_CONTAR( "LIS_VerificarLista_f" ) ;
			if(pLista->numElem != 0)
			{
				TST_NotificarFalha( "A cabe�a de uma lista suposta n�o vazia tem 'ponteiro para elementos' nulos. " ) ;
				CNT_CONTAR( "LIS_VerificarLista_E5" ) ;
				return LIS_CondRetDeturpacao;
			}
		}
		/* if */
		// Fim verificar cabe�a

		//Verificar cada elemento
		CNT_CONTAR( "LIS_VerificarLista_g" ) ;
		if(Elem == NULL)
		{
			CNT_CONTAR( "LIS_VerificarLista_h" ) ;
			if(pLista->numElem != 0)
			{
				TST_NotificarFalha( " Elem passado � null mas lista � suposta n�o vazia. " ) ;
				CNT_CONTAR( "LIS_VerificarLista_E6" ) ;
				return LIS_CondRetDeturpacao;
			}
			CNT_CONTAR( "LIS_VerificarLista_i" ) ;
			if(pLista->pOrigemLista != NULL || pLista->pFimLista != NULL || pLista->pElemCorr != NULL)
			{
				TST_NotificarFalha( " Numero de elementos � zero mas h� ponteiro(s) n�o nulo(s) para elemento(s) na cabe�a. " ) ;
				CNT_CONTAR( "LIS_VerificarLista_E7" ) ;
				return LIS_CondRetDeturpacao;
			}
		}
		
		else
		{
			CNT_CONTAR( "LIS_VerificarLista_j" ) ;
			i = 0;
			aux = Elem;
			ret  = LIS_CondRetOK;
			do
			{
				ret = LIS_VerificarElem(pLista, aux);
				aux = aux->pProx;
				i++;
			} while(aux && ret == LIS_CondRetOK && i < pLista->numElem - 1);
			if(ret != LIS_CondRetOK)
			{
					CNT_CONTAR( "LIS_VerificarLista_E8" ) ; 
					return LIS_CondRetDeturpacao;
			}
			CNT_CONTAR( "LIS_VerificarLista_k" ) ;
			if(aux && aux->pProx != NULL)
			{
				TST_NotificarFalha( " Ultimo elemento n�o tem pProx NULL " ) ;
				CNT_CONTAR( "LIS_VerificarLista_E9" ) ;
				return LIS_CondRetDeturpacao;
			}
		}
		
		//Fim verificar cada elemento

		//Verificar para o conjunto de elementos e cabe�a
		CNT_CONTAR( "LIS_VerificarLista_l" ) ;
		if(pLista->numElem == 0) /* lista suposta vazia */
		{
			CNT_CONTAR( "LIS_VerificarLista_m" ) ;
			if(pLista->pOrigemLista != NULL || pLista->pFimLista != NULL || pLista->pElemCorr != NULL)
			{
				TST_NotificarFalha( " Numero de elementos � zero mas h� ponteiro(s) n�o nulo(s) para elemento(s) na cabe�a. " ) ;
				CNT_CONTAR( "LIS_VerificarLista_E10" ) ;
				return LIS_CondRetDeturpacao;
			}
		}
		else /* lista suposta n�o vazia */
		{
			CNT_CONTAR( "LIS_VerificarLista_n" ) ;
			if(pLista->pOrigemLista != Elem)
			{
				TST_NotificarFalha( " Ponteiro para origem da lista discrepante com elemento passado " ) ;
				CNT_CONTAR( "LIS_VerificarLista_E11" ) ;
				return LIS_CondRetDeturpacao;
			}
			CNT_CONTAR( "LIS_VerificarLista_o" ) ;
			if(Elem->pAnt != NULL)
			{
				TST_NotificarFalha( " pAnt do primeiro elemento n�o � NULL " ) ;
				CNT_CONTAR( "LIS_VerificarLista_E12" ) ;
				return LIS_CondRetDeturpacao;
			}
			CNT_CONTAR( "LIS_VerificarLista_p" ) ;
			if(Elem == pLista->pElemCorr) /* elemento corrente � o primeiro */
			{
				corrOk = 1;
				CNT_CONTAR( "LIS_VerificarLista_q" ) ;
				if(pLista->numCorrente != 0)
				{
					TST_NotificarFalha( " NumCorrente n�o condiz.Eh o primeiro " ) ;
					CNT_CONTAR( "LIS_VerificarLista_E13" ) ;
					return LIS_CondRetDeturpacao;
				}
			}
			aux = Elem; 
			ant = NULL; /* ant � o elemento anterior a aux. Usado para testar se pAnt condiz. */
			i = 0;
			CNT_CONTAR( "LIS_VerificarLista_r" ) ;
			while(aux->pProx && i < pLista->numElem) /* testa para todos elementos que n�o s�o o primeiro nem o �ltimo */
			{
				CNT_CONTAR( "LIS_VerificarLista_s" ) ;
				if(aux->pAnt != ant )
				{
					TST_NotificarFalha( " pAnt n�o aponta para elemento que aponta para um dado elemento. " ) ;
					CNT_CONTAR( "LIS_VerificarLista_E14" ) ;
					return LIS_CondRetDeturpacao;
				}
				CNT_CONTAR( "LIS_VerificarLista_t" ) ;
				if(aux->posicaoElementoLista != i)
				{
					TST_NotificarFalha( " Contagem dos elementos n�o correspondeu com sua posi��o indicada. " ) ;
					CNT_CONTAR( "LIS_VerificarLista_E15" ) ;
					return LIS_CondRetDeturpacao;
				}
				CNT_CONTAR( "LIS_VerificarLista_u" ) ;
				if(aux == pLista->pElemCorr)
				{
					corrOk = 1;
					CNT_CONTAR( "LIS_VerificarLista_v" ) ;
					if(pLista->numCorrente != i)
					{
						TST_NotificarFalha( " NumCorrente n�o condiz. " ) ;
						CNT_CONTAR( "LIS_VerificarLista_E16" ) ;
						return LIS_CondRetDeturpacao;
					}
				}
				i++;
				ant = aux;
				aux = aux->pProx;
			}
			//aux = ultimo elemento alcan�ado
			CNT_CONTAR( "LIS_VerificarLista_x" ) ;
			if(aux->posicaoElementoLista != pLista->numElem - 1 || aux->posicaoElementoLista != i)
			{
				TST_NotificarFalha( " Numero de elementos indicados n�o condiz com contagem dos elementos. " ) ;
				CNT_CONTAR( "LIS_VerificarLista_E17" ) ;
				return LIS_CondRetDeturpacao;
			}
			CNT_CONTAR( "LIS_VerificarLista_w" ) ;
			if(aux != pLista->pFimLista)
			{
				TST_NotificarFalha( " pFimLista n�o aponta para o fim da lista OU percorrimento n�o alcan�ou o fim da lista " ) ;
				CNT_CONTAR( "LIS_VerificarLista_E18" ) ;
				return LIS_CondRetDeturpacao;
			}
			CNT_CONTAR( "LIS_VerificarLista_y" ) ;
			if(aux == pLista->pElemCorr)
				{
					corrOk = 1;
					CNT_CONTAR( "LIS_VerificarLista_z" ) ;
					if(pLista->numCorrente != i)
					{
						TST_NotificarFalha( " NumCorrente n�o condiz. � o �ltimo" ) ;
						CNT_CONTAR( "LIS_VerificarLista_E19" ) ;
						return LIS_CondRetDeturpacao;
					}
				}
			CNT_CONTAR( "LIS_VerificarLista_aa" ) ;
			if(corrOk != 1)
			{
				TST_NotificarFalha( " Elemento corrente n�o foi percorrido " ) ;
				CNT_CONTAR( "LIS_VerificarLista_E20" ) ;
				return LIS_CondRetDeturpacao;
			}

		}
		CNT_CONTAR( "LIS_VerificarLista_ab" ) ;
		//Fim verificar para o conjunto de elementos e cabe�a

		return LIS_CondRetOK;
		
   }
#endif

//******************Fim fun��o LIS_VerificaLista



/***********************************************************************
*
*  $FC Fun��o: LIS  - Deturpa Lista.
*
*  $ED Descri��o da fun��o
*     Deturpa a lista de alguma maneiras diferente, determinadas pelo parametro char passado. Us�vel em modo _DEBUG
*
***********************************************************************/

#ifdef _DEBUG
   LIS_tpCondRet LIS_DeturparLista( LIS_tppLista   pLista, LIS_tpModosDeturpacao modo)
   {
	   CNT_CONTAR( "LIS_DeturparLista_a" ) ;
	   switch(modo)
	   {
			case Desencadear_TRAS:
				{
					CNT_CONTAR( "LIS_DeturparLista_b" ) ;
					if(pLista->pElemCorr->pProx)
					{
						pLista->pElemCorr->pProx->pAnt = NULL;
						return LIS_CondRetOK;
					}
					else
					{
						CNT_CONTAR( "LIS_DeturparLista_p1" ) ;
						return LIS_CondRetFimLista;
					}
					break;
				}
			case Desencadear_FRENTE:
				{
					CNT_CONTAR( "LIS_DeturparLista_c" ) ;
					if(pLista->pElemCorr->pAnt)
					{
						pLista->pElemCorr->pAnt->pProx = NULL;
						return LIS_CondRetOK;
					}
					else 
					{
						CNT_CONTAR( "LIS_DeturparLista_p2" ) ;
						return LIS_CondRetFimLista;
					}
					break;
				}
			case DeturpaTipoCabeca:
				{
					CNT_CONTAR( "LIS_DeturparLista_d" ) ;
					CED_DefinirTipoEspaco( pLista , CED_ID_TIPO_VALOR_NULO ) ;
					return LIS_CondRetOK;
					break;
				}
			case DeturpaCorrenteNulo:
				{
					CNT_CONTAR( "LIS_DeturparLista_e" ) ;
					pLista->pElemCorr = NULL;
					return LIS_CondRetOK;
					break;
				}
			case DeturpaTipoCorrente:
				{
					CNT_CONTAR( "LIS_DeturparLista_f" ) ;
					CED_DefinirTipoEspaco( pLista->pElemCorr , CED_ID_TIPO_VALOR_NULO ) ;
					return LIS_CondRetOK;
					break;
				}
			case DeturpaListaCircular:
				{
					CNT_CONTAR( "LIS_DeturparLista_g" ) ;
					if(pLista->pOrigemLista && pLista->pFimLista)
					{
						pLista->pOrigemLista->pAnt = pLista->pFimLista;
						pLista->pFimLista->pProx = pLista->pOrigemLista;
						return LIS_CondRetOK;
					}
					else
					{
						CNT_CONTAR( "LIS_DeturparLista_p3" ) ;
						return LIS_CondRetListaVazia;
					}
					break;
				}
			case DeturpaPonteiroCabecaLista:
				{
					CNT_CONTAR( "LIS_DeturparLista_h" ) ;
					if(pLista->pElemCorr)
					{
						pLista->pElemCorr->ponteiroCabeca = NULL;
						return LIS_CondRetOK;
						break;
					}
					else 
					{
						CNT_CONTAR( "LIS_DeturparLista_p4" ) ;
						return LIS_CondRetListaVazia;
					}
					break;
				}
			case DeturpaContagem:
				{
					CNT_CONTAR( "LIS_DeturparLista_i" ) ;
					if(pLista->pElemCorr)
					{
						pLista->pElemCorr->posicaoElementoLista = -1;
						return LIS_CondRetOK;
						break;
					}
					else 
					{
						CNT_CONTAR( "LIS_DeturparLista_p5" ) ;
						return LIS_CondRetListaVazia;
					}
					break;
				}
			case DeturpaPerdeElemento:
				{
					CNT_CONTAR( "LIS_DeturparLista_j" ) ;
					if(pLista->pElemCorr->pProx && pLista->pElemCorr->pAnt)
					{
						pLista->pElemCorr->pAnt->pProx = pLista->pElemCorr->pProx;
						pLista->pElemCorr->pProx->pAnt = pLista->pElemCorr->pAnt;
						return LIS_CondRetOK;
						break;
					}
					else 
					{
						CNT_CONTAR( "LIS_DeturparLista_p6" ) ;
						return LIS_CondRetListaVazia;
					}
					break;
				}
			default:
				{
					CNT_CONTAR( "LIS_DeturparLista_p7" ) ;
					return LIS_CondRetNaoAchou;
					break;
				}
				
	   }
      

   } /* Fim fun��o: LIS  - Deturpar lista */
#endif





/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: LIS  -Liberar elemento da lista
*
*  $ED Descri��o da fun��o
*     Elimina os espa�os apontados pelo valor do elemento e o
*     pr�prio elemento.
*
***********************************************************************/

   void LiberarElemento( LIS_tppLista   pLista ,
                         tpElemLista  * pElem   )
   {

      if ( ( pLista->ExcluirValor != NULL )
        && ( pElem->pValor != NULL        ))
      {
        #ifdef _DEBUG
			 CNT_CONTAR( "LiberarElemento_a" ) ;
		#endif
		 pLista->ExcluirValor( pElem->pValor ) ;
      } /* if */

	#ifdef _DEBUG
	  pElem->ponteiroCabeca = NULL;
	  CNT_CONTAR( "LiberarElemento_b" ) ;
	#endif
	  free( pElem ) ;

      pLista->numElem-- ;

   } /* Fim fun��o: LIS  -Liberar elemento da lista */


/***********************************************************************
*
*  $FC Fun��o: LIS  -Criar o elemento
*
***********************************************************************/

   tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                void *       pValor  )
   {

      tpElemLista * pElem ;

      pElem = ( tpElemLista * ) malloc( sizeof( tpElemLista )) ;
		#ifdef _DEBUG
			CED_DefinirTipoEspaco( pElem , LIS_TipoEspacoElem ) ;
			CNT_CONTAR( "CriarElemento_a" ) ;
		#endif
      if ( pElem == NULL )
      {
        #ifdef _DEBUG
			 CNT_CONTAR( "CriarElemento_b" ) ;
			 //passagem proibida.
		#endif
		  return NULL ;
      } /* if */

      pElem->pValor = pValor ;
      pElem->pAnt   = NULL  ;
      pElem->pProx  = NULL  ;

	#ifdef _DEBUG
	  assert(pLista != NULL);
	  pElem->ponteiroCabeca = pLista;
	  assert(pElem->ponteiroCabeca != NULL);
	  CNT_CONTAR( "CriarElemento_c" ) ;
	#endif

      pLista->numElem ++ ;

      return pElem ;

   } /* Fim fun��o: LIS  -Criar o elemento */


/***********************************************************************
*
*  $FC Fun��o: LIS  -Limpar a cabe�a da lista
*
***********************************************************************/

   void LimparCabeca( LIS_tppLista pLista )
   {

      pLista->pOrigemLista = NULL ;
      pLista->pFimLista = NULL ;
      pLista->pElemCorr = NULL ;
      pLista->numElem   = 0 ;
		#ifdef _DEBUG
			pLista->numCorrente = -1;
			CNT_CONTAR( "LimparCabeca_a" ) ;
		#endif

   } /* Fim fun��o: LIS  -Limpar a cabe�a da lista */


/***********************************************************************
*
*  $FC Fun��o: LIS  - incrementar posi��es da lista a partir de. S� dispon�vel no modo _DEBUG
*
***********************************************************************/
#ifdef _DEBUG

   void IncrementarAPartirde(tpElemLista* Elem)
   {
	   while(Elem != NULL)
	   {
		   Elem->posicaoElementoLista = Elem->posicaoElementoLista + 1;
		   Elem = Elem->pProx;
	   }
	   return;
   }
#endif

/***********************************************************************
*
*  $FC Fun��o: LIS  - decrementar posi��es da lista a partir de. S� dispon�vel no modo _DEBUG
*
***********************************************************************/
#ifdef _DEBUG

   void DecrementarAPartirde(tpElemLista* Elem)
   {
	   while(Elem != NULL)
	   {
		   Elem->posicaoElementoLista = Elem->posicaoElementoLista - 1;
		   Elem = Elem->pProx;
	   }
	   return;
   }
#endif



/***********************************************************************
*
*  $FC Fun��o: LIS  - Verificar corretude de um �nico elemento. Fun��o auxiliar chamada em LIS_VerificarLista() para cada elemento. S� dispon�vel no modo _DEBUG
*
***********************************************************************/
#ifdef _DEBUG

   LIS_tpCondRet LIS_VerificarElem(LIS_tpLista* pLista, tpElemLista* Elem)
   {
	   CNT_CONTAR( "LIS_VerificarElem_i" ) ;
	   if(Elem != NULL)
		{
			CNT_CONTAR( "LIS_VerificarElem_a" ) ;
			if ( ! CED_VerificarEspaco( Elem , NULL ) )
			 {
				TST_NotificarFalha( "Controle do espa�o acusou erro em um elemento" ) ;
				CNT_CONTAR( "LIS_VerificarElem_E1" ) ;
				return LIS_CondRetDeturpacao ;
			 } /* if */
		   CNT_CONTAR( "LIS_VerificarElem_b" ) ;
			if (CED_ObterTipoEspaco(Elem) != LIS_TipoEspacoElem)
			{
				TST_NotificarFalha( "Um elemento da lista n�o foi definido como LIS_TipoEspacoElem. " ) ;
				CNT_CONTAR( "LIS_VerificarElem_E2" ) ;
				return LIS_CondRetDeturpacao;
			} /* if */
			CNT_CONTAR( "LIS_VerificarElem_c" ) ;
			if (CED_ObterTamanhoValor(Elem) != sizeof(tpElemLista))
			{
				TST_NotificarFalha( "Um elemento da Lista n�o tem o tamanho certo. " ) ;
				CNT_CONTAR( "LIS_VerificarElem_E3" ) ;
				return LIS_CondRetDeturpacao;
			} /* if */
			CNT_CONTAR( "LIS_VerificarElem_d" ) ;
			if(pLista != Elem->ponteiroCabeca )
			{
				TST_NotificarFalha( " Um elemento da Lista n�o est� com o ponteiro para cabe�a correta. " );
				CNT_CONTAR( "LIS_VerificarElem_E4" ) ;
				return LIS_CondRetDeturpacao;
			}
		CNT_CONTAR( "LIS_VerificarElem_e" ) ;
			if( Elem->pValor == NULL)
			{
				TST_NotificarFalha( " Um elemento da lista tem o ponteiro para valor nulo ");
				CNT_CONTAR( "LIS_VerificarElem_E5" ) ;
				return LIS_CondRetDeturpacao;
			}
	   }
	   CNT_CONTAR( "LIS_VerificarElem_f" ) ;
		return LIS_CondRetOK;
   }
#endif



/********** Fim do m�dulo de implementa��o: LIS  Lista duplamente encadeada **********/

