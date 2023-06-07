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
