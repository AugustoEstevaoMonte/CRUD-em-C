#ifndef VALIDACOES_H
#define VALIDACOES_H
#include <string.h>
#define TAM 30

void leValidaUsrName(char[]);
void leValidaUsrNickname(char[]);
void leValidaUsrPassword(char[]);
int leValidaCodigo();
void leValidaNomeBanda(char[]);
void leValidaEstilo(char[]);
void leValidaLocal(char[]);


void leValidaUsrName(char nomeUser[])
{
  do
  {
       printf("Digite aqui o seu nome: ");
       fflush(stdin);
       fgets(nomeUser,TAM,stdin);

       if(strlen(nomeUser)==1 || strlen(nomeUser)<=5)
       {
         printf("Nome de usuario invalido, necessita ter pelo menos 6 caracteres...\n");
       }

  }while(strlen(nomeUser)==1 || strlen(nomeUser)<=5);
}

void leValidaUsrNickname(char nickUser[])
{
  do
  {
       printf("\nDigite aqui o seu nickname: ");
       fflush(stdin);
       fgets(nickUser,TAM,stdin);

       if(strlen(nickUser)==1 || strlen(nickUser)<=5)
       {
         printf("Nickname invalido, necessita ter pelo menos 6 caracteres...\n");
       }

  }while(strlen(nickUser)==1 || strlen(nickUser)<=5);
}

void leValidaUsrPassword(char passwordUser[])
{
  do
  {
       printf("\nDigite aqui o sua senha: ");
       fflush(stdin);
       fgets(passwordUser,TAM,stdin);

       if(strlen(passwordUser)==1 || strlen(passwordUser)<=5)
       {
         printf("Senha invalida, necessita ter pelo menos 6 caracteres...\n");
       }

  }while(strlen(passwordUser)==1 || strlen(passwordUser)<=5);
}

//PARTE DA RAFAELA, NÃO PADRONIZADA DE ACORDO COM O CÓDIGO
int leValidaCodigo()
{
  int cod;
  printf("Digite o codigo so show: ");
  scanf("%d", &cod);
  return cod;
}

void leValidaNomeBanda(char banda[])
{
   do
    {
        printf("\nBanda: ");
        fflush(stdin);
        fgets(banda, TAM, stdin);
        if(strlen(banda)==1)
        {
          printf(ERRO);
        }
    }while(strlen(banda)==1);
}

void leValidaEstilo(char estilo[]){
  do
    {
        printf("\nEstilo: ");
        fflush(stdin);
        fgets(estilo, 40, stdin);
        if(strlen(estilo)==1)
        {
          printf(ERRO);
        }
    }while(strlen(estilo)==1);
}

void leValidaLocal(char local[])
{
  do
  {
      printf("Local do show: ");
      fflush(stdin);
      fgets(local, MAX, stdin);
      if(strlen(local)==1)
      {
          printf(ERRO);
      }
  }while(strlen(local)==1);

}

//FIM DA PARTE RAFAELA, NÃO PADRONIZADA DE ACORDO COM O CÓDIGO

#endif