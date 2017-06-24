#ifndef GERCARQUIZ_H
#define GERCARQUIZ_H
#include <stdio.h>  /*bibliotecas*/
#include <stdlib.h>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include "dirent.h"

/*verifica qual a versao do SO*/
#ifdef __WIN32__
#include <windows.h>
#include <direct.h>
#define CLEAR "cls"
#elif __linux__
#define CLEAR "clear"
#endif

using namespace std;

class GerQuiz /*gerenciador de quiz*/
{
private:
    void PegaAttributo(string dado);/*captura atributos de dados lidos do arquivo com quiz*/
    void ReorganizarPerguntaArquivo(string editind,string novap);/*reorganiza o arquivo quiz com as perguntas*/
    string FormularPerguntaImprimir(string pergunta);/*formula uma pergunta do arquivo para ser imprimida ao usuario*/
    string BuscarPergunta(string ind);/*busca a pergunta no arquivo atravez de um indice*/
    string data1,data2,data3;/*data1=index de uma pergunta data2=pergunta data3=resposta*/
    string arquivo,diretorio;/*nome do arquivo e nome do diretorio*/
    string indice; /*indice referente aos topicos e disciplinas relacionados*/
    int limiterespostas;
    string tabelarelationquiz;
  public:
    GerQuiz(); /*construtor*/
    ~GerQuiz();
    void SetIndexTopicDisc(string index);
    void CriarQuiz() throw(invalid_argument);/*metodo que cria o arquivo contendo o quiz*/
    bool carregaQuiz();/*metodo que carrega o arquivo contendo o quiz*/
    void CarregaQuizEditar()throw(invalid_argument);/*metodo que tenta carregar o quiz previamente setado*/
    void SelecionarArquivo()throw(invalid_argument);/*seleciona o arquivo contendo o quiz*/
    void ApagarQuiz()throw(invalid_argument); /*apaga o arquivo contendo o quiz*/
    void AdicionarPerguntas()throw(invalid_argument); /*adiciona perguntas ao quiz setado em questão*/
    void EditarPergunta()throw(invalid_argument);/*editor de perguntas no arquivo do quiz*/
    void DeletarPergunta()throw(invalid_argument);/*deleta perguntas do arquivo com quiz*/
    string getQuizFileName();/*retorna o destino juntamente ao nome do ultimo arquivo setado*/
    string getFolderFilesName(); /*retorna a pasta contendo os quizes*/
    string getQuizesFilesName(); /*retorna uma lista com todos os nomes dos quizes dentro de uma pasta*/
};

#endif // GERCARQUIZ_H
