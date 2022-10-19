#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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