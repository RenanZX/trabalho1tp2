#ifndef GERCARQUIZ_H
#define GERCARQUIZ_H
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <direct.h>
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
    void carregaQuiz();/*seta um quiz de um arquivo*/
    void EditarQuiz();
    void ApagarQuiz();
public:
    GerQuiz();
    ~GerQuiz();
    void GerIU();
};

#endif // GERCARQUIZ_H
