#ifndef GERCARQUIZ_H
#define GERCARQUIZ_H
#include <stdio.h>  /*bibliotecas*/
#include <stdlib.h>
#include <direct.h>
#include <stdexcept>
#include <windows.h>
#include <iostream>
#include "dirent.h"

/*verifica qual a versao do SO*/
#ifdef _WIN32
#define CLEAR "cls"
#elif LINUX
#define CLEAR "clear"
#endif

using namespace std;

class GerQuiz /*gerenciador de quiz*/
{
private:
    void PegaAttr(string dado);/*captura atributos de dados lidos do arquivo com quiz*/
    void AddPerguntas(); /*adiciona perguntas ao quiz setado em questão*/
    void ReorganizarPerArq(string editind,string novap);/*reorganiza o arquivo quiz com as perguntas*/
    string FormularPergArq(string form1,string form2,string form3); /*formula as perguntas no arquivo*/
    void EditPer();/*editor de perguntas no arquivo do quiz*/
    void DelPer();/*deleta perguntas do arquivo com quiz*/
    string BuscPer(string ind);/*busca a pergunta no arquivo atravez de um indice*/
    string data1,data2,data3;/*data1=index de uma pergunta data2=pergunta data3=resposta*/
    string arquivo,diretorio;/*nome do arquivo e nome do diretorio*/
    static const int ADICIONARP;/*constantes*/
    static const int DELELETARP;
    static const int EDITARP;
    static const int SAIRP;
    static const int SAIR;
    static const int SELQUIZ;
    static const int LOGQUIZ;
    static const int DELQUIZ;
    static const int EDITQUIZ;
    static const int CREATEQUIZ; /*metodos exclusivos e privados da classe*/
    void CriarQuiz();/*metodo que cria o arquivo contendo o quiz*/
    bool carregaQuiz();/*metodo que carrega o arquivo contendo o quiz*/
    void CarregaQuizEd();/*metodo que tenta carregar o quiz previamente setado*/
    void SelecionarArq();/*seleciona o arquivo contendo o quiz*/
    void EditarQuiz(); /*edita o arquivo contendo o quiz*/
    void ApagarQuiz(); /*apaga o arquivo contendo o quiz*/
public:
    GerQuiz(); /*construtor*/
    ~GerQuiz();
    void executar(); /*interface com o usuario*/
    string getQuizFileName();/*retorna o nome do ultimo arquivo setado*/
    string getFolderFilesName(); /*retorna a pasta contendo os quizes*/
};

#endif // GERCARQUIZ_H
