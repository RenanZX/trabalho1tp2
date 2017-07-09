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
#define root "\\."
#define CLEAR "cls"
#define PAUSE system("pause")
#endif // __WIN32__
#ifdef __linux__
#include <sys/types.h>
#define root "./"
#define CLEAR "clear"
#define PAUSE cout << "pressione enter para continuar..." << endl;getchar();
#endif

using namespace std;

class TabelaDisciplinasTopicos
{
private:
    string index;
    static const string TABLETOPICOS;
    static const string TABLEDISCIPLINAS;
public:
    void showTableDisc(); /*metodo ao qual mostra o conteudo da tabela ao usuario*/
    void showTableTopics();
    void setTableTopics(string topico); /*seta um topico na tabela de topicos*/
    void setTableDisc(string disciplina); /*seta uma disciplina na tabela de topicos*/
    void findTableTopics(string topico)throw(invalid_argument); /*busca um topico na tabela e manda uma excessao caso nao encontre*/
    void findTableDisc(string disciplina)throw(invalid_argument);/*encontra uma disciplina na tabela de disciplinas e manda uma excessao caso nao encontre*/
    string getGeneratedIndex();
};

class GerQuiz /*gerenciador de quiz*/
{
private:
    TabelaDisciplinasTopicos tabela;
    void ReorganizarPerguntaArquivo(string editind,string novap);/*reorganiza o arquivo quiz com as perguntas*/
    string arquivo,diretorio;/*nome do arquivo e nome do diretorio*/
    string indice; /*indice referente aos topicos e disciplinas relacionados*/
    int limiterespostas;
    string tabelarelationquiz;
    void mkdir(const char* nome);
public:
    GerQuiz(); /*construtor*/
    ~GerQuiz();
    string BuscarPergunta(string ind);/*busca a pergunta no arquivo atravez de um indice*/
    void SetIndexTopicDisc(string index);
    void EditarPergunta(string index,string pergunta);
    void SetPerguntaQuiz(string perguntarquivo)throw(invalid_argument); /*seta uma pergunta no formato do arquivo*/
    void CriaQuiz(string nomequiz)throw(invalid_argument);
    void SetQuiz(string nomequiz)throw(invalid_argument);
    string getPerguntaQuiz(string index);
    void DeletarPerguntaQuiz(string index)throw(invalid_argument);
    void DeletarQuizSetado()throw(invalid_argument);
    string getQuizFileNameSeted();/*retorna o destino juntamente ao nome do ultimo arquivo setado*/
    string getFolderFilesName(); /*retorna a pasta contendo os quizes*/
    string getQuizesFilesName(); /*retorna uma lista com todos os nomes dos quizes dentro de uma pasta*/
};

#endif // GERCARQUIZ_H
