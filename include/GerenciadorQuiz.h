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
    void ReorganizarPerArq(string editind,string novap);/*reorganiza o arquivo quiz com as perguntas*/
    string FormularPergArq(string form1,string form2,string form3); /*formula as perguntas no arquivo*/
    string BuscPer(string ind);/*busca a pergunta no arquivo atravez de um indice*/
    string data1,data2,data3;/*data1=index de uma pergunta data2=pergunta data3=resposta*/
    string arquivo,diretorio;/*nome do arquivo e nome do diretorio*/
public:
    GerQuiz(); /*construtor*/
    ~GerQuiz();
    void CriarQuiz() throw(invalid_argument);/*metodo que cria o arquivo contendo o quiz*/
    bool carregaQuiz();/*metodo que carrega o arquivo contendo o quiz*/
    void CarregaQuizEd()throw(invalid_argument);/*metodo que tenta carregar o quiz previamente setado*/
    void SelecionarArq()throw(invalid_argument);/*seleciona o arquivo contendo o quiz*/
    void ApagarQuiz()throw(invalid_argument); /*apaga o arquivo contendo o quiz*/
    void AddPerguntas()throw(invalid_argument); /*adiciona perguntas ao quiz setado em questão*/
    void EditPer()throw(invalid_argument);/*editor de perguntas no arquivo do quiz*/
    void DelPer()throw(invalid_argument);/*deleta perguntas do arquivo com quiz*/
    string getQuizFileName();/*retorna o nome do ultimo arquivo setado*/
    string getFolderFilesName(); /*retorna a pasta contendo os quizes*/
};

#endif // GERCARQUIZ_H
