/////////////////////////////////////////
///		Descrição do arquivo:
///		@author		Marcos Paulo Batalha Bispo
///		@since		??/04/2017
///		@version	1.0
/////////////////////////////////////////

#ifndef LISTAGEMDEDICIPLINAS_H_INCLUDED
#define LISTAGEMDEDICIPLINAS_H_INCLUDED

#include <string>
#include <stdexcept>
#include "GerenciaDiciplinas.h"

using namespace std;

class ListagemDeDiciplinas {
private:

	//////////////////////////////////////////////////////////////////////////////////
	///		@brief Atributos do Gerenciador de Disciplinas
	///		Opção: Seleciona uma das constantes utilizadas para realizar uma ação
	///		escolhida pelo usuário
	///		
	///		arquivo_disciplina e lista_disciplinas são ponteiros para os arquivos
	///		relacionados a disciplinas
	///		
	///		nome_arquivo é uma variável para uso temporário de manejo de arquivos
	///	
	///		CONTINUAR e SAIR são constantes que representam opções de ações pro usuário
	///		
	///		numero_de_disciplinas Refere-se ao número de disciplinas na lista
	///		
	///		indice é o índice de cada disciplina
	//////////////////////////////////////////////////////////////////////////////////
    int opcao;
	FILE * arquivo_diciplina;
	FILE * lista_diciplinas;
	string nome_arquivo;
	const static int CONTINUAR;
	const static int SAIR;
	int numero_de_diciplinas;
	int indice;
public:

	//////////////////////////////////////////////////////////////////////////////////
	///		@brief Construtor
	//////////////////////////////////////////////////////////////////////////////////
    ListagemDeDiciplinas();

    //////////////////////////////////////////////////////////////////////////////////
    ///		@brief Faz a listagem de disciplinas
    //////////////////////////////////////////////////////////////////////////////////
    void listarDiciplinas();

};

#endif // LISTAGEMDEDICIPLINAS_H_INCLUDED
