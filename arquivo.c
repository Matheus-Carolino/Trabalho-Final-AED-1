#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "receita.h"

    void carregarReceitas(ListaReceita *lr, char *nome){
        FILE *fp;
        //abro um novo arquivo em modo de leitura
        fp = fopen(nome, "r");
        if(!fp){
            printf("Erro ao abrir o arquivo!\n");
            return;
        }
        
        //pego a linha
        char linha[256];
        char nomeReceita[50], preparo[200], tipo [50];
        
        Receita *nova;
        
        while (fgets(linha, sizeof(linha), fp)){
            //removo o \n
            linha[strcspn(linha, "\n")] = 0;
            
            //pego os dados que correspondem a cada campo
            if(strncmp(linha, "Receita:", 8) == 0){
                //pulo "Receita: " e adiciono o resto da linha na variavel
                strcpy(nomeReceita, linha + 9);
            } else if (strncmp(linha, "Preparo:", 8) == 0){
                //pulo "Preparo: " e adiciono o resto da linha na variavel
                strcpy(preparo, linha + 9);
            } else if (strncmp(linha, "Tipo:", 5) == 0){
                //pulo "Tipo: " e adiciono o resto da linha na variavel
                strcpy(tipo, linha + 6);
            }
            else if (strncmp(linha, "Ingredientes:", 13) == 0){
                //crio nova receita com os campos informados
                nova = criarReceita(nomeReceita, preparo, tipo);
                //adiciono a receita na lista
                adicionarReceita(nova, lr);
                
                //percorro até a ultima receita da lista
                Receita *aux = lr->head;
                while (aux->prox != NULL){
                    aux = aux->prox;
                }
                
                //separa a lista de ingredientes a cada ";", assim eu pego cada ingrediente separado
                char *separador = strtok(linha + 13, ";");
                while (separador != NULL){
                    char nomeIngrediente[50];
                    int kcal;
                    
                    //pego o nome sem o caractere | e a kcal do ingrediente
                    sscanf(separador, "%49[^|]|%dKcal", nomeIngrediente, &kcal);
                    
                    //adiciono na receita 
                    adicionarIngredienteNaReceita(nomeReceita, nomeIngrediente, kcal, lr);
                    
                    //limpo o separador 
                    separador = strtok(NULL, ";");
                }
            }
        }
        //fecho o arquivo
        fclose(fp);
        printf("Receitas carregadas de %s\n", nome);
    }
    
    void salvarArquivo(ListaReceita *lr, char *nomeArquivo){
        //abro o arquivo no modo de escrita
        FILE *fp = fopen(nomeArquivo, "w");
        if (!fp){
            printf("Erro ao abrir arquivo %s\n", nomeArquivo);
            return;
        }
        Receita *aux = lr->head;
        // percorro a lista e escrevo cada receita no arquivo respeitando a formatação
        while (aux != NULL){
            fprintf(fp, "\nReceita: %s\n", aux->nome);
            fprintf(fp, "Preparo: %s\n", aux->preparo);
            fprintf(fp, "Tipo: %s\n", aux->tipo);
            //escrevo cada ingrediente da lista no arquivo respeitando a formataçao
            Ingrediente *temp = aux->ingredientes;
            fprintf(fp, "Ingredientes:");
            while (temp != NULL){
                fprintf(fp, "%s|%dKcal", temp->nome, temp->kcal);
                if(temp->prox != NULL){
                    fprintf(fp, ";");
                }
                temp = temp->prox;
            }
            aux = aux->prox;
        }
        //fecho o arquivo
        fclose(fp);
    }