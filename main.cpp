#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char CHAVE[] = "AbCd";
char TEXTO[100000];
int TAM_CHAVE=strlen(CHAVE);
int TAM_TEXTO=100000;
int TEXTO_CRIPT[100000];

bool Criptografar(){
	int CHAVE_int;
	for(int i=0; i < strlen(TEXTO) ; i++){
		TEXTO_CRIPT[i]=TEXTO[i];
	}
	for (int aux=0; aux < strlen(TEXTO) ; ){
		for(int i=0;i<TAM_CHAVE;i++){
			CHAVE_int = CHAVE[i];
			TEXTO_CRIPT[aux] = TEXTO_CRIPT[aux] * CHAVE_int;
			aux++;
		}
	}
	return true;
}

bool Descriptografar(){
	
	int valor;
	int p_chave;
	int p_texto;
	
	FILE * arquivo;
	
	arquivo = fopen("c:\\cript\\arquivos_recebidos\\criptografado.txt","r");
	
	if(arquivo==NULL){
		return false;
	}
	
	
	p_chave=0;
	p_texto=0;
	
	while(!feof(arquivo)){
		fscanf(arquivo,"%d", &valor);
		
		valor /= CHAVE[p_chave];
		
		TEXTO[p_texto] = (char)valor;
		
		p_texto++;
		
		if(p_chave==TAM_CHAVE-1){
			p_chave=0;
		}else{
			p_chave++;
		}
	}
	
	fclose(arquivo);
	return true;
	
}


void Recebe_texto(char tipo[]){
	char aux[TAM_TEXTO];
	char pause;
	bool ok;
	
	FILE *arquivo;
	char palavra[100];
		
	if(strcmp(tipo,"msg")==0){
		printf("\n\tReceber texto para Criptografar");
		printf("\n\nDigite o texto: ");
		gets(aux);
		if(strlen(aux) <= TAM_TEXTO){
			strcpy(TEXTO,aux);
			printf("\nTexto Recebido com sucesso!");
			printf("\n\nCriptografando texto...\n\n");
			
			ok=true;	
		}else{
			printf("\n\nErro!!\nO tamanho do texto e muito grande.\n\n");
			ok=false;
			system("pause");
		}
	 	
	}else if(strcmp(tipo,"arquivo")==0){
		printf("\n\nIntrucoes para importar um arquivo de texto:\n\n");
		printf("\n\n 1 - Renomeie o arquivo para 'original.txt'");
		printf("\n\n 2 - Copie o arquivo para a pasta que sera aberta a seguir.");
		printf("\n\n 3 - Feche a pasta e retorne a aplicacao");
		
		printf("\n\n\n Pressione ENTER apos colar o arquivo na pasta...\n");
		scanf("%c", &pause);
		setbuf(stdin,NULL);
		system("explorer c:\\cript\\arquivos_originais\\");
		printf("\n\nImportando arquivo...\n\n");
		
		arquivo = fopen("c:\\cript\\arquivos_originais\\original.txt","r");
		if(arquivo==NULL){
			printf("\n\nErro ao abrir o arquivo!!");
		}else{
			while(!feof(arquivo)){
                fscanf(arquivo,"%s",palavra);
                strcat(aux," ");
                strcat(aux,palavra);
            }
			fclose(arquivo);
            if( strlen(aux) <= TAM_TEXTO){
                strcpy(TEXTO,aux);
                printf("\n\nTexto recebido com sucesso!");
                printf("\n\nCriptografando texto...\n\n");

                ok=true;
            }else{
                printf("\n\nErro!\nO texto e muito grande!!\n\n");
                ok=false;
            	system("pause");
            }
        }
    }else{
        printf("\n\nErro ao receber texto\n\n");
    }
    if(ok){
        if(Criptografar()){
            printf("\n\nTexto criptografado com sucesso!");

            arquivo = fopen("c:\\cript\\arquivos_gerados\\criptografado.txt","wt");
            if(arquivo==NULL){
                printf("\n\nErro ao criar o arquivo...\n\n");
            }else{
                for(int i=0; i < strlen(TEXTO); i++){
                    fprintf(arquivo,"%d ",TEXTO_CRIPT[i]);
                }
            }
            fclose(arquivo);

            printf("\n\nPressione ENTER para abrir a pasta do arquivo gerado!\n");
            scanf("%c",&pause);
            setbuf(stdin,NULL);
            system("explorer c:\\cript\\arquivos_gerados\\");
        }else{
            printf("\n\nNao foi possivel criptografar o texto!\n\n");
        }

    }
}


void Receber_Arquivo_cript(){
	char pause;
	printf("\n\nInstrucoes para importar um arquivo criptografado:");
    printf("\n\n 1 - Renomeie o arquivo para 'criptografado.txt'");
    printf("\n\n 2 - Copie o arquivo para a pasta que sera aberta a seguir");
    printf("\n\n 3 - Feche o explorador e retorne a aplicacao");
    
	printf("\n\n\n Pressione ENTER para abrir a pasta");
    scanf("%c",&pause);
    setbuf(stdin,NULL);
    
	system("explorer c:\\cript\\arquivos_recebidos\\");
    printf("\n\nPressione ENTER apos colar o arquivo na pasta...\n");
    scanf("%c",&pause);
    setbuf(stdin,NULL);

    
    printf("\n\nImportando arquivo...\n\n");
    
    if(Descriptografar()){
    	printf("\n Arquivo Descriptografado com sucesso!\n\n");
    	system("pause");
    	system("cls");
    	printf("\n%s\n\n",TEXTO);
    	system("pause");
	}else{
		printf("\n Nao foi possivel Descriptografar o arquivo!\n\n");
    	system("pause");
	}
    

}

void Menu_Criptografar(){
	int opcao;
	printf("\n\tCriptografia de dados");
	printf("\n\nCriptografar mensagem ou arquivo");
	printf("\n\n 1 - Digitar Mensagem");
	printf("\n\n 2 - Importar arquivo de texto (txt)");
	printf("\n\n 3 - Voltar ao menu principal");
	printf("\n\n Informe a opcao desejada:");
	scanf("%d", &opcao);
	setbuf(stdin,NULL);
	switch(opcao){
		case 1:
			system("cls");
			Recebe_texto("msg");
			break;
		case 2:
			system("cls");
			Recebe_texto("arquivo");
			break;
		case 3:
			break;
		
		default:
			printf("Opcao Invalida!! Tente novamente...");
	}
	
}

void Menu(){
	int opcao;
	while(1){
		system("cls");
		printf("\n\tCriptografia de dados");
		printf("\n\n 1 - Criptografar Mensagem");
		printf("\n\n 2 - Receber arquivo");
		printf("\n\n 3 - Sair");
		printf("\n\n Informe a opcao desejada:");
		scanf("%d", &opcao);
		setbuf(stdin, NULL);
		switch(opcao){
			case 1:
				system("cls");
				Menu_Criptografar();
				break;
			
			case 2:
				system("cls");
				Receber_Arquivo_cript();
				break;
			case 3:
				printf("\nFinalizando...\n\n");
				system("pause");
				exit(0);
				break;
			default:
				printf("Opcao invalida!! Tente novamente...");
		}
	}
}
int main(){
	
	Menu();
	
	return 0;
}
