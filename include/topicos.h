#ifndef TOPICOS_H
#define TOPICOS_H

#include <iostream>
#include <string>
#include <cstring>
#include <stdexcept>

using namespace std;

class Topico {
private:
  string nome;

public:
    Topico(){
    }
    Topico(string);
    void setNomeTopico(string) throw(runtime_error);
    string getNomeTopico() throw(runtime_error);

};

class GerenciadorTopico {

private:

  const static int CRIAR;
  const static int PESQUISAR;
  const static int EDITAR;
  const static int EXCLUIR;
  const static int ASSOCIAR;
  const static int RETORNAR;

  string arquivo_disciplina;



public:

  void criarTopico() throw(runtime_error);
  void pesquisarTopico() throw(runtime_error);
  void editarTopico() throw(runtime_error);
  void associarTopico() throw(runtime_error);
  void excluirTopico() throw(runtime_error);



};

#endif /* TOPICOS_H */
