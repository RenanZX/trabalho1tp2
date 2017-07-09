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
#ifdef __WIN32__
#define PAUSE system("pause")
#endif // __WIN32__
#ifdef __linux__
#define PAUSE cout << "pressione enter para continuar..." << endl;getchar();
#endif

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
    int pontuacao;
public:
    void SetPergunta(string ind,string per,Resposta *res) throw(invalid_argument); /*seta a pergunta*/
    void SetPontuacao(int pontos);
    string getIndex();/*retorna o indice da pergunta*/
    string getPergunta(); /*retorna a pergunta*/
    Resposta getResposta(); /*retorna a resposta da pergunta*/
    void ImprimirOpcoes();
    bool Comparar(Pergunta p); /*compara duas perguntas*/
    bool CompararResposta(int respostaverificar);
    int getRespostaCorreta();
    int getPontuacao();
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
    void OrganizarLista(string inds);/*organiza a lista apartir de uma string de indices*/
    string topicosdisciplinas;
    string file;
    int acertos;
    int erros;
    int pontuacao;
    std::vector<string> relatorioquestoes;
    void SetPergunta(string in,string p,Resposta r,int pontuacao)throw(invalid_argument); /*seta as perguntas para o usuario*/
public:
    Quiz();/*construtor*/
    virtual ~Quiz();/*destrutor*/
    void SelecionarPerguntas(string indices)throw(invalid_argument);
    void SelecionarDisciplina(string Disciplina)throw(invalid_argument);
    void SelecionarTopico(string Topico)throw(invalid_argument);
    int ImprimirPerguntas()throw(invalid_argument);
    bool QuizTerminou();
    Pergunta* QuizgetPergunta();
    void QuizPularPergunta(Pergunta *p)throw(invalid_argument);
    void QuizResponderPergunta(Pergunta *p,int resposta)throw(invalid_argument);
    std::vector<string> QuizgetRelatorio();
    int getNumeroAcertos();
    int getNumeroErros();
    int getPontosUsuario();
    void lerQuiz(string nomequiz)throw(invalid_argument);/*lê o quiz*/
};

#endif // QUIZ_H
