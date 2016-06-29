/***************************************************************************
*  $MCI Módulo de implementação: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
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
*  typedef's da cabeça e elemento da lista
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
				/* ponteiro para a cabeça da lista */
		 int posicaoElementoLista;
				/* a posição do elemento na lista */
		#endif
   } ;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabeça de lista
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
               /* Número de elementos da lista */

         void ( * ExcluirValor ) ( void * pValor ) ;
               /* Ponteiro para a função de destruição do valor contido em um elemento */
		
		#ifdef _DEBUG

		 int numCorrente ;
				/* a posição na lista do elemento corrente*/
		#endif


   } ;

/***** Protótipos das funções encapuladas no módulo *****/

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

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: LIS  &Criar lista
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

   } /* Fim função: LIS  &Criar lista */

/***************************************************************************
*
*  Função: LIS  &Destruir lista
*  ****/

   void LIS_DestruirLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
		 assert( pLista != NULL ) ;
		 CNT_CONTAR( "LIS_DestruirLista_a" ) ;
      #endif

      LIS_EsvaziarLista( pLista ) ;

      free( pLista ) ;

   } /* Fim função: LIS  &Destruir lista */

/***************************************************************************
*
*  Função: LIS  &Esvaziar lista
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

   } /* Fim função: LIS  &Esvaziar lista */

/***************************************************************************
*
*  Função: LIS  &Inserir elemento antes
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

         if ( pLista->pElemCorr == NULL ) /* se a lista é vazia: */
         {
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_InserirElementoAntes_b" ) ;
				pLista->numCorrente = 0;
				pElem->posicaoElementoLista = 0;
			#endif
         } else /* senão...*/
         {
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_InserirElementoAntes_a" ) ;
			#endif
            if ( pLista->pElemCorr->pAnt != NULL ) /* nao é o primeiro da lista */
            {
				#ifdef _DEBUG
					CNT_CONTAR( "LIS_InserirElementoAntes_c" ) ;
				#endif
				pElem->pAnt  = pLista->pElemCorr->pAnt ;
               pLista->pElemCorr->pAnt->pProx = pElem ;
				
            } else /* é o primeiro da lista */
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
					IncrementarAPartirde(pLista->pElemCorr); /* incrementa a posição de cada elemento a partir deste */
			#endif
         } /* if */

         pLista->pElemCorr = pElem ;
		#ifdef _DEBUG
		 pLista->numCorrente = pElem->posicaoElementoLista;
		 CNT_CONTAR( "LIS_InserirElementoAntes_f" ) ;
		#endif

         return LIS_CondRetOK ;

   } /* Fim função: LIS  &Inserir elemento antes */

/***************************************************************************
*
*  Função: LIS  &Inserir elemento após
*  ****/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor        )
      
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
		 CNT_CONTAR( "LIS_InserirElementoApos_i" ) ;
      #endif

      /* Criar elemento a inserir após */

         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL )
         {
            #ifdef _DEBUG
				CNT_CONTAR( "LIS_InserirElementoApos_p" ) ;
				//passagem proibida
			#endif
			 return LIS_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento após o elemento */

         if ( pLista->pElemCorr == NULL ) /* se a lista é vazia */
         {
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
			#ifdef _DEBUG
				CNT_CONTAR( "LIS_InserirElementoApos_b" ) ;
				pLista->numCorrente = 0;
				pElem->posicaoElementoLista = 0;
			#endif
         } else /* senão... */
         {
            #ifdef _DEBUG
				CNT_CONTAR( "LIS_InserirElementoApos_a" ) ;
			#endif
			if ( pLista->pElemCorr->pProx != NULL ) /* elemento não é o último */ 
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
					IncrementarAPartirde(pElem->pProx); /* incrementa a posição de cada elemento a partir deste */
			#endif
         } /* if */
                  
         pLista->pElemCorr = pElem ;
		 #ifdef _DEBUG
			CNT_CONTAR( "LIS_InserirElementoApos_f" ) ;
			pLista->numCorrente = pElem->posicaoElementoLista;
		 #endif
                  
         return LIS_CondRetOK ;

   } /* Fim função: LIS  &Inserir elemento após */

/***************************************************************************
*
*  Função: LIS  &Excluir elemento
*  ****/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista )
   {

      tpElemLista * pElem ;

      if ( pLista->pElemCorr == NULL )
      {
         return LIS_CondRetListaVazia ;
      } /* if */

      pElem = pLista->pElemCorr ;

      

	  //Decrementa posições
	#ifdef _DEBUG
		CNT_CONTAR( "LIS_ExcluirElemento_a" ) ;
		DecrementarAPartirde(pElem->pProx);
	#endif

	/* Desencadeia à esquerda */
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

      /* Desencadeia à direita */

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
		if(pLista->pElemCorr) pLista->numCorrente = pLista->pElemCorr->posicaoElementoLista; /*lista não ficou vazia */
		else pLista->numCorrente = -1; /* lista ficou vazia */
		CNT_CONTAR( "LIS_ExcluirElemento_f" ) ;
	#endif 

      return LIS_CondRetOK ;

   } /* Fim função: LIS  &Excluir elemento */

/***************************************************************************
*
*  Função: LIS  &Obter referência para o valor contido no elemento
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

   } /* Fim função: LIS  &Obter referência para o valor contido no elemento */

/***************************************************************************
*
*  Função: LIS  &Ir para o elemento inicial
*  ****/

   void IrInicioLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
		 CNT_CONTAR( "IrInicioLista_a" ) ;
		 pLista->numCorrente = 0;
      #endif

      pLista->pElemCorr = pLista->pOrigemLista ;


   } /* Fim função: LIS  &Ir para o elemento inicial */

/***************************************************************************
*
*  Função: LIS  &Ir para o elemento final
*  ****/

   void IrFinalLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
		 CNT_CONTAR( "IrFinalLista_a" ) ;
		 pLista->numCorrente = pLista->numElem - 1;
      #endif

      pLista->pElemCorr = pLista->pFimLista ;

   } /* Fim função: LIS  &Ir para o elemento final */

/***************************************************************************
*
*  Função: LIS  &Avançar elemento
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

      /* Tratar avançar para frente */

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

         } /* fim ativa: Tratar avançar para frente */

      /* Tratar avançar para trás */

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

         } /* fim ativa: Tratar avançar para trás */

      /* Tratar não avançar */
		#ifdef _DEBUG
         			CNT_CONTAR( "LIS_AvancarElementoCorrente_o" ) ;
		#endif
         return LIS_CondRetOK ;

   } /* Fim função: LIS  &Avançar elemento */

/***************************************************************************
*
*  Função: LIS  &Procurar elemento contendo valor
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
// pq pLista->pElemCorr, e não o primeiro elem???
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
   
   /* Fim função: LIS  &Procurar elemento contendo valor */


//******************************************************
   /* Função: LIS &Numero de Elementos */

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
*  $FC Função: LIS  - Verificar corretude das estruturas de lista através das redundâncias. Só disponível no modo _DEBUG
*
***********************************************************************/
#ifdef _DEBUG

   LIS_tpCondRet LIS_VerificarLista(LIS_tppLista pLista)
   {
	   
	   LIS_tpCondRet ret;
	   tpElemLista *aux, *ant;
	   int i, corrOk = 0;
	    tpElemLista* Elem = pLista->pOrigemLista;
	   // Verificar cabeça
		CNT_CONTAR( "LIS_VerificarLista_a" ) ;
	   if(pLista == NULL)
	   {
		    TST_NotificarFalha( "Cabeça da lista recebida é nula" ) ;
            CNT_CONTAR( "LIS_VerificarLista_E1" ) ;
			return LIS_CondRetDeturpacao ;
	   }
	   CNT_CONTAR( "LIS_VerificarLista_b" ) ;
		if ( ! CED_VerificarEspaco( pLista , NULL ) )
         {
            TST_NotificarFalha( "Controle do espaço acusou erro." ) ;
            CNT_CONTAR( "LIS_VerificarLista_E2" ) ;
			return LIS_CondRetDeturpacao ;
         } /* if */
		CNT_CONTAR( "LIS_VerificarLista_c" ) ;
		if (CED_ObterTipoEspaco(pLista) != LIS_TipoEspacoCabeca)
		{
			TST_NotificarFalha( "Cabeça da Lista não foi definida como LIS_TipoEspacoCabeca. " ) ;
			CNT_CONTAR( "LIS_VerificarLista_E3" ) ;
			return LIS_CondRetDeturpacao;
		} /* if */
		CNT_CONTAR( "LIS_VerificarLista_d" ) ;
		if (CED_ObterTamanhoValor(pLista) != sizeof(LIS_tpLista))
		{
			TST_NotificarFalha( "Cabeça da Lista não tem o tamanho certo. " ) ;
			CNT_CONTAR( "LIS_VerificarLista_E4" ) ;
			return LIS_CondRetDeturpacao;
		}
		CNT_CONTAR( "LIS_VerificarLista_e" ) ;
		if( pLista->pOrigemLista == NULL || pLista->pFimLista == NULL || pLista->pElemCorr == NULL)
		{
			CNT_CONTAR( "LIS_VerificarLista_f" ) ;
			if(pLista->numElem != 0)
			{
				TST_NotificarFalha( "A cabeça de uma lista suposta não vazia tem 'ponteiro para elementos' nulos. " ) ;
				CNT_CONTAR( "LIS_VerificarLista_E5" ) ;
				return LIS_CondRetDeturpacao;
			}
		}
		/* if */
		// Fim verificar cabeça

		//Verificar cada elemento
		CNT_CONTAR( "LIS_VerificarLista_g" ) ;
		if(Elem == NULL)
		{
			CNT_CONTAR( "LIS_VerificarLista_h" ) ;
			if(pLista->numElem != 0)
			{
				TST_NotificarFalha( " Elem passado é null mas lista é suposta não vazia. " ) ;
				CNT_CONTAR( "LIS_VerificarLista_E6" ) ;
				return LIS_CondRetDeturpacao;
			}
			CNT_CONTAR( "LIS_VerificarLista_i" ) ;
			if(pLista->pOrigemLista != NULL || pLista->pFimLista != NULL || pLista->pElemCorr != NULL)
			{
				TST_NotificarFalha( " Numero de elementos é zero mas há ponteiro(s) não nulo(s) para elemento(s) na cabeça. " ) ;
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
				TST_NotificarFalha( " Ultimo elemento não tem pProx NULL " ) ;
				CNT_CONTAR( "LIS_VerificarLista_E9" ) ;
				return LIS_CondRetDeturpacao;
			}
		}
		
		//Fim verificar cada elemento

		//Verificar para o conjunto de elementos e cabeça
		CNT_CONTAR( "LIS_VerificarLista_l" ) ;
		if(pLista->numElem == 0) /* lista suposta vazia */
		{
			CNT_CONTAR( "LIS_VerificarLista_m" ) ;
			if(pLista->pOrigemLista != NULL || pLista->pFimLista != NULL || pLista->pElemCorr != NULL)
			{
				TST_NotificarFalha( " Numero de elementos é zero mas há ponteiro(s) não nulo(s) para elemento(s) na cabeça. " ) ;
				CNT_CONTAR( "LIS_VerificarLista_E10" ) ;
				return LIS_CondRetDeturpacao;
			}
		}
		else /* lista suposta não vazia */
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
				TST_NotificarFalha( " pAnt do primeiro elemento não é NULL " ) ;
				CNT_CONTAR( "LIS_VerificarLista_E12" ) ;
				return LIS_CondRetDeturpacao;
			}
			CNT_CONTAR( "LIS_VerificarLista_p" ) ;
			if(Elem == pLista->pElemCorr) /* elemento corrente é o primeiro */
			{
				corrOk = 1;
				CNT_CONTAR( "LIS_VerificarLista_q" ) ;
				if(pLista->numCorrente != 0)
				{
					TST_NotificarFalha( " NumCorrente não condiz.Eh o primeiro " ) ;
					CNT_CONTAR( "LIS_VerificarLista_E13" ) ;
					return LIS_CondRetDeturpacao;
				}
			}
			aux = Elem; 
			ant = NULL; /* ant é o elemento anterior a aux. Usado para testar se pAnt condiz. */
			i = 0;
			CNT_CONTAR( "LIS_VerificarLista_r" ) ;
			while(aux->pProx && i < pLista->numElem) /* testa para todos elementos que não são o primeiro nem o último */
			{
				CNT_CONTAR( "LIS_VerificarLista_s" ) ;
				if(aux->pAnt != ant )
				{
					TST_NotificarFalha( " pAnt não aponta para elemento que aponta para um dado elemento. " ) ;
					CNT_CONTAR( "LIS_VerificarLista_E14" ) ;
					return LIS_CondRetDeturpacao;
				}
				CNT_CONTAR( "LIS_VerificarLista_t" ) ;
				if(aux->posicaoElementoLista != i)
				{
					TST_NotificarFalha( " Contagem dos elementos não correspondeu com sua posição indicada. " ) ;
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
						TST_NotificarFalha( " NumCorrente não condiz. " ) ;
						CNT_CONTAR( "LIS_VerificarLista_E16" ) ;
						return LIS_CondRetDeturpacao;
					}
				}
				i++;
				ant = aux;
				aux = aux->pProx;
			}
			//aux = ultimo elemento alcançado
			CNT_CONTAR( "LIS_VerificarLista_x" ) ;
			if(aux->posicaoElementoLista != pLista->numElem - 1 || aux->posicaoElementoLista != i)
			{
				TST_NotificarFalha( " Numero de elementos indicados não condiz com contagem dos elementos. " ) ;
				CNT_CONTAR( "LIS_VerificarLista_E17" ) ;
				return LIS_CondRetDeturpacao;
			}
			CNT_CONTAR( "LIS_VerificarLista_w" ) ;
			if(aux != pLista->pFimLista)
			{
				TST_NotificarFalha( " pFimLista não aponta para o fim da lista OU percorrimento não alcançou o fim da lista " ) ;
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
						TST_NotificarFalha( " NumCorrente não condiz. É o último" ) ;
						CNT_CONTAR( "LIS_VerificarLista_E19" ) ;
						return LIS_CondRetDeturpacao;
					}
				}
			CNT_CONTAR( "LIS_VerificarLista_aa" ) ;
			if(corrOk != 1)
			{
				TST_NotificarFalha( " Elemento corrente não foi percorrido " ) ;
				CNT_CONTAR( "LIS_VerificarLista_E20" ) ;
				return LIS_CondRetDeturpacao;
			}

		}
		CNT_CONTAR( "LIS_VerificarLista_ab" ) ;
		//Fim verificar para o conjunto de elementos e cabeça

		return LIS_CondRetOK;
		
   }
#endif

//******************Fim função LIS_VerificaLista



/***********************************************************************
*
*  $FC Função: LIS  - Deturpa Lista.
*
*  $ED Descrição da função
*     Deturpa a lista de alguma maneiras diferente, determinadas pelo parametro char passado. Usável em modo _DEBUG
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
      

   } /* Fim função: LIS  - Deturpar lista */
#endif





/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: LIS  -Liberar elemento da lista
*
*  $ED Descrição da função
*     Elimina os espaços apontados pelo valor do elemento e o
*     próprio elemento.
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

   } /* Fim função: LIS  -Liberar elemento da lista */


/***********************************************************************
*
*  $FC Função: LIS  -Criar o elemento
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

   } /* Fim função: LIS  -Criar o elemento */


/***********************************************************************
*
*  $FC Função: LIS  -Limpar a cabeça da lista
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

   } /* Fim função: LIS  -Limpar a cabeça da lista */


/***********************************************************************
*
*  $FC Função: LIS  - incrementar posições da lista a partir de. Só disponível no modo _DEBUG
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
*  $FC Função: LIS  - decrementar posições da lista a partir de. Só disponível no modo _DEBUG
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
*  $FC Função: LIS  - Verificar corretude de um único elemento. Função auxiliar chamada em LIS_VerificarLista() para cada elemento. Só disponível no modo _DEBUG
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
				TST_NotificarFalha( "Controle do espaço acusou erro em um elemento" ) ;
				CNT_CONTAR( "LIS_VerificarElem_E1" ) ;
				return LIS_CondRetDeturpacao ;
			 } /* if */
		   CNT_CONTAR( "LIS_VerificarElem_b" ) ;
			if (CED_ObterTipoEspaco(Elem) != LIS_TipoEspacoElem)
			{
				TST_NotificarFalha( "Um elemento da lista não foi definido como LIS_TipoEspacoElem. " ) ;
				CNT_CONTAR( "LIS_VerificarElem_E2" ) ;
				return LIS_CondRetDeturpacao;
			} /* if */
			CNT_CONTAR( "LIS_VerificarElem_c" ) ;
			if (CED_ObterTamanhoValor(Elem) != sizeof(tpElemLista))
			{
				TST_NotificarFalha( "Um elemento da Lista não tem o tamanho certo. " ) ;
				CNT_CONTAR( "LIS_VerificarElem_E3" ) ;
				return LIS_CondRetDeturpacao;
			} /* if */
			CNT_CONTAR( "LIS_VerificarElem_d" ) ;
			if(pLista != Elem->ponteiroCabeca )
			{
				TST_NotificarFalha( " Um elemento da Lista não está com o ponteiro para cabeça correta. " );
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



/********** Fim do módulo de implementação: LIS  Lista duplamente encadeada **********/

