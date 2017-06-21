#ifndef GERENCIADISCIPLINAS_H_INCLUDED
#define GERENCIADISCIPLINAS_H_INCLUDED

#include <string.h>
#include <stdexcept>
#include <stdlib.h>


using namespace std;

class Disciplina {

private:
	string nome;
	string codigo;
	int indice;
	const static char ESPACO;
    const static int TAMANHO_CERTO;
	void validarNome (string) throw (invalid_argument);
	void validarCodigo (string) throw (invalid_argument);

public:
	Disciplina();
	void setNome(string)throw (invalid_argument);
	string getNome();
	void setCodigo(string)throw (invalid_argument);
	string getCodigo();


};


class GerenciaDisciplinas{
private:
	int opcao;
	FILE * arquivo_disciplina;
	FILE * lista_disciplinas;
	string nome_arquivo;
	const static int CONTINUAR;
	const static int SAIR;

public:
	GerenciaDisciplinas();
	/*~GerenciaDisciplina(); */
	void criarDisciplina();
    void removerDisciplina();

};

#endif
