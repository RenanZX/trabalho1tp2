#include "GerenciaDiciplinas.h"
#include <iostream>
#include <stdio.h>



const char Diciplinas::ESPACO =' ';
const int Diciplinas::TAMANHO_CERTO = 2;
const int GerenciaDiciplinas::CONTINUAR = 1;
const int GerenciaDiciplinas::SAIR = 0;

Diciplinas::Diciplinas(){
}

string Diciplinas::getNome () {
	return nome;
}

void Diciplinas::setNome (string nome)throw (invalid_argument) {
	validarNome (nome);
	this->nome = nome;

}

void Diciplinas::validarNome (string nome) throw (invalid_argument){
    indice = 0;
	while(nome[indice] != NULL) { // Loop que testa se todos os caracteres são letras ou espacos usando a funcao isalpha.
        if ((isalpha(nome[indice]) == false ) || (nome[indice] == ESPACO))  throw invalid_argument("Nome invalido.");
        indice++;
    }
}

string Diciplinas::getCodigo()  {
    return codigo;
}

void Diciplinas::setCodigo (string codigo)throw (invalid_argument) {
    validarCodigo(codigo);
    this->codigo = codigo;
}

void Diciplinas::validarCodigo (string codigo) throw (invalid_argument){
	if(codigo.size() != TAMANHO_CERTO) throw invalid_argument("Tamanho do codigo invalido.");
    indice = 0;
	while(codigo[indice] != '\0') { // Loop que testa se todos os caracteres são letras usando a funcao isalpha.
        if (isdigit(codigo[indice]) == false ) throw invalid_argument("Codigo invalido.");
        indice++;
    }
}

void GerenciaDiciplinas::criarDiciplina (){
	Diciplinas diciplina;
	string diciplina_a_adicionar;
	string codigo_a_adicionar;
	opcao = CONTINUAR;


    lista_diciplinas = fopen("lista_diciplinas.txt", "a");


	while(opcao != SAIR) {
		cout << "Insira o nome da Diciplinas a ser adicionada." << endl;
		cin >> diciplina_a_adicionar;
        while(getchar() != '\n');
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
				fprintf(arquivo_diciplina, "%s | %s", codigo_a_adicionar.c_str(),diciplina_a_adicionar.c_str());
				fprintf(lista_diciplinas, "%s | %s\n" , codigo_a_adicionar.c_str(),diciplina_a_adicionar.c_str());
				fclose(arquivo_diciplina);

			}
			catch (invalid_argument excecao) {
				cout << excecao.what() << endl;

			}
		}
		cout << "Aperte 1 para continuar ou 0 para sair." << endl;
		cin >> opcao;
	}
	fclose(lista_diciplinas);

}
void GerenciaDiciplinas::removerDiciplina() {
    string diciplina_a_remover;
    opcao = CONTINUAR;

    while(opcao != SAIR) {
        cout << "Insira o nome da Diciplina a ser removida." << endl;
		cin >> diciplina_a_remover;
		nome_arquivo = diciplina_a_remover +".txt";
		arquivo_diciplina = fopen(nome_arquivo.c_str(), "r");
		if(arquivo_diciplina == NULL) {
			cout << "A diciplina nao existe" << endl;
		}
		else {
            cout << "A diciplina:" << diciplina_a_remover << " sera removida, para continuar aperte 1, para voltar aperte 0" << endl;
            cout << nome_arquivo << endl;
            cin >> opcao;
            if (opcao == CONTINUAR) {
                if(remove(nome_arquivo.c_str()) == 0) {
                    cout << "A diciplina foi removida" << endl;
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

