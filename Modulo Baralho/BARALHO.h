/*

M�dulo de Defini��o: BAR m�dulo baralho

arquivo gerado:BARALHO.h
letras identificadoras: BAR

Para o trabalho T2 da disciplina Programa��o Modular na PUC-RIO, professor Alessandro. 2016.1

Autores: Andr�, Danillo e Albert
Descri��o do m�dulo:
	O m�dulo implementa utilidades de baralho que podem ser utilizadas para jogos de cartas. S�o definidos os tipos: 'carta' e 'baralho', e 
	fun��es para manipul�-los.
	O m�dulo usa os m�dulos lista duplamente encadeada( LISTA.h) e gerador de aleat�rios (GERAALT.h)


*/

#include "LISTA.h"
#include "GERAALT.h"


#define struct carta Carta{
	char naipe;
	int numero;
}

#define struct baralho Baralho;


/* ***************************************
	BAR_Inicializar() : 
		Inicializa o baralho. Essa fun��o deve ser chamada uma vez antes das outras fun��es do m�dulo serem utilizadas.
*/	
	
void BAR_Inicializar();

//88888888888888888888888888888888888888888

/* ******************************************
	
	BAR_CriarBaralho() : 
		Cria um novo baralho vazio e retorna um ponteiro para o mesmo.

*/
	Baralho* BAR_CriarBaralho();

//88888888888888888888888888888888888888888

/**********************

	Carta* BAR_PedirCarta(Baralho* baralho) : 
		Remove uma carta aleat�ria do baralho, e retorna um ponteiro para ela. Se o baralho est� vazio, s� retorna NULL.  
		Par�metros:
			baralho � ponteiro para baralho do qual a carta ser� removida
		Valor de retorno: um ponteiro para uma carta ou NULL.
*/

	Carta* BAR_PedirCarta(Baralho* baralho);

//8888888888888888888888888888888888888	
	
/*

	Baralho* BAR_DevolverCarta(Baralho* baralho, Carta* devolucao) :
		Devolve para o baralho a carta passada como par�metro. Retorna o baralho atualizado. 
		Par�metros:
			baralho � ponteiro para o  baralho para qual a carta ser� devolvida
			devolucao � ponteiro para a carta que ser� devolvida ao baralho
			Valor de retorno: um ponteiro para o baralho atualizado.
*/

	Baralho* BAR_DevolverCarta(Baralho* baralho, Carta* devolucao);

//888888888888888888888888888888888888888888


/*
	Baralho* BAR_SetarBaralho(Baralho* baralho) :
		Transforma qualquer baralho passado como par�metro em um baralho convencional com 54 cartas. Jokers inclu�dos. Retorna o baralho atualizado.
		Par�metros:
			baralho � ponteiro para baralho que ser� transformado
		Valor de retorno: um ponteiro para o baralho atualizado

*/
	Baralho* BAR_SetarBaralho(Baralho* baralho);

//888888888888888888888888888888888888888888888


/*
	BAR_SetarBaralhoTruco(Baralho* baralho) : 
		Transforma qualquer baralho passado como par�metro em um baralho de truco com 40 cartas. Retorna o baralho atualizado
		Par�metros: 
			baralho � ponteiro para o baralho que ser� transformado
		Valor de retorno: um ponteiro para o baralho atualizado
*/

	BAR_SetarBaralhoTruco(Baralho* baralho);

//888888888888888888888888888888888888888888888


/*
	void BAR_DestruirBaralho(Baralho* baralho) :
		Desaloca o baralho passado e suas cartas.
		Par�metros: 
			baralho � ponteiro para o baralho que ser� transformado
*/
	BAR_DestruirBaralho(Baralho* baralho);

//8888888888888888888888888888888888888888







// fim de BARALHO.h