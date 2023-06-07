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


void alteraTabelaSecundaria(TABELA_S table_s, int chave_velha, int chave_nova, int indice, bool * teste){

	NO * p = table_s[indice].chave_prima;
	while(p){
		if(p->valor == chave_velha){
			p->valor = chave_nova;
			*teste = true;
			
			return;
		}
	}
	*teste = false;	
}


//ex 6
void alteraRegistroCurso(FILE * f, TABELA_P * table_p, TABELA_S * table_s, int nroUSPX, int cursoY){

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
		indice = buscaIndiceSecundario(table_, cursoY);
		insereChave(table_s, indice, nroUSPX);
		
	}
}

//ex 7
void alteraRegistroAluno(FILE * f, TABELA_P * table_aluno, TABELA_S * table_curso, TABELA_S * table_estado, int nroUSPX, int nroUSPY){

	int end = buscarEndereco(table_p, nroUSPX);
	if(end < 0) return;
	REGISTRO aux;
	
	fseek(f, end * sizeof(REGISTRO), SEEK_SET);
	fread(&aux, sizeof(REGISTRO), 1, f);
	if(aux.nroUSP != nroUSPY){
		aux.nroUSP = nroUSPX;
		
		
		
		fseek(f, -sizeof(REGISTRO), SEEK_CUR);
		fwrite(aux, sizeof(REGISTRO), 1, f);
		for(int i = 0;i < TAM;i++){
			if(table_aluno[i].chave == nroUSPX){
				table_aluno[i.chave] == nroUSPY;
			}
		}
		int indice = buscaIndiceSecundario(table_curso, aux.curso);
		bool teste;	
		alteraTabelaSecundaria(table_aluno, nroUSPX, nroUSPY, indice, &teste);
		if(teste) 
			printf("Chave alterada de %d para %d na table_curso\n", nroUSPX, nroUSPY);
		int indice = buscaIndiceSecundario(table_estado, aux.estado);
		if(teste)
			printf("Chave alterada de %d para %d na table_estado\n", nroUSPX, nroUSPY);
		alteraTabelaSecundaria(table_curso, nroUSPX, nroUSPY, indice, &teste);		
	}
	
}

int main(){

	FILE * f = fopen("arq.bin", "wb+");
	int prox_aluno = 0;
	TABELA_P * table_aluno = (TABELA_P *)malloc(sizeof(TABELA_P) * TAM);
	int prox_curso = 0;
	TABELA_S * table_curso = (TABELA_S *)malloc(sizeof(TABELA_S) * TAM);
	int prox_estado = 0;
	TABELA_S * table_estado = (TABELA_S *)malloc(sizeof(TABELA_S) * TAM);
	
	//criacao das tabelas de indice primario e secundario
	criaTabelaPrimaria(f, table_aluno, &prox_aluno);
	bubbleSortTabbleP(table_aluno, prox_aluno);
	criaTabelaSecundaria(f, table_curso, &prox_curso);
	bubbleSortTabbleS(table_curso, prox_curso);
	criaTabelaSecundaria(f, table_estado, &prox_estado);
	bubbleSortTabbleS(table_curso, prox_estado);
	
	int nroUSPX, cursoY, nroUSPY;
	scanf("%d %d", &nroUSPX, &cursoY);
	alteraRegistroCurso(f, table_aluno, table_curso, nroUSPX, nroUSPY);
	
	scanf("%d %d", &nroUSPX, &nroUSPY);
	alteraRegistroAluno(f, table_aluno, table_curso, table_estado, nroUSPX, nroUSPY);
	
	
	
	
	
	
	
	return 0;
}
