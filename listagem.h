#ifndef LISTAGEM_H
#define LISTAGEM_H

void listagemIngressos(FILE *arq);
void listarUsuarios(FILE *arq);
void listarAdmin(FILE *arq);
void listArqCar(FILE *arq);
int listarArquivoCarrinho(FILE *arq);



void listagemIngressos(FILE *arq)
{
  struct tIngressos ingressos;
  fseek(arq, 0, SEEK_SET);
  while(fread(&ingressos, sizeof(ingressos), 1, arq)!=0)
  {       if(ingressos.cancelado!='c')
          {
               printf("\n%d - %sLocal: %sInicio: %d:%d - Final: %d:%d\nValor: %.2f\n",ingressos.codigo, ingressos.banda, ingressos.local, ingressos.horaIni, ingressos.minIni, ingressos.horaFim, ingressos.minFim, ingressos.valor);
          }
  }
}

void listarUsuarios(FILE *arq)
{
  struct tUsuario usr;
  fseek(arq,0,SEEK_SET);
  while(fread(&usr,sizeof(usr),1,arq)!=0)
  {
    printf("Nome do usuario: %s\nNickName Usuario: %s\n",usr.usrName,usr.usrNickName);
    getchar();
  }
}

void listarAdmin(FILE *arq)
{
  struct tAdministrador adm;
  fseek(arq,0,SEEK_SET);
  while(fread(&adm,sizeof(adm),1,arq)!=0)
  {
    printf("Nome do administrador: %s\nSenha do administrador: %s\n",adm.adminName,adm.adminPassword);
    getchar();
  }
}

void listArqCar(FILE *arq)
{
    struct tIngressos ingressos;
    fseek(arq, 0, SEEK_SET);
    while(fread(&ingressos, sizeof(ingressos), 1, arq)!=0)
    {    
            
                printf("\n\n\n%d - %sLocal: %sInicio: %d:%d - Final: %d:%d\nValor: %.2f\n\n",ingressos.codigo, ingressos.banda, ingressos.local, ingressos.horaIni, ingressos.minIni, ingressos.horaFim, ingressos.minFim, ingressos.valor);
            
    }
}

int listarArquivoCarrinho(FILE *arq)
{
  float val=0;
  struct tIngressos ingressos;
  fseek(arq, 0, SEEK_SET);
  while(fread(&ingressos, sizeof(ingressos), 1, arq)!=0)
  {   
               printf("\n\n\n%d - %sLocal: %sInicio: %d:%d - Final: %d:%d\nValor: %.2f\n\n",ingressos.codigo, ingressos.banda, ingressos.local, ingressos.horaIni, ingressos.minIni, ingressos.horaFim, ingressos.minFim, ingressos.valor);
               val+=ingressos.valor;

  }
  return val;
}


#endif