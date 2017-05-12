#include "GerenciaDiciplinas.h"
#include <iostream>
#include <stdio.h>



const char Diciplina::ESPACO =' ';
const int Diciplina::TAMANHO_CERTO = 2;
const int GerenciaDiciplinas::CONTINUAR = 1;
const int GerenciaDiciplinas::SAIR = 0;

Diciplina::Diciplina(){
}

string Diciplina::getNome () {
	return nome;
}

void Diciplina::setNome (string nome)throw (invalid_argument) {
	validarNome (nome);
	this->nome = nome;

}

void Diciplina::validarNome (string nome) throw (invalid_argument){
    indice = 0;
	while(nome[indice] != '\0') { // Loop que testa se todos os caracteres são letras ou espacos usando a funcao isalpha.
        if ((isalpha(nome[indice]) == false ) && (nome[indice] != ESPACO))  throw invalid_argument("Nome invalido.");
        indice++;
    }
}

string Diciplina::getCodigo()  {
    return codigo;
}

void Diciplina::setCodigo (string codigo)throw (invalid_argument) {
    validarCodigo(codigo);
    this->codigo = codigo;
}

void Diciplina::validarCodigo (string codigo) throw (invalid_argument){
	if(codigo.size() != TAMANHO_CERTO) throw invalid_argument("Tamanho do codigo invalido.");
    indice = 0;
	while(codigo[indice] != '\0') { // Loop que testa se todos os caracteres são letras usando a funcao isalpha.
        if (isdigit(codigo[indice]) == false ) throw invalid_argument("Codigo invalido.");
        indice++;
    }
}

void GerenciaDiciplinas::criaDiciplina (){
	Diciplina diciplina;
	string diciplina_a_adicionar;
	string codigo_a_adicionar;
	string nome_arquivo;
	opcao = CONTINUAR;


	while(opcao != SAIR) {
		cout << "Insira o nome da Diciplina a ser adicionada." << endl;
		cin>> diciplina_a_adicionar;
		nome_arquivo = diciplina_a_adicionar +".txt";
		arquivo_diciplina = fopen(nome_arquivo.c_str(), "r");
		if(arquivo_diciplina != NULL) {
			cout << "A diciplina ja existe" << endl;
		}
		else {
			try {
				diciplina.setNome(diciplina_a_adicionar);
				cout << "Insira o codigo da diciplina a ser criada." << endl;
				cin >> codigo_a_adicionar;
				diciplina.setCodigo(codigo_a_adicionar);
				arquivo_diciplina = fopen(nome_arquivo.c_str(), "w");
				cout << "A diciplina foi criada." << endl;
				fprintf(arquivo_diciplina, "%s", codigo_a_adicionar.c_str());
				fclose(arquivo_diciplina);
			}
			catch (invalid_argument excecao) {
				cout << excecao.what() << endl;

			}
		}
		cout << "Aperte 1 para continuar ou 0 para sair." << endl;
		cin >> opcao;
	}

}

