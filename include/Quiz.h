#ifndef QUIZ_H
#define QUIZ_H
#include "GerenciadorQuiz.h"
#include <iostream>
#include <ctype.h>

using namespace std;

class Pergunta/*classe de perguntas*/
{
private:
    string index;/*indice da pergunta*/
    string p;/*pergunta*/
    string r; /*resposta*/
public:
    void SetPergunta(string ind,string per,string res) throw(invalid_argument); /*seta a pergunta*/
    string getIndex();/*retorna o indice da pergunta*/
    string getPergunta(); /*retorna a pergunta*/
    string getResposta(); /*retorna a resposta da pergunta*/
    bool Comparar(Pergunta p); /*compara duas perguntas*/
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
    const static int RESPONDER;
    const static int PULAR;
    const static int SAIR;
    void OrganizarLista(string inds);/*organiza a lista apartir de uma string de indices*/
    void lerQuiz()throw(invalid_argument);/*l� o quiz*/
public:
    Quiz();
    virtual ~Quiz();
    void ComecarQuiz()throw(invalid_argument);/*comeca um quiz*/
    void CarregarQuiz()throw(invalid_argument);/*carrega um quiz existente*/
    void SelecionarPergunta()throw(invalid_argument); /*seleciona as perguntas para o usuario*/
    void SetPergunta(string in,string p,string r)throw(invalid_argument); /*seta as perguntas para o usuario*/
};

#endif // QUIZ_H
