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
			carregarReceitas(lr, nomeArquivo);
			break;
		case 2:
			listarReceita(lr);
			break;
		case 3:
			char tipoBuscar[50];
			printf("Digite o tipo: ");
			scanf("%s", tipoBuscar);
			filtrarPorTipo(tipoBuscar, lr);
			break;
		case 4:
			exibirMenorValorCalorico(lr);
			break;
		case 5:
			char nomeCalorico[50];
			printf("Digite o nome da receita: ");
			fgets(nomeCalorico, sizeof(nomeCalorico), stdin);
			nomeCalorico[strcspn(nomeCalorico, "\n")] = 0;
			exibirValorCalorico(nomeCalorico,lr);
			break;
		case 6:
            char nomeRemove[50];
            printf("Digite o nome da receita: ");
            fgets(nomeRemove, sizeof(nomeRemove), stdin);
            nomeRemove[strcspn(nomeRemove, "\n")] = 0;
			
			removerReceita(nomeRemove, lr);
			break;
        case 7:
            char nomeReceita[50], preparo[200], tipo[50];
            printf("Digite o nome da receita: ");
            fgets(nomeReceita, sizeof(nomeReceita), stdin);
            nomeReceita[strcspn(nomeReceita, "\n")] = 0;
            
            printf("Digite o preparo da receita: ");
            fgets(preparo, sizeof(preparo), stdin);
            preparo[strcspn(preparo, "\n")] = 0;
            
            printf("Digite o tipo da receita: ");
            fgets(tipo, sizeof(tipo), stdin);
            tipo[strcspn(tipo, "\n")] = 0;
            
            Receita *nova = criarReceita(nomeReceita, preparo, tipo);
            adicionarReceita(nova, lr);
            
            int num = 0;
            printf("Digite o número de ingredientes:");
            scanf("%d", &num);
            
            char nomeIngrediente[50]; 
            int kcal;
            for(int i = 0; i < num; i++){
                setbuf(stdin, NULL);
                printf("Digite o nome do ingrediente(%d): ", i + 1);
                fgets(nomeIngrediente, sizeof(nomeIngrediente), stdin);
                nomeIngrediente[strcspn(nomeIngrediente, "\n")] = 0;
                
                printf("Digite as Kcal do ingrediente(%d): ", i + 1);
                scanf("%d", &kcal);
                
                adicionarIngredienteNaReceita(nova->nome, nomeIngrediente, kcal, lr);
            }
            break;
		}
	} while (opcao != 0);
	
	salvarArquivo(lr, nomeArquivo);

	return 0;
}