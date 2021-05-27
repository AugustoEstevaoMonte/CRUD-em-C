#ifndef EXCLUSAOCANCELAMENTO_H
#define EXCLUSAOCANCELAMENTO_H

void cancelaCartaoUsr(FILE *arq, int reg);
void excluirFisicamenteCartao (FILE **arqCard, char nome[]);



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



#endif