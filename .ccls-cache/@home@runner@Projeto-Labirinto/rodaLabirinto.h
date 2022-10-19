#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "config_labirinto.h"

void criarLabirintoCaminho(Labirinto* lab, Labirinto lb)
{
	int distancia=0, terminou=0;
	lab->labMenorCaminho[lb.lczQueijo_X][lb.lczQueijo_Y] = 0;
	while (terminou==0)
	{
		terminou=1;
		for (int a=1; a<lb.linha; a++)
		{
			for (int b=1; b<lb.coluna; b++)
			{
				if(lab->labMenorCaminho[a][b]==distancia)
				{
					if(lab->labMenorCaminho[a+1][b]==-1)
						lab->labMenorCaminho[a+1][b]=distancia+1;
					if(lab->labMenorCaminho[a-1][b]==-1)
						lab->labMenorCaminho[a-1][b]=distancia+1;
					if(lab->labMenorCaminho[a][b+1]==-1)
						lab->labMenorCaminho[a][b+1]=distancia+1;
					if(lab->labMenorCaminho[a][b-1]==-1)
						lab->labMenorCaminho[a][b-1]=distancia+1;
					terminou=0;
				}
			}
		}
		distancia++;
	}
	lab->labMenorCaminho[lb.lczRato_X][lb.lczRato_Y] = 33;
	lab->labBase[lb.lczQueijo_X][lb.lczQueijo_Y] = 99;
	lab->labBase[lb.lczRato_X][lb.lczRato_Y] = 33;
}

void criarLabirintoFinal(Labirinto* lab, Labirinto lb)
{
	if (lb.possibilidades>=1)
	{
		int nr_passos, passo, outros;
		int dist_X, dist_Y;
		int **caminhos;
		
		outros=lab->possibilidades;
		nr_passos = lb.labMenorCaminho[lb.lczRato_X][lb.lczRato_Y];
		passo = nr_passos;
		dist_X=lb.lczRato_X;
		dist_Y=lb.lczRato_Y;
		
		caminhos = (int**) malloc((lab->possibilidades)*sizeof(int*));
		for(int a=0; a<(lab->possibilidades); a++)
		{
			caminhos[a] = (int*) malloc((passo*2)*sizeof(int));
			caminhos[a][0] = lb.lczRato_X;
		    caminhos[a][1] = lb.lczRato_Y;
		}
		
		for(int h=0; h<(lab->possibilidades); h++)
		{	
			for(int i=1; i<=nr_passos*2; i+=2)
			{
				if(lb.labMenorCaminho[dist_X-1][dist_Y]==passo-1)
				{
					dist_X--;
				}
			    else if(lb.labMenorCaminho[dist_X+1][dist_Y]==passo-1)
			    {
					dist_X++;
				}
			    else if(lb.labMenorCaminho[dist_X][dist_Y-1]==passo-1)
			    {
					dist_Y--;
				}
			    else if(lb.labMenorCaminho[dist_X][dist_Y+1]==passo-1)
			    {
					dist_Y++;
				}
				caminhos[h][i] = dist_X;
		    	caminhos[h][i+1] = dist_Y;
		    	passo--;
			}
		}		
	}
}

void verificaExisteResolucao (Labirinto* lab, Labirinto lb)
{
	if(lb.labMenorCaminho[lb.lczRato_X+1][lb.lczRato_Y]==-1)
		lab->possibilidades=0;
	else if(lb.labMenorCaminho[lb.lczRato_X-1][lb.lczRato_Y]==-1)
		lab->possibilidades=0;
	else if(lb.labMenorCaminho[lb.lczRato_X][lb.lczRato_Y+1]==-1)
		lab->possibilidades=0;
	else if(lb.labMenorCaminho[lb.lczRato_X][lb.lczRato_Y-1]==-1)
		lab->possibilidades=0;
	else if(lb.labMenorCaminho[lb.lczRato_X+1][lb.lczRato_Y]==-2 && 
			lb.labMenorCaminho[lb.lczRato_X-1][lb.lczRato_Y-1]==-2 && 
			lb.labMenorCaminho[lb.lczRato_X][lb.lczRato_Y+1]==-2 && 
			lb.labMenorCaminho[lb.lczRato_X][lb.lczRato_Y-1]==-2)
		lab->possibilidades=-1;
	else
	{
		lab->possibilidades=1;
	}
		
}

void imprimirLabirintoBase (Labirinto lb)
{
	for (int u=0; u<lb.linha_m; u++)
	{
		for (int v=0; v<lb.coluna_m; v++)
		{
			printf("%d", lb.labBase[u][v]);
		}
		printf("\n");
	}
}

void imprimirLabirintoMenorCaminho (Labirinto lb)
{
	for (int w=0; w<lb.linha_m; w++)
	{
		for (int x=0; x<lb.coluna_m; x++)
		{
			printf("%d ", lb.labMenorCaminho[w][x]);
		}
		printf("\n");
	}
}

void imprimirLabirintoFinal (Labirinto lb)
{
	for (int x=0; x<lb.possibilidades; x++)
	{
		for (int y=0; y<lb.linha_m; y++)
		{
			for (int z=0; z<lb.coluna_m; z++)
			{
				printf("%d", lb.labEstrutura[0][y][z]);
			}
			printf("\n");
		}
	}
		
}

void imprimirExisteResolucao (Labirinto lb)
{
	if(lb.possibilidades==-1)
	printf("Não há resolução para este labirinto,\nhá paredes em todos os cantos do rato!");
	else if(lb.possibilidades==0)
		printf("Não há resolução para este labirinto,\nhá um bloqueio no meio do caminho!");
	else
		printf("Oi");
}