#ifndef LISTA_LIGADA_H
#define LISTA_LIGADA_H

//Estrutura da lista
typedef struct{
	int tipo;
	double tempo;
	struct lista * proximo;
} lista;

// Fun��o que remove o primeiro elemento da lista
lista * remover (lista * apontador);

// Fun��o que adiciona novo elemento � lista, ordenando a mesma por tempo
lista * adicionar (lista * apontador, int n_tipo, double n_tempo);

// Fun��o que imprime no ecra todos os elementos da lista
void imprimir (lista * apontador);


#endif