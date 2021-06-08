#ifndef FUNCOESUTEIS_H
#define FUNCOESUTEIS_H

void allPause();
FILE *abreArquivo(char nomeArquivo[]);



void allPause()
{
  char allP;
  printf("\n\nPressione qualquer tecla para continuar...\n");
  setbuf(stdin,NULL);
  allP = getchar();
  system("cls||clear");
} 


FILE *abreArquivo(char nomeArquivo[])
{
  FILE *arq;
	arq = fopen(nomeArquivo, "r+b");
	if(arq == NULL)
  {
    arq = fopen(nomeArquivo, "w+b");
  }
		
	return arq;
}

#endif