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
	printf("4) Ler arquivo CSV.\n\n");
	printf("5) Como funciona?\n\n");
	printf("6) Terminar jogo.\n\n");
}



void titulo_Menu_Detalhamento(int pergunta, int descricao)
{
	if (pergunta == 0)
	{
		if (descricao == 0)
    		printf("Modos:\n");
		else if (descricao == 1)
		{
			printf("Criação de labirinto.\n");
	    	printf("Digite o labirinto a ser criado abaixo.\n");
		}
	    else
		{
	    	printf("Opções de jogo:\n");
	    	printf("Digite 'S' para sim ou 'N' para não.\n");
	    }
		printf("---------------------------------------------\n\n");
	}
	else
	{
	    printf("Opções de jogo:\n");
	    if (descricao == 0)
	      printf("Digite um único caracter do teclado.\n");
	    if (descricao == 1)
	      printf("Digite o tamanho da tabela, considerando o tamanho mínimo de 15x15.\n");
	    if (descricao == 2)
	      printf("Digite as coordernadas da tabela em X e Y, sendo as coordenadas positivas.\n");
	    if (descricao == 3)
	    	printf("Digite a chance de aparecer uma parede. É uma em cada:\n");
		
	   	printf("---///---///---///---///---///---///---///---\n\n");
	}
	return;
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
	if (tipoErro == 1)
	{
    	titulo_Menu_Detalhamento(0, 0);
    	printf("Digite o número novamente!!!\n"
			"O número precisa estar presente no menu de seleção!\n");
	}
	else if (tipoErro == 2)
	{
    	titulo_Menu_Detalhamento(0, 2);
    	printf("Digite a letra novamente!!!\n"
			"A letra precisa ser 'S' para sim ou 'N' para não!\n");
	}
	else if (tipoErro == 3)
	{
    	titulo_Menu_Detalhamento(1, 1);
    	printf("Digite o tamanho novamente!!!\n"
			"O tamanho precisa estar entre os requisitos!\n");
	}
	else if (tipoErro == 4)
	{
    	titulo_Menu_Detalhamento(1, 2);
    	printf("Digite o número novamente!!!\n"
			"O número precisa estar entre os requisitos!\n");
	}
	else if (tipoErro == 5)
	{
    	titulo_Menu_Detalhamento(1, 3);
    	printf("Digite o número novamente!!!\n"
			"O número precisa ser positivo!\n");
	}
	else if (tipoErro == 6)
	{
    	titulo_Menu_Detalhamento(0, 1);
    	printf("Digite a linha novamente!!!\n"
			"Só pode ser usado o caracter de parede e o de caminho!\n");
	}
	else if (tipoErro == 7)
	{
    	titulo_Menu_Detalhamento(0, 1);
    	printf("Digite o linha novamente!!!\n"
			"A linha precisa ter o tamanho correto!\n");
	}
	else if (tipoErro == 8)
	{
    	titulo_Menu_Detalhamento(0, 1);
    	printf("Digite o linha novamente!!!\n"
			"A linha precisa ter o tamanho correto e os caracteres correto!\n");
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
	return;
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
	return;
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
	    printf("Deseja mudar os caracteres da tabela padrão (0 e .)? ");
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
	return;
}



void perguntaTamanhoTabela(Labirinto* lab)
{
	char resposta_Tamanho;
	do
	{
	    titulo_Menu();
	    titulo_Menu_Detalhamento(0, 2);
	    printf("Deseja mudar o tamanho da tabela padrão? ");
	    ler_string(&resposta_Tamanho);
	    if (resposta_Tamanho == 's' || resposta_Tamanho == 'n')
	    	resposta_Tamanho -= 32;
	    if (resposta_Tamanho != 'S' && resposta_Tamanho != 'N')
	    	aviso_Erro(2);
	}
	while (resposta_Tamanho != 'S' && resposta_Tamanho != 'N');
	if (resposta_Tamanho == 'S')
	{
	    lab->linha = 0, lab->coluna = 0;
	    system(LIMPA);
	    while (lab->linha < 3 || lab->coluna < 3)
		{
	    	titulo_Menu();
	    	titulo_Menu_Detalhamento(1, 1);
	    	printf("Escolha o comprimento da linha e da coluna (O mínimo é 3x3): ");
	    	scanf("%d %d", &lab->linha, &lab->coluna);
	    	if (lab->linha < 3 || lab->coluna < 3)
	        	aviso_Erro(3);
	    }
		lab->linha_m = lab->linha+2;
		lab->coluna_m = lab->coluna+2;
	}
	system(LIMPA);
	return;
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
		while ((lab->lczQueijo_X < 1 || lab->lczQueijo_X > lb.linha) ||
		(lab->lczQueijo_Y < 1 || lab->lczQueijo_Y > lb.coluna))
		{
	    	titulo_Menu();
	    	titulo_Menu_Detalhamento(1, 2);
	    	printf("Escolha a localização X Y (O mínimo é 1x1 e"
			" o máximo é %dx%d): ", lb.linha, lb.coluna);
	    	scanf("%d %d", &lab->lczQueijo_X, &lab->lczQueijo_Y);
	    	if ((lab->lczRato_X < 1 || lab->lczRato_X > lb.linha) ||
			(lab->lczRato_Y < 1 || lab->lczRato_Y > lb.coluna))
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
	return;
}



void perguntaChanceParede(Labirinto* lab)
{
	char chance;
	char resposta_Chance;
	do
	{
	    titulo_Menu();
	    titulo_Menu_Detalhamento(0, 2);
	    printf("Deseja mudar a chance de aparecer uma parede? ");
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
			printf("Deseja mudar a chance de aparecer uma parede? ");
			ler_string(&chance);
	    	lab->chance=chance-'0';
			if((lab->chance)<1)
				aviso_Erro(5);
		}
		while(lab->chance<1);
	}
}



void comoFunciona(void)
{
	char continuar;
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
	printf("Labirinto Padrão: \n\n");
	printf("Labirinto Aleatório: \n\n");
	printf("Criar Matriz pelo Programa: \n\n");
	printf("Ler Arquivo CSV: \n\n\n");
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
	for (int i = 0; i < 1; i++)
	{
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
}



void telaReinicio(void)
{
	system(LIMPA);
	for (int i = 0; i < 1; i++)
	{
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
}



void fim_de_Jogo(void)
{
	printf("*********************************************\n");
	printf("                      FIM\n");
	printf("*********************************************\n");
	sleep(3);
	return;
}