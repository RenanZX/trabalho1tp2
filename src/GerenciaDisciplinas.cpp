#include "GerenciaDisciplinas.h"
#include <iostream>
#include <stdio.h>



const char Disciplina::ESPACO =' ';
const int Disciplina::TAMANHO_CERTO = 2;
const int GerenciaDisciplinas::CONTINUAR = 1;
const int GerenciaDisciplinas::SAIR = 0;

Disciplina::Disciplina(){
}

string Disciplina::getNome () {
	return nome;
}

void Disciplina::setNome (string nome)throw (invalid_argument) {
	validarNome (nome);
	this->nome = nome;

}

void Disciplina::validarNome (string nome) throw (invalid_argument){
    indice = 0;
	while(nome[indice] != NULL) { // Loop que testa se todos os caracteres são letras ou espacos usando a funcao isalpha.
        if ((isalpha(nome[indice]) == false ) || (nome[indice] == ESPACO))  throw invalid_argument("Nome invalido.");
        indice++;
    }
}

string Disciplina::getCodigo()  {
    return codigo;
}

void Disciplina::setCodigo (string codigo)throw (invalid_argument) {
    validarCodigo(codigo);
    this->codigo = codigo;
}

void Disciplina::validarCodigo (string codigo) throw (invalid_argument){
	if(codigo.size() != TAMANHO_CERTO) throw invalid_argument("Tamanho do codigo invalido.");
    indice = 0;
	while(codigo[indice] != '\0') { // Loop que testa se todos os caracteres são letras usando a funcao isalpha.
        if (isdigit(codigo[indice]) == false ) throw invalid_argument("Codigo invalido.");
        indice++;
    }
}

void GerenciaDisciplinas::criarDisciplina (){
	Disciplina disciplina;
	string disciplina_a_adicionar;
	string codigo_a_adicionar;
	opcao = CONTINUAR;


    lista_disciplinas = fopen("lista_disciplinas.txt", "a");


	while(opcao != SAIR) {
		cout << "Insira o nome da Disciplinas a ser adicionada." << endl;
		cin >> disciplina_a_adicionar;
        while(getchar() != '\n');
		nome_arquivo = disciplina_a_adicionar +".txt";
		arquivo_disciplina = fopen(nome_arquivo.c_str(), "r");
		if(arquivo_disciplina != NULL) {
			cout << "A disciplina ja existe" << endl;
		}
		else {
			try {
				disciplina.setNome(disciplina_a_adicionar);
				cout << "Insira o codigo da disciplina a ser criada." << endl;
				cin >> codigo_a_adicionar;
				disciplina.setCodigo(codigo_a_adicionar);
				arquivo_disciplina = fopen(nome_arquivo.c_str(), "w");
				cout << "A disciplina foi criada." << endl;
				fprintf(arquivo_disciplina, "%s | %s", codigo_a_adicionar.c_str(),disciplina_a_adicionar.c_str());
				fprintf(lista_disciplinas, "%s | %s\n" , codigo_a_adicionar.c_str(),disciplina_a_adicionar.c_str());
				fclose(arquivo_disciplina);

			}
			catch (invalid_argument excecao) {
				cout << excecao.what() << endl;

			}
		}
		cout << "Aperte 1 para continuar ou 0 para sair." << endl;
		cin >> opcao;
	}
	fclose(lista_disciplinas);

}
void GerenciaDisciplinas::removerDisciplina() {
    string disciplina_a_remover;
    opcao = CONTINUAR;

    while(opcao != SAIR) {
        cout << "Insira o nome da Disciplina a ser removida." << endl;
		cin >> disciplina_a_remover;
		nome_arquivo = disciplina_a_remover +".txt";
		arquivo_disciplina = fopen(nome_arquivo.c_str(), "r");
		if(arquivo_disciplina == NULL) {
			cout << "A disciplina nao existe" << endl;
		}
		else {
            cout << "A disciplina:" << disciplina_a_remover << " sera removida, para continuar aperte 1, para voltar aperte 0" << endl;
            cout << nome_arquivo << endl;
            cin >> opcao;
            if (opcao == CONTINUAR) {
                if(remove(nome_arquivo.c_str()) == 0) {
                    cout << "A disciplina foi removida" << endl;
                }
                else {
                    cout << "Erro ao remover" << endl;
                }
            }
		}
        cout << "Aperte 1 para continuar ou 0 para sair." << endl;
		cin >> opcao;
    }

}

