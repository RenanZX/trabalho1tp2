#ifndef GERCARQUIZ_H
#define GERCARQUIZ_H
#include <stdio.h>
#include <stdlib.h>
#include "stubQuiz.h"

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
    void EditPer();
    void DelPer();
    void BuscPer();
    string dat1,dat2,dat3;
    Quiz* q;
    static const int ADICIONARP;
    static const int DELELETARP;
    static const int EDITARP;
    static const int BUSCARP;
    static const int SAIR;
    static const int LOGQUIZ;
    static const int DELQUIZ;
    static const int EDITQUIZ;
    void carregaQuiz();/*seta um quiz de um arquivo*/
    void EditarQuiz();
    void ApagarQuiz();
public:
    GerQuiz();
    virtual ~GerQuiz();
    void GerIU();
};

#endif // GERCARQUIZ_H
