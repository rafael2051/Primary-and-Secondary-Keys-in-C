#include <stdio.h>
#include <stdlib.h>


#define TAM 1000

typedef struct {
	int nroUSP;
	int curso;
	int estado;
	int idade;
	bool valido;
} REGISTRO;


typedef struct {
	int chave;
	int end;
} TABELA_P;//tabela primaria

typedef struct no {
	int valor;//valor da chave primaria desse no
	struct no * prox;
} NO;


typedef struct {
	int chave_secundaria;
	NO * chave_primaria;//uma lista ligada com todas as
			     //chaves primarias associadas a esta
			     //chave secundaria
} TABELA_S;//tabela secundaria

int inserirIndicePrimario(TABELA_P * table, int chave, int end){
	table[i].chave = chave;
	table[i].end = end;
	bubbleSortTabbleP(TABELA_P * table, int end);
}




int buscarEndereco(TABELA_P * table, int chave){
	for(int i = 0;i < TAM;i++){
		if(table[i].chave == chave)
			return table[i].end;
	}
	return -1;
}

int excluirIndicePrimario(TABELA_P * table, int chave){
	for(int i =0; i < TAM;i++){
		if(table[i].chave == chave){
			int end  table[i].end;
			excluiChave(table, i);
			return end;
			
		}
	}
}


int buscaIndiceSecundario(TABELA_S * table, int chave_s){
	for(int i = 0;i < TAM;i++){
		if(table[i].chave_secundaria == chave_s){
			return i;
		}
	}
	return -1;
}



void removeChave(TABELA_S * table_s, int indice, int chave_p){
	
	NO * p = table_s[indice].chave_primaria;
	if(p->valor == chave_p){
		table_s[indice].chave_primaria = p->prox;
		p->prox = NULL;
		free(p);
	}
	NO * ant;
	ant = NULL;
	while(p->prox){
		ant = p;
		p = p->prox;
		if(p->valor == chave_p){
			ant->prox = p->prox;
			p->prox = NULL;
			free(p);
		}
	}
	
}

void insereChave(TABELA_S * table_s, int indice, int chave_p){
	NO * novo = (NO *)malloc(sizeof(NO));
	novo->valor = chave_p;
	novo->prox = table_s[indice].chave_primaria;
	table_s[indice].chave_primaria = novo;
	return;
}



void alteraRegistro(FILE * f, TABELA_P * table_p, TABELA_S * table_s, int nroUSPX, int cursoY){

	int end = buscarEndereco(table_p, nroUSPX);
	int curso_antigo;
	if(end < 0) return;
	REGISTRO aux;
	fseek(f, end * sizeof(REGISTRO), SEEK_SET);
	fread(&aux, sizeof(REGISTRO), 1, f);
	if(aux.curso != cursoY){
		curso_antigo = aux.curso;
		aux.curso = cursoY;
		fseek(f, -sizeof(REGISTRO), SEEK_CUR);
		fwrite(aux, sizeof(REGISTRO), 1, f);
		int indice = buscaIndiceSecundario(table_s, curso_antigo);
		removeChave(table_s, indice, nroUSPX);
		indice = buscaIndiceSecundario(table_s, cursoY);
		insereChave(table_s, indice, nroUSPX);
		
	}
}
