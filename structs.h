#ifndef STRUCTS_H
#define STRUCTS_H

struct tIngressos ////Modificado hoje no dia 08/05/2021
{ 
	int codigo;
  int horaIni;
  int minIni;
  int horaFim;
  int minFim;
  char banda[MAX];
  char local[MAX];
  float valor;
  char cancelado;
};

struct tAdministrador
{
	char adminName[MAX];
	char adminPassword[MAX];
  char cancelado;
};

struct tCartaoUsr
{
  char usrNumCartao[MAX];
  int cvCard;
  char cartaoCancelado;
};

struct tUsuario
{
  char usrName[MAX];
  char usrPassword[MAX];
  char usrNickName[MAX];
  struct tCartaoUsr card;
  float valorCarteira;
};


#endif