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

typedef struct Disciplinas{
	Disciplina d;
	Disciplinas* prox;
} Disciplinas;

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
			break;
		}
	} while (loginLeitura != EOF);

	return logado;
}

void Cadastrar(String^ l, String^ s, String^ n, int p, Disciplinas* d){
	
	return;
}