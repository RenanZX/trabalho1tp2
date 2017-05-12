#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "disciplinas.h"
#include "Usuario.h"

using namespace System::IO;

class Usuario{
	String^ nome;//[50];
	String^ login;//[30];
	String^ senha;//[30];
	enum PERFIL {admin, estudante} perfil;
	bool logado = false;

	typedef struct listaDisciplinas{
		Disciplina d;
		Disciplinas* prox;
	} listaDisciplinas ld;

	String getNome(){
		return nome;
	}
	
	void setNome(String^ n){
		this.nome = n;
	}

	String^ getLogin(){
		return this.login;
	}
	
	void setLogin(String^ l){//[30]){
		this.login = l;
	}
	
	String^ getSenha(){
		return this.senha;
	}
	
	void setSenha(String^ s){//[30]){
		this.senha = s;
	}

	int getPerfil(){
	
		if (this.perfil == admin)
			return 1;
		else
			return 0;
			
	}
	
	void setPerfil(char p){
		if (p == 'a')
			this.perfil = admin;
		else
			this.perfil = estudante;
	}

	void Usuario(){
		return;
	}

	//Retorna uma string, pulando linhas, de cada nome de disciplina na
	//lista de disciplinas do usuario, de uma vez
	String^ listarDisciplinas(){
		String^ minhasDisciplinas = "";
		listaDisciplinas* buscador;
		
		while(buscador != NULL){
			minhasDisciplinas += buscador->d->nome+"\n";
			buscador = buscador->prox;
		}
		
		return minhasDisciplinas;

	}

	//Acrescenta uma disciplina na lista de disciplinas do usuario
	//Procura-se uma disciplina no Gerenciador de Disciplinas,
	//utilizando o codigo recebido por parametro
	void adicionarDisciplina(int codigo){

		listaDisciplinas* procurador = this.ld;
		while(procurador != NULL){
			procurador = procurador->prox;
		}
		procurador = malloc(sizeof(listaDisciplinas));
		
		procurador->d = GerDisciplinas.getDisciplina(codigo);

		return;
	}

	//Faz o login de um usuario
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
				this.nome = nomeLeitura;
				this.login = l;
				this.senha = s;
				this.perfil = ((perfilLeitura == 1) ? admin : estudante);
				//Adicionar disciplinas
				
				String^ leitor;
				listaDisciplinas* lds = malloc(sizeof(listaDisciplinas));
				this.ld = lds;
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
	void Cadastrar(String^ l, String^ s, String^ n, int p, Disciplinas* d){
		if (this.perfil != admin){
			return;
		}
		
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
	
	//Encriptacao ainda nao implementado
	//Encripta e decripta a senha salva no arquivo de usuarios
	/*
	String^ encriptaSenha(String^ s){
		return;
	}
	
	String^ decriptaSenha(String^ s){
		return;
	}*/

	
	//Metodos de "gerenciamento" de Disciplinas e Quizzes, onde o admin
	//Pode fazer alteracoes nos arquivos de Disciplinas e Quizzes
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

}