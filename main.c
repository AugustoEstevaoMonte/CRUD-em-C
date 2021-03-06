//BIBLIOTECAS****************************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funcoesuteis.h" //Contém AllPause, abreArquivo
#include "menus.h" //Biblioteca criada no dia 11/05 para os "Menus"
#include "validacoes.h" //Biblioteca criada no dia 11/05 para validações
#include "structs.h" //Biblioteca contendo structs | OBS: ELA SEMPRE DEVE ESTAR EM PRIMEIRO NA INCLUSAO |
#include "gravacoes.h" //Biblioteca contendo funções de gravação
#include "listagem.h" //Biblioteca contendo funções de listagem
#include "leitura.h" //Biblioteca contendo funções de leitura
#include "verificacoes.h" //Biblioteca contendo funções de verificação
#include "consultas.h" //Biblioteca contendo funções de consulta
#include "exclusaocancelamento.h" //Biblioteca contendo funções de cancelamento e exclusão
#include "exportaxml.h" //Biblioteca contendo o código para exportar arquivos XML


//MAIN***********************************************************************************************
int main (void){
  printf("Inicio do programa");
  FILE *arqCadastro,*arqAdministrador, *arqIngressos, *arqCartaoUsuario, *arqCarrinho; //Modificado hoje no dia 08/05/2021 
  struct tUsuario usr;
	struct tAdministrador admin;
  struct tIngressos ingressos;
  char nomeUser,userKey, userKey2;
	int opcaoMenuLogin, opcaoSMenuUser, opcaoSSMenuPagamento, opcaoSSMenuCarrinho, opcaoSMenuAdm, opcaoSSMenuGerenciamento,erroFunc=0,posX, posY, flag;
  int buscaIngresso,totCart=0,regex=0;
  float saldoCarteira=0,totalIngressos=0;


	arqCadastro = abreArquivo("cadastro.csv"); 
  arqIngressos = abreArquivo("ingressos.csv");
  arqCartaoUsuario = abreArquivo("infoCartao.csv");
  arqCarrinho = abreArquivo("carrinhoUser.csv");

	do{
	opcaoMenuLogin = menuLogin();
		//primeiro menu, onde tem:
		// 1 - Entrar
		// 2 - Cadastrar
		// 3 - Entrar como administrador
		// 0 - Sair
		
		switch(opcaoMenuLogin){
			case 1:
      do{
        system("cls||clear");
        printf("\n\n\n*** ENTRAR ***\n\n\n");
        setbuf(stdin,NULL);
        leValidaUsrNickname(usr.usrNickName);
        setbuf(stdin,NULL);
        leValidaUsrPassword(usr.usrPassword);
        if(verificaSeLoginEsenhaCorrespondem(arqCadastro,usr.usrNickName,usr.usrPassword)==1){
          printf(ERRO);
          allPause();
          flag=0;
        }else{
          flag=1;
          usr.valorCarteira = 0;
          exportarCadastroXML(arqCadastro,"cadastro.xml");
        }

      }while(flag==0);
				
				//INICIO DO SUB-MENU PARA USER
				do{
					opcaoSMenuUser=menuUser();
					// 1 - Ingressos disponiveis
					// 2 - Forma de pagamento
					// 3 - Meu carrinho
          // 4 - Consulta
					// 0 - Logout
					switch(opcaoSMenuUser){
						case 1:
             system("cls||clear");
							printf("\n\n\n*** INGRESSOS DISPONIVEIS ***\n\n\n");
              listagemIngressos(arqIngressos);
                setbuf(stdin,NULL);
                allPause();

							break;
						case 2:
							//INICIO DO SUB-SUB-MENU PARA PAGAMENTO
							do{
								opcaoSSMenuPagamento = menuPagamento(); 
								// 1 - Adicionar cartao
								// 2 - Retirar cartao
								// 3 - Adicionar dinheiro na carteira
                // 4 - Saldo na carteira
								// 0 - Voltar
								switch(opcaoSSMenuPagamento){
									case 1:
                    do{    
                      system("cls||clear");
                          printf("\n\n\n*** ADICIONAR CARTAO ***\n\n\n");
                          printf("Digite aqui o numero do cartao: \n");
                          setbuf(stdin,NULL);
                          fgets(usr.card.usrNumCartao,MAX,stdin);
                          erroFunc = leValidaNumeroCartao(usr.card.usrNumCartao);
                          if(erroFunc==1){
                            printf("O cartao precisa ter no minimo 8 numeros...\n");
                            allPause();
                          }

                    }while(erroFunc==1);

                    posX = consultaNumeroCartao(arqCartaoUsuario,usr.card.usrNumCartao);
                    if(posX==-1){
                        do{
                        printf("Digite aqui o CV do cartao: \n");
                        setbuf(stdin,NULL);
                        scanf("%d",&usr.card.cvCard);
                        erroFunc = leValidaCVcard(usr.card.cvCard);
                        if(erroFunc==1){
                             printf("O CV precisa ter 3 digitos...\n");
                             allPause();
                        }
										  }while(erroFunc==1);

                        setbuf(stdin,NULL);
                        gravaDadosArqCartao(arqCartaoUsuario,usr,posX);
                        printf("CADASTRADO COM SUCESSO!!\n");
                        printf("Numero cartao: %s\n",usr.card.usrNumCartao);
                        printf("CV cartao: %d\n",usr.card.cvCard);
                        usr.valorCarteira = 0;
                    }else{
                      printf("Numero de cartao ja inserido anteriormente...\n");
                      allPause();
                    }
                    


                      
										break;
									case 2:
                  system("cls||clear");
										printf("\n\n\n*** RETIRAR CARTAO ***\n\n\n");
                    do{
                      printf("Digite aqui o numero do cartao que deseja remover: \n");
                      setbuf(stdin,NULL);
                      fgets(usr.card.usrNumCartao,MAX,stdin);
                      erroFunc = leValidaNumeroCartao(usr.card.usrNumCartao);
                      if(erroFunc==1){
                        printf("Numero de cartao invalido, tente novamente...\n");
                        setbuf(stdin,NULL);
                        allPause();
                      }
                      
                    }while(erroFunc==1);

                    posX = consultaNumeroCartao(arqCartaoUsuario,usr.card.usrNumCartao);
                    if(posX > 0){   
                        setbuf(stdin,NULL);
                        usr = lerUser(posX, arqCartaoUsuario);
                        printf("Numero do cartao: %s\n",usr.card.usrNumCartao); 
                        printf("Deseja remover o cartao? (S ou n) \n");
                        setbuf(stdin,NULL); 
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
                      setbuf(stdin,NULL);
                      allPause();
										break;	
									case 3:
                  system("cls||clear");
										printf("\n\n\n*** ADICIONAR DINHEIRO NA CARTEIRA ***\n\n\n");
                     do
                    {
                      printf("Confirme o numero do cartao: \n");
                      setbuf(stdin,NULL);
                      fgets(usr.card.usrNumCartao,MAX,stdin);
                      erroFunc = leValidaNumeroCartao(usr.card.usrNumCartao);
                      if(erroFunc==1)
                      {
                        printf("Numero de cartao invalido, tente novamente...\n");
                      }
                      
                    }while(erroFunc==1);
                    posX = consultaNumeroCartao(arqCartaoUsuario,usr.card.usrNumCartao);
                    if(posX > 0)
                    { setbuf(stdin,NULL);
                     usr =  lerCarteiraUsr(posX,arqCartaoUsuario);
                      printf("Valor na carteira: %0.2f\n",usr.valorCarteira);
                      printf("Deseja adicionar o valor na carteira? (S ou n) \n");
                      setbuf(stdin,NULL);
                      scanf("%c",&userKey);
                      userKey = toupper(userKey);
                      if(userKey=='S')
                      {    
                          do
                          { 
                          printf("Digite um valor que deseja adicionar: \n");
                          scanf("%f",&saldoCarteira);

                          if(saldoCarteira<=0.0)
                          {
                             printf("Saldo invalido, tente novamente...\n\n");
                          }

                          }while(saldoCarteira<=0.0);

                          setbuf(stdin,NULL);
                          usr.valorCarteira+=saldoCarteira;
                          printf("VALOR ADICIONADO COM SUCESSO!!\n");
                          gravaDadosArqCartao(arqCartaoUsuario,usr,posX);
                          exportarCardXML(arqCartaoUsuario,"cartao.xml");
                      }else{
                        printf("Transacao abortada pelo usuario...\n");
                      }
                    } else{
                      printf("NAO FOI ENCONTRADO NENHUM CARTAO...\n");
                    }
                    setbuf(stdin,NULL);
                    allPause();
										break;
                    case 4:
                    system("cls||clear");
                  	printf("\n\n\n*** SALDO ***\n\n\n");
                     
                    do
                    {
                      printf("Confirme o numero do cartao: \n");
                      setbuf(stdin,NULL);
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
                      usr = lerCarteiraUsr(posX,arqCartaoUsuario); 
                      printf("Voce tem na carteira: %0.2f\n",usr.valorCarteira);
                      setbuf(stdin,NULL);
                      allPause();
                   }else{
                     printf("Cartao nao encontrado...\n");
                     setbuf(stdin,NULL);
                     allPause();
                   }

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
                  system("cls||clear");
										printf("\n\n\n*** VER MEU CARRINHO ***\n\n\n");
                    setbuf(stdin,NULL);
                    listArqCar(arqCarrinho);
                    setbuf(stdin,NULL);
                    allPause();
										break;
									case 2:
                  system("cls||clear");
										printf("\n\n\n*** ADICIONAR ITEM ***\n\n\n");
                    listagemIngressos(arqIngressos);
                    setbuf(stdin,NULL);
                    printf("Digite aqui o codigo do ingresso que deseja adicionar...\n");
                    setbuf(stdin,NULL);
                    ingressos.codigo=leValidaCodigo();
                    posX = consultaCodShow(&ingressos,arqIngressos,ingressos.codigo);
                    if(posX > 0)
                    {
                       setbuf(stdin,NULL);
                       ingressos = lerIngressos(posX, arqIngressos);
                       printf("Nome do Artista: %s\nLocal: %s\nInicio: %i:%i - Final: %i:%i\nValor: %0.2f\n",ingressos.banda,ingressos.local,ingressos.horaIni,ingressos.minIni,ingressos.horaFim,ingressos.minFim,ingressos.valor);
                       gravaDadosNoArquivoCarrinho(arqCarrinho,ingressos,posX);
                       printf("Gravado com sucesso!!!\n");
                    }else{
                      printf("Codigo nao encontrado, tente novamente....\n");
                    }
                    setbuf(stdin,NULL);
                    allPause();
										break;	
									case 3:
                  system("cls||clear");
										printf("\n\n\n*** EXCLUIR ITEM ***\n\n\n");
                    listArqCar(arqCarrinho);
                    printf("Digite aqui o codigo do ingresso que deseja EXCLUIR...\n");
                    ingressos.codigo = leValidaCodigo();
                    posX = consultaCodShow(&ingressos,arqIngressos,ingressos.codigo);
                    if(posX > 0)
                    {  setbuf(stdin,NULL);
                       ingressos = lerIngressos(posX, arqIngressos);
                       printf("Nome do Artista: %s\nLocal: %s\nInicio: %i:%i - Final: %i:%i\n",ingressos.banda,ingressos.local,ingressos.horaIni,ingressos.minIni,ingressos.horaFim,ingressos.minFim);
                       printf("Tem certeza que deseja excluir? (S ou n)\n");
                       setbuf(stdin,NULL);
                       scanf("%c",&userKey);
                       userKey = toupper(userKey);
                       if(userKey=='S') 
                       {
                         cancelaIngressoArqCarrinho(arqCarrinho,posX);
                         excluirFisicamenteCarrrinho (&arqCarrinho,"carrinhoUser.csv");
                         printf("EXCLUIDO COM SUCESSO!!!!\n");
                       } else{
                         printf("Operacao abortada pelo usuario...\n");
                       }
                    }else{
                      printf(ERRO);
                    }
                    setbuf(stdin,NULL);
                    allPause();
										break;
									case 4:
                  system("cls||clear");
										printf("\n\n\n*** FINALIZAR COMPRA ***\n\n\n");
                    printf("Confirme o numero do seu cartao...\n");

                    do
                    {
                      printf("Digite aqui o numero do cartao: \n");
                      setbuf(stdin,NULL);
                      fgets(usr.card.usrNumCartao,MAX,stdin);
                      erroFunc = leValidaNumeroCartao(usr.card.usrNumCartao);
                      if(erroFunc==1)
                      {
                        printf("Numero de cartao invalido, tente novamente...\n");
                      }
                      
                    }while(erroFunc==1);

                    setbuf(stdin,NULL);
                    posX = consultaNumeroCartao(arqCartaoUsuario,usr.card.usrNumCartao);
                    if(posX > 0)
                    { 
                          totalIngressos = listarArquivoCarrinho(arqCarrinho);
                          totCart = totalNaCarteira(arqCartaoUsuario);
                          if(totalIngressos <= totCart && totalIngressos>0.0)
                          { 
                            ingressos = lerIngressos(posX,arqCarrinho);
                            printf("Valor total da(s) compra(s): %0.2f\n",totalIngressos);
                            usr = lerCarteiraUsr(posX,arqCartaoUsuario);
                            printf("Voce tem na carteira: %0.2f\n",usr.valorCarteira);//Exibe o valor da carteira
                            printf("Deseja continuar com a transacao? (S ou N)\n");
                            setbuf(stdin,NULL);
                            scanf("%c",&userKey);
                            userKey = toupper(userKey);
                            if(userKey=='S')
                            {
                                subtraiValores(&usr,totalIngressos,arqCartaoUsuario,usr.card.usrNumCartao);
                                gravaCardAlt(arqCartaoUsuario,usr,posX);
                                setbuf(stdin,NULL);
                                cancelaIngressoArqCarrinho(arqCarrinho,posX);
                                excluirFisicamenteCarrrinho(&arqCarrinho,"carrinhoUser.csv");
                                printf("TRANSACAO REALIZADA COM SUCESSO!!!!\n");
                            } else{
                              printf("Transacao abortada pelo usuario...\n");
                            }
                          }else{
                            printf("Valor na carteira menor do que o valor dos ingressos ou NENHUM ITEM FOI ADICIONADO AO CARRINHO\n");
                          }
                    
                    } else {
                      printf(ERRO);
                    }
                    allPause();
										break;
								}
							}while(opcaoSSMenuCarrinho!=0);
							break;
              case 4:
              system("cls||clear");
              printf("\n\n*** CONSULTA ***\n\n");
              printf("Digite aqui o codigo do ingresso: ");
              setbuf(stdin,NULL);
              scanf("%d", &buscaIngresso);
              posX = consultaCodShow(&ingressos,arqIngressos,buscaIngresso);
              if(posX > 0){
                       leituraIngresso(arqIngressos, buscaIngresso);
                       setbuf(stdin,NULL);
									  	 allPause();
                        
                    } else {
                      printf("Codigo invalido, tente novamente...\n");
                      setbuf(stdin,NULL);
									  	allPause();
                    }
               setbuf(stdin,NULL);
               allPause();
              break;
					}
			}while(opcaoSMenuUser!=0);
				break;
			case 2:
      
          do{
            system("cls||clear");
              printf("\n\n\n*** CADASTRAR ***\n\n\n");
              setbuf(stdin,NULL);
              leValidaUsrName(usr.usrName);
              setbuf(stdin,NULL);
              leValidaUsrNickname(usr.usrNickName);
              if(verificaNicknameJaEstaEmUso(arqCadastro,usr.usrNickName)==1)
              {
                printf("Este nickname ja esta em uso, tente novamente...\n");
                allPause();
                flag=0;
              }else{
                flag=1;
              }
          }while(flag==0);
          leValidaUsrPassword(usr.usrPassword);
          usr.valorCarteira = 0;
          gravaDadosNoArquivoUsuario(arqCadastro,usr,-1); 
					printf("Usuario cadastrado com sucesso...\n");
        setbuf(stdin,NULL);
				allPause();
				break;
			case 3:
      do{
        system("cls||clear");
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
          setbuf(stdin,NULL);
          leValidaUsrName(admin.adminName);  // ADMINISTRADOR ENCOTRADO, INICIANDO LOGIN E SENHA 
          leValidaUsrPassword(admin.adminPassword); 
          if(verificaUsuarioAdminEsenha(arqAdministrador,admin.adminName,admin.adminPassword)==1)   
          {
            printf(ERRO);
            allPause();
            flag=0;
          }else{
            flag=1;
            exportarAdminXML(arqAdministrador,"admina.xml");
          }
      }while (flag==0);
				printf("LOGIN REALIZADO COM SUCESSO!!!!\n"); 
        setbuf(stdin,NULL);
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
            system("cls||clear");
							printf("\n\n\n*** INGRESSOS DISPONIVEIS ***\n\n\n");

              listagemIngressos(arqIngressos);
              allPause();
							
							break;
						case 2:
            system("cls||clear");
							printf("\n\n\n*** ADICIONAR INGRESSOS ***\n\n\n");
            do
            {
              ingressos.codigo=leValidaCodigo();
              regex = codRepetido(arqIngressos,ingressos.codigo);
              if(regex<0)
              {
                 printf("Codigo de ingresso repetido, tente novamente...\n");
              }

            }while(regex<0);
            setbuf(stdin,NULL);

            leValidaNomeBanda(ingressos.banda);
            leValidaLocal(ingressos.local);
            ingressos.horaIni=leValidaHorasIni();
            ingressos.minIni=leValidaMinIni();
            ingressos.horaFim =leValidaHorasFim();
            ingressos.minFim= leValidaMinFim();
            ingressos.valor=leValidaValor();

        
            

             printf("\n\n\n%d - %sLocal: %sInicio: %d:%d - Final: %d:%d\nValor: %.2f\n\n",ingressos.codigo, ingressos.banda, ingressos.local, ingressos.horaIni, ingressos.minIni, ingressos.horaFim, ingressos.minFim, ingressos.valor);
             
            gravaDadosArquivoIngressos(arqIngressos, ingressos);
            posX = exportarIngressosXML(arqIngressos,"ingressos.xml");
          




							break;
						case 3:
            system("cls||clear");
							printf("\n\n\n*** ALTERAR INGRESSOS ***\n\n\n");

              do
              {
                
                printf("Digite aqui o codigo do ingresso: \n");
                scanf("%i",&buscaIngresso);
                if(buscaIngresso<0)
                {
                  printf(ERRO);
                } 
              }while(buscaIngresso<0);


              posX = consultaCodShow(&ingressos,arqIngressos,buscaIngresso);

              if(posX>0)
              {
                  ingressos = lerIngressos(posX,arqIngressos);
                  printf("A banda e: %s\n",ingressos.banda);
                  printf("Digite a nova banda...\n");
                  setbuf(stdin,NULL);
                  leValidaNomeBanda(ingressos.banda);
                  printf("O local e: %s\n",ingressos.local);
                  printf("Digite o novo local...\n");
                  setbuf(stdin,NULL);
                  leValidaLocal(ingressos.local);
                  printf("A hora inicial e: %i\n",ingressos.horaIni);
                  printf("Digite a nova hora inicial...\n");
                  setbuf(stdin,NULL);
                  ingressos.horaIni = leValidaHorasIni();
                  printf("Os minuto inicial e: %i\n",ingressos.minIni);
                  printf("Digite o novo minuto inicial...\n");
                  ingressos.minIni = leValidaMinIni();
                  printf("A hora final e: %i\n",ingressos.horaFim);
                  printf("Digite a hora final...\n");
                  ingressos.horaFim = leValidaHorasFim();
                  printf("O minuto final e: %i\n",ingressos.minFim);
                  printf("Digite o minuto final...\n");
                  ingressos.minFim = leValidaMinFim();
                  printf("O valor do ingresso e: %0.2f\n",ingressos.valor);
                  printf("Digite o novo valor do ingresso...\n");
                  ingressos.valor = leValidaValor();
                  gravaIngAlt(arqIngressos,ingressos,posX);
                  printf("ALTERADO COM SUCESSO!!!!\n");
              }else{
                printf(ERRO);
              }


              
							
							break;
						case 4:
            system("cls||clear");
							printf("\n\n\n*** EXCLUIR INGRESSOS ***\n\n\n");

                   
                      printf("Digite aqui o codigo do ingresso: \n");
                      
                      setbuf(stdin,NULL);
                      fscanf(stdin, "%d", &ingressos.codigo);

                    posX = consultaCodShow(&ingressos,arqIngressos,ingressos.codigo);
                    if(posX > 0)
                    {   
                        setbuf(stdin,NULL);
                        ingressos=lerIngressos(posX, arqIngressos);
                        printf("Numero do codigo: %d\n",ingressos.codigo);printf("\n\n\n%d - %sLocal: %sInicio: %d:%d - Final: %d:%d\nValor: %.2f\n\n",ingressos.codigo, ingressos.banda, ingressos.local, ingressos.horaIni, ingressos.minIni, ingressos.horaFim, ingressos.minFim, ingressos.valor);
                        printf("Deseja remover o ingresso? (S ou N) \n");
                        setbuf(stdin,NULL); 
                        scanf("%c",&userKey);
                        userKey = toupper(userKey);
                        if(userKey=='S')
                        {
                          excluiIngresso(arqIngressos,posX);
                          excluirFisicamenteIngressos(&arqIngressos,"ingressos.csv");
                          printf("Ingresso excluido\n");
                        }
                    } else {
                      printf("Ingresso indisponivel\n");
                    }
                  setbuf(stdin,NULL);
                  allPause();

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
                  system("cls||clear");
										printf("\n\n\n*** USUARIOS ***\n\n\n");
                    listarUsuarios(arqCadastro);
                    setbuf(stdin,NULL);
										allPause();
										break;
									case 2:
                  system("cls||clear");
										printf("\n\n\n*** ADMINISTRACAO ***\n\n\n");
                    listarAdmin(arqAdministrador);
                    setbuf(stdin,NULL);
										allPause();
										break;
									case 3:
                  system("cls||clear");
										printf("\n\n\n*** ADICIONAR CONTA DE ADMINISTRADOR ***\n\n\n");
                    leValidaUsrName(admin.adminName);
					          leValidaUsrPassword(admin.adminPassword);
					          gravaDadosArquivoAdministrador(arqAdministrador,admin);
                    printf("CONTA CRIADA COM SUCESSO!!!\n");
                    setbuf(stdin,NULL);
										allPause();
										break;
									case 4:
                  system("cls||clear");
										printf("\n\n\n*** EXCLUIR CONTA DE ADMINISTRADOR ***\n\n\n");
                    printf("Digite aqui o nome do administrador(a)...\n");
                    do
                    {
                      printf("Digite aqui o nome do Adm para ser excluido: \n");
                      setbuf(stdin,NULL);
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
                      setbuf(stdin,NULL); //SE NÃO FOR EXECUTADO GERA ERRO NO CÓDIGO
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
                    setbuf(stdin,NULL);
                    allPause();
										break;
									
								}
							}while(opcaoSSMenuGerenciamento!=0);
							break;
              case 6:
              system("cls||clear");
              printf("\n\n*** CONSULTA ***\n\n");
              printf("Digite aqui o codigo do ingresso: ");
              scanf("%d", &buscaIngresso);
              posX = consultaCodShow(&ingressos,arqIngressos,buscaIngresso);
              if(posX > 0){
                       leituraIngresso(arqIngressos, buscaIngresso);
                       setbuf(stdin,NULL);
									  	allPause();
                        
                    } else {
                      printf("Codigo invalido, tente novamente...\n");
                      setbuf(stdin,NULL);
									  	allPause();
                    }
              break;
					}
				}while(opcaoSMenuAdm!=0);
				break;

		}
	}while(opcaoMenuLogin!=0);

	fclose(arqCadastro);
	fclose(arqAdministrador);
  fclose(arqCartaoUsuario);
  fclose(arqCarrinho);
	return 0;
}




