#ifndef FUNCOESUTEIS_H
#define FUNCOESUTEIS_H

void allPause();
FILE *abreArquivo(char nomeArquivo[]);
int exportaCartaoXML(FILE *arqA);



void allPause()
{
  char allP;
  printf("Pressione qualquer tecla para continuar...\n");
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

int exportaCartaoXML(FILE *arqA) //Criar uma função de exportação específica pra cada entidade, passar como parametro a struct
{
  char ch;
  FILE *arq = fopen("dados.xml","w");
  if(arq==NULL || arqA == NULL)
  {
    return 0;
  }

  fseek(arqA,0,SEEK_SET);
  while(!feof(arqA))
  {
    ch = fgetc(arqA); //Errado, fread
    if(ch !=EOF)
    {
       fputc(ch, arq); //fprintf
    }
  }

  fclose(arq);
  return 0;
}


#endif