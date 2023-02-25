#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<conio.h>
#include<unistd.h>
#include<time.h>
//#include<windows.h>

#define VERMELHO     "\x1b[31m"
#define VERDE   "\x1b[32m"
#define AMARELO "\x1b[33m"
#define AZUL    "\x1b[34m"
#define RESET   "\x1b[0m"

//parametros: int (maior valor possivel sorteado)
//retorno: int
//função realiza: sorteia um valor de 0 ao numero máximo definido
int sorteiaNumero(int num_max)
{
	int numero;
	numero = (rand() % num_max);
	return numero;
}

//parametros: matriz de inteiros
//retorno: void
//função realiza: zerar a matriz
void  ResetarTabuleiro(int tabuleiro[][9], int valor)
{
	int vetLinha[valor];
	int vetColuna[valor];
	int vetValores[valor];
	int parou = 0;
	
	for(int c = 0; c < valor; c++)
	{
	    int linha = sorteiaNumero(8);
	    int coluna = sorteiaNumero(8);
	    for(int h = 0;h < valor ; h++)
    	{
    	    if(vetLinha[h] == linha && vetColuna[h] == coluna)
    	    {
    	        linha = sorteiaNumero(8);
	            coluna = sorteiaNumero(8);
	            h = 0;
    	    }
    	}
	    
		vetLinha[c] = linha;
		vetColuna[c] = coluna;
    	
		vetValores[c] = tabuleiro[vetLinha[c]][vetColuna[c]];
	}
	
    for (int l = 0; l < 9;l++)
    {
        for (int c = 0; c < 9; c++)
        {
            tabuleiro[l][c] = 0;
        }
    }
    
    for(int c = 0; c < valor; c++)
	{
		tabuleiro[vetLinha[c]][vetColuna[c]] = vetValores[c];
	}
}

//parametros: matriz de inteiros
//retorno: void
//função realiza: zerar parcialmente a matriz para testes
void  ResetarTabuleiroParcial(int tabuleiro[][9])
{
    for (int l = 0; l < 9;l++)
    {
        for (int c = 0; c < 9; c++)
        {
        	if(l == 0 && c == 0)
        	{
        		tabuleiro[l][c] = 0;
			}
        }
    }
}

//parametros: matriz de inteiros
//retorno: void
//função realiza: exibir a matriz, no formato de tabuleiro
void ExibirTabuleiro(int tabuleiro[][9])
{
    printf("    0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |\n");
    for (int l = 0; l < 9; l++)
    {
        
        printf(AZUL "   ------------------------------------\n" RESET);
        printf("%d |", l);
        for (int c = 0; c < 9; c++)
        {
            printf(VERMELHO " %d " RESET, tabuleiro[l][c]);
            printf(AZUL "|" RESET);
        }
        printf("\n");
    }
    printf(AZUL "   ------------------------------------\n" RESET);
}

//parametros: int (valor da linha), int (valor da coluna), int (valor a ser colocado na matriz)
//retorno: bool
//função realiza: verificar se as linhas e colunas estão entre 0 e 8 e se o valor entre 1 e 9
bool VerificaParametros(int linha, int coluna, int numero)
{
	if (numero >= 1 && numero <=9)
    {
    	if ((linha >= 0 && linha <= 8) && (coluna >= 0 && coluna <= 8))
	    {
	    	return true;
	    }
	}
	return false;	
}

//parametros: int (valor da linha), int (valor da coluna),matriz (representando o tabuleiro), int (valor a ser colocado na matriz)
//retorno: void
//função realiza: marca o valor informado na matriz indicada no parametro, nas coordenadas também indicadas nos parametros
void MarcaTabuleiro(int linha, int coluna,int tabuleiro[][9], int numero)
{
	tabuleiro[linha][coluna] = numero; 
}

//parametros: vetor de int (com ao valores a ser comparada), int (valor a ser colocado na matriz)
//retorno: bool
//função realiza: verifica se o valor já existe no vetor em questão
bool verificaRepeticaoVetor(int vetor[9], int valor)
{
	for (int c = 0; c < 9; c++)
    {
    	if(vetor[c] == valor)
		{
			return false;
		}	
        
    }
    return true;
}

//parametros: int (linha)
//retorno: int
//função realiza: indicar a linha de inicio do bloco
int inicioLinhaBloco(int linha)
{
	if(linha >= 0 && linha <=2)
	{
		return 0;
	}
	else if(linha >= 3 && linha <=5)
	{
		return 3;
	}
	else
	{
		return 6;
	}
}

//parametros: int (coluna)
//retorno: int
//função realiza: indicar a coluna de inicio do bloco
int inicioColunaBloco(int coluna)
{
	if(coluna >= 0 && coluna <=2)
	{
		return 0;
	}
	else if(coluna >= 3 && coluna <=5)
	{
		return 3;
	}
	else
	{
		return 6;
	}
}

bool verificaLinhas(int tabuleiro[][9], int linha, int valor)
{
	int vetor_linha[9];
	
	for (int c = 0; c < 9; c++)
    {
    	
    	vetor_linha[c] = tabuleiro[linha][c];	
    	
    }
    return verificaRepeticaoVetor(vetor_linha, valor);
}

bool verificaColunas(int tabuleiro[][9], int coluna, int valor)
{
	int vetor_coluna[9];
	
	for (int l = 0; l < 9; l++)
    {
    	
    	vetor_coluna[l] = tabuleiro[l][coluna];	
    	
    }
    return verificaRepeticaoVetor(vetor_coluna, valor);
}

bool verificaBlocos(int tabuleiro[][9], int coluna, int linha, int valor)
{
	
	int vetor_bloco[9];
	int linhaInicio = inicioLinhaBloco(linha);
	int colunaInicio = inicioColunaBloco(coluna);
	int cont = 0;
	
	for (int l = linhaInicio; l < linhaInicio + 3; l++)
    {
    	for (int c = colunaInicio; c < colunaInicio + 3; c++)
	    {
	    	vetor_bloco[cont] = tabuleiro[l][c];
			cont++;	
	    }
    }

    return verificaRepeticaoVetor(vetor_bloco, valor);
}
//parametros: matriz
//retorno: bool
//função realiza: verifica se todos os elemento da matriz são diferentes de zero, se sim vitoria, se não derrota
bool verificaVitoria(int tabuleiro[][9])
{
	for (int l = 0; l < 9; l++)
    {
        for (int c = 0; c < 9; c++)
        {
            if(tabuleiro[l][c] == 0)
            {
            	return false;
			}
        }
    }
    return true;
}

void timer(int tempo_pausa)
{
	for(int s = tempo_pausa; s > 0;s--)
	{
		printf("%d seg...\n", s);
		sleep(1);
	}
}

void montaTabuleiro(int origem[9][9], int destino[9][9])
{
    for (int l = 0; l < 9; l++)
    {
        for (int c = 0; c < 9; c++)
        {
            destino[l][c] = origem[l][c];
        }
    }
}

int menuInicial()
{
	int opcao;
	do
	{
		printf("---SUDOKU---\n");
		printf("Bem vindo, escolha uma opção:\n");
		printf("1 - Começar\n");
		printf("0 - Sair\n");
		
		scanf("%d", &opcao);
	}
	while(opcao != 0 && opcao != 1);
	
	return opcao;	
}

void limpaTela()
{
	#ifdef __linux__
		system("clear"); // limpar tela linux
	#elif _WIN32
		system("cls"); //limpar tela windows
		//clrscr();
	#endif
}

int main()
{
	srand((int)time(NULL));
	int opcaoInicial;
	do
	{
		opcaoInicial = menuInicial();

		if(opcaoInicial == 1)
		{
		
			int sorteioTab, opcao, linha, coluna, valor, nivel, contErro;
			char corLetra[10], corTabela[10];
			int tabuleiro[9][9];
			
			do
			{
			    printf("Informe a dificuldade:\n");
    			printf("1 - Fácil\n");
    			printf("2 - Médio\n");
    			printf("3 - Difícil\n");
    			
    			scanf("%d", &nivel);  
			}
			while(nivel < 0 || nivel > 3);
			
			sorteioTab = sorteiaNumero(3);
	
			if(sorteioTab == 0)
			{
			    
			   int t1[9][9] = {
    			   {5, 3, 4, 6, 7, 8, 9, 1, 2},
    			   {6, 7, 2, 1, 9, 5, 3, 4, 8},
    			   {1, 9, 8, 3, 4, 2, 5, 6, 7},
    			   {8, 5, 9, 7, 6, 1, 4, 2, 3},
    			   {4, 2, 6, 8, 5, 3, 7, 9, 1},
    			   {7, 1, 3, 9, 2, 4, 8, 5, 6},
    			   {9, 6, 1, 5, 3, 7, 2, 8, 4},
    			   {2, 8, 7, 4, 1, 9, 6, 3, 5},
    			   {3, 4, 5, 2, 8, 6, 1, 7, 9}
			    };
			    montaTabuleiro(t1, tabuleiro);
			}
			else if(sorteioTab == 1)
			{
			    int t1[9][9] = {
    			   {3, 5, 2, 4, 7, 6, 8, 1, 9},
    			   {1, 6, 8, 3, 5, 9, 4, 7, 2},
    			   {4, 9, 7, 8, 2, 1, 6, 3, 5},
    			   {2, 4, 5, 9, 6, 7, 3, 8, 1},
    			   {9, 8, 6, 1, 4, 3, 5, 2, 7},
    			   {7, 3, 1, 2, 8, 5, 9, 6, 4},
    			   {6, 2, 3, 7, 9, 4, 1, 5, 8},
    			   {5, 7, 9, 6, 1, 8, 2, 4, 3},
    			   {8, 1, 4, 5, 3, 2, 7, 9, 6}
			    };
			    montaTabuleiro(t1, tabuleiro);
			}
			else
			{
			   	int t1[9][9] = {
    			   {9, 1, 3, 6, 5, 8, 4, 7, 2},
    			   {5, 2, 7, 4, 1, 9, 8, 3, 6},
    			   {6, 4, 8, 2, 7, 3, 1, 5, 9},
    			   {7, 3, 2, 8, 4, 1, 9, 6, 5},
    			   {8, 5, 1, 9, 3, 6, 7, 2, 4},
    			   {4, 9, 6, 5, 2, 7, 3, 8, 1},
    			   {1, 8, 4, 7, 6, 5, 2, 9, 3},
    			   {3, 7, 5, 1, 9, 2, 6, 4, 8},
    			   {2, 6, 9, 3, 8, 4, 5, 1, 7}
			    }; 
			    montaTabuleiro(t1, tabuleiro);
			}
		
			limpaTela();
			ExibirTabuleiro(tabuleiro);
			printf("\nO jogo vai começar!\n");
			timer(5);
			limpaTela();
			
			//ResetarTabuleiroParcial(tabuleiro);
			if(nivel == 1)
			{
			    ResetarTabuleiro(tabuleiro, 45);
			}
			else if(nivel == 2)
			{
			    ResetarTabuleiro(tabuleiro, 30);
			}
			else if(nivel == 3)
			{
			    ResetarTabuleiro(tabuleiro, 10);
			}
		
		    do
		    {
		        ExibirTabuleiro(tabuleiro);
		
		        printf("Informe a linha:");
		        scanf("%d", &linha);
		
		        printf("Informe a coluna:");
		        scanf("%d", &coluna);
		
		        printf("Informe o valor:");
		        scanf("%d", &valor);
				
		        if( VerificaParametros(linha, coluna, valor) )
		        {
		        	if( verificaLinhas(tabuleiro, linha, valor) &&
						verificaColunas(tabuleiro, coluna, valor) && 
						verificaBlocos(tabuleiro, coluna, linha, valor)
					)
		        	{
		        		MarcaTabuleiro(linha, coluna, tabuleiro, valor);
		        		printf("\nMarcado com sucesso!!!\n");
					}
					else
					{
						printf("\nErrou!!!\n");
						if(nivel == 3)
						{
						  	contErro++;
						  	limpaTela();
						    printf("ERROU!\n");
						    printf("\nQuantidade de erros %d de 5\n", contErro);
						    timer(3);
						}
						if(nivel == 3 && contErro >= 5)
						{
						    printf("\nO jogo acabou!!!\n\n\n\n");
						    break;
						}
					
					}
				}
				else
				{
					printf("\nPosição ou valor inválido!!!\n");
				}
		
		        if( !verificaVitoria(tabuleiro) )
		        {
		        	opcao = 1;
				}
				else
				{
					opcao = 0;
				}
				
				sleep(1);
		
				limpaTela();
			} while (opcao != 0);
			
			if(opcao == 0)
			{
				printf("\nVocê ganhou!!!\n");
			}
	    }
	}
	while(opcaoInicial != 0);
	
	printf("\nSaindo......\n");
	timer(3);

    return 0;
}
