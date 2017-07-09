#ifndef LISTAGEMDEDICIPLINAS_H_INCLUDED
#define LISTAGEMDEDICIPLINAS_H_INCLUDED

#include <string>
#include <stdexcept>
#include "Disciplina.hpp"

using namespace std;

class ListagemDeDiciplinas {
private:
    int opcao;
	FILE * arquivo_diciplina;
	FILE * lista_diciplinas;
	string nome_arquivo;
	const static int CONTINUAR;
	const static int SAIR;
	int numero_de_diciplinas;
	int indice;
public:
    ListagemDeDiciplinas();
    void listarDiciplinas();

};

#endif // LISTAGEMDEDICIPLINAS_H_INCLUDED
