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
    void ReorganizarPerArq(string ind,string p,string r);
    void EditPer();
    void DelPer();
    string BuscPer(string ind);
    string dat1,dat2,dat3;
    string arquivo;
    static const int ADICIONARP;
    static const int DELELETARP;
    static const int EDITARP;
    static const int SAIR;
    static const int LOGQUIZ;
    static const int DELQUIZ;
    static const int EDITQUIZ;
    void carregaQuiz();
    void EditarQuiz();
    void ApagarQuiz();
public:
    GerQuiz(); /*construtor*/
    ~GerQuiz();
    void GerIU(); /*interface com o usuario*/
    Quiz* getQuiz()throw(runtime_error);
};

#endif // GERCARQUIZ_H
