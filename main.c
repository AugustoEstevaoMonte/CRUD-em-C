//BIBLIOTECAS****************************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "menus.h" //Biblioteca criada no dia 11/05 para os "Menus"
#include "validacoes.h" //Biblioteca criada no dia 11/05 para validações
#include "structs.h" //Biblioteca contendo structs | OBS: ELA SEMPRE DEVE ESTAR EM PRIMEIRO NA INCLUSAO |
#include "gravacoes.h" //Biblioteca contendo funções de gravação
#include "listagem.h" //Biblioteca contendo funções de listagem
#include "leitura.h" //Biblioteca contendo funções de leitura
#include "verificacoes.h"


void cancelaCartaoUsr(FILE *arq, int reg);
void excluirFisicamenteCartao (FILE **arqCard, char nome[]); // 2 asteriscos em arq
void excluiIngresso(FILE *arq, int reg);
void excluirFisicamenteIngressos (FILE *arq, char ingresso[]);
int consultaNumeroCartao(FILE *arq, char busca[]);
int consultaIngressos(FILE *arq, int busca);
int consultaAdmin(FILE *arq, char buscaAdmin[]);
void cancelaAdmin(FILE *arq, int reg);
FILE *abreArquivo(char nomeArquivo[]);
void excluirFisicamenteAdmin (FILE **arqAdm, char nome[]);
int consultaCodShow(struct tIngressos *ing, FILE *arq, int cod);
void gravaDadosNoArquivoCarrinho(FILE *arq, struct tIngressos ing, int reg);
void cancelaIngressoArqCarrinho(FILE *arq, int reg);
void excluirFisicamenteCarrrinho (FILE **arqCarrinho, char nome[]);
void gravaDadosArqCartao(FILE *arq, struct tUsuario usr, int reg);
int exportaCartaoXML(FILE *arqA);



//MAIN***********************************************************************************************
int main (void){
  printf("Inicio do programa");
  FILE *arqCadastro,*arqAdministrador, *arqIngressos, *arqCartaoUsuario, *arqCarrinho; //Modificado hoje no dia 08/05/2021 
  struct tUsuario usr;
	struct tAdministrador admin;
  struct tIngressos ingressos;
  struct tNo *new, *administradores=NULL; //Struct tNo ligada a Administrador
  char nomeUser,userKey, userKey2;
	int opcaoMenuLogin, opcaoSMenuUser, opcaoSSMenuPagamento, opcaoSSMenuCarrinho, opcaoSMenuAdm, opcaoSSMenuGerenciamento,erroFunc=0,posX, posY;
  int buscaIngresso;
  float saldoCarteira=0;


	arqCadastro = abreArquivo("cadastro.csv"); 
  arqIngressos = abreArquivo("ingressos.csv");
  arqCartaoUsuario = abreArquivo("infoCartao.csv");
  arqCarrinho = abreArquivo("carrinhoUser.csv");


  // ARRANJAR UM JEITO DE FAZER ISSO TUDO VIRAR UM ARQUIVO .XML
	do{
	volta: opcaoMenuLogin = menuLogin();  // :volta é usado pela função goto(volta) na linha 125 do CADASTRO, é usado para voltar ao MENU !!!!!!GAMBIARRA ATÉ SURGIR OUTRA SOLUÇÃO MELHOR
		//primeiro menu, onde tem:
		// 1 - Entrar
		// 2 - Cadastrar
		// 3 - Entrar como administrador
		// 0 - Sair
		
		switch(opcaoMenuLogin){
			case 1:
				printf("\n\n\n*** ENTRAR ***\n\n\n");
        leValidaUsrNickname(usr.usrNickName);
        leValidaUsrPassword(usr.usrPassword);
        if(verificaSeLoginEsenhaCorrespondem(arqCadastro,usr.usrNickName,usr.usrPassword)==1)
        {
          printf(ERRO);
          allPause();
          goto volta;
        }
				//INICIO DO SUB-MENU PARA USER
				do{
					opcaoSMenuUser=menuUser();
					// 1 - Ingressos disponiveis
					// 2 - Forma de pagamento
					// 3 - Meu carrinho
					// 0 - Logout
					switch(opcaoSMenuUser){
						case 1:
							printf("\n\n\n*** INGRESSOS DISPONIVEIS ***\n\n\n");
              listagemIngressos(arqIngressos);
              
							break;
						case 2:
							//INICIO DO SUB-SUB-MENU PARA PAGAMENTO
							do{
								opcaoSSMenuPagamento = menuPagamento(); 
								// 1 - Adicionar cartao
								// 2 - Retirar cartao
								// 3 - Adicionar dinheiro na carteira
								// 0 - Voltar
								switch(opcaoSSMenuPagamento){
									case 1:
                    do
                    {    printf("\n\n\n*** ADICIONAR CARTAO ***\n\n\n");
                          printf("Digite aqui o numero do cartao: \n");
                          fflush(stdin);
                          fgets(usr.card.usrNumCartao,MAX,stdin);
                          erroFunc = leValidaNumeroCartao(usr.card.usrNumCartao);
                          if(erroFunc==1)
                          {
                            printf("O cartao precisa ter no minimo 8 numeros...\n");
                            allPause();
                          }

                    }while(erroFunc==1);

                    posX = consultaNumeroCartao(arqCartaoUsuario,usr.card.usrNumCartao);
                    if(posX==-1)
                    {
                        do
                      {
                        printf("Digite aqui o CV do cartao: \n");
                        scanf("%d",&usr.card.cvCard);
                        erroFunc = leValidaCVcard(usr.card.cvCard);
                        if(erroFunc==1)
                        {
                             printf("O CV precisa ter 3 digitos...\n");
                             allPause();
                        }
										  }while(erroFunc==1);


                        gravaDadosArqCartao(arqCartaoUsuario,usr,posX);
                        printf("CADASTRADO COM SUCESSO!!\n");
                        printf("Numero cartao: %s\n",usr.card.usrNumCartao);
                        printf("CV cartao: %d\n",usr.card.cvCard);
                    }else{
                      printf("Numero de cartao ja inserido anteriormente...\n");
                      allPause();
                    }
                    


                      
										break;
									case 2:
										printf("\n\n\n*** RETIRAR CARTAO ***\n\n\n");
                    do
                    {
                      printf("Digite aqui o numero do cartao que deseja remover: \n");
                      fflush(stdin);
                      fgets(usr.card.usrNumCartao,MAX,stdin);
                      erroFunc = leValidaNumeroCartao(usr.card.usrNumCartao);
                      if(erroFunc==1)
                      {
                        printf("Numero de cartao invalido, tente novamente...\n");
                      }
                      
                    }while(erroFunc==1);

                    posX = consultaNumeroCartao(arqCartaoUsuario,usr.card.usrNumCartao);
                    if(posX > 0)
                    {
                        usr = lerUser(posX, arqCartaoUsuario);
                        printf("Numero do cartao: %s\n",usr.card.usrNumCartao); 
                        printf("Deseja remover o cartao? (S ou n) \n");
                        fflush(stdin); 
                        scanf("%c",&userKey);
                        userKey = toupper(userKey);
                        if(userKey=='S')
                        {
                          cancelaCartaoUsr(arqCartaoUsuario,posX);
                          excluirFisicamenteCartao (&arqCartaoUsuario,"infoCartao.csv");
                          printf("Cartao cancelado com sucesso!!!\n");
                        }
                    } else {
                      printf("Numero de cartao invalido, tente novamente...\n");
                    }
                      
										break;	
									case 3:
										printf("\n\n\n*** ADICIONAR DINHEIRO NA CARTEIRA ***\n\n\n");
                     do
                    {
                      printf("Confirme o numero do cartao: \n");
                      fflush(stdin);
                      fgets(usr.card.usrNumCartao,MAX,stdin);
                      erroFunc = leValidaNumeroCartao(usr.card.usrNumCartao);
                      if(erroFunc==1)
                      {
                        printf("Numero de cartao invalido, tente novamente...\n");
                      }
                      
                    }while(erroFunc==1);
                    posX = consultaNumeroCartao(arqCartaoUsuario,usr.card.usrNumCartao);
                    if(posX > 0)
                    {
                      lerCarteiraUser(arqCartaoUsuario,&usr);
                      //printf("Seu saldo atual na conta: %0.2f\n",usr.valorCarteira);
                      printf("Digite um valor que deseja adicionar: \n");
                      scanf("%f",&saldoCarteira);
                      usr.valorCarteira+=saldoCarteira;
                      printf("VALOR ADICIONADO COM SUCESSO!!\n");
                      gravaDadosArqCartao(arqCartaoUsuario,usr,posX);
                    } else{
                      printf("NAO FOI ENCONTRADO NENHUM CARTAO...\n");
                    }
                    posX = exportaCartaoXML(arqCartaoUsuario); 
										break;
								}
							}while(opcaoSSMenuPagamento!=0);
							break;
						case 3:
							do{
							//INICIO SUB-SUB MENU PARA O CARRINHO
								opcaoSSMenuCarrinho=menuCarrinho(); 
								// 1 - Ver meu carrinho
								// 2 - Adicionar item
								// 3 - Excluir intem
								// 4 - Finalizar compra
								// 0 - Voltar
								switch(opcaoSSMenuCarrinho){
									case 1:
										printf("\n\n\n*** VER MEU CARRINHO ***\n\n\n");
                    listagemIngressos(arqCarrinho);
										break;
									case 2:
										printf("\n\n\n*** ADICIONAR ITEM ***\n\n\n");
                    listagemIngressos(arqIngressos);
                    printf("Digite aqui o codigo do ingresso que deseja adicionar...\n");
                    ingressos.codigo=leValidaCodigo();
                    posX = consultaCodShow(&ingressos,arqIngressos,ingressos.codigo);
                    if(posX > 0)
                    {
                       ingressos = lerIngressos(posX, arqIngressos);
                       printf("Nome do Artista: %s\nLocal: %s\nInicio: %i:%i - Final: %i:%i\n",ingressos.banda,ingressos.local,ingressos.horaIni,ingressos.minIni,ingressos.horaFim,ingressos.minFim);
                       gravaDadosNoArquivoCarrinho(arqCarrinho,ingressos,posX);
                       printf("Gravado com sucesso!!!\n");
                    }else{
                      printf("Codigo nao encontrado, tente novamente....\n");
                    }
                    

										break;	
									case 3:
										printf("\n\n\n*** EXCLUIR ITEM ***\n\n\n");
                    listagemIngressos(arqIngressos);
                    printf("Digite aqui o codigo do ingresso que deseja EXCLUIR...\n");
                    ingressos.codigo = leValidaCodigo();
                    posX = consultaCodShow(&ingressos,arqIngressos,ingressos.codigo);
                    if(posX > 0)
                    {
                       ingressos = lerIngressos(posX, arqIngressos);
                       printf("Nome do Artista: %s\nLocal: %s\nInicio: %i:%i - Final: %i:%i\n",ingressos.banda,ingressos.local,ingressos.horaIni,ingressos.minIni,ingressos.horaFim,ingressos.minFim);
                       gravaDadosNoArquivoCarrinho(arqCarrinho,ingressos,posX);
                       printf("Tem certeza que deseja excluir? (S ou n)\n");
                       userKey = getchar();
                       userKey = toupper(userKey);
                       if(userKey=='S') //Se o userKey pegar lixo de memória ele não grava no arquivo o ingresso excluido.
                       {
                         cancelaIngressoArqCarrinho(arqCarrinho,posX);
                         excluirFisicamenteCarrrinho (&arqCarrinho,"carrinhoUser.csv");
                       } else{
                         printf("Operacao abortada pelo usuario...\n");
                       }
                    }else{
                      printf(ERRO);
                    }
										break;
									case 4:
										printf("\n\n\n*** FINALIZAR COMPRA ***\n\n\n");
										break;
								}
							}while(opcaoSSMenuCarrinho!=0);
							break;
					}
			}while(opcaoSMenuUser!=0);
				break;
			case 2:
					printf("\n\n\n*** CADASTRAR ***\n\n\n");
          leValidaUsrName(usr.usrName);
          leValidaUsrNickname(usr.usrNickName);
          if(verificaNicknameJaEstaEmUso(arqCadastro,usr.usrNickName)==1)
          {
            printf("Este nickname ja esta em uso, tente novamente...\n");
            allPause();
            goto volta;
          }
          leValidaUsrPassword(usr.usrPassword);
          gravaDadosNoArquivoUsuario(arqCadastro,usr,-1); //Era pra escrever aqui
					printf("Usuario cadastrado com sucesso...\n");
        
				getchar();//allPause();
				break;
			case 3:
				printf("\n\n\n*** ENTRAR COMO ADMINISTRADOR ***\n\n\n");
				arqAdministrador = fopen("admin.csv","r+b");
				if(arqAdministrador == NULL) //ARQ = NULL QUER DIZER QUE NÃO FOI ENCONTRADO NENHUM ADMIN/ARQUIVO,  Modificado hoje no dia 07/05/2021 
				{
					arqAdministrador = abreArquivo("admin.csv");
					printf("Nenhum administrador encontrado, faca seu cadastro....\n");
					leValidaUsrName(admin.adminName);
					leValidaUsrPassword(admin.adminPassword);
					gravaDadosArquivoAdministrador(arqAdministrador,admin);
					printf("CADASTRO REALIZADO COM SUCESSO!!!\n");
				}
				leValidaUsrName(admin.adminName);  // ADMINISTRADOR ENCOTRADO, INICIANDO LOGIN E SENHA Modificado hoje no dia 07/05/2021 
				leValidaUsrPassword(admin.adminPassword);  //Modificado hoje no dia 07/05/2021 
				if(verificaUsuarioAdminEsenha(arqAdministrador,admin.adminName,admin.adminPassword)==1)  //Modificado hoje no dia 07/05/2021 
				{
					printf(ERRO);
					allPause();
					goto volta;
				}
				printf("LOGIN REALIZADO COM SUCESSO!!!!\n"); // //Modificado hoje no dia 07/05/2021
				allPause();
				//INICIO DO SUB-MENU PARA ADMINISTRADOR
				do{
					opcaoSMenuAdm = menuAdm(); 
					// 1 - Ingressos disponiveis
					// 2 - Adicionar ingresso
					// 3 - Alterar ingresso
					// 4 - Excluir ingresso
					// 5 - Gerenciar contas
					// 0 - Logout
					switch(opcaoSMenuAdm){
						case 1:
							printf("\n\n\n*** INGRESSOS DISPONIVEIS ***\n\n\n");

              listagemIngressos(arqIngressos);
							
							break;
						case 2:
							printf("\n\n\n*** ADICIONAR INGRESSOS ***\n\n\n");

            ingressos.codigo=leValidaCodigo();
            leValidaNomeBanda(ingressos.banda);
            leValidaLocal(ingressos.local);
            ingressos.horaIni=leValidaHorasIni();
            ingressos.minIni=leValidaMinIni();
            ingressos.horaFim =leValidaHorasFim();
            ingressos.minFim= leValidaMinFim();
            ingressos.valor=leValidaValor();

           
            //fwrite(&ingressos, sizeof(ingressos), 1, arqIngressos);//Tenta SEEK_SET
            

             printf("\n\n\n%d - %sLocal: %sInicio: %d:%d - Final: %d:%d\nValor: %.2f\n\n",ingressos.codigo, ingressos.banda, ingressos.local, ingressos.horaIni, ingressos.minIni, ingressos.horaFim, ingressos.minFim, ingressos.valor);
             
            gravaDadosArquivoIngressos(arqIngressos, ingressos);
          




							break;
						case 3:
							printf("\n\n\n*** ALTERAR INGRESSOS ***\n\n\n");
              //posY = consultaIngressos(arqIngressos,ingressos.codigo);
              
							
							break;
						case 4:
							printf("\n\n\n*** EXCLUIR INGRESSOS ***\n\n\n");

              printf("Digite aqui o codigo do ingresso que deseja excluir: \n");
              //fscanf(stdin, "%d", &ingressos.codigo);
              scanf("%d", &buscaIngresso);

              //aaaaa

              posY = consultaCodShow(&ingressos,arqIngressos,ingressos.codigo);


              if(posY > 0)
                    {
                       // leituraIngresso(arqIngressos, buscaIngresso);
                       	fseek(arqIngressos, 0, SEEK_SET);
                        while(fread(&ingressos, sizeof(ingressos), 1, arqIngressos) != 0){
                          if(ingressos.codigo == buscaIngresso){
                          printf("\n\n\n%d - %sLocal: %sInicio: %d:%d - Final: %d:%d\nValor: %.2f\n\n",ingressos.codigo, ingressos.banda, ingressos.local, ingressos.horaIni, ingressos.minIni, ingressos.horaFim, ingressos.minFim, ingressos.valor);
                          printf("Deseja excluir o ingresso? (S ou N) \n");
                          scanf(" %c", &userKey2);
                          userKey2 = toupper(userKey2);
                            if(userKey2=='S')
                            {
                              excluiIngresso(arqIngressos,posY);
                              gravaDadosEspecificoIngressos(arqIngressos, ingressos, posY);
                              excluirFisicamenteIngressos(arqIngressos,"ingressos.csv");
                              printf("Ingresso excluído!!!\n");
                            }
                          }
                        }
                        
                    } else {
                      printf("Codigo invalido, tente novamente...\n");
                      //allPause();
                    }


							break;
						case 5:
							printf("\n\n\n*** GERENCIAMENTO DE CONTAS ***\n\n\n");
							
							do{
								//INICIO SU-SUB MENU PARA GERENCIAMENTO DE CONTAS
								opcaoSSMenuGerenciamento = menuGerenciamento();
								// 1 - Usuarios
								// 2 - Administracao
								// 3 - Adicionar conta de administrador
								// 4 - excluir conta de administrador
								// 0 - Voltar 
								switch(opcaoSSMenuGerenciamento){
									case 1:
										printf("\n\n\n*** USUARIOS ***\n\n\n");
                    listarUsuarios(arqCadastro);
										allPause();
										break;
									case 2:
										printf("\n\n\n*** ADMINISTRACAO ***\n\n\n");
                    listarAdmin(arqAdministrador);
										allPause();
										break;
									case 3:
										printf("\n\n\n*** ADICIONAR CONTA DE ADMINISTRADOR ***\n\n\n");
                    leValidaUsrName(admin.adminName);
					          leValidaUsrPassword(admin.adminPassword);
					          gravaDadosArquivoAdministrador(arqAdministrador,admin);
                    printf("CONTA CRIADA COM SUCESSO!!!\n");
										allPause();
										break;
									case 4:
                  
										printf("\n\n\n*** EXCLUIR CONTA DE ADMINISTRADOR ***\n\n\n");
                    printf("Digite aqui o nome do administrador(a)...\n");
                    do
                    {
                      printf("Digite aqui o nome do Adm para ser excluido: \n");
                      fgets(admin.adminName,MAX,stdin);
                      if(strlen(admin.adminName)==1 || strlen(admin.adminName)<=5)
                      {
                        printf(ERRO);
                      } 
                    }while(strlen(admin.adminName)==1 || strlen(admin.adminName)<=5);
                    posX = consultaAdmin(arqAdministrador,admin.adminName);
                    if(posX > 0)
                    {
                      printf("ADMINISTRADOR ENCONTRADO!!!\n");
                      admin =  lerAdministrador(posX,arqAdministrador);
                      printf("Deseja remover o administrador(a) ? (S ou n) \n");
                      fflush(stdin); //SE NÃO FOR EXECUTADO GERA ERRO NO CÓDIGO
                      scanf("%c",&userKey);
                      userKey = toupper(userKey);
                      if(userKey=='S')
                      {
                          cancelaAdmin(arqAdministrador,posX);
                          excluirFisicamenteAdmin(&arqAdministrador,"admin.csv");
                          printf("ADMINISTRADOR REMOVIDO COM SUCESSO!!!\n");
                      }else{
                        printf(ERRO);
                      }

                    }else{
                      printf(ERRO);
                    }
										break;
									
								}
							}while(opcaoSSMenuGerenciamento!=0);
							break;
					}
				}while(opcaoSMenuAdm!=0);
				break;
		}
	}while(opcaoMenuLogin!=0);

	fclose(arqCadastro); //Modificado hoje no dia 07/05/2021 - CONSERTADO O PROBLEMA DE REESCREVER USUARIOS
	fclose(arqAdministrador);
  fclose(arqCartaoUsuario);
  fclose(arqCarrinho);
	return 0;
}



//INICIO DO FILE
FILE *abreArquivo(char nomeArquivo[])
{
  FILE *arq;
	arq = fopen(nomeArquivo, "r+b");
	if(arq == NULL)
  {
    arq = fopen(nomeArquivo, "w+b");
  }
		
	return arq;
}
//FIM  DO FILE


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



void cancelaCartaoUsr(FILE *arq, int reg)
{
	struct tUsuario usr;
	fseek(arq, (reg-1)*sizeof(usr), SEEK_SET);
  fread(&usr,sizeof(usr),1,arq);
	usr.card.cartaoCancelado = 'c';
  fseek(arq,-sizeof(usr), SEEK_CUR);
	fwrite(&usr, sizeof(usr), 1, arq);

}

void excluirFisicamenteCartao (FILE **arqCard, char nome[]){//mudar int pra void
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
	fseek(arq, sizeof(ingressos)*reg, SEEK_SET);
	ingressos.cancelado = 'c';
	fwrite(&ingressos, sizeof(ingressos), 1, arq);

}


void excluirFisicamenteIngressos (FILE *arq, char ingresso[]){//mudar int pra void
	FILE *arqAux = fopen("ingressosAux.dat", "wb");
	struct tIngressos ingressos;
	
	fseek(arq, 0, SEEK_SET);
	while(fread(&ingressos, sizeof(ingressos), 1, arq) != 0)
		if(ingressos.cancelado != 'c')
    {
      fwrite(&ingressos, sizeof(ingressos), 1, arqAux);
    }
	
	fclose(arq);
	fclose(arqAux);
	remove(ingresso);
	rename("ingressosAux.dat", ingresso); // .dat pode dar erro por estar em .cvs na main
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
	FILE *arqAux = fopen("carrinhoUser.aux", "a+b");
	struct tIngressos ing;
	
	if(arqAux == NULL){
		printf("Erro de abertura!!!");
		return;
	}
	
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



void gravaDadosArqCartao(FILE *arq, struct tUsuario usr, int reg)
{
    if(reg <=0)
    {
      usr.card.cartaoCancelado = ' '; //Se não for feito isso, ele não cancela o negócio
      fseek(arq,0,SEEK_END);
    }
    fseek(arq,(reg-1)*sizeof(usr),SEEK_SET);
    fwrite(&usr, sizeof(usr), 1, arq);
}

int exportaCartaoXML(FILE *arqA)
{
  char ch;
  FILE *arq = fopen("dados.xml","w+b");
  if(arq==NULL || arqA == NULL)
  {
    return 0;
  }

  fseek(arqA,0,SEEK_SET);
  while(!feof(arqA))
  {
    ch = fgetc(arqA);
    if(ch !=EOF)
    {
       fputc(ch, arq);
    }
  }

  fclose(arq);
  return 0;
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