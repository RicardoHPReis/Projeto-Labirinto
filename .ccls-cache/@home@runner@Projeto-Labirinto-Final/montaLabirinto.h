#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "config_labirinto.h"

void primeiroLabirinto (Labirinto* lab)
{
	int base[12][12] = {
	{-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, }, //1
	{-2, -1, -2, -1, -1, -1, -1, -1, -1, -1, -2, -2, }, //2
	{-2, -1, -2, -1, -1, -2, -2, -2, -1, -1, -2, -2, }, //3
	{-2, -1, -2, -2, -2, -2, -1, -2, -1, -1, -2, -2, }, //4
	{-2, -1, -1, -1, -1, -1, -1, -2, -2, -1, -1, -2, }, //5
	{-2, -1, -1, -1, -1, -1, -1, -1, -2, -1, -1, -2, }, //6
	{-2, -1, -1, -1, -2, -1, -1, -1, -2, -1, -1, -2, }, //7
	{-2, -1, -1, -1, -2, -1, -1, -1, -1, -1, -1, -2, }, //8
	{-2, -1, -2, -2, -2, -1, -2, -2, -2, -2, -1, -2, }, //9
	{-2, -1, -1, -1, -1, -1, -1, -1, -1, -2, -1, -2, }, //10
	{-2, -2, -2, -2, -2, -1, -1, -1, -1, -1, -1, -2, }, //11
	{-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, }}; //12

	lab->linha=10, lab->coluna=10;
	lab->linha_m=lab->linha+2, lab->coluna_m=lab->coluna+2; 
	
	lab->labBase = (int**) malloc (12*sizeof(int*));
	for (int z=0; z<12; z++)
		(lab->labBase)[z] = (int*) malloc (12*sizeof(int));
	
	for (int y=0; y<12; y++)
	{
		for (int x=0; x<12; x++)
			(lab->labBase)[y][x] = base[y][x];
	}
}

void montarLabirintoAleatorio (Labirinto* lab, Labirinto lb)
{
	int numero;
	srand(time(NULL));
	lab->labBase = (int**) malloc ((lb.linha_m)*sizeof(int*));
	for (int a=0; a<lb.linha_m; a++)
		(lab->labBase)[a] = (int*) malloc ((lb.coluna_m)*sizeof(int));
	
	for (int h=0; h<lb.coluna_m; h++)
	{
		(lab->labBase)[0][h] = -2;
		(lab->labBase)[lb.linha_m-1][h] = -2;
	}
	for (int i=0; i<lb.linha_m; i++)
	{
		(lab->labBase)[i][0] = -2;	
		(lab->labBase)[i][lb.coluna_m-1] = -2;
	}
	for (int j=1; j<=lb.linha; j++)
	{
		for (int k=1; k<=lb.coluna; k++)
		{
			numero = rand()%4;
			if(numero==0)
				(lab->labBase)[j][k] = -2;
			else
				(lab->labBase)[j][k] = -1;
		}
	}
}


void montarLabirinto(Labirinto* lab, Labirinto lb)
{
	int erro, *tamanho;
	char letra;
	char **criar;
	lab->labCriacao = (char**) malloc ((lb.linha_m)*sizeof(char*));
	for (int a=0; a<lb.linha_m; a++)
		(lab->labCriacao)[a] = (char*) malloc ((lb.coluna_m)*sizeof(char));
	
	criar = (char**) malloc ((lb.linha)*sizeof(char*));
	for (int b=0; b<lb.linha; b++)
		criar[b] = (char*) malloc (2*sizeof(char));

	tamanho = (int*) malloc (lb.linha*sizeof(int));
    
	titulo_Menu();
    titulo_Menu_Detalhamento(0, 1);
    printf("Desenhe a figura linha por linha:\n\n");
    for (int i = 0; i < lb.linha; i++) 
	{
		erro = 0;
		scanf(" %c", &letra);

	    for (tamanho[i] = 0; letra != '\n'; tamanho[i]++)
	    {
	        criar[i][tamanho[i]] = letra;
	        criar[i] = (char*) realloc(criar[i], (tamanho[i] + 3)*sizeof(char));
	        scanf("%c", &letra);
	    }
	    criar[i][tamanho[i] + 1] = '\0';
		
    	for (int j = 0; j < lb.coluna; j++) 
		{
	        if (criar[i][j] != lb.parede && criar[i][j] != lb.chao)
	        	erro = 2;
			if (criar[i][j]=='\n')
			{
				erro += 1;
				break;
			}
      	}
    	if (erro != 0) 
		{
			if (erro==1)
		        aviso_Erro(6);
			else if (erro==2)
				aviso_Erro(7);
			else if (erro==3)
				aviso_Erro(8);
	        titulo_Menu();
	        titulo_Menu_Detalhamento(0, 1);
	        printf("Desenhe a figura linha por linha:\n\n");
			for (int k = 0; k < i; k++) 
			{
				for (int l = 0; l < lb.coluna; l++) 
				{
					printf("%c", criar[k][l]);
				}
				printf("\n");
			}
			i -= 1;
    	}
	}
	
	for (int y=0; y<lb.linha; y++)
	{
		for (int z=0; z<lb.coluna; z++)
		{
			(lab->labCriacao)[y+1][z+1]=criar[y][z];
		}
	}
	for (int m=0; m<lb.linha_m; m++)
	{
		(lab->labCriacao)[0][m] = lb.parede;
		(lab->labCriacao)[lb.coluna_m-1][m] = lb.parede;
	}
	for (int n=0; n<lb.coluna_m; n++)
	{
		(lab->labCriacao)[n][0] = lb.parede;
		(lab->labCriacao)[n][lb.linha_m-1] = lb.parede;
	}
	
	for (int l = 0; l <lb.linha; l++) 
	{
		free(criar[l]);
	}
	free(criar);
	free(tamanho);
	system(LIMPA);
	return;
}

void transformaLabirinto(Labirinto* lab, Labirinto lb)
{
	lab->labBase = (int**) malloc ((lb.linha_m)*sizeof(int*));
	for (int a=0; a<lb.linha_m; a++)
		(lab->labBase)[a] = (int*) malloc ((lb.coluna_m)*sizeof(int));
	
	for (int b=0; b<lb.linha_m; b++)
	{
		for (int c=0; c<lb.coluna_m; c++)
		{
			if((lab->labCriacao)[b][c] == lb.parede)
				(lab->labBase)[b][c] = -2;
			else
				(lab->labBase)[b][c] = -1;
		}
	}
}

void verificaExisteResolucao (Labirinto* lab, Labirinto lb)
{
	if(lb.labMenorCaminho[lb.lczRato_X+1][lb.lczRato_Y]==-1)
		lab->existe_caminho=0;
	else if(lb.labMenorCaminho[lb.lczRato_X-1][lb.lczRato_Y]==-1)
		lab->existe_caminho=0;
	else if(lb.labMenorCaminho[lb.lczRato_X][lb.lczRato_Y+1]==-1)
		lab->existe_caminho=0;
	else if(lb.labMenorCaminho[lb.lczRato_X][lb.lczRato_Y-1]==-1)
		lab->existe_caminho=0;
	else if(lb.labMenorCaminho[lb.lczRato_X+1][lb.lczRato_Y]==-2 && 
			lb.labMenorCaminho[lb.lczRato_X-1][lb.lczRato_Y-1]==-2 && 
			lb.labMenorCaminho[lb.lczRato_X][lb.lczRato_Y+1]==-2 && 
			lb.labMenorCaminho[lb.lczRato_X][lb.lczRato_Y-1]==-2)
		lab->existe_caminho=-1;
	else
	{
		lab->existe_caminho=1;
	}
}

void criarLabirintoCaminho(Labirinto* lab, Labirinto lb)
{
	int distancia=0, terminou=0;
	lab->labMenorCaminho = (int**) malloc ((lb.linha_m)*sizeof(int*));
	for (int a=0; a<lb.linha_m; a++)
		(lab->labMenorCaminho)[a] = (int*) malloc ((lb.coluna_m)*sizeof(int));
	lab->labMenor = (char**) malloc ((lb.linha_m)*sizeof(char*));
	for (int b=0; b<lb.linha_m; b++)
		(lab->labMenor)[b] = (char*) malloc ((lb.coluna_m)*sizeof(char));
	
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
	for (int c=1; c<lb.linha; c++)
	{
		for (int d=1; d<lb.coluna; d++)
		{
			if(lab->labMenorCaminho[c][d]==-2)
				lab->labMenor[c][d]='.';
			else
				lab->labMenor[c][d]=lab->labMenorCaminho[c][d];
		}
	}
	lab->labMenorCaminho[lb.lczRato_X][lb.lczRato_Y] = 33;
	lab->labMenor[lb.lczRato_X][lb.lczRato_Y] = 'R';
	lab->labMenor[lb.lczQueijo_X][lb.lczQueijo_Y] = 'Q';
	lab->labBase[lb.lczQueijo_X][lb.lczQueijo_Y] = 99;
	lab->labBase[lb.lczRato_X][lb.lczRato_Y] = 33;
}

void criarLabirintoFinal(Labirinto* lab, Labirinto lb)
{
	verificaExisteResolucao (lab, lb);
	if (lb.existe_caminho==1)
	{
		int nr_passos, passo, outros;
		int dist_X, dist_Y;
		int *caminho;
		
		outros=lab->existe_caminho;
		nr_passos = lb.labMenorCaminho[lb.lczRato_X][lb.lczRato_Y];
		passo = nr_passos;
		dist_X=lb.lczRato_X;
		dist_Y=lb.lczRato_Y;

		lab->labEstrutura = (char**) malloc ((lb.linha_m)*sizeof(char*));
	for (int a=0; a<lb.linha_m; a++)
		(lab->labEstrutura)[a] = (char*) malloc ((lb.coluna_m)*sizeof(char));
		caminho = (int*) malloc((nr_passos*2)*sizeof(int));
		
		caminho[0] = lb.lczRato_X;
		caminho[1] = lb.lczRato_Y;	
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
			caminho[i] = dist_X;
		   	caminho[i+1] = dist_Y;
		   	passo--;
		}		
	}
}

void imprimirLabirintoBase (Labirinto lb)
{
	for (int u=0; u<lb.linha_m; u++)
	{
		for (int v=0; v<lb.coluna_m; v++)
		{
			printf("%d ", lb.labBase[u][v]);
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
			if(lb.labMenorCaminho[w][x]>=10 || lb.labMenorCaminho[w][x]<=-1)
				printf("%d ", lb.labMenorCaminho[w][x]);
			else
				printf("%d  ", lb.labMenorCaminho[w][x]);
		}
		printf("\n");
	}
}

void imprimirLabirintoMenor (Labirinto lb)
{
	for (int w=0; w<lb.linha_m; w++)
	{
		for (int x=0; x<lb.coluna_m; x++)
		{
			if(lb.labMenorCaminho[w][x]>=10)
				printf("%c ", lb.labMenor[w][x]);
			else
				printf("%c  ", lb.labMenor[w][x]);
		}
		printf("\n");
	}
}

void imprimirLabirintoFinal (Labirinto lb)
{
	for (int y=0; y<lb.linha_m; y++)
	{
		for (int z=0; z<lb.coluna_m; z++)
		{
			printf("%c ", lb.labEstrutura[y][z]);
		}
		printf("\n");
	}	
}

void imprimirExisteResolucao (Labirinto lb)
{
	if(lb.existe_caminho==-1)
	printf("Não há resolução para este labirinto,\nhá paredes em todos os cantos do rato!");
	else if(lb.existe_caminho==0)
		printf("Não há resolução para este labirinto,\nhá um bloqueio no meio do caminho!");
	else
		printf("É necessário, no mínimo, %d passos\npara o rato chegar no queijo", lb.labMenorCaminho[lb.lczRato_X][lb.lczRato_Y]);
}