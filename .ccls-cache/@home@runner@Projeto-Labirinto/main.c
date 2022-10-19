// Projeto Bônus - Labirinto
// Ricardo Henrique Pires dos Reis

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "montaLabirinto.h"
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
	srand(time(NULL));
	lab.chance=5;
	lab.linha=5, lab.coluna=5;
	lab.linha_m = lab.linha+2, lab.coluna_m = lab.coluna+2; 
	lab.parede='X', lab.chao='.', lab.caminho='#';
	int modo=0, resposta, escolha, arquivo, vezes=1;
	while(modo!=6)
	{
		modo=0;
		system(LIMPA);
		selecao_Menu(&modo);
		switch(modo)
		{
			case 6:
			{
				fim_de_Jogo();
				continue;
			}
			case 5:
			{
				comoFunciona();
				continue;
			}
			case 4:
			{
				perguntaEscreverOuLer(&arquivo);
				if (arquivo==2)
				{
					apagaArquivoCSV();
					tamanhoArquivoCSV(&lab);
					escreveLabirintoArquivoCSV(&lab, lab);
				}
				descobreValoresArquivoCSV(&lab);
				perguntaTamanhoTabela(&lab, 4);
				montaLabirintoArquivoCSV(&lab, lab);
				break;
			}
			case 3:
			{
				perguntaTamanhoTabela(&lab, 3);
				montarLabirinto(&lab, lab);
				transformaLabirinto(&lab, lab);
				break;
			}
			case 2:
			{
				perguntaTamanhoTabela(&lab, 2);
				perguntaChanceParede(&lab);
				montarLabirintoAleatorio(&lab, lab);
				break;
			}	
			case 1:
			{
				primeiroLabirinto(&lab);
				break;
			}
			default:
			{
				aviso_Erro(1);
				break;
			}
				
		}
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
		do
		{
			scanf("%d", &escolha);
			system(LIMPA);
			switch(escolha)
			{
				case 0:
				{
					break;
				}
				case 1:
				{
					imprimirLabirintoBase (lab);
					break;
				}
				case 2:
				{
					imprimirLabirintoMenorCaminho (lab);
					break;
				}
				default:
				{
					imprimirLabirintoFinal (lab);
					break;
				}
			}
		}
		while (escolha!=0);
		telaReinicio();
		vezes++;
	}
	if (vezes>1)
		freeLabirinto(&lab, lab);
	system(LIMPA);
	return 0;
}