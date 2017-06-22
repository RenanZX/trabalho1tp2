#ifndef CONTROLEINTERFACEUSUARIO_H
#define CONTROLEINTERFACEUSUARIO_H

#include "Interfaces.h"
#include "GerenciadorQuiz.h"
#include "Quiz.h"
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <stdexcept>

using namespace std;

class InterfaceUserGerQuiz:public InterfaceUsuarioGerQuiz/*interfaces que irão interagir com o usuario*/
{
private:
    static const int ADICIONARP;/*constantes*/
    static const int DELELETARP;
    static const int EDITARP;
    static const int SAIRP;
    static const int SAIR;
    static const int SELQUIZ;
    static const int LOGQUIZ;
    static const int DELQUIZ;
    static const int EDITQUIZ;
    static const int CREATEQUIZ;
    static const string TABLETOPICS;
    static const string TABLEDISC;
    GerQuiz *gerente;
    void EditarQuiz()throw(runtime_error);
    string index;
    void setTableTopics(string topico);
    void setTableDisc(string disciplina);
    void findTableTopics(string topico)throw(invalid_argument);
    void findTableDisc(string disciplina)throw(invalid_argument);
    string AddTopDisc()throw(runtime_error);
    string EditarTopDisc()throw(runtime_error);
    string ExcluirTopDisc()throw(runtime_error);
public:
    void executar()throw(runtime_error);
};

class InterfaceUserQuiz:public InterfaceUsuarioQuiz
{
private:
    static const int COMECARQUIZ;
    static const int CARREGAP;
    static const int SELP;
    static const int SAIR;
public:
    void executar()throw(runtime_error);
};
#endif // CONTROLEINTERFACEUSUARIO_H
