#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int chave;
	int info;
} no_sem_ponteiro;

typedef struct no {

	int chave;
	int info;
	struct no * prox;
} NO;

NO * leListaBIN(FILE * f){
	NO * lista;
	lista = NULL;
	no_sem_ponteiro aux;
	while(1 == fread(&aux, sizeof(no_sem_ponteiro), 1, f)){
		NO * novo = (NO *) malloc(sizeof(NO));
		novo->chave = aux.chave;
		novo->info = aux.info;
		novo->prox = lista;
		lista = novo;
		
	}
	return lista;
}

NO * leListaTXT(FILE * f){
	
	NO * lista;
	lista = NULL;
	while(!feof(f)){
		NO * novo = (NO *) malloc(sizeof(NO));
		fscanf(f, "%i\\", &ano->chave);
		fscanf(f, "%i\\", &ano->info);
		novo->prox = lista;
		lista = novo;
	}
	return lista;

FILE * criaTXT(FILE * f){

	FILE * novo = fopen("arq.txt", "w");
	rewind(f);
	no_sem_ponteiro aux;
	while(1 == fread(&aux, sizeof(no_sem_ponteiro), 1, f)){
		
		fprintf("%d\\", aux.chave);
		fprintf("%d\n", aux.info);
	}
}

int main(){



	FILE * f = fopen("arq.bin", wr);
	NO * lista = leLista(f);
}
