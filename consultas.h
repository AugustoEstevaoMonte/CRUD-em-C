#ifndef CONSULTAS_H
#define CONSULTAS_H

int consultaNumeroCartao(FILE *arq, char busca[]);
int consultaIngressos(FILE *arq, int busca);
int consultaAdmin(FILE *arq, char busca[]);
int consultaCodShow(struct tIngressos *ing, FILE *arq, int cod);


int consultaNumeroCartao(FILE *arq, char busca[])
{
  struct tUsuario usr;
  int reg = 0;
	fseek(arq, 0, SEEK_SET);
	while(fread(&usr, sizeof(usr), 1, arq) != 0)
  {
    reg++;
		if(strcmp(busca,usr.card.usrNumCartao)==0 && (usr.card.cartaoCancelado!='c'))
    {
      return reg; // 0 representa que achou o numero do cartao
    }
	}
	return -1; // -1 representa não encontrado
}

int consultaIngressos(FILE *arq, int busca)
{
  struct tIngressos ingressos;
	fseek(arq, 0, SEEK_SET);
	while(fread(&ingressos, sizeof(ingressos), 1, arq) != 0)
  {
		if(ingressos.codigo == busca)
    {
      return 0; // 0 representa que achou o ingresso
    }
	}
	return -1; // -1 representa não encontrado
}

int consultaAdmin(FILE *arq, char busca[])
{
  struct tAdministrador adm;
  int reg = 0;
	fseek(arq, 0, SEEK_SET);
	while(fread(&adm, sizeof(adm), 1, arq) != 0)
  {
    reg++;
		if(strcmp(busca,adm.adminName)==0 && (adm.cancelado!='c'))
    {
      return reg; // 0 representa que achou o numero do cartao
    }
	}
	return -1; // -1 representa não encontrado
}


int consultaCodShow(struct tIngressos *ing, FILE *arq, int cod)
{
  fseek(arq,0,SEEK_SET);
  int reg = 0;
  while(fread(&(*ing),sizeof(*ing),1,arq)!=0)
  {
    reg++;
    if(cod==(*ing).codigo)
    {
      return reg; //Encontrou o codigo do show
    }
  }
  return -1; //Não encontrou
}




#endif