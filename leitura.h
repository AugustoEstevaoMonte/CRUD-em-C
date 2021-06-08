#ifndef LEITURA_H
#define LEITURA_H
#include "structs.h"

struct tUsuario lerUser(int reg, FILE *arq);
void leituraUsuario(FILE *arq);
struct tUsuario lerCarteiraUsr(int reg, FILE *arq);
void leituraIngresso(FILE *arq, int busca);
struct tIngressos lerIngressos(int reg, FILE *arq);
struct tAdministrador lerAdministrador(int reg, FILE *arq);



struct tUsuario lerUser(int reg, FILE *arq)
{
  struct tUsuario usr;
  fseek(arq,(reg-1)*sizeof(struct tUsuario),SEEK_SET);
  fread(&usr,sizeof(usr),1,arq);
  return usr;
}

void leituraUsuario(FILE *arq)
{
  struct tUsuario usr;
	fseek(arq, 0, SEEK_SET);
	fread(&usr,sizeof(usr),1,arq);
}


struct tUsuario lerCarteiraUsr(int reg, FILE *arq)
{
  struct tUsuario usr;
  fseek(arq,(reg-1)*sizeof(struct tUsuario),SEEK_SET);
  fread(&usr,sizeof(usr),1,arq);
  return usr;
}

void leituraIngresso(FILE *arq, int busca)
{
  struct tIngressos ingressos;
	fseek(arq, 0, SEEK_SET);
  while(fread(&ingressos, sizeof(ingressos), 1, arq) != 0){
		if(ingressos.codigo == busca){
     printf("Banda: %sLocal: %sInicio: %d:%d - Final: %d:%d\nValor: %.2f\n\n", ingressos.banda, ingressos.local, ingressos.horaIni, ingressos.minIni, ingressos.horaFim, ingressos.minFim, ingressos.valor);
      return;
    }
	}
 
	
}

struct tIngressos lerIngressos(int reg, FILE *arq)
{
  struct tIngressos ing;
  fseek(arq,(reg-1)*sizeof(struct tIngressos),SEEK_SET);
  fread(&ing,sizeof(ing),1,arq);
  return ing;
}

struct tAdministrador lerAdministrador(int reg, FILE *arq)
{
  struct tAdministrador adm;
  fseek(arq,(reg-1)*sizeof(struct tAdministrador),SEEK_SET);
  fread(&adm,sizeof(adm),1,arq);
  return adm;
}

#endif