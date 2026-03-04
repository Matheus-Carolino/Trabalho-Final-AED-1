#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "receita.h"
    
    //inicio a lista vazia
    void iniciarLista(ListaReceita *lr){
        lr->head = NULL;
    }
    
    //retorno uma nova receita
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
    
    //faço a busca da receita na lista comparando com um nome informado
    Receita *buscaReceita(char *nome, ListaReceita *lr){
        //recebe a cabeça da lista
        Receita *aux = lr->head;
        
        //strcmp da biblioteca <string.h>
        while(aux != NULL && strcmp (aux->nome, nome) != 0){
            aux = aux->prox;
        }
        
        return aux;
    }
    
    void adicionarReceita(Receita *receita, ListaReceita *lr){
        //se a lista for vazia so incere na cabeça
        if(lr->head == NULL){
            lr->head = receita;
        } else {
            Receita *aux = lr->head;
            
            //percorre ate o ultimo elemento 
            while(aux->prox != NULL){
                aux = aux->prox;
            }
            
            //faço a ligaçao para inserir no final
            aux->prox = receita;
            receita->ant = aux;
        }
        
        printf ("%s, foi adicionada a lista de receitas!\n", receita->nome);
    }
    
    void removerReceita(char *nome, ListaReceita *lr){
        //chamo a função de busca
        Receita *aux = buscaReceita(nome, lr);
        
        //se nula retorna uma msg
        if(aux == NULL){
            printf("%s, não foi encontrada na lista de receitas!\n", nome);
            return;
        }
        
        //faço a remoçao 
        if(aux == lr->head){
            lr->head = aux->prox;
        } else {
            aux->ant->prox = aux->prox;
            if(aux->prox != NULL){
                aux->prox->ant = aux->ant;
            }
        }
        
        //libero o espaço de memoria
        free(aux);
        printf("%s, foi removida da lista de receitas!\n", nome);
    }
    
    void listarReceita(ListaReceita *lr){
        Receita *aux = lr->head;
        //verifica se a lista é vazia
        if(aux == NULL){
            printf ("A lista de receitas está vazia!\n");
            return;
        };
        
        //percorro e imprimo cada receita da lista
        printf ("Lista de receitas: \n");
        while (aux != NULL){
            printf("-> %s|%s:\n", aux->nome, aux->tipo);
            //chamo a função para imprimir a sublista ingredientes
            listarIngrediente(aux->nome, lr);
            printf("\tPreparo:\n");
            printf("\t %s\n", aux->preparo);
            aux = aux->prox;
        }
    }
    
    void filtrarPorTipo(char *tipo, ListaReceita *lr){
        Receita *aux = lr->head;
        //verifica se a lista é vazia
        if(aux == NULL){
            printf("A lista de receitas está vazia!\n");
            return;
        }
        
        //percorro e imprimo as listas que possui o tipo informado
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
        //verifica se a lista é vazia
        if(aux == NULL){
            printf("A lista de receitas está vazia!\n");
            return;
        }
        
        //assumo o menor valor sendo o inicial e guardo o nome receita
        char *nomeMenor = aux->nome;
        int menor = calcularKcal(aux);
        
        //percorro a lista e verifico se é o menor, caso seja substituo o menor e nomeMenor antigos
        while(aux != NULL){
            int temp = calcularKcal(aux);
            if(temp < menor){
                char *nomeMenor = aux->nome;
                menor = temp;
            }
            aux = aux->prox;
        }
        
        //imprimo o menor e o nomeMenor
        printf("%s, possui o menor valor calórico: %dKcal\n", nomeMenor, menor);
    }
    
    void exibirValorCalorico(char *nome, ListaReceita *lr){
        //busco a receita na lista
        Receita *aux = buscaReceita(nome, lr);
        
        //se nula retorno a msg
        if(aux == NULL){
            printf ("%s, não foi encontrada na lista de receitas!\n", nome);
            return;
        }
        
        //chamo a função que calcula as kcal
        int total = calcularKcal(aux);
        
        //imprimo o nome mais o total
        printf ("%s, possui: %dKcal\n", nome, total);
    }
    
    int calcularKcal(Receita *receita){
        //variavel temporaria para percorrer a sublista ingredientes
        Ingrediente *temp = receita->ingredientes;
        //se a receita for nula ou não tiver ingredientes retorno 0
        if(receita == NULL || temp == NULL){
            return 0;
        }
        
        int total = 0;
        //uso um acumulador para somar as kcal de cada ingrediente
        while(temp != NULL){
            total += temp->kcal;
            temp = temp->prox;
        }
        return total;
    }
    
    
    
    