#ifndef VALIDACOES_H
#define VALIDACOES_H
#include <string.h>
#define MAX 30

void leValidaUsrName(char[]);
void leValidaUsrNickname(char[]);
void leValidaUsrPassword(char[]);
int leValidaCodigo();
void leValidaNomeBanda(char[]);
void leValidaEstilo(char[]);
void leValidaLocal(char[]);
int leValidaHorasIni();
int leValidaMinIni();
float leValidaValor();
int leValidaHorasFim();
int leValidaMinFim();
int leValidaNumeroCartao(char[]);
int leValidaCVcard(int cvCard);


void leValidaUsrName(char nomeUser[])
{
  do
  {
       printf("Digite aqui o seu nome: ");
       fflush(stdin);
       fgets(nomeUser,MAX,stdin);

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
       fgets(nickUser,MAX,stdin);

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
       fgets(passwordUser,MAX,stdin);

       if(strlen(passwordUser)==1 || strlen(passwordUser)<=5)
       {
         printf("Senha invalida, necessita ter pelo menos 6 caracteres...\n");
       }

  }while(strlen(passwordUser)==1 || strlen(passwordUser)<=5);
}

//PARTE DA RAFAELA, NÃO PADRONIZADA DE ACORDO COM O CÓDIGO
int leValidaCodigo() // Não fez a validação
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
        fgets(banda, MAX, stdin);
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

int leValidaHorasIni()  //Tinha que ter colocado um char aqui, não precisava ter criado outra função só pra isso.
{
    int horas;
     do
    {
        printf("Hora do inicio (apenas a hora): ");
        fflush(stdin);
        scanf("%d", &horas);
        if(horas<1 || horas>24)
        {
          printf(ERRO);
        }
    }while(horas<1 || horas>24);
return horas;
}


int leValidaMinIni()
{
    int min;
     do
    {
        printf("Minutos do inicio: ");
        fflush(stdin);
        scanf("%d", &min);
        if(min<0 || min>59)
        {
          printf(ERRO);
        }
    }while(min<0 || min>59);
return min;
}

float leValidaValor() //Não fez a validação
{
  float valor;
  printf("Valor do ingresso: ");
  scanf("%f", &valor);
  return valor;
}

int leValidaHorasFim()
{
    int horas;
     do
    {
        printf("Hora do final (apenas a hora): ");
        fflush(stdin);
        scanf("%d", &horas);
        if(horas<1 || horas>24)
        {
          printf(ERRO);
        }
    }while(horas<1 || horas>24);
return horas;
}

int leValidaMinFim()
{
    int min;
     do
    {
        printf("Minutos do final: ");
        fflush(stdin);
        scanf("%d", &min);
        if(min<0 || min>59)
        {
          printf(ERRO);
        }
    }while(min<0 || min>59);
return min;
}

//FIM DA PARTE RAFAELA, NÃO PADRONIZADA DE ACORDO COM O CÓDIGO

int leValidaNumeroCartao(char num[])
{
  if(strlen(num)!=9)
  {
    return 1;
  }
  return 0;
}


int leValidaCVcard(int cvCard)
{
  if(cvCard>=100 && cvCard<=999)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}


#endif