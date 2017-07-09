#ifndef INTERFACEESTUDO_H
#define INTERFACEESTUDO_H

#include "Interfaces.hpp"
#include "Usuario.hpp"
#include "Quiz.hpp"
#include "GerenciadorQuiz.hpp"
//#include "InterfaceAdmin.hpp"
//#include "InterfaceEstudo.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <stdexcept>
#include "ControleInterfaceUsuario.h"
using namespace std;

/*interfaces que irão interagir com o usuario*/
class InterfaceEstudo{//:public InterfacePrograma{
private:
	/*constantes*/
	static const int ADDDISC;
	static const int RESPONDER;

	bool fecha;
	Usuario user;
	Quiz quiz;

	void listarUsuarios();
	void listarDisciplinas();
	void listarQuiz();
public:
	void mostrarOpcoes(Usuario&, bool*)throw(runtime_error);
	void executarOpcao(int)throw(runtime_error);
};

#endif //INTERFACEESTUDO_H
