//trabalho final, Matheus da Silva Carolino

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "receita.h"

int main()
{
	ListaReceita *lr;
	lr = (ListaReceita *)malloc(sizeof(ListaReceita));

	iniciarLista(lr);

	int opcao;
	char *nomeArquivo = "arquivo.txt";

	do {
		printf("\n|-------------MENU-------------|\n");
		printf("1. Carregar receitas do arquivo\n");
		printf("2. Listar receitas\n");
		printf("3. Filtrar por tipo\n");
		printf("4. Exibir menor valor calórico\n");
        printf("5. Pesquisar valor calórico\n");
        printf("6. Remover receitas\n");
        printf("7. Cadastrar receitas\n");
		printf("0. EXIT\n");
		printf("=> ");
		scanf("%d", &opcao);
		getchar();

		switch(opcao) {
		case 1:
		    //alimenta a lista com o arquivo
			carregarReceitas(lr, nomeArquivo);
			break;
		case 2:
			listarReceita(lr);
			break;
		case 3:
			char tipoBuscar[50];
			printf("Digite o tipo: ");
			scanf("%s", tipoBuscar);
			//retorna as receitas do tipo informado
			filtrarPorTipo(tipoBuscar, lr);
			break;
		case 4:
			exibirMenorValorCalorico(lr);
			break;
		case 5:
			char nomeCalorico[50];
			printf("Digite o nome da receita: ");
			fgets(nomeCalorico, sizeof(nomeCalorico), stdin);
			//removo o \n da string
			nomeCalorico[strcspn(nomeCalorico, "\n")] = 0;
			//retorna o valor calorico da receita informada
			exibirValorCalorico(nomeCalorico,lr);
			break;
		case 6:
            char nomeRemove[50];
            printf("Digite o nome da receita: ");
            fgets(nomeRemove, sizeof(nomeRemove), stdin);
            //removo o \n da string
            nomeRemove[strcspn(nomeRemove, "\n")] = 0;
			
			//removo a receita da lista carregada na memoria, ainda tenho que atualizar o arquivo para remove-la
			removerReceita(nomeRemove, lr);
			break;
        case 7:
            char nomeReceita[50], preparo[200], tipo[50];
            printf("Digite o nome da receita: ");
            fgets(nomeReceita, sizeof(nomeReceita), stdin);
            //removo o \n da string
            nomeReceita[strcspn(nomeReceita, "\n")] = 0;
            
            printf("Digite o preparo da receita: ");
            fgets(preparo, sizeof(preparo), stdin);
            //removo o \n da string
            preparo[strcspn(preparo, "\n")] = 0;
            
            printf("Digite o tipo da receita: ");
            fgets(tipo, sizeof(tipo), stdin);
            //removo o \n da string
            tipo[strcspn(tipo, "\n")] = 0;
            
            //crio uma receita com os campos informados
            Receita *nova = criarReceita(nomeReceita, preparo, tipo);
            //adiciono ela na lista
            adicionarReceita(nova, lr);
            
            int num = 0;
            printf("Digite o número de ingredientes:");
            scanf("%d", &num);
            
            char nomeIngrediente[50]; 
            int kcal;
            
            //adiciono os ingredientes da receita recem criada
            for(int i = 0; i < num; i++){
                setbuf(stdin, NULL);
                printf("Digite o nome do ingrediente(%d): ", i + 1);
                fgets(nomeIngrediente, sizeof(nomeIngrediente), stdin);
                //removo o \n da string
                nomeIngrediente[strcspn(nomeIngrediente, "\n")] = 0;
                
                printf("Digite as Kcal do ingrediente(%d): ", i + 1);
                scanf("%d", &kcal);
                
                adicionarIngredienteNaReceita(nova->nome, nomeIngrediente, kcal, lr);
            }
            break;
		}
		
	} while (opcao != 0);
	
	//salvo a lista carregada na memoria no arquivo
	salvarArquivo(lr, nomeArquivo);

	return 0;
}