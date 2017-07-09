#ifndef INTERFACEUSUARIO_H
#define INTERFACEUSUARIO_H

#include "Interfaces.hpp"
//#include "Usuario.hpp"
#include "InterfaceAdmin.hpp"
#include "InterfaceEstudo.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <stdexcept>
using namespace std;

/*interfaces que irão interagir com o usuario*/
class InterfaceUsuario{//:public InterfacePrograma{
private:
	/*constantes*/
	static const int LOGAR;
	static const int CADASTRAR;
	static const int SAIR;

	bool fecha;
	Usuario user;

	bool Login(string, string)throw(runtime_error);;
	void Cadastrar(string, string, string, int)throw(runtime_error);
	void Sair();
public:
	void mostrarOpcoes()throw(runtime_error);
	//void mostrarOpcoes(Usuario)throw(runtime_error);
	void executarOpcao(int opcao)throw(runtime_error);
};

#endif //INTERFACEUSUARIO_H
