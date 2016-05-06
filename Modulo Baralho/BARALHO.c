#include "BARALHO.h"

struct baralho{

}



/* ***************************************
	BAR_Inicializar() : 
		Inicializa o baralho. Essa fun��o deve ser chamada uma vez antes das outras fun��es do m�dulo serem utilizadas.
*/	
	
void BAR_Inicializar()
{
}

//88888888888888888888888888888888888888888

/* ******************************************
	
	BAR_CriarBaralho() : 
		Cria um novo baralho vazio e retorna um ponteiro para o mesmo.

*/
	Baralho* BAR_CriarBaralho()
	{
	}

//88888888888888888888888888888888888888888

/**********************

	Carta* BAR_PedirCarta(Baralho* baralho) : 
		Remove uma carta aleat�ria do baralho, e retorna um ponteiro para ela. Se o baralho est� vazio, s� retorna NULL.  
		Par�metros:
			baralho � ponteiro para baralho do qual a carta ser� removida
		Valor de retorno: um ponteiro para uma carta ou NULL.
*/

	Carta* BAR_PedirCarta(Baralho* baralho)
	{
	}

//8888888888888888888888888888888888888	
	
/*

	Baralho* BAR_DevolverCarta(Baralho* baralho, Carta* devolucao) :
		Devolve para o baralho a carta passada como par�metro. Retorna o baralho atualizado. 
		Par�metros:
			baralho � ponteiro para o  baralho para qual a carta ser� devolvida
			devolucao � ponteiro para a carta que ser� devolvida ao baralho
			Valor de retorno: um ponteiro para o baralho atualizado.
*/

	Baralho* BAR_DevolverCarta(Baralho* baralho, Carta* devolucao)
	{
	}

//888888888888888888888888888888888888888888


/*
	Baralho* BAR_SetarBaralho(Baralho* baralho) :
		Transforma qualquer baralho passado como par�metro em um baralho convencional com 54 cartas. Jokers inclu�dos. Retorna o baralho atualizado.
		Par�metros:
			baralho � ponteiro para baralho que ser� transformado
		Valor de retorno: um ponteiro para o baralho atualizado

*/
	Baralho* BAR_SetarBaralho(Baralho* baralho)
	{
	}

//888888888888888888888888888888888888888888888


/*
	BAR_SetarBaralhoTruco(Baralho* baralho) : 
		Transforma qualquer baralho passado como par�metro em um baralho de truco com 40 cartas. Retorna o baralho atualizado
		Par�metros: 
			baralho � ponteiro para o baralho que ser� transformado
		Valor de retorno: um ponteiro para o baralho atualizado
*/

	BAR_SetarBaralhoTruco(Baralho* baralho)
	{
	}

//888888888888888888888888888888888888888888888


/*
	void BAR_DestruirBaralho(Baralho* baralho) :
		Desaloca o baralho passado e suas cartas.
		Par�metros: 
			baralho � ponteiro para o baralho que ser� transformado
*/
	BAR_DestruirBaralho(Baralho* baralho)
	{
	}

//8888888888888888888888888888888888888888







// fim de BARALHO.c