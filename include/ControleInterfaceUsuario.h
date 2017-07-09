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

class InterfaceGerenteQuiz:public Interface
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
    TabelaDisciplinasTopicos tabela;
    int lastIndexFile;
    int limiterespostas;
    GerQuiz *gerente;
    void AdicionarPerguntas()throw(runtime_error);
    void EditarPerguntas()throw(runtime_error);
    void DeletarPergunta()throw(runtime_error);
    void CriarQuiz()throw(runtime_error);
    void CarregarQuiz()throw(runtime_error);
    void SelecionarQuiz()throw(runtime_error);
    void EditarQuiz()throw(runtime_error);
    void ApagarQuiz()throw(runtime_error);
    string PegaAtributo(string dado,int atributo);
    string FormularPerguntaImprimir(string pergunta);/*formula uma pergunta do arquivo para ser imprimida ao usuario*/
public:
    void MostrarOpcoes()throw(runtime_error);
    void executarOpcao(int opcao)throw(runtime_error);
};

class InterfaceQuiz:public Interface
{
private:
    static const int COMECARQUIZ;
    static const int CARREGAP;
    static const int SELP;
    static const int SELECIONARQUIZ;
    static const int SAIR;
    const static int RESPONDER;/*constantes*/
    const static int PULAR;
    const static int SAIRP;
    Quiz *quiz;
    void selecionarTopicosDisciplinas()throw(invalid_argument);
    void ComecarQuiz()throw(invalid_argument);/*comeca um quiz*/
    void CarregarQuiz()throw(invalid_argument);/*carrega um quiz existente*/
    void SelecionarPergunta()throw(invalid_argument); /*seleciona as perguntas para o usuario*/
    string SelecionarQuiz()throw(invalid_argument);
public:
    void MostrarOpcoes()throw(runtime_error);
    void executarOpcao(int opcao)throw(runtime_error);
};

#endif // CONTROLEINTERFACEUSUARIO_H
