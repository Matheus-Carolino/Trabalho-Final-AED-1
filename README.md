# Trabalho-Final-AED-1
Introdução: O tema abordado foi a lista de receitas sustentáveis, foi pedido uma lista duplamente encadeada de receitas que dentro dela irira uma lista duplamente encadeada de ingredientes.
Para resolver esse problema, comecei criande 3 structs (TAD's):
* 1 - struct de Ingredientes:
```
typedef struct Ingrediente{
      char nome[50];
      int kcal;
      struct Ingrediente *ant;
      struct Ingrediente *prox;
  } Ingrediente;
```
* 2 - struct de Receitas:
```
typedef struct Receita{
        char nome[50];
        char preparo[200];
        char tipo[50];
        Ingrediente *ingredientes;
        struct Receita *ant;
        struct Receita *prox;
} Receita;
```
* 3 - struct para a Lista de Receitas:
```
typedef struct{
    Receita *head;
} ListaReceita;
```
Tendo as structs prontas foi organizado o projeto conforme a imagem abaixo:

<img width="600" height="450" alt="AED-Projeto" src="https://github.com/user-attachments/assets/177964f7-9a28-40de-bcab-e41823594d4d" />

**Observação: Cadastrar Receita é a opção do menu que o usuário irá informar o (nome, preparo e tipo) da receita para inseri-la no arquivo, ela chama as funções (cadastrarReceita e criarReceita);

Documentação: Aqui deixo a explicação de como cada função foi utilizada.
### Funções Básicas:
* void carregarReceitas(ListaReceita *lista, char *nomeArquivo): essa função vai receber a lista de receitas, que está nula e ira cadastrar cada receita que está no arquivo cujo o nome foi informado, para isso ela irá chamar as funções (adicionarReceita e adicionarIngredienteNaReceita);
* void adicionarReceita(Receita *receita, ListaReceita *lista): essa função adiciona uma receita na lista de receitas, para isso ela chama a função (criarReceita);
* Receita criarReceita(char *nomeReceita, char *preparo, char *tipo): essa função é chamada quando uma nova receita for ser criada, ela recebe o nome, modo de preparo e tipo da receita e retorna a receita criada;
* void adicionarIngredienteNaReceita(char *nomeReceita, char *nomeIngrediente, int kcal, ListaReceita *lista): essa função é chamada toda vez que uma nova receita for adicionada, ela chama a função criarIngrediente;
* Ingrediente criarIngrediente(char *nomeIngrediente, int kcal): é chamada toda vez que um novo ingrediente for ser criado, recebe o nome e as kcal d eum ingrediente e retorna o ingrediente criado;
* void removerReceita(char *nomeReceita, ListaReceita *lista): essa função serve para remover uma receita da lista, para isso primeiro ela chama a função buscaReceita, se ela for encontrada então é removida da lista e o espaço de memória é desalocado;
* Receita buscaReceita(char *nomeReceita, ListaReceita *lista): quando essa função é chamada ela faz uma varredura na lista e retorna a receita que possui o campo nome igual ao nomeReceita;
* void listarReceita(ListaReceita *lista): essa função recebe a lista de receitas e imprime todas as receitas dentro dela, para imprimir a sublista de ingredientes ela chama a função listarIngrediente;
* void listarIngrediente(char *nomeReceita, ListaReceita *lista): recebe o nome da receita desejada e imprime todos os ingredientes dela, faz isso para todas as receitas da lista;
* void salvarArquivo(ListaReceita *lista, char *nomeArquivo): função extremamente importante, pois é ela que irá guardar a lista ao final das operações, sem isso o arquivo não seria atualizado conforme as operações do usuário.
### Funções Extras:
* void filtrarPorTipo(char *tipo, ListaReceita *lista): essa função retorna todas as receitas que possuam o tipo informado.
* void exibirMenorValorCalorico(ListaReceita *lista): essa função compara o valor calórico de cada receita da lista, valor esse que foi obtido pela função calcularKcal, e retorna o de menor valor;
* void exibirValorCalorico(char *nome, ListaReceita *lista): essa função recebe o nome da receita desejada e retorna o valor calórico dela obtido pela função calcularKcal;
* int calcularKcal(Receita *receita): essa função é chamada toda vez que deseja saber o valor calórico da receita, ela soma as kcal de todos os ingredientes da receita e retorna esse valor;

Exemplos de uso: Aqui deixo alguns exemplos de como as operações são feitas.
### arquivo.txt:
```
Receita: Salada de Quinoa Sustentável
Preparo: Cozinhe a quinoa e misture com legumes orgânicos picados
Tipo: Vegana
Ingredientes: Quinoa|120Kcal; Tomate Orgânico|20Kcal; Cenoura Orgânica|40Kcal; Azeite Extra Virgem|90Kcal 
```
### exemplo de código listarReceita(ListaReceita *lista):
```
void listarReceita(ListaReceita *lr){
    //head é a cabeça da lista (primeiro elemento)
    Receita *aux = lr->head;
    if(aux == NULL){
        printf ("A lista de receitas está vazia!\n");
        return;
    };
    
    printf ("Lista de receitas: \n");
    //percorro enquanto existir elementos na lista
    while (aux != NULL){
        printf("-> %s|%s:\n", aux->nome, aux->tipo);
        listarIngrediente(aux->nome, lr);
        printf("\tPreparo:\n");
        printf("\t %s\n", aux->preparo);
        aux = aux->prox;
    }
}
```
### saida de listarReceita(lista):
```
Lista de receitas: 
-> Salada de Quinoa Sustentável|Vegana:
        Ingredientes:
        . Quinoa|120Kcal
        . Tomate Orgânico|20Kcal
        . Cenoura Orgânica|40Kcal
        . Azeite Extra Virgem|90Kcal
        Preparo:
         Cozinhe a quinoa e misture com legumes orgânicos picados
```
### exemplo de código de exibirValorCalorico(char *nomeReceita, ListaReceita *lista):
```
void exibirValorCalorico(char *nome, ListaReceita *lr){
    //faço a busca pela receita informada
    Receita *aux = buscaReceita(nome, lr);
    
    if(aux == NULL){
        printf ("%s, não foi encontrada na lista de receitas!\n", nome);
        return;
    }
    //chamo a função que calcula o valor calórico
    int total = calcularKcal(aux);
    
    printf ("%s, possui: %dKcal\n", nome, total);
}
```
### exemplo exibirValorCalorico("Salada de Quinoa Sustentável", lista):
```
//entrada
Digite o nome da receita: Salada de Quinoa Sustentável
//saída
Salada de Quinoa Sustentável, possui: 270Kcal
```
Considerações finais: Acredito que esse projeto foi bem completo, pois contou com conceitos importantes como listas duplamente encadeadas, structs (TAD's), uso de arquivos para entrada de dados, esse último sendo a parte mais desafiadora na minha opinião, pois a lógica muda em relação a inserção manual das informações. As principais lições aprendidas foram a necessidade de uma boa organização de código (como modularização, identação correta e nomes claros e objetivos para funções e variáveis), descrição clara do fluxo de dados nas funções e nos elementos das lista (quando percorremos anterior e próximo) e manipulação de strings com ajuda da biblioteca <string.h>.
