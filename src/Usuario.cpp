#include "Usuario.h"
using namespace System;
using namespace System::IO;

//class Usuario{
string nome;//[50];
string login;//[30];
string senha;//[30];
enum PERFIL {admin, estudante} perfil;
bool logado = false;

typedef struct listaDisciplinas{
	Disciplina d;
	listaDisciplinas* prox;
} listaDisciplinas ld;

string getNome(){
	return nome;
}

void setNome(string n){
	nome = n;
}

string getLogin(){
	return login;
}

void setLogin(string l){//[30]){
	login = l;
}

string getSenha(){
	return senha;
}

void setSenha(string s){//[30]){
	senha = s;
}

int getPerfil(){

	if (perfil == admin)
		return 1;
	else
		return 0;
		
}

void setPerfil(char p){
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
string listarDisciplinas(){
	string minhasDisciplinas = "";
	listaDisciplinas* buscador;
	
	while(buscador != NULL) {
		minhasDisciplinas += buscador->d->nome+"\n";
		buscador = buscador->prox;
	}
	
	return minhasDisciplinas;

}

//Acrescenta uma disciplina na lista de disciplinas do usuario
//Procura-se uma disciplina no Gerenciador de Disciplinas,
//utilizando o codigo recebido por parametro
void adicionarDisciplina(int codigo){

	listaDisciplinas* procurador = ld;
	while(procurador != NULL){
		procurador = procurador->prox;
	}
	procurador = malloc(sizeof(listaDisciplinas));
	
	procurador->d = GerDisciplinas.getDisciplina(codigo);

	return;
}

//Faz o login de um usuario
bool Login(string l, string s){
	string loginLeitura;
	string senhaLeitura;
	string nomeLeitura;
	string perfilLeitura;
	string disciplinasLeitura;
	
	string f = "usuarios.bin";
	StreamReader^ file = File::OpenText(f);
	
	do {
		fscanf(file, "%[^|]%[^|]%[^|]%[^|]%[^\n]",
			&loginLeitura, 
			&senhaLeitura, 
			&nomeLeitura,
			&perfilLeitura,
			&disciplinasLeitura);
			
		if (loginLeitura == l) && (senhaLeitura == s){
			nome = nomeLeitura;
			login = l;
			senha = s;
			perfil = ((perfilLeitura == 1) ? admin : estudante);
			//Adicionar disciplinas
			
			string leitor;
			listaDisciplinas* lds = malloc(sizeof(listaDisciplinas));
			ld = lds;
			fscanf(disciplinasLeitura,"%[^\n]",&leitor);
			while(leitor != NULL){
				lds->d = GerDisciplinas.getDisciplina(leitor.toInt32());
				lds->prox = malloc(sizeof(listaDisciplinas));
				lds = lds->prox;
			}
			free(lds);
			logado = true;
			break;
		}
	} while (loginLeitura != EOF);

	file.close();
	return logado;
}

//Adiciona um usuario no arquivo de usuarios, para que ele possa, futuramente,
//logar e utilizar o sistema
void Cadastrar(string l, string s, string n, int p, listaDisciplinas* disc){
	if (perfil != admin){
		return;
	}
	
	StreamWriter^ f = gcnew StreamWriter("usuarios.bin");
	//f.Write( l + "|" + s + "|" + n + "|" + p );
	
	listaDisciplinas* ld = disc;
	while (ld != NULL){
		f.Write("|");
		f.Write(ld->d.getCodigo());
		ld = ld->prox;
	}
	f.Write("\n");
	
	f.close();
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
}

//}