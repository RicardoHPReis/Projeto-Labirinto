#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "struct_labirinto.h"
#ifdef _WIN32
    #include <Windows.h>
    #define LIMPA "cls"
#else
    #include <unistd.h>
    #define LIMPA "clear"
#endif



void titulo_Menu(void)
{
	printf("*********************************************\n");
	printf("                  Labirinto\n");
	printf("*********************************************\n\n\n\n");
}



void titulo_Menu_Opcao(void)
{
	printf("1) Labirinto padrão.\n\n");
	printf("2) Labirinto aleatório.\n\n");
	printf("3) Criar Matriz pelo programa.\n\n");
	printf("4) Escrever ou ler arquivo CSV.\n\n");
	printf("5) Como funciona?\n\n");
	printf("6) Terminar jogo.\n\n");
}



void titulo_Menu_Detalhamento(int pergunta, int descricao)
{
	switch(pergunta)
	{
		case 0:
		{
			switch(descricao)
			{
				case 0:
				{
					printf("Modos:\n");
					break;
				}
				case 1:
				{
					printf("Criação de labirinto.\n");
	    			printf("Digite o labirinto a ser criado abaixo.\n");
					break;
				}
				case 2:
				{
					printf("Opções de jogo:\n");
	    			printf("Digite 'S' para sim ou 'N' para não.\n");
					break;
				}
				case 3:
				{
					printf("Criação do Arquivo CSV:\n");
	    			printf("Digite o número de linhas do arquivo.\n");
					break;
				}
				case 4:
				{
					printf("Criação do Arquivo CSV:\n");
	    			printf("Digite os locais das paredes por linha.\n");
					break;
				}
			}
			printf("---------------------------------------------\n\n");
			break;
		}
		case 1:
		{
			printf("Opções de jogo:\n");
			switch(descricao)
			{
				case 0:
				{
					printf("Digite um único caracter do teclado.\n");
					break;
				}
				case 1:
				{
					printf("Digite o tamanho da tabela, sendo um "
					"tamanho positivo.\n");
					break;
				}
				case 2:
				{
					printf("Digite as coordernadas da tabela em X e Y,\n"
					" sendo as coordenadas positivas.\n");
					break;
				}
				case 3:
				{
					printf("Digite a chance de aparecer uma parede. "
					"É uma em cada:\n");
					break;
				}
			}
			printf("---///---///---///---///---///---///---///---\n\n");
			break;
		}
	}
}



void ler_string(char *resposta)
{
	int tamanho;
    char letra, *string;
	string = (char*) malloc (2*sizeof(char));
    
	scanf(" %c", &letra);

    for (tamanho = 0; letra != '\n'; tamanho++)
    {
        string[tamanho] = letra;
        string = (char*) realloc(string, (tamanho+3)*sizeof(char));

        scanf("%c", &letra);
    }
    string[tamanho+1] = '\0';
	*resposta = string[0];
	free(string);
}



void aviso_Erro(int tipoErro)
{
	system(LIMPA);
	titulo_Menu();
	switch(tipoErro)
	{
		case 1:
		{
			titulo_Menu_Detalhamento(0, 0);
    		printf("Digite o número novamente!!!\n"
			"O número precisa estar presente no menu "
			"de seleção!\n");
			break;
		}
		case 2:
		{
			titulo_Menu_Detalhamento(0, 2);
    		printf("Digite a letra novamente!!!\n"
			"A letra precisa ser 'S' para sim ou 'N' "
			"para não!\n");
			break;
		}
		case 3:
		{
			titulo_Menu_Detalhamento(1, 1);
    		printf("Digite o tamanho novamente!!!\n"
			"O tamanho precisa estar entre os "
			"requisitos!\n");
			break;
		}
		case 4:
		{
			titulo_Menu_Detalhamento(1, 2);
    		printf("Digite o número novamente!!!\n"
			"O número precisa estar entre os requisitos!\n");
			break;
		}
		case 5:
		{
			titulo_Menu_Detalhamento(1, 3);
    		printf("Digite o número novamente!!!\n"
			"O número precisa ser positivo!\n");
			break;
		}
		case 6:
		{
			titulo_Menu_Detalhamento(0, 1);
    		printf("Digite a linha novamente!!!\n"
			"Só pode ser usado o caracter de parede e "
			"o de caminho!\n");
			break;
		}
		case 7:
		{
			titulo_Menu_Detalhamento(0, 1);
    		printf("Digite o linha novamente!!!\n"
			"A linha precisa ter o tamanho correto!\n");
			break;
		}
		case 8:
		{
			titulo_Menu_Detalhamento(0, 1);
    		printf("Digite o linha novamente!!!\n"
			"A linha precisa ter o tamanho correto e "
			"os caracteres corretos!\n");
			break;
		}
		
	}
  sleep(3);
  system(LIMPA);
  return;
}



void selecao_Menu(int *modo)
{
	char escolha;
	while (*modo < 1 || *modo > 6)
	{
	    titulo_Menu();
	    titulo_Menu_Detalhamento(0, 0);
	    titulo_Menu_Opcao();
	    printf("Escolha o modo de jogo: ");
		ler_string(&escolha);
		*modo = escolha-'0';
	    if (*modo < 1 || *modo > 6)
	    	aviso_Erro(1);
	}
	system(LIMPA);
}



void perguntaCustomizarInicializacao(int *resposta)
{
	char resposta_Customizar;
	do
	{
	    titulo_Menu();
	    titulo_Menu_Detalhamento(0, 2);
	    printf("Deseja customizar algo no jogo? ");
	    ler_string(&resposta_Customizar);
	    if (resposta_Customizar == 's' || resposta_Customizar == 'n')
	    	resposta_Customizar -= 32;
	    if (resposta_Customizar != 'S' && resposta_Customizar != 'N')
	    	aviso_Erro(2);
	}
	while (resposta_Customizar != 'S' && resposta_Customizar != 'N');
	
	if (resposta_Customizar == 'S') 
		*resposta=1;
	else
		*resposta=0;
	system(LIMPA);
}



void perguntaMudarCaracter(Labirinto* lab)
{
	char caracter;
	char resposta_Mudar_Caracter;
	system(LIMPA);
	do
	{
	    titulo_Menu();
	    titulo_Menu_Detalhamento(0, 2);
	    printf("Deseja mudar os caracteres da tabela padrão (%c %c %c)? ", lab->parede, lab->caminho, lab->chao);
	    ler_string(&resposta_Mudar_Caracter);
	    if (resposta_Mudar_Caracter == 's' || resposta_Mudar_Caracter == 'n')
	    	resposta_Mudar_Caracter -= 32;
	    if (resposta_Mudar_Caracter != 'S' && resposta_Mudar_Caracter != 'N')
	    	aviso_Erro(2);
	}
	while (resposta_Mudar_Caracter != 'S' && resposta_Mudar_Caracter != 'N');
	if (resposta_Mudar_Caracter == 'S')
	{
	    system(LIMPA);
	    titulo_Menu();
	    titulo_Menu_Detalhamento(1, 0);
	    printf("\nEscolha o caracter para as paredes: ");
		ler_string(&caracter);
	    lab->parede = caracter;
	    
		printf("\n\nEscolha o caracter para os corredores: ");
		ler_string(&caracter);
	    lab->chao = caracter;
		
		printf("\n\nEscolha o caracter para o caminho correto: ");
		ler_string(&caracter);
		lab->caminho = caracter;
	}
	system(LIMPA);
}



void perguntaTamanhoTabela(Labirinto* lab, int pergunta)
{
	int min_X=2, min_Y=2;
	char resposta_Tamanho;
	do
	{
	    titulo_Menu();
	    titulo_Menu_Detalhamento(0, 2);
	    printf("Deseja mudar o tamanho da tabela padrão (%d x %d)? ", lab->linha, lab->coluna);
	    ler_string(&resposta_Tamanho);
	    if (resposta_Tamanho == 's' || resposta_Tamanho == 'n')
	    	resposta_Tamanho -= 32;
	    if (resposta_Tamanho != 'S' && resposta_Tamanho != 'N')
	    	aviso_Erro(2);
	}
	while (resposta_Tamanho != 'S' && resposta_Tamanho != 'N');

	if(pergunta==4)
	{
		min_X=lab->linha;
		min_Y=lab->coluna;
	}
	
	if (resposta_Tamanho == 'S')
	{
	    lab->linha = 0, lab->coluna = 0;
	    system(LIMPA);
	    do
		{
	    	titulo_Menu();
	    	titulo_Menu_Detalhamento(1, 1);
	    	printf("Escolha o comprimento da linha e da coluna (O mínimo é %d x %d): ", min_X, min_Y);
	    	scanf("%d %d", &lab->linha, &lab->coluna);
	    	if (lab->linha < min_X || lab->coluna < min_Y)
	        	aviso_Erro(3);
	    }
		while (lab->linha < min_X || lab->coluna < min_Y);
		lab->linha_m = lab->linha+2;
		lab->coluna_m = lab->coluna+2;
	}
	system(LIMPA);
}



void perguntaLocalizacao(Labirinto* lab, Labirinto lb)
{
	char resposta_Localizacao;
	do
	{
	    titulo_Menu();
	    titulo_Menu_Detalhamento(0, 2);
	    printf("Deseja escolher o local inicial da figura? ");
	    ler_string(&resposta_Localizacao);
	    if (resposta_Localizacao == 's' || resposta_Localizacao == 'n')
	    	resposta_Localizacao -= 32;
	    if (resposta_Localizacao != 'S' && resposta_Localizacao != 'N')
	    	aviso_Erro(2);
	}
	while (resposta_Localizacao != 'S' && resposta_Localizacao != 'N');
	if (resposta_Localizacao == 'S')
	{
		lab->lczRato_X = 0, lab->lczRato_Y = 0;
	    system(LIMPA);
	    while ((lab->lczRato_X < 1 || lab->lczRato_X > lb.linha) ||
		(lab->lczRato_Y < 1 || lab->lczRato_Y > lb.coluna))
		{
	    	titulo_Menu();
	    	titulo_Menu_Detalhamento(1, 2);
	    	printf("Escolha a localização X Y do rato(O mínimo é 1x1 e"
			" o máximo é %dx%d): ", lb.linha, lb.coluna);
	    	scanf("%d %d", &lab->lczRato_X, &lab->lczRato_Y);
	    	if ((lab->lczRato_X < 1 || lab->lczRato_X > lb.linha) ||
			(lab->lczRato_Y < 1 || lab->lczRato_Y > lb.coluna))
	        	aviso_Erro(4);
		}
		system(LIMPA);
		while ((lab->lczQueijo_X < 1 || lab->lczQueijo_X > lb.linha) ||
		(lab->lczQueijo_Y < 1 || lab->lczQueijo_Y > lb.coluna))
		{
	    	titulo_Menu();
	    	titulo_Menu_Detalhamento(1, 2);
	    	printf("Escolha a localização X Y do queijo (O mínimo é 1x1 e"
			" o máximo é %dx%d): ", lb.linha, lb.coluna);
	    	scanf("%d %d", &lab->lczQueijo_X, &lab->lczQueijo_Y);
	    	if ((lab->lczQueijo_X < 1 || lab->lczQueijo_X > lb.linha) ||
			(lab->lczQueijo_Y < 1 || lab->lczQueijo_Y > lb.coluna))
	        	aviso_Erro(4);
		}
	}
	else 
	{
		do
		{
			lab->lczRato_X = rand()%(lb.linha);
			lab->lczRato_Y = rand()%(lb.coluna);
		}
		while(lb.labBase[lab->lczRato_X][lab->lczRato_Y]==-2);
		
		do
		{
			lab->lczQueijo_X = rand()%(lb.linha);
			lab->lczQueijo_Y = rand()%(lb.coluna);
		}
		while(lb.labBase[lab->lczQueijo_X][lab->lczQueijo_Y]==-2);
	}
	system(LIMPA);
}



void perguntaChanceParede(Labirinto* lab)
{
	int chance;
	char resposta_Chance;
	do
	{
	    titulo_Menu();
	    titulo_Menu_Detalhamento(0, 2);
	    printf("Deseja mudar a chance de aparecer uma parede(%d%)? ", 100/lab->chance);
	    ler_string(&resposta_Chance);
	    if (resposta_Chance == 's' || resposta_Chance == 'n')
	    	resposta_Chance -= 32;
	    if (resposta_Chance != 'S' && resposta_Chance != 'N')
	    	aviso_Erro(2);
	}
	while (resposta_Chance != 'S' && resposta_Chance != 'N');
	if(resposta_Chance=='S')
	{
		system(LIMPA);
		do
		{
			titulo_Menu();
	    	titulo_Menu_Detalhamento(1, 3);
			printf("Digite a porcentagem para aparecer uma parede: ");
	    	scanf("%d", &chance);
			lab->chance= 100/chance;
			if(chance<1 || chance>100)
				aviso_Erro(5);
		}
		while(chance<1 || chance>100);
	}
}



void perguntaEscreverOuLer(int *resposta)
{
	char escolha;
	do
	{
	    titulo_Menu();
	    printf("Arquivo CSV:\n");
		printf("---------------------------------------------\n\n");
	    printf("Deseja escrever ou somente ler o arquivo csv?\n\n");
		printf("1) Somente ler.\n");
		printf("2) Escrever e ler.\n\n");
		printf("Escolha uma das opções: ");
		ler_string(&escolha);
		*resposta = escolha-'0';
	    if (*resposta < 1 || *resposta > 2)
	    	aviso_Erro(1);
	}
	while (*resposta < 1 || *resposta > 2);
	system(LIMPA);
}



void comoFunciona(void)
{
	char continuar = 0;
	char base[12][12] = {
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
	
	titulo_Menu();
	printf("Como funciona cada modo:\n");
	printf("---------------------------------------------\n\n");
	printf("Labirinto Padrão: Será apresentado um labirinto\n"
		   "pré-definido, mas os locais do rato e do queijo\n"
		   "são aleatórios ou escolhidos pelo jogador.\n\n");
	printf("Labirinto Aleatório: Será apresentado um labirinto\n"
		   "com paredes aleatórias, ou definidas por uma\n"
		   "porcentagem pelo usuário, além do tamanho do\n"
		   "labirinto que também é aleatórios ou escolhidos\n"
		   "pelo jogador.\n\n");
	printf("Criar Matriz pelo Programa: O usuário poderá\n"
		   "criar um labirinto pelo programa a partir do\n"
		   "tamanho do labirinto, escolhido ou não pelo usuário.\n\n");
	printf("Escrever ou ler arquivo CSV: O programa irá\n"
		   "ler ou subscrever o arquivo labirinto.csv e\n"
		   "criará um labirinto conforme os números\n"
		   "apresentados no arquivo.\n\n\n");
	printf("Demonstração do labirinto padrão: \n\n");
	for(int a=0; a<12; a++)
	{
		for(int b=0; b<12; b++)
		{
			if(base[a][b]==-1)
				printf(". ");
			else
				printf("X ");
		}
		printf("\n");
	}
	printf("\n\nDigite qualquer tecla para continuar:\n");
	ler_string(&continuar);
}



void telaCarregamento(void)
{
	system(LIMPA);
    titulo_Menu();
    printf("Preparando jogo\nCarregando.\n");
    usleep(500*1000);
    system(LIMPA);
    titulo_Menu();
    printf("Preparando jogo\nCarregando..\n");
    usleep(500*1000);
    system(LIMPA);
    titulo_Menu();
    printf("Preparando jogo\nCarregando...\n");
    usleep(500*1000);
    system(LIMPA);
}



void telaReinicio(void)
{
	system(LIMPA);
	titulo_Menu();
	printf("Reiniciando.\n");
	usleep(500*1000);
	system(LIMPA);
	
	titulo_Menu();
	printf("Reiniciando..\n");
	usleep(500*1000);
	system(LIMPA);
	
	titulo_Menu();
	printf("Reiniciando...\n");
	usleep(500*1000);
	system(LIMPA);
}



void fim_de_Jogo(void)
{
	printf("*********************************************\n");
	printf("                      FIM\n");
	printf("*********************************************\n");
	sleep(3);
}