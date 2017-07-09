#include "Usuario.hpp"
#include <stdio.h>
#include <stdlib.h>

//class Usuario{
enum PERFIL {admin = 1, estudante = 0} perfil;

Usuario::Usuario(){
	logado = false;
}
Usuario::~Usuario(){}

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

void Usuario(){
	return;
}

//Retorna uma string, pulando linhas, de cada nome de disciplina na
//lista de disciplinas do usuario, de uma vez
string Usuario::listarDisciplinas(){
	string minhasDisciplinas = "";
	caderno* buscador;
	
	while(buscador != NULL) {
		minhasDisciplinas += buscador->ID+"\n";
		buscador = buscador->prox;
	}
	
	return minhasDisciplinas;

}

//Acrescenta uma disciplina na lista de disciplinas do usuario
//Procura-se uma disciplina no Gerenciador de Disciplinas,
//utilizando o codigo recebido por parametro
void Usuario::adicionarDisciplina(int codigo){

	caderno* procurador = c;
	while(procurador != NULL){
		procurador = procurador->prox;
	}
	procurador = new caderno;//malloc(sizeof(caderno));
	
	procurador->ID = codigo;//GerDisciplinas.getDisciplina(codigo);

	return;
}

void Usuario::carregarDisciplinas(string disciplinasLeitura){
	int leitor = 0;
	char contador;
	caderno* lds = new caderno;//malloc(sizeof(caderno));
	//FILE * disc = fopen(disciplinasLeitura, "r");
	c = lds;
	/*do{
		//fscanf(disciplinasLeitura,"%d",&leitor);
		lds->ID = leitor;
		lds->prox = new caderno;//malloc(sizeof(caderno));
		lds = lds->prox;
		//fscanf(disciplinasLeitura,"%[^|]",&leitor);
	} while ((contador = fgetc(disciplinasLeitura)) != EOF);//"\n");*/
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

/*
//Metodos de "gerenciamento" de Disciplinas e Quizzes, onde o admin
//Pode fazer alteracoes nos arquivos de Disciplinas e Quizzes
void criarDisciplina (string nome, GerenciaDisciplinas disc){
	if (perfil == admin){
		disc.criarDisciplina();
		//GerenciaDisciplinas::criarDisciplina(nome);
	}
		
	return;
}

void alterarDisciplina (string nome){//, listaTopicos* lT, listaQuizzes* lQ){
	if (perfil == admin){
		//Disciplina.alterar(nome, lT, lQ);
	}
		
	return;
}

void deletarDisciplina (string nome, GerenciaDisciplinas disc){
	if (perfil == admin){
		disc.removerDisciplina();
		//GerenciaDisciplinas::removerDisciplina(nome);
	}
		
	return;
}

void criarQuiz (string pergunta, bool resposta, string nomeDisciplina, string nomeTopico, GerQuiz quiz){
	if (perfil == admin){
		quiz.CriarQuiz();
		//GerQuiz::CriarQuiz(pergunta, resposta, nomeDisciplina, nomeTopico);
	}
		
	return;
}

void alterarQuiz (string pergunta, bool resposta, string nomeDisciplina, string nomeTopico, GerQuiz quiz){
	if (perfil == admin){
		quiz.EditarPergunta();
		//GerQuiz::alterar(pergunta, resposta, nomeDisciplina, nomeTopico);
	}
		
	return;
}

void deletarQuiz (string pergunta, GerQuiz quiz){
	if (perfil == admin){
		quiz.ApagarQuiz();
		//GerQuiz::ApagarQuiz(pergunta);
	}
		
	return;
}*/

//}

//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
////////////////////////////////////////////////////////////////////////////////