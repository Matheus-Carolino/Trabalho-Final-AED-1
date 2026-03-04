#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "receita.h"

    Ingrediente *criarIngrediente(char *nome, int kcal){
        Ingrediente *novo;
        novo = (Ingrediente *)malloc(sizeof(Ingrediente));
        
        strcpy (novo->nome, nome);
        novo->kcal = kcal;
        novo->ant = NULL;
        novo->prox = NULL;
        
        return novo;
    }
    
    void adicionarIngredienteNaReceita(char *nomeReceita, char *nomeIngrediente, int kcal, ListaReceita *lr){
        Receita *aux = buscaReceita(nomeReceita, lr);
        
        if(aux == NULL){
            printf("%s, não foi encontrada na lista de receitas!\n", nomeReceita);
            return;
        }
        
        Ingrediente *novo = criarIngrediente(nomeIngrediente, kcal);
        if(aux->ingredientes == NULL){
            aux->ingredientes = novo;
        } else {
            Ingrediente *temp = aux->ingredientes;
            while (temp->prox != NULL){
                temp = temp->prox;
            }
            
            temp->prox = novo;
            novo->ant = temp;
        }
        
        printf("%s, foi adicionado a %s\n", nomeIngrediente, nomeReceita);
    }
    
    void filtrarPorIngrediente(char *nome, ListaReceita *lr){
        Receita *aux = lr->head;
        
        if(aux == NULL){
            printf ("A lista de receitas está vazia!\n");
            return;
        }
        
        printf ("Receitas com o ingrediente (%s):\n", nome);
        Ingrediente *temp = aux->ingredientes;
        
        while(aux != NULL){
            if(temp == NULL){
                aux = aux->prox;
                if(aux != NULL){
                    temp = aux->ingredientes;   
                } else {
                    printf ("-> Nenhum!\n");
                    return;
                }
            }
            if(strcmp(temp->nome, nome) == 0){
                printf("-> %s\n", aux->nome);
            }
            temp = temp->prox;
        }
    }
    
    void listarIngrediente(char *nomeReceita, ListaReceita *lr){
        Receita *aux = buscaReceita(nomeReceita, lr);
        
        if(aux == NULL){
            printf("%s, não foi encontrada na lista de receitas!\n", nomeReceita);
            return;
        }
        
        Ingrediente *temp = aux->ingredientes;
        if(temp == NULL){
            printf("%s, não tem ingredientes cadastrados!\n", nomeReceita);
            return;
        }

        printf("\tIngredientes:\n");
        while(temp != NULL){
            printf("\t.%s|%dKcal\n", temp->nome, temp->kcal);
            temp = temp->prox;
        }
    }