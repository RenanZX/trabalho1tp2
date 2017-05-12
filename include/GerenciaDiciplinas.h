#ifndef GERENCIADICIPLINAS_H_INCLUDED
#define GERENCIADICIPLINAS_H_INCLUDED

#include <string>
#include <stdexcept>

using namespace std;

class Diciplina {

private:
	string nome;
	string codigo;
	int indice;
	const static char ESPACO;
    const static int TAMANHO_CERTO;
	void validarNome (string) throw (invalid_argument);
	void validarCodigo (string) throw (invalid_argument);

public:
	Diciplina();
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
	const static int CONTINUAR;
	const static int SAIR;
public:
	GerenciaDiciplina();
	/*~GerenciaDiciplina(); */
	void criaDiciplina();


};

#endif
