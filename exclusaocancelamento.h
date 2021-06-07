#ifndef EXCLUSAOCANCELAMENTO_H
#define EXCLUSAOCANCELAMENTO_H

void cancelaCartaoUsr(FILE *arq, int reg);
void excluirFisicamenteCartao (FILE **arqCard, char nome[]);
void excluiIngresso(FILE *arq, int reg);
void excluirFisicamenteIngressos (FILE **arq, char ingresso[]);
void cancelaAdmin(FILE *arq, int reg);
void excluirFisicamenteAdmin (FILE **arqAdm, char nome[]);
void cancelaIngressoArqCarrinho(FILE *arq, int reg);
void excluirFisicamenteCarrrinho (FILE **arqCarrinho, char nome[]);



void cancelaCartaoUsr(FILE *arq, int reg)
{
	struct tUsuario usr;
	fseek(arq, (reg-1)*sizeof(usr), SEEK_SET);
  fread(&usr,sizeof(usr),1,arq);
	usr.card.cartaoCancelado = 'c';
  fseek(arq,-sizeof(usr), SEEK_CUR);
	fwrite(&usr, sizeof(usr), 1, arq);

}

void excluirFisicamenteCartao (FILE **arqCard, char nome[]){
	FILE *arqAux = fopen("infoCartao.aux", "a+b");
	struct tUsuario usr;
	
	if(arqAux == NULL){
		printf("Erro de abertura!!!");
		return;
	}
	
	fseek(*arqCard, 0, SEEK_SET);
	while(fread(&usr, sizeof(usr), 1, *arqCard))
		if(usr.card.cartaoCancelado != 'c')
    {
      fwrite(&usr, sizeof(usr), 1, arqAux);
    }
	
	fclose(*arqCard);
	fclose(arqAux);
	remove(nome);
	rename("infoCartao.aux", nome); //
  *arqCard = abreArquivo(nome);
}

void excluiIngresso(FILE *arq, int reg)
{
	struct tIngressos ingressos;
	fseek(arq, (reg-1)*sizeof(ingressos), SEEK_SET);
  fread(&ingressos, sizeof(ingressos), 1, arq);
	ingressos.cancelado = 'c';
  fseek(arq, -sizeof(ingressos), SEEK_CUR);
	fwrite(&ingressos, sizeof(ingressos), 1, arq);
}

void excluirFisicamenteIngressos (FILE **arq, char ingresso[]){
	FILE *arqAux = fopen("ingressosAux.aux", "a+b");
	struct tIngressos ingressos;

  if(arqAux == NULL){
    printf("Erro de abertura\n");
    return;
  }
	
	fseek(*arq, 0, SEEK_SET);
	while(fread(&ingressos, sizeof(ingressos), 1, *arq))
		if(ingressos.cancelado != 'c')
    {
      fwrite(&ingressos, sizeof(ingressos), 1, arqAux);
    }
	
	fclose(*arq);
	fclose(arqAux);
	remove(ingresso);
	rename("ingressosAux.aux", ingresso);
  *arq = abreArquivo(ingresso);
}


void cancelaAdmin(FILE *arq, int reg)
{
	struct tAdministrador adm;
	fseek(arq, (reg-1)*sizeof(adm), SEEK_SET);
  fread(&adm,sizeof(adm),1,arq);
	adm.cancelado = 'c';
  fseek(arq,-sizeof(adm), SEEK_CUR);
	fwrite(&adm, sizeof(adm), 1, arq);

}

void excluirFisicamenteAdmin (FILE **arqAdm, char nome[])
{
	FILE *arqAux = fopen("admin.aux", "a+b");
	struct tAdministrador adm;
	
	if(arqAux == NULL){
		printf("Erro de abertura!!!");
		return;
	}
	
	fseek(*arqAdm, 0, SEEK_SET);
	while(fread(&adm, sizeof(adm), 1, *arqAdm))
		if(adm.cancelado != 'c')
    {
      fwrite(&adm, sizeof(adm), 1, arqAux);
    }
	
	fclose(*arqAdm);
	fclose(arqAux);
	remove(nome);
	rename("admin.aux", nome); //
  *arqAdm = abreArquivo(nome);
}

void cancelaIngressoArqCarrinho(FILE *arq, int reg)
{
	struct tIngressos ing;
	fseek(arq, (reg-1)*sizeof(ing), SEEK_SET);
  fread(&ing,sizeof(ing),1,arq);
	ing.cancelado = 'c';
  fseek(arq,-sizeof(ing), SEEK_CUR);
	fwrite(&ing, sizeof(ing), 1, arq);

}

void excluirFisicamenteCarrrinho (FILE **arqCarrinho, char nome[]){//mudar int pra void
	FILE *arqAux = fopen("carrinhoUser.aux", "w");
	struct tIngressos ing;
	
	if(arqAux == NULL){
		printf("Erro de abertura!!!");
		return;
	}
  setbuf(stdin,NULL);
	fseek(*arqCarrinho, 0, SEEK_SET);
	while(fread(&ing, sizeof(ing), 1, *arqCarrinho))
		if(ing.cancelado != 'c')
    {
      
      fwrite(&ing, sizeof(ing), 1, arqAux);
    }
	
	fclose(*arqCarrinho);
	fclose(arqAux);
	remove(nome);
	rename("carrinhoUser.aux", nome); //
  *arqCarrinho = abreArquivo(nome);
}



#endif