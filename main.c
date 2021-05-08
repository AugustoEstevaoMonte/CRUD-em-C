//BIBLIOTECAS****************************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//INICIO DAS DEFINIÇÕES*****************************************************************************************
#define ERRO "O dado inserido e invalido!!\n"
#define MAX 30
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
  char local[40];
  float valor;
};

struct tAdministrador
{
	char adminName[MAX];
	char adminPassword[MAX];
};

struct tUsuario
{
  char usrName[MAX];
  char usrPassword[MAX];
  char usrNickName[MAX];
  char usrCartao[MAX];
	char cancelado;
  char nomeCartao[MAX];
  char cvCard[4];
};
//FIM DA STRUCT*********************************************************************************************


//INICIO DA  ENTRADA DE DADOS**************************************************************************************
void leValidaUsrName(char[]);
void leValidaUsrNickname(char[]);
void leValidaUsrPassword(char[]);
int verificaNicknameJaEstaEmUso(FILE *arq, char nickUsername[]);
int verificaSeLoginEsenhaCorrespondem(FILE *arq, char nomeUser[], char senhaUser[]);
int verificaUsuarioAdminEsenha(FILE *arq, char nomeUser[], char senhaUser[]); 
//Modificado hoje no dia 07/05/2021
void leValidaNumeroCartao(char numCard[]);
void leValidaNomeCartao(char nome[]);
void leValidaCVcartao(char cv[]);

int leValidaCodigo();
void leValidaNomeBanda(char banda[]);
void leValidaEstilo(char estilo[]);
void leValidaLocal(char local[]);
int leValidaHorasIni();
int leValidaMinIni();
int leValidaHorasFim();
int leValidaMinFim();
float leValidaValor();

//void leValidaIngressos(int cod, char banda[], int hIni, int mIni, int hFim, int mFim, char local[], float valor);

//FIM DA  ENTRADA DE DADOS**************************************************************************************



//INICIO DA GRAVAÇÃO DOS ARQUIVOS**************************************************************************************
void gravaDadosNoArquivoUsuario(FILE *arq, struct tUsuario usr, int reg);
void gravaDadosArquivoAdministrador(FILE *arq, struct tAdministrador admin); //Modificado hoje no dia 07/05/2021
void gravaDadosArquivoIngressos(FILE *arq, struct tIngressos ingressos);
//FIM DA GRAVAÇÃO DOS ARQUIVOS**************************************************************************************


//Mostrar as informações dos ARQUIVOS
void listagemIngressos(FILE*);

//INICIO DA FUNÇÃO FILE**************************************************************************************
FILE *abreArquivo(char nomeArquivo[]);
//FIM  DA FUNÇÃO FILE**************************************************************************************


//SUB-PROGRAMAS**************************************************************************************

//__________MENUS____________________________________________________________________________________
int menuLogin();
int menuUser();
int menuPagamento();
int menuCarrinho();
int menuAdm();
int menuGerenciamento();

//MAIN***********************************************************************************************
int main (void){
  FILE *arqCadastro,*arqAdministrador, *arqIngressos; //Modificado hoje no dia 08/05/2021 
  struct tUsuario usr;
	struct tAdministrador admin;
  struct tIngressos ingressos;
  char nomeUser;
	int opcaoMenuLogin, opcaoSMenuUser, opcaoSSMenuPagamento, opcaoSSMenuCarrinho, opcaoSMenuAdm, opcaoSSMenuGerenciamento;
	arqCadastro = abreArquivo("cadastro.csv"); //Modificado hoje no dia 07/05/2021 - CONSERTADO O PROBLEMA DE REESCREVER USUARIOS
  arqIngressos = abreArquivo("ingressos.csv");
  // ARRANJAR UM JEITO DE FAZER ISSO TUDO VIRAR UM ARQUIVO .XML
	do{
	volta: opcaoMenuLogin=menuLogin();  // :volta é usado pela função goto(volta) na linha 125 do CADASTRO, é usado para voltar ao MENU !!!!!!GAMBIARRA ATÉ SURGIR OUTRA SOLUÇÃO MELHOR
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
          system("pause");
          goto volta;
        }
				//INICIO DO SUB-MENU PARA USER
				do{
					opcaoSMenuUser=menuUser();
					// 1 - Ingressos disponiveis
					// 2 - Forma de pagamento
					// 3 - Excluir compra
					// 0 - Logout
					switch(opcaoSMenuUser){
						case 1:
							printf("\n\n\n*** INGRESSOS DISPONIVEIS ***\n\n\n");
							system("pause");
							break;
						case 2:
							//INICIO DO SUB-SUB-MENU PARA PAGAMENTO
							do{
								opcaoSSMenuPagamento=menuPagamento();
								// 1 - Adicionar cartao
								// 2 - Retirar cartao
								// 3 - Adicionar dinheiro na carteira
								// 0 - Voltar
								switch(opcaoSSMenuPagamento){
									case 1:
										printf("\n\n\n*** ADICIONAR CARTAO ***\n\n\n");
                    // vou editar aqui 
                    leValidaNumeroCartao(usr.usrCartao); //Falta CV, nome da pessoa
                    leValidaNomeCartao(usr.usrName);
                    leValidaCVcartao(usr.cvCard);
                    gravaDadosNoArquivoUsuario(arqCadastro,usr,-1);
										getchar();//system("pause");
										break;
									case 2:
										printf("\n\n\n*** RETIRAR CARTAO ***\n\n\n");
                    // e aqui também
										getchar();//system("pause");
										break;	
									case 3:
										printf("\n\n\n*** ADICIONAR DINHEIRO NA CARTEIRA ***\n\n\n");
										getchar();//system("pause");
										break;
								}
							}while(opcaoSSMenuPagamento!=0);
							system("pause");
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
										system("pause");
										break;
									case 2:
										printf("\n\n\n*** ADICIONAR INTEM ***\n\n\n");
										system("pause");
										break;	
									case 3:
										printf("\n\n\n*** EXCLUIR INTEM ***\n\n\n");
										system("pause");
										break;
									case 4:
										printf("\n\n\n*** FINALIZAR COMPRA ***\n\n\n");
										system("pause");
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
            system("pause");
            goto volta;
          }
          leValidaUsrPassword(usr.usrPassword);
          gravaDadosNoArquivoUsuario(arqCadastro,usr,-1); //Era pra escrever aqui
					printf("Usuario cadastrado com sucesso...\n");
        
				getchar();//system("pause");
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
					system("pause");
					goto volta;
				}
				printf("LOGIN REALIZADO COM SUCESSO!!!!\n"); // //Modificado hoje no dia 07/05/2021
				system("pause");
				//INICIO DO SUB-MENU PARA ADMINISTRADOR
				do{
					opcaoSMenuAdm=menuAdm();
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
								opcaoSSMenuGerenciamento=menuGerenciamento();
								// 1 - Usuarios
								// 2 - Administracao
								// 3 - Adicionar conta de administrador
								// 4 - excluir conta de administrador
								// 0 - Voltar 
								switch(opcaoSSMenuGerenciamento){
									case 1:
										printf("\n\n\n*** USUARIOS ***\n\n\n");
										system("pause");
										break;
									case 2:
										printf("\n\n\n*** ADMINISTRACAO ***\n\n\n");
										system("pause");
										break;
									case 3:
										printf("\n\n\n*** ADICIONAR CONTA DE ADMINISTRADOR ***\n\n\n");
										system("pause");
										break;
									case 4:
										printf("\n\n\n*** EXCLUIR CONTA DE ADMINISTRADOR ***\n\n\n");
										system("pause");
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
int menuLogin(){
	int op;
	do{
		system("cls");
		printf("\n\n\n*** LOGIN ***\n\n\n");
		printf(" 1 - Entrar\n");
		printf(" 2 - Cadastrar\n");
		printf(" 3 - Entrar como administrador\n");
		printf(" 0 - Sair\n");
		printf("\nDigite sua opcao: ");
		scanf("%d", &op);
		if(op<0 || op>3){
			printf(ERRO);
			system("pause");
		}
	}while(op<0 || op>3);
	return op;
}

//______USER_________________________________________________________________________________________

//Menu principal - onde tem as opcoes principais para o user
int menuUser(){
	int op;
	do{
		system("cls");
		printf("\n\n\n*** ENTRADA ***\n\n\n");
		printf(" 1 - Ingressos disponiveis\n");
		printf(" 2 - Formas de pagamento\n");
		printf(" 3 - Meu carrinho\n");
		printf(" 0 - Logout\n");
		printf("\nDigite sua opcao: ");
		scanf("%d", &op);
		if(op<0 || op>3){
			printf(ERRO);
			system("pause");
		}
	}while(op<0 || op>3);
	return op;
}

//Menu de pagamento - onde vai dar pra adicionar cartao e retirar cartao
int menuPagamento(){
	int op;
	do{
		system("cls");
		printf("\n\n\n*** FORMAS DE PAGAMENTO ***\n\n\n");
		printf(" 1 - Adicionar cartao\n");
		printf(" 2 - Retirar cartao\n");
		printf(" 3 - Adicionar dinheiro na carteira\n");
		printf(" 0 - Voltar\n");
		printf("\nDigite sua opcao: ");
		scanf("%d", &op);
		if(op<0 || op>3){
			printf(ERRO);
			system("pause");
		}
	}while(op<0 || op>3);
	return op;
}

//Menu do Carrinho - onde o user ve o que tem em seu carrinho, onde adiciona (por codigo de ingresso) o que comprar,
//exclui e finaliza compra
int menuCarrinho(){
	int op;
	do{
		system("cls");
		printf("\n\n\n*** MEU CARRINHO ***\n\n\n");
		printf(" 1 - Ver meu carrinho\n");
		printf(" 2 - Adicionar item\n");
		printf(" 3 - Excluir intem\n");
		printf(" 4 - Finalizar compra\n");
		printf(" 0 - Voltar\n");
		printf("\nDigite sua opcao: ");
		scanf("%d", &op);
		if(op<0 || op>4){
			printf(ERRO);
			system("pause");
		}
	}while(op<0 || op>4);
	return op;
}

//______ADMINISTRADOR__________________________________________________________________________________

//Menu principal - onde tem as opcoes principais para o administrador
int menuAdm(){
	int op;
	do{
		printf("\n\n\n*** MENU DO ADMINISTRADOR ***\n\n\n");
		printf(" 1 - Ingressos disponiveis\n");
		printf(" 2 - Adicionar ingresso\n");
		printf(" 3 - Alterar ingresso\n");
		printf(" 4 - Excluir ingresso\n");
		printf(" 5 - Gerenciar contas\n");
		printf(" 0 - Logout\n");
		printf("\nDigite sua opcao: ");
		scanf("%d", &op);
		if(op<0 || op>5){
			printf(ERRO);
			system("pause");
		}
	}while(op<0 || op>5);
	return op;
}

//Menu de Gerenciamento das contas
int menuGerenciamento(){
	int op;
	do{
		system("cls");
		printf("\n\n\n*** GERENCIAMENTO DE CONTAS ***\n\n\n");
		printf(" 1 - Usuarios\n");
		printf(" 2 - Administracao\n");
		printf(" 3 - Adicionar conta de administrador\n");
		printf(" 4 - excluir conta de administrador\n");
		printf(" 0 - Voltar\n");
		printf("\nDigite sua opcao: ");
		scanf("%d", &op);
		if(op<0 || op>4){
			printf(ERRO);
			system("pause");
		}
	}while(op<0 || op>4);
	return op;
}

//INICIO DO SISTEMA QUE PEDE O VALIDA O NOME DO USUÁRIO
void leValidaUsrName(char nomeUser[])
{
  do
  {
       printf("Digite aqui o seu nome: ");
       fflush(stdin);
       fgets(nomeUser,MAX,stdin);

       if(strlen(nomeUser)==1 || strlen(nomeUser)<6)
       {
         printf("Nome de usuario invalido, necessita ter pelo menos 6 caracteres...\n");
       }

  }while(strlen(nomeUser)==1 || strlen(nomeUser)<6);
}
//FIM DO SISTEMA QUE PEDE O VALIDA O NOME DO USUÁRIO

//INICIO DO SISTEMA QUE PEDE O VALIDA O NICKNAME
void leValidaUsrNickname(char nickUser[])
{
  do
  {
       printf("\nDigite aqui o seu nickname: ");
       fflush(stdin);
       fgets(nickUser,MAX,stdin);

       if(strlen(nickUser)==1 || strlen(nickUser)<6)
       {
         printf("Nickname invalido, necessita ter pelo menos 6 caracteres...\n");
       }

  }while(strlen(nickUser)==1 || strlen(nickUser)<6);
}
//FIM DO SISTEMA QUE PEDE O VALIDA O NICKNAME

//INICIO DO SISTEMA QUE PEDE O VALIDA A SENHA
void leValidaUsrPassword(char passwordUser[])
{
  do
  {
       printf("\nDigite aqui o sua senha: ");
       fflush(stdin);
       fgets(passwordUser,MAX,stdin);

       if(strlen(passwordUser)==1 || strlen(passwordUser)<6)
       {
         printf("Senha invalida, necessita ter pelo menos 6 caracteres...\n");
       }

  }while(strlen(passwordUser)==1 || strlen(passwordUser)<6);
}
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

int leValidaCodigo(){
  int cod;
  printf("Digite o codigo so show: ");
  scanf("%d", &cod);
  return cod;
}

void leValidaNomeBanda(char banda[])
{
   do
    {
        printf("\nBanda: ");
        fflush(stdin);
        fgets(banda, MAX, stdin);
        if(strlen(banda)==1)
        {
          printf("ERRO");
        }
    }while(strlen(banda)==1);
}

void leValidaEstilo(char estilo[]){
  do
    {
        printf("\nEstilo: ");
        fflush(stdin);
        fgets(estilo, 40, stdin);
        if(strlen(estilo)==1)
        {
          printf("ERRO");
        }
    }while(strlen(estilo)==1);
}

void leValidaLocal(char local[])
{
  do
  {
      printf("Local do show: ");
      fflush(stdin);
      fgets(local, 40, stdin);
      if(strlen(local)==1)
      {
          printf(ERRO);
      }
  }while(strlen(local)==1);

}

int leValidaHorasIni()
{
    int horas;
     do
    {
        printf("Hora do inicio (apenas a hora): ");
        fflush(stdin);
        scanf("%d", &horas);
        if(horas<1 || horas>24)
        {
          printf(ERRO);
        }
    }while(horas<1 || horas>24);
return horas;
}

int leValidaMinIni()
{
    int min;
     do
    {
        printf("Minutos do inicio: ");
        fflush(stdin);
        scanf("%d", &min);
        if(min<0 || min>59)
        {
          printf(ERRO);
        }
    }while(min<0 || min>59);
return min;
}

int leValidaHorasFim()
{
    int horas;
     do
    {
        printf("Hora do final (apenas a hora): ");
        fflush(stdin);
        scanf("%d", &horas);
        if(horas<1 || horas>24)
        {
          printf(ERRO);
        }
    }while(horas<1 || horas>24);
return horas;
}

int leValidaMinFim()
{
    int min;
     do
    {
        printf("Minutos do final: ");
        fflush(stdin);
        scanf("%d", &min);
        if(min<0 || min>59)
        {
          printf(ERRO);
        }
    }while(min<0 || min>59);
return min;
}

float leValidaValor(){
  float valor;
  printf("Valor do ingresso: ");
  scanf("%f", &valor);
  return valor;
}


void leValidaNumeroCartao(char numCard[])
{
  do
  {
    printf("Digite aqui o numero do seu cartao: \n");
    fflush(stdin);
    fgets(numCard,MAX,stdin);
    if(strlen(numCard)==1 || strlen(numCard)<=8)
    {
        printf("Numero do cartao e invalido, necessita ter 8 digitos...\n");
    }
  }while(strlen(numCard)==1 || strlen(numCard)<=8); //Resolvido o erro
}

void leValidaNomeCartao(char nome[])
{
    do
    {
      printf("Digite aqui o nome do usuario do cartao: \n");
      fflush(stdin);
      fgets(nome,MAX,stdin);
      if(strlen(nome)==1 || strlen(nome)<5)
      {
        printf("Nome invalido, necessita ter ate 5 caracteres...\n");
      }
    }while(strlen(nome)==1 || strlen(nome)<5);
}


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


void leValidaCVcartao(char cv[])
{
  do
  {
    printf("Digite aqui o CV do seu cartao: \n");
    fflush(stdin);
    fgets(cv,4,stdin);
    
    if(strlen(cv)==1 || strlen(cv)!=3)
    {
      printf("CV invalido, necessita ter 3 digitos...\n");
    }

  }while(strlen(cv)==1 || strlen(cv)!=3);
}





