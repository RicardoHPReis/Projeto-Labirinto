#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "config_labirinto.h"

void primeiroLabirinto (Labirinto *lab)
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
	for (int a=0; a<12; a++)
		(lab->labBase)[a] = (int*) malloc (12*sizeof(int));
	
	for (int b=0; b<12; b++)
	{
		for (int c=0; c<12; c++)
			(lab->labBase)[b][c] = base[b][c];
	}
}



void montarLabirintoAleatorio (Labirinto *lab, Labirinto lb)
{
	int numero;
	srand(time(NULL));
	lab->labBase = (int**) malloc ((lb.linha_m)*sizeof(int*));
	for (int d=0; d<lb.linha_m; d++)
		(lab->labBase)[d] = (int*) malloc ((lb.coluna_m)*sizeof(int));
	
	for (int e=0; e<lb.coluna_m; e++)
	{
		(lab->labBase)[0][e] = -2;
		(lab->labBase)[lb.linha_m-1][e] = -2;
	}
	for (int f=0; f<lb.linha_m; f++)
	{
		(lab->labBase)[f][0] = -2;	
		(lab->labBase)[f][lb.coluna_m-1] = -2;
	}
	for (int g=1; g<=lb.linha; g++)
	{
		for (int h=1; h<=lb.coluna; h++)
		{
			numero = rand()%lb.chance;
			if(numero==0)
				(lab->labBase)[g][h] = -2;
			else
				(lab->labBase)[g][h] = -1;
		}
	}
	system(LIMPA);
}


void montarLabirinto(Labirinto *lab, Labirinto lb)
{
	int erro, *tamanho;
	char letra;
	char **criar;
	lab->labCriacao = (char**) malloc ((lb.linha_m)*sizeof(char*));
	for (int i=0; i<lb.linha_m; i++)
		(lab->labCriacao)[i] = (char*) malloc ((lb.coluna_m)*sizeof(char));
	
	criar = (char**) malloc ((lb.linha)*sizeof(char*));
	for (int j=0; j<lb.linha; j++)
		criar[j] = (char*) malloc (2*sizeof(char));

	tamanho = (int*) malloc (lb.linha*sizeof(int));
    
	titulo_Menu();
    titulo_Menu_Detalhamento(0, 1);
    printf("Desenhe a figura linha por linha:\n\n");
    for (int k = 0; k < lb.linha; k++) 
	{
		erro = 0;
		scanf(" %c", &letra);

	    for (tamanho[k] = 0; letra != '\n'; tamanho[k]++)
	    {
	        criar[k][tamanho[k]] = letra;
	        criar[k] = (char*) realloc(criar[k], (tamanho[k] + 3)*sizeof(char));
	        scanf("%c", &letra);
	    }
	    criar[k][tamanho[k] + 1] = '\0';
		
    	for (int l = 0; l < lb.coluna; l++) 
		{
	        if (criar[k][l] != lb.parede && criar[k][l] != lb.chao)
	        	erro = 2;
			if (criar[k][l]=='\n')
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
			for (int m = 0; m < k; m++) 
			{
				for (int n = 0; n < lb.coluna; n++) 
				{
					printf("%c", criar[m][n]);
				}
				printf("\n");
			}
			k -= 1;
    	}
	}
	
	for (int o=0; o<lb.linha; o++)
	{
		for (int p=0; p<lb.coluna; p++)
		{
			(lab->labCriacao)[o+1][p+1]=criar[o][p];
		}
	}
	for (int q=0; q<lb.linha_m; q++)
	{
		(lab->labCriacao)[0][q] = lb.parede;
		(lab->labCriacao)[lb.coluna_m-1][q] = lb.parede;
	}
	for (int r=0; r<lb.coluna_m; r++)
	{
		(lab->labCriacao)[r][0] = lb.parede;
		(lab->labCriacao)[r][lb.linha_m-1] = lb.parede;
	}
	
	for (int s = 0; s <lb.linha; s++) 
	{
		free(criar[s]);
	}
	free(criar);
	free(tamanho);
	system(LIMPA);
	return;
}



void transformaLabirinto(Labirinto *lab, Labirinto lb)
{
	lab->labBase = (int**) malloc ((lb.linha_m)*sizeof(int*));
	for (int t=0; t<lb.linha_m; t++)
		(lab->labBase)[t] = (int*) malloc ((lb.coluna_m)*sizeof(int));
	
	for (int u=0; u<lb.linha_m; u++)
	{
		for (int v=0; v<lb.coluna_m; v++)
		{
			if((lab->labCriacao)[u][v] == lb.parede)
				(lab->labBase)[u][v] = -2;
			else
				(lab->labBase)[u][v] = -1;
		}
	}
	for (int w=0; w<lb.linha_m; w++) 
	{
		free((lab->labCriacao)[w]);
	}
	free(lab->labCriacao);
}



void apagaArquivoCSV ()
{
	char line[200];
	
	FILE *arquivo = fopen("labirinto.csv", "r");
	if(!arquivo)
	{
		perror("Não foi possível achar o arquivo labirinto.csv.");
		exit(1);
	}
	
	while (fgets(line, 200, arquivo))
	{
		remove(line);
	}
	
	fclose(arquivo);
}



void tamanhoArquivoCSV (Labirinto *lab)
{
	do
	{
    	titulo_Menu();
    	titulo_Menu_Detalhamento(0, 3);
    	printf("Escolha a quantidade de linhas que será usado (O mínimo é 1): ");
    	scanf("%d", &lab->linha);
    	if (lab->linha < 1)
        	aviso_Erro(3);
    }
	while (lab->linha < 1);
}



void escreveLabirintoArquivoCSV (Labirinto *lab, Labirinto lb)
{
	char *string, letra;
	int tamanho;

	string = (char*) malloc (2*sizeof(char));

	system(LIMPA);
	titulo_Menu();
   	titulo_Menu_Detalhamento(0, 4);
	
	FILE *arquivo = fopen("labirinto.csv", "w");
	if(!arquivo)
	{
		perror("Não foi possível achar o arquivo labirinto.csv.");
		exit(1);
	}
	
	for(int x=1; x<=lb.linha; x++)
	{
		scanf(" %c", &letra);
		fprintf(arquivo, "%c", letra);
	    for (tamanho = 0; letra != '\n'; tamanho++)
	    {
			scanf("%c", &letra);
	        string[tamanho] = letra;
	        string = (char*) realloc(string, (tamanho+3)*sizeof(char));
			if(x!=lb.linha || letra!='\n')
				fprintf(arquivo, "%c", letra);
	    }
	}
	system(LIMPA);
	free(string);
	fclose(arquivo);
}



void descobreValoresArquivoCSV (Labirinto *lab)
{
	char previa[200], *token;
	int numero, lineMatriz=0, nmMatriz=1;
	
	FILE *arquivo = fopen("labirinto.csv", "r");
	if(!arquivo)
	{
		perror("Não foi possível ler o arquivo labirinto.csv.");
		exit(1);
	}
	
	while (fgets(previa, 200, arquivo))
	{
		token = strtok(previa, ",");
		while(token!=NULL)
		{
			numero = abs(atoi(token));
			if(nmMatriz==1)
			{
				lab->maior = numero;
			}
			else
			{
				if(numero!=0)
				{
					lab->maior = (numero+lab->maior+abs(numero-lab->maior))/2;
				}
			}
			token = strtok(NULL, ",");
			nmMatriz++;
		}
		lineMatriz++;
	}
	lab->linha = lineMatriz;
	lab->linha_m = lab->linha+2;
	lab->coluna = lab->maior;
	lab->coluna_m = lab->coluna+2;
}



void montaLabirintoArquivoCSV (Labirinto *lab, Labirinto lb)
{
	char line[200], *token;
	int numero, lineMatriz=1;

	(lab->labBase) = (int**) malloc (lb.linha_m*sizeof(int*));
	for(int y=0; y<lb.linha_m; y++)
	{
		(lab->labBase)[y] = (int*) malloc (lb.coluna_m*sizeof(int));
	}
	
	FILE *arquivo = fopen("labirinto.csv", "r");
	if(!arquivo)
	{
		perror("Não foi possível ler o arquivo labirinto.csv.");
		exit(1);
	}
	
	while (fgets(line, 200, arquivo))
	{
		token = strtok(line, ",");
		while(token!=NULL)
		{
			numero = abs(atoi(token));
			(lab->labBase)[lineMatriz][numero] = -2;
			token = strtok(NULL, ",");
		}
		lineMatriz++;
	}
	
	for (int z=0; z<lb.coluna_m; z++)
	{
		(lab->labBase)[0][z] = -2;
		(lab->labBase)[lb.linha_m-1][z] = -2;
	}
	
	for (int a=0; a<lb.linha_m; a++)
	{
		(lab->labBase)[a][0] = -2;
		(lab->labBase)[a][lb.coluna_m-1] = -2;
	}
	
	for (int b=1; b<=lb.linha; b++)
	{
		for (int c=1; c<=lb.coluna; c++)
		{
			if((lab->labBase)[b][c] == 0)
				(lab->labBase)[b][c] = -1;
		}
	}
	free(token);
	fclose(arquivo);
}



void verificaExisteResolucao (Labirinto *lab, Labirinto lb)
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

//Rever a partir daqui ->d

void criarLabirintoCaminho(Labirinto *lab, Labirinto lb)
{
	int distancia=0, terminou=0;
	
	lab->labMenorCaminho = (int**) malloc ((lb.linha_m)*sizeof(int*));
	for (int d=0; d<lb.linha_m; d++)
		(lab->labMenorCaminho)[d] = (int*) malloc ((lb.coluna_m)*sizeof(int));

	for (int e=0; e<lb.linha_m; e++)
	{
		for (int f=0; f<lb.coluna_m; f++)
		{
			lab->labMenorCaminho[e][f] = lb.labBase[e][f];
		}
	}
	lab->labMenorCaminho[lb.lczQueijo_X][lb.lczQueijo_Y] = 0;
	
	while (terminou==0)
	{
		terminou=1;
		for (int g=1; g<=lb.linha; g++)
		{
			for (int h=1; h<=lb.coluna; h++)
			{
				if(lab->labMenorCaminho[g][h]==distancia)
				{
					if(lab->labMenorCaminho[g+1][h]==-1)
						lab->labMenorCaminho[g+1][h]=distancia+1;
					if(lab->labMenorCaminho[g-1][h]==-1)
						lab->labMenorCaminho[g-1][h]=distancia+1;
					if(lab->labMenorCaminho[g][h+1]==-1)
						lab->labMenorCaminho[g][h+1]=distancia+1;
					if(lab->labMenorCaminho[g][h-1]==-1)
						lab->labMenorCaminho[g][h-1]=distancia+1;
					terminou=0;
				}
			}
		}
		distancia++;
	}
	lab->labBase[lb.lczRato_X][lb.lczRato_Y] = 99;
	lab->labBase[lb.lczQueijo_X][lb.lczQueijo_Y] = 33;
	lab->nr_passos = (lab->labMenorCaminho)[lb.lczRato_X][lb.lczRato_Y];
}



void criarLabirintoFinal(Labirinto *lab, Labirinto lb)
{
	int teste;
	lab->labEstrutura = (char**) malloc (lb.linha_m*sizeof(char*));
	for (int e=0; e<lb.linha_m; e++)
		(lab->labEstrutura)[e] = (char*) malloc (lb.coluna_m*sizeof(char));

	for(int i=0; i<lb.linha_m; i++)
	{
		for(int j=0; j<lb.coluna_m; j++)
		{
			if(lb.labMenorCaminho[i][j]==-2)
				(lab->labEstrutura)[i][j] = lb.parede;
			else
				(lab->labEstrutura)[i][j] = lb.chao;
		}
	}
	
	verificaExisteResolucao (lab, lb);
	if (lab->existe_caminho==1)
	{
		int passo, outros;
		int dist_X, dist_Y;
		int *caminho_X, *caminho_Y;
		
		outros = lab->existe_caminho;
		passo = lb.nr_passos;
		dist_X = lb.lczRato_X;
		dist_Y = lb.lczRato_Y;
		
		caminho_X = (int*) malloc(lb.nr_passos*sizeof(int));
		caminho_Y = (int*) malloc(lb.nr_passos*sizeof(int));
		caminho_X[0] = lb.lczRato_X;
		caminho_Y[0] = lb.lczRato_Y;
		
		for(int k=0; k<lb.nr_passos; k++)
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
			caminho_X[k] = dist_X;
		   	caminho_Y[k] = dist_Y;
		   	passo--;
		}
		for(int l=0; l<lb.nr_passos ; l++)
            (lab->labEstrutura)[caminho_X[l]][caminho_Y[l]] = lb.caminho;
	}
	(lab->labEstrutura)[lb.lczQueijo_X][lb.lczQueijo_Y] = 'Q';
	(lab->labEstrutura)[lb.lczRato_X][lb.lczRato_Y] = 'R';
	(lab->labMenorCaminho)[lb.lczRato_X][lb.lczRato_Y] = 99;
	
}




void imprimirExisteResolucao (Labirinto lb)
{
	switch(lb.existe_caminho)
	{
		case -1:
		{
			printf("\nNão há resolução para este labirinto,\n"
		   		   "há paredes em todos os cantos do rato!\n\n");
			break;
		}
		case 0:
		{
			printf("\nNão há resolução para este labirinto,\n"
				   "há um bloqueio no meio do caminho!\n\n");
			break;
		}
		case 1:
		{
			printf("É necessário, no mínimo, %d passos\n"
				   "para o rato chegar no queijo!\n\n",
				    lb.nr_passos);
			break;
		}
	}
	printf("Digite de 1-3, digite 0 para reiniciar.\n");
	printf("Digite outra base do labirinto: ");
}



void imprimirLabirintoBase (Labirinto lb)
{
	for (int m=0; m<lb.linha_m; m++)
	{
		for (int n=0; n<lb.coluna_m; n++)
		{
			printf("%d ", lb.labBase[m][n]);
		}
		printf("\n");
	}
	printf("\nLabirinto Base.\n");
	imprimirExisteResolucao(lb);
}



void imprimirLabirintoMenorCaminho (Labirinto lb)
{
	for (int o=0; o<lb.linha_m; o++)
	{
		for (int p=0; p<lb.coluna_m; p++)
		{
			if(lb.labMenorCaminho[o][p]>=10 || lb.labMenorCaminho[o][p]<=-1)
				printf("%d ", lb.labMenorCaminho[o][p]);
			else
				printf(" %d ", lb.labMenorCaminho[o][p]);
		}
		printf("\n");
	}
	printf("\nLabirinto Menor Caminho.\n");
	imprimirExisteResolucao(lb);
}



void imprimirLabirintoFinal (Labirinto lb)
{
	for (int q=0; q<lb.linha_m; q++)
	{
		for (int r=0; r<lb.coluna_m; r++)
		{
			printf("%c ", lb.labEstrutura[q][r]);
		}
		printf("\n");
	}
	printf("\nLabirinto Final.\n");
	imprimirExisteResolucao(lb);
}



void freeLabirinto(Labirinto *lab, Labirinto lb)
{	
	for (int s=0; s<lb.linha_m; s++) 
	{
		free((lab->labBase)[s]);
	}
	free(lab->labBase);
	
	for (int t=0; t<lb.linha_m; t++) 
	{
		free((lab->labEstrutura)[t]);
	}
	free(lab->labEstrutura);
	
	for (int u=0; u<lb.linha_m; u++) 
	{
		free((lab->labMenorCaminho)[u]);
	}
	free(lab->labMenorCaminho);
}