#include "topicos.h"
#include <string>
#include <stdio.h>

using namespace std;


/*Definicao de constantes*/
const int CRIAR     = 1;
const int PESQUISAR = 2;
const int EDITAR    = 3;
const int EXCLUIR   = 4;
const int ASSOCIAR  = 5;
const int RETORNAR  = 6;

using namespace std;

Topico::Topico(string nome){
  this->nome = nome;
}

void Topico::setNomeTopico(string nome) throw(runtime_error){
  this->nome = nome;
}

string Topico::getNomeTopico() throw(runtime_error){
  return this->nome;
}



void GerenciadorTopico::criarTopico() throw(runtime_error){
    Topico topico;
	string topico_adicionar, novo_topico, nome_arquivo, topico_existente, conteudo_arquivo;
	char linha[100];
	FILE * nome_disciplina;
	int opcao = 1;


	while(opcao != 0) {
		cout << "Digite o nome da Disciplina a qual deseja adicionar um Topico." << endl;

		cin >> topico_adicionar;
		nome_arquivo = topico_adicionar + ".txt";
		nome_disciplina = fopen(nome_arquivo.c_str(), "r+");

		if(nome_disciplina == NULL) {
			cout << "A Disciplina nao existe" << endl;
		}
		else{
			try{
				cout << "Digite o nome do novo Topico." << endl;
				cin >> novo_topico;
				getchar();

				cout << "novo top" << novo_topico << endl;
				fgets(linha,sizeof(linha),nome_disciplina);

                topico_existente = linha;
                conteudo_arquivo = linha;


                rewind(nome_disciplina);


                topico_existente = topico_existente.substr(topico_existente.find("|")+1,topico_existente.length());
                topico_existente = topico_existente.substr(topico_existente.find("|")+1,topico_existente.length());
                topico_existente = topico_existente.substr(0,topico_existente.find("|"));
                novo_topico = " " + novo_topico;
                if(topico_existente == novo_topico){
                    cout << "Topico ja existe" << endl;
                }
                else{
                    fclose(nome_disciplina);
                    nome_disciplina = fopen(nome_arquivo.c_str(), "a+");
                    topico.setNomeTopico(topico_adicionar);
                    fprintf(nome_disciplina, "%s %s |", conteudo_arquivo.c_str(), novo_topico.c_str());
                    cout << "Novo Topico adicionado." << endl;
                }
			}
			catch (invalid_argument excecao) {
				cout << excecao.what() << endl;

			}
		}
		fclose(nome_disciplina);
		cout << "0-Sair" << endl;
		cout << "1-Continuar" << endl;
		cin >> opcao;
    }
}

void GerenciadorTopico::pesquisarTopico() throw(runtime_error){

    Topico topico;
	string disciplina_pesquisar, topico_pesquisar, nome_arquivo, topico_existente, conteudo_arquivo;
	char linha[100];
	FILE * nome_disciplina;
	int opcao = 1;

    while(opcao != 0) {
		cout << "Digite o nome da Disciplina a qual deseja pesquisar um Topico." << endl;

		cin >> disciplina_pesquisar;
		nome_arquivo = disciplina_pesquisar + ".txt";
		nome_disciplina = fopen(nome_arquivo.c_str(), "r");

		if(nome_disciplina == NULL) {
			cout << "A Disciplina nao existe" << endl;
		}
		else{
			try{
				cout << "Digite o nome do Topico procurado: " << endl;
				cin >> topico_pesquisar;
				getchar();

                topico_pesquisar = " " + topico_pesquisar;
				fgets(linha,sizeof(linha),nome_disciplina);
                topico_existente = linha;
                conteudo_arquivo = linha;

                rewind(nome_disciplina);


                topico_existente = topico_existente.substr(topico_existente.find("|")+1,topico_existente.length());
                topico_existente = topico_existente.substr(topico_existente.find("|")+1,topico_existente.length());
                topico_existente = topico_existente.substr(0,topico_existente.find("|"));
                cout << "existente: " << topico_existente << endl;

                cout << "pesquisar: " << topico_pesquisar << endl;


                if(topico_existente == topico_pesquisar){
                    rewind(nome_disciplina);
                    fgets(linha,sizeof(linha),nome_disciplina);
                    topico_existente = linha;
                    cout << "Conteudo do topico: " << endl;
                    cout << conteudo_arquivo << endl;
                    fclose(nome_disciplina);
                }
                else{
                    cout << "Topico nao existe!" << endl;
                }
			fclose(nome_disciplina);
			}
			catch (invalid_argument excecao) {
				cout << excecao.what() << endl;
			}
		}
		cout << "0-Sair" << endl;
		cout << "1-Continuar" << endl;
		cin >> opcao;
    }
}

void GerenciadorTopico::editarTopico() throw(runtime_error) {

    Topico topico;
	string disciplina_pesquisar, topico_pesquisar, nome_arquivo, topico_existente, novo_topico, conteudo_arquivo;
	char linha[100];
	FILE * nome_disciplina;
	int opcao = 1;

    while(opcao != 0) {
		cout << "Digite o nome da Disciplina a qual deseja pesquisar um Topico." << endl;

		cin >> disciplina_pesquisar;
		nome_arquivo = disciplina_pesquisar + ".txt";
		nome_disciplina = fopen(nome_arquivo.c_str(), "r");

		if(nome_disciplina == NULL) {
			cout << "A Disciplina nao existe" << endl;
		}
		else{
			try{
				cout << "Digite o nome do Topico procurado: " << endl;
				cin >> topico_pesquisar;

				fgets(linha,sizeof(linha),nome_disciplina);
                topico_existente = linha;
                conteudo_arquivo = linha;

                rewind(nome_disciplina);


                topico_existente = topico_existente.substr(topico_existente.find("|")+1,topico_existente.length());
                topico_existente = topico_existente.substr(topico_existente.find("|")+1,topico_existente.length());
                topico_existente = topico_existente.substr(0,topico_existente.find("|"));
                cout << "existente: " << topico_existente << endl;

                if(topico_existente == topico_pesquisar){
                    rewind(nome_disciplina);
                    fgets(linha,sizeof(linha),nome_disciplina);
                    topico_existente = linha;
                    cout << "Nome do novo topico: " << endl;
                    cin >> novo_topico;
                    fclose(nome_disciplina);
                    nome_disciplina = fopen(nome_arquivo.c_str(), "a+");
                    topico.setNomeTopico(novo_topico);
                    fprintf(nome_disciplina, "%s %s |", conteudo_arquivo.c_str(), novo_topico.c_str());
                    cout << "Nome Topico alterado." << endl;
                }
                else{
                    cout << "O Topico nao existe! " << endl;
                }
			fclose(nome_disciplina);
			}
			catch (invalid_argument excecao) {
				cout << excecao.what() << endl;
			}
		}
		cout << "0-Sair" << endl;
		cout << "1-Continuar" << endl;
		cin >> opcao;
    }

}


