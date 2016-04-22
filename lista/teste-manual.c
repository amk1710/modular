#include <stdio.h>
#include <string.h>
#include "lista.h"



void liberaString(char *s)
{
	free(s);
}

int main(void)
{
	LIS_tppLista *pLista  = LIS_CriarLista(void   ( * liberaString ) ( void * char ) ) ;
	LIS_DestruirLista(pLista);
	return 0;
}