#ifndef GERCARQUIZ_H
#define GERCARQUIZ_H
#include <stdio.h>
#include <stdlib.h>
#include "Quiz.h"

class GerQuiz/*gerenciador de quiz*/
{
public:
    GerQuiz();
    virtual ~GerQuiz();
    void setQuiz(FILE *arq);/*seta um quiz de um arquivo*/
    Quiz getQuiz(); /*retorna um quiz*/

};

#endif // GERCARQUIZ_H
