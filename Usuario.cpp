#include "Usuario.h"
#include <stdio.h>
#include <stdlib.h>


string Usuario::getNome(){
	return nome;
}

void Usuario::setNome(string n){
	nome = n;
}

string Usuario::getLogin(){
	return login;
}

void Usuario::setLogin(string l){//[30]){
	login = l;
}

string Usuario::getSenha(){
	return senha;
}

void Usuario::setSenha(string s){//[30]){
	senha = s;
}

int Usuario::getPerfil(){

	if (perfil == admin)
		return 1;
	else
		return 0;

}

void Usuario::setPerfil(char p){
	if (p == 'a')
		perfil = admin;
	else
		perfil = estudante;
}

Usuario::Usuario(){
    logado = false;
	return;
}

//Retorna uma string, pulando linhas, de cada nome de disciplina na
//lista de disciplinas do usuario, de uma vez
string Usuario::listarDisciplinas(){
	string minhasDisciplinas = "";
	caderno* buscador;

	while(buscador != NULL) {
		minhasDisciplinas += buscador->d->nome+"\n";
		buscador = buscador->prox;
	}

	return minhasDisciplinas;

}

//Acrescenta uma disciplina na lista de disciplinas do usuario
//Procura-se uma disciplina no Gerenciador de Disciplinas,
//utilizando o codigo recebido por parametro
void Usuario::adicionarDisciplina(int codigo){

	caderno* procurador = ld;
	while(procurador != NULL){
		procurador = procurador->prox;
	}
	procurador = malloc(sizeof(caderno));

	procurador->d = GerDisciplinas.getDisciplina(codigo);

	return;
}

void Usuario::carregarDisciplinas(string disciplinasLeitura){
	int leitor;
	char contador;
	caderno* lds = malloc(sizeof(caderno));
	c = lds;
	do(leitor != NULL){
		fscanf(disciplinasLeitura,"%d",&leitor);
		lds->ID = leitor;
		lds->prox = malloc(sizeof(caderno));
		lds = lds->prox;
		fscanf(disciplinasLeitura,"%[^|]",&leitor);
	} while ((contador = fgetc(disciplinasLeitura)) != EOF);//"\n");
	free(lds);
	return;
}

//Encriptacao ainda nao implementado
//Encripta e decripta a senha salva no arquivo de usuarios
/*
string encriptaSenha(string s){
	return;
}

string decriptaSenha(string s){
	return;
}*/


//Metodos de "gerenciamento" de Disciplinas e Quizzes, onde o admin
//Pode fazer alteracoes nos arquivos de Disciplinas e Quizzes
void Usuario::criarDisciplina (string nome, GerenciaDisciplinas disc){
	if (perfil == admin){
		disc.criarDisciplina();
		//GerenciaDisciplinas::criarDisciplina(nome);
	}

	return;
}

void Usuario::alterarDisciplina (string nome){//, listaTopicos* lT, listaQuizzes* lQ){
	if (perfil == admin){
		//Disciplina.alterar(nome, lT, lQ);
	}

	return;
}

void Usuario::deletarDisciplina (string nome, GerenciaDisciplinas disc){
	if (perfil == admin){
		disc.removerDisciplina();
		//GerenciaDisciplinas::removerDisciplina(nome);
	}

	return;
}

void Usuario::criarQuiz (string nomequiz, GerQuiz quiz){
	if (perfil == admin){
		quiz->CriaQuiz(nomequiz);
		//GerQuiz::CriarQuiz(pergunta, resposta, nomeDisciplina, nomeTopico);
	}

	return;
}

void Usuario::alterarQuiz (string nomequiz, GerQuiz quiz){
	if (perfil == admin){
		quiz->EditarPergunta();
		//GerQuiz::alterar(pergunta, resposta, nomeDisciplina, nomeTopico);
	}

	return;
}

void Usuario::deletarQuiz (string pergunta, GerQuiz quiz){
	if (perfil == admin){
		quiz.ApagarQuiz();
		//GerQuiz::ApagarQuiz(pergunta);
	}

	return;
}

//}

//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
////////////////////////////////////////////////////////////////////////////////
