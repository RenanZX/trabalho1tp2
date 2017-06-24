/////////////////////////////////////////
///     Descrição do arquivo:
///     @author     Renan Godoi de Medeiros
///     @since      ??/04/2017
///     @version    1.0
/////////////////////////////////////////

#ifndef CONTROLEINTERFACEUSUARIO_H
#define CONTROLEINTERFACEUSUARIO_H

#include "Interfaces.h"
#include "GerenciadorQuiz.h"
#include "Quiz.h"
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <stdexcept>

using namespace std;

class InterfaceUserGerQuiz:public InterfaceUsuarioGerQuiz/*interfaces que irão interagir com o usuario*/
{
private:

    //////////////////////////////////////////////////////////////////////////////////
    ///     Constantes para seleção de funções no programa
    ///     Cada constante representa uma opção durante a execução do programa,
    ///     que serão mostradas num menu
    //////////////////////////////////////////////////////////////////////////////////
    static const int ADICIONARP;/*constantes*/
    static const int DELELETARP;
    static const int EDITARP;
    static const int SAIRP;
    static const int SAIR;
    static const int SELQUIZ;
    static const int LOGQUIZ;
    static const int DELQUIZ;
    static const int EDITQUIZ;
    static const int CREATEQUIZ;
    static const string TABLETOPICS;
    static const string TABLEDISC;

    GerQuiz *gerente;
    string index;

    //////////////////////////////////////////////////////////////////////////////////
    ///     Edita um quiz, com adição, edição e exclusão de perguntas
    //////////////////////////////////////////////////////////////////////////////////
    void EditarQuiz()throw(runtime_error);
    
    //////////////////////////////////////////////////////////////////////////////////
    ///     @param topico Tópico a ser carregado
    ///     Carrega o tópico no arquivo-texto
    //////////////////////////////////////////////////////////////////////////////////
    void setTableTopics(string topico);
    

    //////////////////////////////////////////////////////////////////////////////////
    ///     @param disciplina Disciplina a ser carregada
    ///     Carrega a disciplina no arquivo-texto
    //////////////////////////////////////////////////////////////////////////////////
    void setTableDisc(string disciplina);
    
    //////////////////////////////////////////////////////////////////////////////////
    ///     @param topico Tópico a ser encontrado
    ///     Procura um tópico ou avisa se o tópico não existe
    //////////////////////////////////////////////////////////////////////////////////
    void findTableTopics(string topico)throw(invalid_argument);
    
    //////////////////////////////////////////////////////////////////////////////////
    ///     @param disciplina Disciplina a ser encontrada
    ///     Procura uma disciplina ou avisa que não existe
    //////////////////////////////////////////////////////////////////////////////////
    void findTableDisc(string disciplina)throw(invalid_argument);
    
    //////////////////////////////////////////////////////////////////////////////////
    ///     Adiciona tópicos às disciplinas
    //////////////////////////////////////////////////////////////////////////////////
    string AddTopDisc()throw(runtime_error);
    
    //////////////////////////////////////////////////////////////////////////////////
    ///     Prepara uma disciplina e tópico para editar uma pergunta, utilizando o
    ///     método acima, findTableDisc e findTableTopics
    //////////////////////////////////////////////////////////////////////////////////
    string EditarTopDisc()throw(runtime_error);
    
    //////////////////////////////////////////////////////////////////////////////////
    ///     Prepara uma disciplina e tópico para apagar uma pergunta
    //////////////////////////////////////////////////////////////////////////////////
    string ExcluirTopDisc()throw(runtime_error);

public:
    void executar()throw(runtime_error);
};

class InterfaceUserQuiz:public InterfaceUsuarioQuiz
{
private:
    static const int COMECARQUIZ;
    static const int CARREGAP;
    static const int SELP;
    static const int SAIR;
public:

    //////////////////////////////////////////////////////////////////////////////////
    ///     Começa o quiz, carrega ou seleciona perguntas, dependendo da
    ///     escolha do usuário
    //////////////////////////////////////////////////////////////////////////////////
    void executar()throw(runtime_error);
};
#endif // CONTROLEINTERFACEUSUARIO_H
