#ifndef RECEITA_H
#define RECEITA_H
    typedef struct Ingrediente{
        char nome[50];
        int kcal;
        struct Ingrediente *ant;
        struct Ingrediente *prox;
    } Ingrediente;
    
    typedef struct Receita{
        char nome[50];
        char preparo[200];
        char tipo[50];
        Ingrediente *ingredientes;
        struct Receita *ant;
        struct Receita *prox;
    } Receita;
    
    typedef struct{
        Receita *head;
    } ListaReceita;
    
    void iniciarLista(ListaReceita *lr);    
    
    void carregarReceitas(ListaReceita *lr, char *nome);
    void salvarArquivo(ListaReceita *lr, char *nomeArquivo);
    
    Receita *criarReceita(char *nome, char *preparo, char *tipo);
    Receita *buscaReceita(char *nome, ListaReceita *lr);
    
    void adicionarReceita(Receita *receita, ListaReceita *lr);
    void removerReceita(char *nomeReceita, ListaReceita*lr);
    void listarReceita(ListaReceita *lr);
    
    void filtrarPorTipo(char *tipo, ListaReceita *lr);
    void exibirMenorValorCalorico(ListaReceita *lr);
    
    Ingrediente *criarIngrediente(char *nome, int kcal);
    void adicionarIngredienteNaReceita(char *nomeReceita, char *nomeIngrediente, int kcal, ListaReceita *lr);
    void listarIngrediente(char *nomeReceita, ListaReceita *lr);
    void filtrarPorIngrediente(char *nome, ListaReceita *lr);
     
    void exibirValorCalorico(char *nome, ListaReceita *lr);
    int calcularKcal(Receita *receita);
    
#endif