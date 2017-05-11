#ifndef MODULOGERENCIADICIPLINAS_H_INCLUDED
#define MODULOGERENCIADICIPLINAS_H_INCLUDED

#include <string>
#include <stdexcept>

class Diciplina {

private:
	string nome;

public:
	Diciplina();
	~diciplina();
	setNome();
	getNome();
	
};

class Topico {

private:
	string nome;
public:
	topico();
	~topico();
	setNome();
	getNome();
	
};

class GerenciaDiciplina{
public:
	GerenciaDiciplina();
	~GerenciaDiciplina();
	
};

#endif