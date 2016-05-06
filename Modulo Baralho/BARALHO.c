#include "BARALHO.h"

struct baralho{

}



/* ***************************************
	BAR_Inicializar() : 
		Inicializa o baralho. Essa função deve ser chamada uma vez antes das outras funções do módulo serem utilizadas.
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
		Remove uma carta aleatória do baralho, e retorna um ponteiro para ela. Se o baralho está vazio, só retorna NULL.  
		Parâmetros:
			baralho – ponteiro para baralho do qual a carta será removida
		Valor de retorno: um ponteiro para uma carta ou NULL.
*/

	Carta* BAR_PedirCarta(Baralho* baralho)
	{
	}

//8888888888888888888888888888888888888	
	
/*

	Baralho* BAR_DevolverCarta(Baralho* baralho, Carta* devolucao) :
		Devolve para o baralho a carta passada como parâmetro. Retorna o baralho atualizado. 
		Parâmetros:
			baralho – ponteiro para o  baralho para qual a carta será devolvida
			devolucao – ponteiro para a carta que será devolvida ao baralho
			Valor de retorno: um ponteiro para o baralho atualizado.
*/

	Baralho* BAR_DevolverCarta(Baralho* baralho, Carta* devolucao)
	{
	}

//888888888888888888888888888888888888888888


/*
	Baralho* BAR_SetarBaralho(Baralho* baralho) :
		Transforma qualquer baralho passado como parâmetro em um baralho convencional com 54 cartas. Jokers incluídos. Retorna o baralho atualizado.
		Parâmetros:
			baralho – ponteiro para baralho que será transformado
		Valor de retorno: um ponteiro para o baralho atualizado

*/
	Baralho* BAR_SetarBaralho(Baralho* baralho)
	{
	}

//888888888888888888888888888888888888888888888


/*
	BAR_SetarBaralhoTruco(Baralho* baralho) : 
		Transforma qualquer baralho passado como parâmetro em um baralho de truco com 40 cartas. Retorna o baralho atualizado
		Parâmetros: 
			baralho – ponteiro para o baralho que será transformado
		Valor de retorno: um ponteiro para o baralho atualizado
*/

	BAR_SetarBaralhoTruco(Baralho* baralho)
	{
	}

//888888888888888888888888888888888888888888888


/*
	void BAR_DestruirBaralho(Baralho* baralho) :
		Desaloca o baralho passado e suas cartas.
		Parâmetros: 
			baralho – ponteiro para o baralho que será transformado
*/
	BAR_DestruirBaralho(Baralho* baralho)
	{
	}

//8888888888888888888888888888888888888888







// fim de BARALHO.c