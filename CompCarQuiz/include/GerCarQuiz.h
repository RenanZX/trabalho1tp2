#ifndef GERCARQUIZ_H
#define GERCARQUIZ_H
#include <stdio.h>  /*bibliotecas*/
#include <stdlib.h>
#include <direct.h>
#include <stdexcept>
#include <windows.h>
#include "Interfaces.h"
#include "stubQuiz.h"
#include <iostream>

using namespace std;
/*verifica qual a versao do SO*/
#ifdef _WIN32
#define CLEAR "cls"
#elif LINUX
#define CLEAR "clear"
#endif

class GerQuiz/*gerenciador de quiz*/
{
private:
    void PegaAttr(string dado);
    void AddPerguntas();
    void ReorganizarPerArq(string editind,string novap);
    string FormularPergArq(string n1,string n2,string n3);
    void EditPer();
    void DelPer();
    string BuscPer(string ind);
    string dat1,dat2,dat3;
    string arquivo,dir;
    static const int ADICIONARP;
    static const int DELELETARP;
    static const int EDITARP;
    static const int SAIR;
    static const int LOGQUIZ;
    static const int DELQUIZ;
    static const int EDITQUIZ;
    bool carregaQuiz();
    void EditarQuiz();
    void ApagarQuiz();
public:
    GerQuiz(); /*construtor*/
    ~GerQuiz();
    void executar(); /*interface com o usuario*/
    Quiz* getQuiz();
};

#endif // GERCARQUIZ_H
