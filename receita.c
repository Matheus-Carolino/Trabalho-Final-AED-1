#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "receita.h"
    
    void iniciarLista(ListaReceita *lr){
        lr->head = NULL;
    }
    
    Receita *criarReceita(char *nome, char *preparo, char *tipo){
        Receita *nova;
        nova = (Receita *)malloc(sizeof(Receita));
        
        strcpy (nova->nome, nome);
        strcpy (nova->preparo, preparo);
        strcpy (nova->tipo, tipo);
        nova->ingredientes = NULL;
        nova->ant = NULL;
        nova->prox = NULL;
        
        return nova;
    }
    
    Receita *buscaReceita(char *nome, ListaReceita *lr){
        Receita *aux = lr->head;
        
        while(aux != NULL && strcmp (aux->nome, nome) != 0){
            aux = aux->prox;
        }
        
        return aux;
    }
    
    void adicionarReceita(Receita *receita, ListaReceita *lr){
        
        if(lr->head == NULL){
            lr->head = receita;
        } else {
            Receita *aux = lr->head;
            
            while(aux->prox != NULL){
                aux = aux->prox;
            }
            
            aux->prox = receita;
            receita->ant = aux;
        }
        
        printf ("%s, foi adicionada a lista de receitas!\n", receita->nome);
    }
    
    void removerReceita(char *nome, ListaReceita *lr){
        Receita *aux = buscaReceita(nome, lr);
        
        if(aux == NULL){
            printf("%s, não foi encontrada na lista de receitas!\n", nome);
            return;
        }
        
        if(aux == lr->head){
            lr->head = aux->prox;
        } else {
            aux->ant->prox = aux->prox;
            if(aux->prox != NULL){
                aux->prox->ant = aux->ant;
            }
        }
        
        free(aux);
        printf("%s, foi removida da lista de receitas!\n", nome);
    }
    
    void listarReceita(ListaReceita *lr){
        Receita *aux = lr->head;
        if(aux == NULL){
            printf ("A lista de receitas está vazia!\n");
            return;
        };
        
        printf ("Lista de receitas: \n");
        while (aux != NULL){
            printf("-> %s|%s:\n", aux->nome, aux->tipo);
            listarIngrediente(aux->nome, lr);
            printf("\tPreparo:\n");
            printf("\t %s\n", aux->preparo);
            aux = aux->prox;
        }
    }
    
    void filtrarPorTipo(char *tipo, ListaReceita *lr){
        Receita *aux = lr->head;
        if(aux == NULL){
            printf("A lista de receitas está vazia!\n");
            return;
        }
        
        printf ("Receitas do tipo %s:\n", tipo);
        while(aux != NULL){
            if(strcmp(aux->tipo, tipo) == 0){
                printf("-> %s\n", aux->nome);
            }
            aux = aux->prox;
        }
    }
    
    void exibirMenorValorCalorico(ListaReceita *lr){
        Receita *aux = lr->head;
        if(aux == NULL){
            printf("A lista de receitas está vazia!\n");
            return;
        }
        
        char *nomeMenor = aux->nome;
        int menor = calcularKcal(aux);
        while(aux != NULL){
            int temp = calcularKcal(aux);
            if(temp < menor){
                char *nomeMenor = aux->nome;
                menor = temp;
            }
            aux = aux->prox;
        }
        
        printf("%s, possui o menor valor calórico: %dKcal\n", nomeMenor, menor);
    }
    
    void exibirValorCalorico(char *nome, ListaReceita *lr){
        Receita *aux = buscaReceita(nome, lr);
        
        if(aux == NULL){
            printf ("%s, não foi encontrada na lista de receitas!\n", nome);
            return;
        }
        
        int total = calcularKcal(aux);
        
        printf ("%s, possui: %dKcal\n", nome, total);
    }
    
    int calcularKcal(Receita *receita){
        Ingrediente *temp = receita->ingredientes;
        if(receita == NULL || temp == NULL){
            return 0;
        }
        
        int total = 0;
        while(temp != NULL){
            total += temp->kcal;
            temp = temp->prox;
        }
        return total;
    }
    
    
    
    