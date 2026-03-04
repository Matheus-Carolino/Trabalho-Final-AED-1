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
        //busco a receita informada
        Receita *aux = buscaReceita(nomeReceita, lr);
        
        //se nula retorno a msg
        if(aux == NULL){
            printf("%s, não foi encontrada na lista de receitas!\n", nomeReceita);
            return;
        }
        
        //chamo a função que cria ingredientes
        Ingrediente *novo = criarIngrediente(nomeIngrediente, kcal);
        //se a lista for vazia so insiro o ingrediente novo
        if(aux->ingredientes == NULL){
            aux->ingredientes = novo;
        } else {
            //se não eu adiciono o novo ingrediente no final da lista
            Ingrediente *temp = aux->ingredientes;
            while (temp->prox != NULL){
                temp = temp->prox;
            }
            
            temp->prox = novo;
            novo->ant = temp;
        }
        
        printf("%s, foi adicionado a %s\n", nomeIngrediente, nomeReceita);
    }
    
    void listarIngrediente(char *nomeReceita, ListaReceita *lr){
        //busco a receita informada
        Receita *aux = buscaReceita(nomeReceita, lr);
        
        //se nula retorno a msg
        if(aux == NULL){
            printf("%s, não foi encontrada na lista de receitas!\n", nomeReceita);
            return;
        }
        
        //pego os ingredientes da receita 
        Ingrediente *temp = aux->ingredientes;
        //se nula retorno a msg
        if(temp == NULL){
            printf("%s, não tem ingredientes cadastrados!\n", nomeReceita);
            return;
        }
        //percorro e imprimo
        printf("\tIngredientes:\n");
        while(temp != NULL){
            printf("\t.%s|%dKcal\n", temp->nome, temp->kcal);
            temp = temp->prox;
        }
    }