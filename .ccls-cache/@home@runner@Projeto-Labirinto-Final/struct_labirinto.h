typedef struct 
{
	char **labEstrutura, **labCriacao, **labMenor, **lab;
	char parede, chao, caminho;
	int **labMenorCaminho, **labBase;
	int linha, coluna, linha_m, coluna_m;
	int lczRato_X, lczRato_Y, lczQueijo_X, lczQueijo_Y;
	int existe_caminho, chance;
} 
Labirinto;