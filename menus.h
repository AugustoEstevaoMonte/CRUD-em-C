#ifndef MENUS_H
#define MENUS_H
#define ERRO "O dado inserido e invalido, tente novamente...\n"
#include <stdio.h>
#include <stdlib.h>

int menuLogin();
int menuUser();
int menuPagamento();
int menuCarrinho();
int menuGerenciamento();



int menuLogin()
{
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

int menuUser(){
	int op;
	do{
		system("cls");
		printf("\n\n\n*** ENTRADA ***\n\n\n");
		printf(" 1 - Ingressos disponiveis\n");
		printf(" 2 - Formas de pagamento\n");
		printf(" 3 - Meu carrinho\n");
    printf(" 4 - Consultar\n");
		printf(" 0 - Logout\n");
		printf("\nDigite sua opcao: ");
		scanf("%d", &op);
		if(op<0 || op>4){
			printf(ERRO);
			allPause();
		}
	}while(op<0 || op>4);
	return op;
}

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
			allPause();
		}
	}while(op<0 || op>3);
	return op;
}

int menuCarrinho(){
	int op;
	do{
		system("cls");
		printf("\n\n\n*** MEU CARRINHO ***\n\n\n");
		printf(" 1 - Ver meu carrinho\n");
		printf(" 2 - Adicionar item\n");
		printf(" 3 - Excluir item\n");
		printf(" 4 - Finalizar compra\n");
		printf(" 0 - Voltar\n");
		printf("\nDigite sua opcao: ");
		scanf("%d", &op);
		if(op<0 || op>4){
			printf(ERRO);
			allPause();
		}
	}while(op<0 || op>4);
	return op;
}

int menuAdm(){
	int op;
	do{
		printf("\n\n\n*** MENU DO ADMINISTRADOR ***\n\n\n");
		printf(" 1 - Ingressos disponiveis\n");
		printf(" 2 - Adicionar ingresso\n");
		printf(" 3 - Alterar ingresso\n");
		printf(" 4 - Excluir ingresso\n");
		printf(" 5 - Gerenciar contas\n");
    printf(" 6 - Consulta\n");
		printf(" 0 - Logout\n");
		printf("\nDigite sua opcao: ");
		scanf("%d", &op);
		if(op<0 || op>6){
			printf(ERRO);
			allPause();
		}
	}while(op<0 || op>6);
	return op;
}

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
			allPause();
		}
	}while(op<0 || op>4);
	return op;
}

#endif