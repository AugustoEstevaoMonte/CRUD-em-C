//BIBLIOTECAS****************************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "menus.h" //Biblioteca criada no dia 11/05 para os "Menus"
#include "validacoes.h" //Biblioteca criada no dia 11/05 para validações

//INICIO DAS DEFINIÇÕES*****************************************************************************************
//DEFINE MAX 30 FICAVA AQUI
//FIM DAS DEFINIÇÕES*****************************************************************************************

//STRUCT*********************************************************************************************
struct tIngressos ////Modificado hoje no dia 08/05/2021
{ 
	int codigo;
  int horaIni;
  int minIni;
  int horaFim;
  int minFim;
  char banda[MAX];
  char local[MAX];
  float valor;
};

struct tAdministrador
{
	char adminName[MAX];
	char adminPassword[MAX];
};

struct tCartaoUsr
{
  char usrNumCartao[MAX];
  int cvCard;
  char cartaoCancelado;
};

struct tUsuario
{
  char usrName[MAX];
  char usrPassword[MAX];
  char usrNickName[MAX];
  struct tCartaoUsr card;
  float valorCarteira;
};

  struct tUsuario lerDadosUsr (int posicao, FILE *arq){
	struct tUsuario usr;
	fseek(arq, sizeof(usr)*posicao, SEEK_SET);
	fread(&usr, sizeof(usr), 1, arq);
	return usr;
}
//FIM DA STRUCT*********************************************************************************************
int leValidaNumeroCartao(char num[]);
int leValidaCVcard(int cvCard);
void leituraUsuario(FILE *arq);
void cancelaCartaoUsr(FILE *arq, int reg);
int excluirFisicamenteCartao (FILE *arqUser, char nome[]);
void lerCarteiraUser(FILE *arq, struct tUsuario *);

//INICIO DA  ENTRADA DE DADOS**************************************************************************************
//void leValidaUsrName(char[]); //Dentro da func
//void leValidaUsrNickname(char[]);
//void leValidaUsrPassword(char[]);
int verificaNicknameJaEstaEmUso(FILE *arq, char nickUsername[]);
int verificaSeLoginEsenhaCorrespondem(FILE *arq, char nomeUser[], char senhaUser[]);
int verificaUsuarioAdminEsenha(FILE *arq, char nomeUser[], char senhaUser[]); 
//Modificado hoje no dia 07/05/2021

//int leValidaCodigo();
//void leValidaNomeBanda(char banda[]);
//void leValidaEstilo(char estilo[]);
//void leValidaLocal(char local[]);
//int leValidaHorasIni();
//int leValidaMinIni();
//int leValidaHorasFim();
//int leValidaMinFim();
//float leValidaValor();

//void leValidaIngressos(int cod, char banda[], int hIni, int mIni, int hFim, int mFim, char local[], float valor);

//FIM DA  ENTRADA DE DADOS**************************************************************************************



//INICIO DA GRAVAÇÃO DOS ARQUIVOS**************************************************************************************
void gravaDadosNoArquivoUsuario(FILE *arq, struct tUsuario usr, int reg);
void gravaDadosArquivoAdministrador(FILE *arq, struct tAdministrador admin); //Modificado hoje no dia 07/05/2021
void gravaDadosArquivoIngressos(FILE *arq, struct tIngressos ingressos);
//FIM DA GRAVAÇÃO DOS ARQUIVOS**************************************************************************************
//CONSULTA informações
int consultaNumeroCartao(FILE *arq, char busca[]);

//CONSULTA INFORMAÇÕES

//Mostrar as informações dos ARQUIVOS
void listagemIngressos(FILE*);

//Excluir coisas



//INICIO DA FUNÇÃO FILE**************************************************************************************
FILE *abreArquivo(char nomeArquivo[]);
//FIM  DA FUNÇÃO FILE**************************************************************************************


//SUB-PROGRAMAS**************************************************************************************



//MAIN***********************************************************************************************
int main (void){
  printf("Inicio do programa");
  FILE *arqCadastro,*arqAdministrador, *arqIngressos, *arqCartaoUsuario; //Modificado hoje no dia 08/05/2021 
  struct tUsuario usr;
	struct tAdministrador admin;
  struct tIngressos ingressos;
  char nomeUser,userKey;
	int opcaoMenuLogin, opcaoSMenuUser, opcaoSSMenuPagamento, opcaoSSMenuCarrinho, opcaoSMenuAdm, opcaoSSMenuGerenciamento,erroFunc=0,posX;
  float saldoCarteira=0;
	arqCadastro = abreArquivo("cadastro.csv"); //Modificado hoje no dia 07/05/2021 - CONSERTADO O PROBLEMA DE REESCREVER USUARIOS
  arqIngressos = abreArquivo("ingressos.csv");
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
                    posX = consultaNumeroCartao(arqCadastro,usr.card.usrNumCartao);
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


                        gravaDadosNoArquivoUsuario(arqCadastro,usr,0);
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

                    posX = consultaNumeroCartao(arqCadastro,usr.card.usrNumCartao);
                    if(posX == 0)
                    {
                        leituraUsuario(arqCadastro);
                        printf("Numero do cartao: %s\n",usr.card.usrNumCartao);
                        printf("Deseja remover o cartao? (S ou n) \n");
                        fflush(stdin); //SE NÃO FOR EXECUTADO GERA ERRO NO CÓDIGO
                        scanf("%c",&userKey);
                        userKey = toupper(userKey);
                        if(userKey=='S')
                        {
                          cancelaCartaoUsr(arqCadastro,posX);
                          gravaDadosNoArquivoUsuario(arqCadastro,usr,posX);
                          excluirFisicamenteCartao (arqCadastro,"cadastro.csv");
                          printf("Cartao cancelado com sucesso!!!\n");
                          allPause();
                        }
                    } else {
                      printf("Numero de cartao invalido, tente novamente...\n");
                      allPause();
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
                    posX = consultaNumeroCartao(arqCadastro,usr.card.usrNumCartao);
                    if(posX==0)
                    {
                      lerCarteiraUser(arqCadastro,&usr);
                      //printf("Seu saldo atual na conta: %0.2f\n",usr.valorCarteira);
                      printf("Digite um valor que deseja adicionar: \n");
                      scanf("%f",&saldoCarteira);
                      usr.valorCarteira+=saldoCarteira;
                      printf("VALOR ADICIONADO COM SUCESSO!!\n");
                      gravaDadosNoArquivoUsuario(arqCadastro,usr,posX);
                      allPause();
                    } else{
                      printf("NAO FOI ENCONTRADO NENHUM CARTAO...\n");
                      allPause();
                    }
                    printf("Valor recebeu: %0.2f\n",usr.valorCarteira);
                    
										allPause();
										break;
								}
							}while(opcaoSSMenuPagamento!=0);
							allPause();
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
										allPause();
										break;
									case 2:
										printf("\n\n\n*** ADICIONAR INTEM ***\n\n\n");
										allPause();
										break;	
									case 3:
										printf("\n\n\n*** EXCLUIR INTEM ***\n\n\n");
										allPause();
										break;
									case 4:
										printf("\n\n\n*** FINALIZAR COMPRA ***\n\n\n");
										allPause();
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
              
							
							break;
						case 4:
							printf("\n\n\n*** EXCLUIR INGRESSOS ***\n\n\n");


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
										allPause();
										break;
									case 2:
										printf("\n\n\n*** ADMINISTRACAO ***\n\n\n");
										allPause();
										break;
									case 3:
										printf("\n\n\n*** ADICIONAR CONTA DE ADMINISTRADOR ***\n\n\n");
										allPause();
										break;
									case 4:
										printf("\n\n\n*** EXCLUIR CONTA DE ADMINISTRADOR ***\n\n\n");
										allPause();
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
	return 0;
}

//MENUs *********************************************************************************************

//______LOGIN________________________________________________________________________________________
//Menu Login ficava aqui

//______USER_________________________________________________________________________________________

//Menu principal - onde tem as opcoes principais para o user
//Menu user ficava aqui

//Menu de pagamento - onde vai dar pra adicionar cartao e retirar cartao
//Aqui ficava o menu pagamento

//Menu do Carrinho - onde o user ve o que tem em seu carrinho, onde adiciona (por codigo de ingresso) o que comprar,
//exclui e finaliza compra
//Aqui ficava o Menu carrinho

//______ADMINISTRADOR__________________________________________________________________________________

//Menu principal - onde tem as opcoes principais para o administrador
//Menu ADM ficava aqui

//Menu de Gerenciamento das contas
//Aqui ficava o menu gerenciamento

//INICIO DO SISTEMA QUE PEDE O VALIDA O NOME DO USUÁRIO
//Aqui ficava leValidaUsrName
//FIM DO SISTEMA QUE PEDE O VALIDA O NOME DO USUÁRIO

//INICIO DO SISTEMA QUE PEDE O VALIDA O NICKNAME
//Aqui ficava a validação do nickname
//FIM DO SISTEMA QUE PEDE O VALIDA O NICKNAME

//INICIO DO SISTEMA QUE PEDE O VALIDA A SENHA
//Aqui ficava o leValidaUsrPassword();
//FIM DO SISTEMA QUE PEDE O VALIDA A SENHA

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

void gravaDadosNoArquivoUsuario(FILE *arq, struct tUsuario usr, int reg) //Modificado hoje no dia 07/05/2021 - CONSERTADO O PROBLEMA DE REESCREVER USUARIOS
{
   if(reg == -1){
		fseek(arq, 0, SEEK_END);
		fwrite(&usr, sizeof(usr), 1, arq);
	}else{
		fseek(arq, sizeof(usr)*reg, SEEK_SET);
		fwrite(&usr, sizeof(usr), 1, arq);
	}
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

void gravaDadosArquivoAdministrador(FILE *arq, struct tAdministrador admin) //Modificado hoje no dia 07/05/2021
{
		fseek(arq, 0, SEEK_END);
		fwrite(&admin, sizeof(admin), 1, arq);
}

int verificaUsuarioAdminEsenha(FILE *arq, char nomeUser[], char senhaUser[]) //Modificado hoje no dia 07/05/2021
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



//Aqui ficava o nome da banda

//Aqui ficava os estilos

//Aqui ficavam os locais

//Aqui ficava o leValidaHorasIni

//aqui ficava o leValidaMinIni

//aqui ficava o leValidaHorasFim

//Aqui ficava leValidaMinFim

//aqui ficava o leValidaValor


void gravaDadosArquivoIngressos(FILE *arq, struct tIngressos ingressos){
    fseek(arq, 0, SEEK_END);
		fwrite(&ingressos, sizeof(ingressos), 1, arq);
}

void listagemIngressos(FILE *arq)
{
  struct tIngressos ingressos;
  fseek(arq, 0, SEEK_SET); //fseek tá certo, é outro erro
  while(fread(&ingressos, sizeof(ingressos), 1, arq)!=0)
  {
      printf("\n\n\n%d - %sLocal: %sInicio: %d:%d - Final: %d:%d\nValor: %.2f\n\n",ingressos.codigo, ingressos.banda, ingressos.local, ingressos.horaIni, ingressos.minIni, ingressos.horaFim, ingressos.minFim, ingressos.valor);
  }
}

int leValidaNumeroCartao(char num[])
{
  if(strlen(num)!=9)
  {
    return 1;
  }
  return 0;
}

 

int leValidaCVcard(int cvCard)
{
  if(cvCard>=100 && cvCard<=999)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

int consultaNumeroCartao(FILE *arq, char busca[])
{
  struct tUsuario usr;
  int ind = 0;
	fseek(arq, 0, SEEK_SET);
	while(fread(&usr, sizeof(usr), 1, arq) != 0)
  {
		if(strcmp(busca,usr.card.usrNumCartao)==0)
    {
      return 0; // 0 representa que achou o numero do cartao
    }
	}
	return -1; // -1 representa não encontrado
}

void leituraUsuario(FILE *arq)
{
  struct tUsuario usr;
	fseek(arq, 0, SEEK_SET);
	fread(&usr,sizeof(usr),1,arq);
}

void cancelaCartaoUsr(FILE *arq, int reg)
{
	struct tUsuario usr;
	fseek(arq, sizeof(usr)*reg, SEEK_SET);
	usr.card.cartaoCancelado = 'c';
	fwrite(&usr, sizeof(usr), 1, arq);

}

int excluirFisicamenteCartao (FILE *arqUser, char nome[]){//mudar int pra void
	FILE *arqAux = fopen("cadastroAux.dat", "wb");
	struct tUsuario usr;
	
  //não precisa por não ter verificação na main (booleana)
	if(arqAux == NULL){
		printf("Erro de abertura!!!");
		return 0;
	}
	
	fseek(arqUser, 0, SEEK_SET);
	while(fread(&usr, sizeof(usr), 1, arqUser) != 0)
		if(usr.card.cartaoCancelado != 'c')
    {
      fwrite(&usr, sizeof(usr), 1, arqAux);
    }
	
	fclose(arqUser);
	fclose(arqAux);
	remove(nome);
	rename("cadastroAux.dat", nome); // .dat pode dar erro por estar em .cvs na main
	
	return 1;
}

void lerCarteiraUser(FILE *arq, struct tUsuario *usr)
{
	  fseek(arq, 0, SEEK_SET);
	  while(fread(&(*usr),sizeof(*usr),1,arq)!=0)
    {
      printf("O valor na carteira e de: %0.2f\n",(*usr).valorCarteira);
    }
}