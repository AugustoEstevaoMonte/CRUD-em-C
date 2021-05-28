#ifndef GRAVACOES_H
#define GRAVACOES_H

void gravaDadosNoArquivoUsuario(FILE *arq, struct tUsuario usr, int reg);
void gravaDadosArquivoAdministrador(FILE *arq, struct tAdministrador admin);
void gravaDadosArquivoIngressos(FILE *arq, struct tIngressos ingressos);
void gravaDadosEspecificoIngressos(FILE *arq, struct tIngressos ingressos, int reg);
void gravaIngAlt(FILE *arq, struct tIngressos ing, int reg);
void gravaDadosNoArquivoCarrinho(FILE *arq, struct tIngressos ing, int reg);
void gravaDadosArqCartao(FILE *arq, struct tUsuario usr, int reg);

void gravaDadosNoArquivoUsuario(FILE *arq, struct tUsuario usr, int reg) 
{
   if(reg == -1){
    usr.card.cartaoCancelado=' ';
		fseek(arq, 0, SEEK_END);
		fwrite(&usr, sizeof(usr), 1, arq);
	}else{
		fseek(arq, sizeof(usr)*reg, SEEK_SET);
		fwrite(&usr, sizeof(usr), 1, arq);
	}
}

void gravaDadosArquivoAdministrador(FILE *arq, struct tAdministrador admin) //Modificado hoje no dia 07/05/2021
{
		fseek(arq, 0, SEEK_END); 
		fwrite(&admin, sizeof(admin), 1, arq);
}

void gravaDadosArquivoIngressos(FILE *arq, struct tIngressos ingressos)
{
    fseek(arq, 0, SEEK_END);
		fwrite(&ingressos, sizeof(ingressos), 1, arq);
}

void gravaDadosEspecificoIngressos(FILE *arq, struct tIngressos ingressos, int reg)
{
  /* if(reg == -1){
		fseek(arq, 0, SEEK_END);
		fwrite(&ingressos, sizeof(ingressos), 1, arq);
	}else{*/
		fseek(arq, sizeof(ingressos)*reg, SEEK_SET);
		fwrite(&ingressos, sizeof(ingressos), 1, arq);
//	}
}

void gravaIngAlt(FILE *arq, struct tIngressos ing, int reg)
{
  
	if(reg<=0)
  {
    fseek(arq,0,SEEK_END);
  }else{
    fseek(arq,(reg-1) * sizeof(struct tIngressos),SEEK_SET);
    fwrite(&ing,sizeof(ing),1,arq);
  }
}

void gravaDadosNoArquivoCarrinho(FILE *arq, struct tIngressos ing, int reg)
{
  if(reg <=0)
  {
    ing.cancelado = ' '; //Se não for feito isso, ele não cancela o negócio
    fseek(arq,0,SEEK_END);
  }
  fseek(arq,(reg-1)*sizeof(ing),SEEK_SET);
  fwrite(&ing, sizeof(ing), 1, arq);
}


void gravaDadosArqCartao(FILE *arq, struct tUsuario usr, int reg)
{
    if(reg <=0)
    {
      usr.card.cartaoCancelado = ' '; //Se não for feito isso, ele não cancela o negócio
      fseek(arq,0,SEEK_END);
    }
    fseek(arq,(reg-1)*sizeof(struct tUsuario),SEEK_SET);
    fwrite(&usr, sizeof(usr), 1, arq);
}

#endif