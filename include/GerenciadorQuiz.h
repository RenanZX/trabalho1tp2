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
    static const string TABLEDISCIPLINA;
    void setTableTopics(string topico); /*seta um topico na tabela de topicos*/
    void setTableDisc(string disciplina); /*seta uma disciplina na tabela de topicos*/
    void findTableTopics(string topico)throw(invalid_argument); /*busca um topico na tabela e manda uma excessao caso nao encontre*/
    void findTableDisc(string disciplina)throw(invalid_argument);/*encontra uma disciplina na tabela de disciplinas e manda uma excessao caso nao encontre*/
public:
    void showTableDisc(); /*metodo ao qual mostra o conteudo da tabela ao usuario*/
    void showTableTopics();
    string AddTopDisc()throw(runtime_error);
    string EditarTopDisc()throw(runtime_error);
    string ExcluirTopDisc()throw(runtime_error);
};

class GerQuiz /*gerenciador de quiz*/
{
private:
    TabelaDisciplinasTopicos tabela;
    void PegaAttributo(string dado);/*captura atributos de dados lidos do arquivo com quiz*/
    void ReorganizarPerguntaArquivo(string editind,string novap);/*reorganiza o arquivo quiz com as perguntas*/
    string FormularPerguntaImprimir(string pergunta);/*formula uma pergunta do arquivo para ser imprimida ao usuario*/
    string BuscarPergunta(string ind);/*busca a pergunta no arquivo atravez de um indice*/
    string data1,data2,data3;/*data1=index de uma pergunta data2=pergunta data3=resposta*/
    string arquivo,diretorio;/*nome do arquivo e nome do diretorio*/
    string indice; /*indice referente aos topicos e disciplinas relacionados*/
    int limiterespostas;
    string tabelarelationquiz;
    void mkdir(const char* nome);
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
