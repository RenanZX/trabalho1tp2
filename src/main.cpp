#include <stdio.h>
#include <stdlib.h>

#include "InterfaceUsuario.hpp"


int main(){

	while(true){
		//Chama impressora da InterfaceUsuario
			/// serão mostradas as opções que o usuário tem:
			/// Cadastrar; Logar; Sair
		InterfaceUsuario* u = new InterfaceUsuario();
		u->mostrarOpcoes();
		//InterfaceUsuario::opções();

		//Ao logar (ou após cadastro), chama opções referentes
		//ao tipo do usuário: ADM ou estudante
			/// Chama opções de Admin ou Estudante, dependendo do nível de permissão
		//InferfaceUsuario::chamarOpções();
			

		//ao terminar o que o usuário tem que fazer,
		//programa fecha


	}

	return 0;
}