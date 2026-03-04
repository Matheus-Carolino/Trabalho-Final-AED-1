#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "receita.h"

    void carregarReceitas(ListaReceita *lr, char *nome){
        FILE *fp;
        
        fp = fopen(nome, "r");
        if(!fp){
            printf("Erro ao abrir o arquivo!\n");
            return;
        }
        
        char linha[256];
        char nomeReceita[50], preparo[200], tipo [50];
        
        Receita *nova;
        
        while (fgets(linha, sizeof(linha), fp)){
            linha[strcspn(linha, "\n")] = 0;
            
            if(strncmp(linha, "Receita:", 8) == 0){
                strcpy(nomeReceita, linha + 9);
            } else if (strncmp(linha, "Preparo:", 8) == 0){
                strcpy(preparo, linha + 9);
            } else if (strncmp(linha, "Tipo:", 5) == 0){
                strcpy(tipo, linha + 6);
            }
            else if (strncmp(linha, "Ingredientes:", 13) == 0){
                nova = criarReceita(nomeReceita, preparo, tipo);
                adicionarReceita(nova, lr);
                
                Receita *aux = lr->head;
                while (aux->prox != NULL){
                    aux = aux->prox;
                }
                
                char *separador = strtok(linha + 13, ";");
                while (separador != NULL){
                    char nomeIngrediente[50];
                    int kcal;
                    
                    sscanf(separador, "%49[^|]|%dKcal", nomeIngrediente, &kcal);
                    
                    adicionarIngredienteNaReceita(nomeReceita, nomeIngrediente, kcal, lr);
                    
                    separador = strtok(NULL, ";");
                }
            }
        }
        fclose(fp);
        printf("Receitas carregadas de %s\n", nome);
    }
    
    void salvarArquivo(ListaReceita *lr, char *nomeArquivo){
        FILE *fp = fopen(nomeArquivo, "w");
        if (!fp){
            printf("Erro ao abrir arquivo %s\n", nomeArquivo);
            return;
        }
        Receita *aux = lr->head;
        
        while (aux != NULL){
            fprintf(fp, "Receita: %s\n", aux->nome);
            fprintf(fp, "Preparo: %s\n", aux->preparo);
            fprintf(fp, "Tipo: %s\n", aux->tipo);
            
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
        
        fclose(fp);
    }