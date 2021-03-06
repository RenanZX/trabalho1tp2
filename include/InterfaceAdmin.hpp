#ifndef INTERFACEADMIN_H
#define INTERFACEADMIN_H

#include "Interfaces.hpp"
#include "GerenciadorQuiz.hpp"
#include "Usuario.hpp"
#include "Disciplina.hpp"
#include "Quiz.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <stdexcept>
using namespace std;

/*interfaces que irão interagir com o usuario*/
class InterfaceAdmin{//:public InterfacePrograma{

private:
	/*constantes*/
	static const char USUARIOS;
	static const char DISCIPLINAS;
	static const char QUIZ;

	static const int CRIAR;
	static const int ALTERAR;
	static const int DELETAR;
	static const int ADDTOPICO;

	static const int VOLTAR;
	static const int SAIR;

	bool fechaSessao;
	bool fechaCategoria;
	bool fechaAcao;


	Usuario user;
	Disciplina disc;
	Quiz quiz;

	void criarUsuario(string, string, string, int)throw(runtime_error);
	void alterarUsuario(string, string, string, int);
	void deletarUsuario(string);

	void criarDisciplina(string, int);
	void alterarDisciplina(int);
	void deletarDisciplina(int);
	void adicionarTopico(int, string);

	void criarQuiz(int, int, Quiz);
	void alterarQuiz(int, int, int, Quiz);
	void deletarQuiz(int, int, int);
	
	void listarUsuarios();
	void listarDisciplinas();
	void listarQuiz();

public:

	void mostrarOpcoes(Usuario&, bool*)throw(runtime_error);
	void executarOpcao(int, bool*)throw(runtime_error);

};

#endif //INTERFACEADMIN_H
