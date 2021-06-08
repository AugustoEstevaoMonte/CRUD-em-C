#ifndef VERIFICACOES_H
#define VERIFICACOES_H

int verificaNicknameJaEstaEmUso(FILE *arq, char nickUsername[]);
int verificaSeLoginEsenhaCorrespondem(FILE *arq, char nomeUser[], char senhaUser[]);
int verificaUsuarioAdminEsenha(FILE *arq, char nomeUser[], char senhaUser[]);
void subtraiValores(struct tUsuario *usr, float valor, FILE *arqCarteira, char numCard[]);
int totalNaCarteira(FILE *arq);
int codRepetido(FILE *arq, int cod);


int verificaNicknameJaEstaEmUso(FILE *arq, char nickUsername[])
{
  struct tUsuario usr;
  fseek(arq, 0, SEEK_SET);
	while(fread(&usr, sizeof(usr), 1, arq) != 0)
  {
		if(strcmp(nickUsername,usr.usrNickName) == 0)
    {
      return 1; //INDICA QUE JÁ TEM UM NICKNAME CADASTRADO
    }
	}
  return 0;
}

int verificaSeLoginEsenhaCorrespondem(FILE *arq, char nomeUser[], char senhaUser[])
{
  struct tUsuario usr;
   fseek(arq, 0, SEEK_SET);
	while(fread(&usr, sizeof(usr), 1, arq) != 0)
  {
		if((strcmp(nomeUser,usr.usrNickName) == 0) && strcmp(senhaUser,usr.usrPassword)==0)
    {
      return 0; //INDICA QUE O NOME DO USUARIO & SENHA SÃO IGUAIS AS CADASTRADAS
    }
	}
  return 1; //  INDICA QUE O NOME DO USUARIO OU SENHA NÃO SÃO IGUAIS
}

int verificaUsuarioAdminEsenha(FILE *arq, char nomeUser[], char senhaUser[]) 
{
  struct tAdministrador admin;
   fseek(arq, 0, SEEK_SET);
	while(fread(&admin, sizeof(admin), 1, arq) != 0)
  {
		if((strcmp(nomeUser,admin.adminName) == 0) && strcmp(senhaUser,admin.adminPassword)==0)
    {
      return 0; //INDICA QUE O NOME DO USUARIO & SENHA SÃO IGUAIS AS CADASTRADAS
    }
	}
  return 1; //  INDICA QUE O NOME DO USUARIO OU SENHA NÃO SÃO IGUAIS
}


void subtraiValores(struct tUsuario *usr, float valor, FILE *arqCarteira, char numCard[])
{
  fseek(arqCarteira, 0, SEEK_SET);
	  while(fread(&(*usr),sizeof(*usr),1,arqCarteira)!=0)
    {
      if(strcmp((*usr).card.usrNumCartao,numCard)==0)
      {
            (*usr).valorCarteira-=valor;
            printf("O novo valor e de: %0.2f R$\n",(*usr).valorCarteira);
      }
    }

}

int totalNaCarteira(FILE *arq)
{
  float car=0;
  struct tUsuario usr;
  fseek(arq,0,SEEK_SET);
  while(fread(&usr,sizeof(usr),1,arq)!=0)
  {
    car+=usr.valorCarteira;
  }
  return car;
}




int codRepetido(FILE *arq, int cod)
{
 struct tIngressos ing;
 fseek(arq,0,SEEK_SET);
 while(fread(&ing,sizeof(ing),1,arq)!=0)
 {
  if(ing.codigo==cod)
  {
     return -1;
  }
 }
 return 1;
}



#endif