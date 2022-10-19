#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void criarLabirinto (char*** labirinto, int linha, int coluna)
{
	*labirinto = (char**) malloc (linha*sizeof(char*));
	for (int a=0; a<coluna; a++)
		(*labirinto)[a] = (char*) malloc (coluna*sizeof(char));
}