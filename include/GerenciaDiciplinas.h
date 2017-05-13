#ifndef GERENCIADICIPLINAS_H_INCLUDED
#define GERENCIADICIPLINAS_H_INCLUDED

#include <string>
#include <stdexcept>
#include <stdlib.h>


using namespace std;

class Diciplinas {

private:
	string nome;
	string codigo;
	int indice;
	const static char ESPACO;
    const static int TAMANHO_CERTO;
	void validarNome (string) throw (invalid_argument);
	void validarCodigo (string) throw (invalid_argument);

public:
	Diciplinas();
	void setNome(string)throw (invalid_argument);
	string getNome();
	void setCodigo(string)throw (invalid_argument);
	string getCodigo();


};

/*class Topico {

private:
	string nome;
public:
	topico();
	setNome();
	getNome();

}; */

class GerenciaDiciplinas{
private:
	int opcao;
	FILE * arquivo_diciplina;
	FILE * lista_diciplinas;
	string nome_arquivo;
	const static int CONTINUAR;
	const static int SAIR;

public:
	GerenciaDiciplina();
	/*~GerenciaDiciplina(); */
	void criarDiciplina();
    void removerDiciplina();

};

#endif
