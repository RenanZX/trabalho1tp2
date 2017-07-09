#ifndef TESTES_H
#define TESTES_H

#include "GerenciadorQuiz.h"
#include "Quiz.h"
#include "iglo/iglo_alt.h"
using namespace igloo

class TesteArquivo
{
private:
    string nomearquivo;
    GerQuiz gerente;
    //GerenciaDisciplinas
    //GerenciadorTopico
    bool TesteArquivoQuiz();
public:
    TesteArquivo();
    void executar()throw(runtime_error);
};

class TesteModuloGerenteQuiz
{
private:
    GerQuiz *gerenteTeste;
    const static int SUCESSO;
    const static int FALHA;
    int estadoTeste;
    const static string CASOSUCESSO_BUSCARPERGUNTA;
    const static string CASOFALHA_BUSCARPERGUNTA;
    const static string SAIDASUCESSO_BUSCARPERGUNTA;
    const static string SAIDAFALHA_BUSCARPERGUNTA;
    void TesteIniciarBuscarPergunta();
    void TesteSucessoBuscarPergunta();
    void TesteFalhaBuscarPergunta();
    void TesteTerminarBuscarPergunta();
    int TesteExecutarBuscarPergunta();
    const static string CASOSUCESSO_SETINDEXTOPICDISC;
    const static string CASOFALHA_SETINDEXTOPICDISC;
    const static string SAIDASUCESSO_SETINDEXTOPICDISC;
    const static string SAIDAFALHA_SETINDEXTOPICDISC;
    void TesteIniciarSetTopicDisc();
    void TesteSucessoSetTopicDisc();
    void TesteFalhaSetTopicDisc();
    void TesteTerminarSetTopicDisc();
    int TesteExecutarSetTopicDisc();
    const static string CASOSUCESSO_EDITARPERGUNTA_INDICE;
    const static string CASOSUCESSO_EDITARPERGUNTA_PERGUNTA;
    const static string CASOFALHA_EDITARPERGUNTA_INDICE;
    const static string CASOFALHA_EDITARPERGUNTA_PERGUNTA;
    void TesteIniciarEditarPergunta();
    void TesteSucessoEditarPergunta();
    void TesteFalhaEditarPergunta();
    void TesteTerminarEditarPergunta();
    int TesteExecutarEditarPergunta();
    const static string CASOSUCESSO_SETPERGUNTAQUIZ_PERGUNTA;
    const static string CASOFALHA_SETPERGUNTAQUIZ_PERGUNTA;
    const static string SAIDAFALHA_SETPERGUNTAQUIZ_PERGUNTA;
    const static string SAIDAFALHA_SETPERGUNTAQUIZ_ARQUIVO;
    void TesteIniciarSetPerguntaQuiz();
    void TesteSucessoSetPerguntaQuiz();
    void TesteFalhaSetPerguntaQuiz();
    void TesteTerminarSetPerguntaQuiz();
    int TesteExecutarSetPerguntaQuiz();
    const static string CASOSUCESSO_CRIARQUIZ;
    const static string CASOFALHA_CRIARQUIZ;
    const static string SAIDAFALHA_CRIARQUIZ;
    void TesteIniciarSetCriarQuiz();
    void TesteSucessoCriarQuiz();
    void TesteFalhaCriarQuiz();
    void TesteTerminarCriarQuiz();
    int TesteExecutarCriarQuiz();
    const static string CASOSUCESSO_SETQUIZ;
    const static string CASOFALHA_SETQUIZ;
    const static string SAIDAFALHA_SETQUIZ;
    void TesteIniciarSetSetQuiz();
    void TesteSucessoSetQuiz();
    void TesteFalhaSetQuiz();
    void TesteTerminarSetQuiz();
    int TesteExecutarSetQuiz();
    const static string CASOSUCESSO_DELETARPERGUNTAQUIZ;
    const static string CASOFALHA_DELETARPERGUNTAQUIZ;
    const static string SAIDAFALHA_DELETARPERGUNTAQUIZ;
    const static string SAIDAFALHA_DELETARPERGUNTAQUIZ_ARQUIVO;
    void TesteIniciarSetDeletarPerguntaQuiz();
    void TesteSucessoDeletarPerguntaQuiz();
    void TesteFalhaDeletarPerguntaQuiz();
    void TesteTerminarDeletarPerguntaQuiz();
    int TesteExecutarDeletarPerguntaQuiz();
    const static string CASOSUCESSO_DELETARQUIZSETADO;
    const static string CASOFALHA_DELETARQUIZSETADO;
    const static string SAIDAFALHA_DELETARQUIZSETADO;
    const static string SAIDAFALHA_DELETARQUIZSETADO_ARQUIVO;
    void TesteIniciarSetDeletarQuizSetado();
    void TesteSucessoDeletarQuizSetado();
    void TesteFalhaDeletarQuizSetado();
    void TesteTerminarDeletarQuizSetado();
    int TesteExecutarDeletarQuizSetado();
public:
    int executar();
};

class TesteModuloQuiz
{
private:
    /*void SelecionarPerguntas(string indices)throw(invalid_argument);
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
    void lerQuiz(string nomequiz)throw(invalid_argument);*/

    Quiz *quiz;
    const static string CASOSUCESSO_SELECIONARPERGUNTAS;
    const static string CASOFALHA_SELECIONARPERGUNTAS;
    void TesteIniciarSelecionarPerguntas();
    void TesteSucessoSelecionarPerguntas();
    void TesteFalhaSelecionarPerguntas();
    void TesteTerminarSelecionarPerguntas();
    int TesteExecutarSelecionarPerguntas();


    const static string CASOSUCESSO_SELECIONARDISCIPLINAS;
    const static string CASOFALHA_SELECIONARDISCIPLINAS;
    void TesteIniciarSelecionarDisciplinas();
    void TesteSucessoSelecionarDisciplinas();
    void TesteFalhaSelecionarDisciplinas();
    void TesteTerminarSelecionarDisciplinas();
    int TesteExecutarSelecionarDisciplinas();


    const static string CASOSUCESSO_SELECIONARTOPICO;
    const static string CASOFALHA_SELECIONARTOPICO;
    void TesteIniciarSelecionarTopico();
    void TesteSucessoSelecionarTopico();
    void TesteFalhaSelecionarTopico();
    void TesteTerminarSelecionarTopico();
    int TesteExecutarSelecionarTopico();


    const static Pergunta* CASOSUCESSO_QUIZPULARPERGUNTA;
    const static Pergunta* CASOFALHA_QUIZPULARPERGUNTA;
    void TesteIniciarQuizPularPergunta();
    void TesteSucessoQuizPularPergunta();
    void TesteFalhaQuizPularPergunta();
    void TesteTerminarQuizPularPergunta();
    int TesteExecutarQuizPularPergunta();


    const static Pergunta* CASOSUCESSO_QUIZRESPONDERPERGUNTA_PERGUNTA;
    const static int CASOSUCESSO_QUIZRESPONDERPERGUNTA_RESPOSTA;
    const static Pergunta* CASOFALHA_QUIZRESPONDERPERGUNTA_PERGUNTA;
    const static int CASOFALHA_QUIZRESPONDERPERGUNTA_RESPOSTA;
    void TesteIniciarQuizResponderPergunta();
    void TesteSucessoQuizResponderPergunta();
    void TesteFalhaQuizResponderPergunta();
    void TesteTerminarQuizResponderPergunta();
    int TesteExecutarQuizResponderPergunta();

    const static string CASOSUCESSO_LERQUIZ;
    const static string CASOFALHA_LERQUIZ;

public:
    void executar()throw(runtime_error);
};

//a implementar
class TesteModuloGerenteDisciplina
{
private:

public:
    void executar()throw(runtime_error);
};

class TesteModuloUsuario
{
private:

public:
    void executar()throw(runtime_error);
};


#endif // TESTES_H
