#ifndef EXPORTAXML_H
#define EXPORTAXML_H

int exportarCadastroXML(FILE *arq, char nome[]);
int exportarCardXML(FILE *arq, char nome[]);
int exportarIngressosXML(FILE *arq, char nome[]);
int exportarAdminXML(FILE *arq, char nome[]);


int exportarCadastroXML(FILE *arq, char nome[])
{
  struct tUsuario usr;
  FILE *arqTxt = fopen(nome,"w");
  if(arqTxt == NULL)
  {
    return 0;
  }
  fseek(arq,0,SEEK_SET);
  fprintf(arqTxt,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
  fprintf(arqTxt,"<usuarios>\n");



  while(fread(&usr,sizeof(usr),1,arq)!=0)
  {
    fprintf(arqTxt,"    <nomeUsuario>%s</nomeUsuario>\n",usr.usrName); 
    fprintf(arqTxt,"      <nickname>%s</nickname>\n",usr.usrNickName);
    fprintf(arqTxt,"      <password>%s</password>\n",usr.usrPassword);
  }
  fprintf(arqTxt,"</usuarios>\n");
  fclose(arqTxt);
  return 1;
}

int exportarCardXML(FILE *arq, char nome[])
{
  struct tUsuario usr;
  FILE *arqTxt = fopen(nome,"w");
  if(arqTxt == NULL)
  {
    return 0;
  }
  fseek(arq,0,SEEK_SET);
  fprintf(arqTxt,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
  fprintf(arqTxt,"<cartaoUsuario>\n");



  while(fread(&usr,sizeof(usr),1,arq)!=0)
  {
    fprintf(arqTxt,"    <nomeUsuario>%s</nomeUsuario>\n",usr.usrName); 
    fprintf(arqTxt,"      <nickname>%s</nickname>\n",usr.usrNickName);
    fprintf(arqTxt,"      <password>%s</password>\n",usr.usrPassword);
    fprintf(arqTxt,"      <valorCarteira>%0.2f</valorCarteira>\n",usr.valorCarteira);
    fprintf(arqTxt,"      <numCartao>%s</numCartao>\n",usr.card.usrNumCartao);
    fprintf(arqTxt,"      <cvCard>\"%d\"</cvCard>\n",usr.card.cvCard);
  }
  fprintf(arqTxt,"</cartaoUsuario>\n");
  fclose(arqTxt);
  return 1;
}


int exportarIngressosXML(FILE *arq, char nome[])
{
  struct tIngressos ing;
  FILE *arqTxt = fopen(nome,"w");
  if(arqTxt == NULL)
  {
    return 0;
  }
  fseek(arq,0,SEEK_SET);
  fprintf(arqTxt,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
  fprintf(arqTxt,"<ingressosUsuario>\n");



  while(fread(&ing,sizeof(ing),1,arq)!=0)
  {
    fprintf(arqTxt,"    <nomeBanda>%s</nomeBanda>\n",ing.banda); 
    fprintf(arqTxt,"      <localShow>%s</localShow>\n",ing.local);
    fprintf(arqTxt,"      <horaInicial>%d</horaInicial>\n",ing.horaIni);
    fprintf(arqTxt,"      <minutoInicial>%d</minutoInicial>\n",ing.minIni);
    fprintf(arqTxt,"      <horaFinal>%d</horaFinal>\n",ing.horaFim);
    fprintf(arqTxt,"      <minutoFinal>\"%d\"</minutoFinal>\n",ing.minFim);
    fprintf(arqTxt,"      <valorIngresso>%0.2f</valorIngresso>\n",ing.valor);

  }
  fprintf(arqTxt,"</ingressosUsuario>\n");
  fclose(arqTxt);
  return 1;
}


int exportarAdminXML(FILE *arq, char nome[])
{
  struct tAdministrador adm;
  FILE *arqTxt = fopen(nome,"w");
  if(arqTxt == NULL)
  {
    return 0;
  }
  fseek(arq,0,SEEK_SET);
  fprintf(arqTxt,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
  fprintf(arqTxt,"<administradores>\n");



  while(fread(&adm,sizeof(adm),1,arq)!=0)
  {
    fprintf(arqTxt,"    <nomeAdmin>%s</nomeAdmin>\n",adm.adminName); 
    fprintf(arqTxt,"      <senhaAdmin>%s</senhaAdmin>\n",adm.adminPassword);
  }
  fprintf(arqTxt,"</administradores>\n");
  fclose(arqTxt);
  return 1;
}

#endif