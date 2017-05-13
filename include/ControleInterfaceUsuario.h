#ifndef CONTROLEINTERFACEUSUARIO_H
#define CONTROLEINTERFACEUSUARIO_H

#include "Interfaces.h"
#include "GerenciadorQuiz.h"
#include "Quiz.h"

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
    GerQuiz *g;
    void EditarQuiz()throw(runtime_error);
public:
    void executar()throw(runtime_error);
};
//falta implementar
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
