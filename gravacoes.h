#ifndef GRAVACOES_H
#define GRAVACOES_H

void gravaDadosNoArquivoUsuario(FILE *arq, struct tUsuario usr, int reg);
void gravaDadosArquivoAdministrador(FILE *arq, struct tAdministrador admin);
void gravaDadosArquivoIngressos(FILE *arq, struct tIngressos ingressos);
void gravaDadosEspecificoIngressos(FILE *arq, struct tIngressos ingressos, int reg);

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
   if(reg == -1){
		fseek(arq, 0, SEEK_END);
		fwrite(&ingressos, sizeof(ingressos), 1, arq);
	}else{
		fseek(arq, sizeof(ingressos)*reg, SEEK_SET);
		fwrite(&ingressos, sizeof(ingressos), 1, arq);
	}
}

#endif