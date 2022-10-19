// Projeto Bônus - Labirinto
// Ricardo Henrique Pires dos Reis

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "montaLabirinto.h"
#include "lerArquivoCSV.h"
#ifdef _WIN32
    #include <Windows.h>
    #define LIMPA "cls"
#else
    #include <unistd.h>
    #define LIMPA "clear"
#endif

int main(void)
{
	Labirinto lab;
	lab.chance=5;
	lab.linha=5, lab.coluna=5;
	lab.linha_m = lab.linha+2, lab.coluna_m = lab.coluna+2; 
	lab.parede='X', lab.chao='.', lab.caminho='#';
	int modo=0, resposta;
	while(modo!=6)
	{
		int escolha=3;
		system(LIMPA);
		selecao_Menu(&modo);
		if(modo==6)
		{
			fim_de_Jogo();
			continue;
		}
		if(modo==5)
		{
			comoFunciona();
			continue;
		}
		else if(modo==4)
		{
			//Ler arquivo
			continue;
		}
		else if(modo==3)
		{
			perguntaTamanhoTabela(&lab);
			montarLabirinto(&lab, lab);
			transformaLabirinto(&lab, lab);
		}
		else if(modo==2)
		{
			perguntaTamanhoTabela(&lab);
			perguntaChanceParede(&lab);
			montarLabirintoAleatorio(&lab, lab);
		}	
		else
			primeiroLabirinto(&lab);
		
		perguntaCustomizarInicializacao(&resposta);
		if(resposta==1)
		{
			perguntaMudarCaracter(&lab);
			perguntaLocalizacao(&lab, lab);
		}
		else
		{
			do
			{
				lab.lczRato_X = rand()%(lab.linha);
				lab.lczRato_Y = rand()%(lab.coluna);
			}
			while(lab.labBase[lab.lczRato_X][lab.lczRato_Y]==-2);
		
			do
			{
				lab.lczQueijo_X = rand()%(lab.linha);
				lab.lczQueijo_Y = rand()%(lab.coluna);
			}
			while(lab.labBase[lab.lczQueijo_X][lab.lczQueijo_Y]==-2);
		}
		criarLabirintoCaminho(&lab, lab);
		criarLabirintoFinal(&lab, lab);
		telaCarregamento();
		imprimirLabirintoFinal(lab);
		while (escolha!=0)
		{
			printf("tESTE\n");
			scanf("%d", &escolha);
			system(LIMPA);
			if(escolha==0)
				continue;
			if(escolha==1)
				imprimirLabirintoBase (lab);
			if(escolha==2)
				imprimirLabirintoMenorCaminho (lab);
			if(escolha==3)
				imprimirLabirintoMenor (lab);
			if(escolha==4)
				imprimirLabirintoFinal (lab);
			imprimirExisteResolucao(lab);
		}
		telaReinicio();
	}
	system(LIMPA);
}