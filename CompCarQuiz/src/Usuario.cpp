#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "disciplinas.h"

using namespace System::IO;


String^ nome;//[50];
String^ login;//[30];
String^ senha;//[30];
enum PERFIL {admin, estudante} perfil;
bool logado = false;

typedef struct listaDisciplinas{
	Disciplina d;
	Disciplinas* prox;
} listaDisciplinas;

String getNome(){
	return nome;
}

void setLogin(String^ l){//[30]){
	login = l;
}

void setSenha(String^ s){//[30]){
	senha = s;
}

void setPerfil(char p){
	if (p == 'a'){
		perfil = admin;
	else
		perfil = estudante;
}

int getPerfil(){
	if (perfil == admin){
		return 1;
	else
		return 0;
}

String^ listarDisciplinas(){
	String^ minhasDisciplinas = "";
	listaDisciplinas* buscador;
	
	while(buscador != NULL){
		minhasDisciplinas += buscador->d->nome+"\n";
		buscador = buscador->prox;
	}
	
	return minhasDisciplinas;

}

bool Login(String^ l, String^ s){
	String^ loginLeitura;
	String^ senhaLeitura;
	String^ nomeLeitura;
	String^ perfilLeitura;
	String^ disciplinasLeitura;
	
	String^ f = "usuarios.bin";
	StreamReader^ file = File::OpenText(f);
	
	do {
		fscanf(file, "%[^|]%[^|]%[^|]%[^|]%[^\n]",
			&loginLeitura, 
			&senhaLeitura, 
			&nomeLeitura,
			&perfilLeitura,
			&disciplinasLeitura);
			
		if (loginLeitura == l) && (senhaLeitura == s){
			logado = true;
			nome = nomeLeitura;
			perfil = ((perfilLeitura == 1) ? admin : estudante);
			//Adicionar disciplinas
			
			String^ leitor;
			listaDisciplinas* ld = malloc(sizeof(listaDisciplinas));
			fscanf(disciplinasLeitura,"%[^\n]",&leitor);
			while(leitor != NULL){
				ld->d = GerDisciplinas.getDisciplina(leitor.toInt32());
				ld->prox = malloc(sizeof(listaDisciplinas));
				ld = ld->prox;
			}
			free(ld);
			break;
		}
	} while (loginLeitura != EOF);

	file.close();
	return logado;
}

void Cadastrar(String^ l, String^ s, String^ n, int p, Disciplinas* d){
	StreamWriter f = new StreamWriter("usuarios.bin");
	f.Write( l + "|" + s + "|" + n + "|" + p );
	
	listaDisciplinas* ld = d;
	while (ld != NULL){
		f.Write("|");
		f.Write(ld->id);
		ld = ld->prox;
	}
	f.Write("\n");
	
	file.close();
	return;
}

void criarDisciplina (String^ nome){
	if (this.perfil == admin){
		Disciplina.criar(nome);
	}
		
	return;
}

void alterarDisciplina (String^ nome, listaTopicos* lT, listaQuizzes* lQ){
	if (this.perfil == admin){
		Disciplina.alterar(nome, lT, lQ);
	}
		
	return;
}

void deletarDisciplina (String^ nome){
	if (this.perfil == admin){
		Disciplina.deletar(nome);
	}
		
	return;
}


void criarQuiz (String^ pergunta, bool resposta, String^ nomeDisciplina, String^ nomeTopico){
	if (this.perfil == admin){
		Quiz.criar(pergunta, resposta, nomeDisciplina, nomeTopico);
	}
		
	return;
}

void alterarQuiz (String^ pergunta, bool resposta, String^ nomeDisciplina, String^ nomeTopico){
	if (this.perfil == admin){
		Quiz.alterar(pergunta, resposta, nomeDisciplina, nomeTopico);
	}
		
	return;
}

void deletarQuiz (String^ pergunta){
	if (this.perfil == admin){
		Quiz.deletar(pergunta);
	}
		
	return;
}