#ifndef QUIZ_H
#define QUIZ_H
#include "GerenciadorQuiz.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <ctype.h>
#include <vector>
/*#include <tempo.h>*/

using namespace std;

class Resposta
{
protected:
    int respostacorreta;
    std::vector<string> opcoes;
public:
    ~Resposta();
    void SetRespostasArquivo(string respostas);
    void MostrarOpcoes();
    bool VerificarRespostaCorreta(int resposta);
    bool CompararResposta(Resposta res);
    int getRespostaCorreta();
};

class Pergunta/*classe de perguntas*/
{
private:
    string index;/*indice da pergunta*/
    string strpergunta;/*pergunta*/
    Resposta resposta;
public:
    void SetPergunta(string ind,string per,Resposta *res) throw(invalid_argument); /*seta a pergunta*/
    string getIndex();/*retorna o indice da pergunta*/
    string getPergunta(); /*retorna a pergunta*/
    Resposta getResposta(); /*retorna a resposta da pergunta*/
    void ImprimirOpcoes();
    bool Comparar(Pergunta p); /*compara duas perguntas*/
    bool CompararResposta(int respostaverificar);
    int getRespostaCorreta();
};

class listaPergunta;

class ELEMENTO/*classe elemento*/
{
friend class listaPergunta;
protected:
    ~ELEMENTO();
    Pergunta* p;
    ELEMENTO* prox;
    ELEMENTO* ant;
};

class listaPergunta/*classe lista de perguntas*/
{
friend class Quiz; /*classe amiga da classe quiz*/
private:
    ELEMENTO *primeiro;
    ELEMENTO *ultimo;
protected:
    ~listaPergunta();/*destrutor da lista*/
    void SetInicio(Pergunta* p);/*insere no inicio da lista*/
    void SetFinal(Pergunta* p);/*insere no final*/
    Pergunta* getInicio();/*retorna um elemento no inicio da lista*/
    Pergunta* getFinal();/*retorna um elemento no final da lista*/
    bool EstaVazia();/*verifica se a lista esta vazia*/
    bool deletarElemento(string ind);/*deleta o elemento*/
    int ShowLista();/*mostra os elementos da lista*/
};

class Quiz
{
private:
    listaPergunta *l;/*ponteiro para a lista de perguntas*/
    const static int RESPONDER;/*constantes*/
    const static int PULAR;
    const static int SAIR;
    void OrganizarLista(string inds);/*organiza a lista apartir de uma string de indices*/
    string topicosdisciplinas;
    string file;
public:
    Quiz();/*construtor*/
    virtual ~Quiz();/*destrutor*/
    void ComecarQuiz()throw(invalid_argument);/*comeca um quiz*/
    void CarregarQuiz()throw(invalid_argument);/*carrega um quiz existente*/
    void SelecionarPergunta()throw(invalid_argument); /*seleciona as perguntas para o usuario*/
    void SetPergunta(string in,string p,Resposta r)throw(invalid_argument); /*seta as perguntas para o usuario*/
    void lerQuiz()throw(invalid_argument);/*lê o quiz*/
    void selectTopicosDisciplinas()throw(invalid_argument) /*seleciona o topico e a disciplina a qual o usuario ira responder*/;
};

#endif // QUIZ_H
