#ifndef QUIZ_H
#define QUIZ_H
#include <string>

using namespace std;

class Perg  /*classe pergunta,armazena uma string com uma pergunta*/
{
private:
    string p;
public:
    void setPerg(string x);
    string getPerg();
};

class Resp /*classe resposta,armazena uma string com uma resposta*/
{
private:
    string res;
public:
    void setResp(string x);
    string getResp();
};

class elemPR    /*elemento da lista de perguntas*/
{
    friend class listaPR;
private:
    ~elemPR();
    elemPR* proximo;
    Perg* p;    /*dados*/
    Resp* res;
    float index;  /*indice do elemento*/
};

class listaPR   /*lista de perguntas*/
{
    friend class Quiz;
private:
    elemPR* primeiro;   /*primeiro e ultimo elemento da lista*/
    elemPR* ultimo;
protected:
    void InsereInicio(Perg *per,Resp *respos,float ind);
    void InsereFinal(Perg *per,Resp *respos,float ind);/*insere elementos na lista*/
    Perg* getPerg(float ind);/*procura um elemento na lista com o indice da pergunta,e retorna a pergunta*/
    Resp* getResp(float ind);
    void DelElem(float ind);/*deleta um elemento*/
    ~listaPR();/*deleta a lista*/
};

class Quiz
{
private:
    listaPR* l;/*ponteiro para a lista*/
    string arq;
public:
    void EditPergResp(Perg novap,Resp novar,float ind);
    void deletarPerg(float ind);/*deleta a pergunta*/
    Quiz();/*cria o quiz*/
    ~Quiz();/*destroi o quiz*/
    void CarregarPerguntas();

};

#endif // QUIZ_H
