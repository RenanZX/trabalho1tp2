#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

class Usuario{
private:
    string nome;
    string login;
    string senha;
    enum PERFIL {admin, estudante} perfil;
    bool logado;

    typedef struct caderno{
        int ID;
        caderno* prox;
    } caderno c;

public:
    string getNome();
    void setNome(string);
    string getLogin();
    void setLogin(string);
    string getSenha();
    void setSenha(string);
    int getPerfil();
    void setPerfil(char);

    Usuario();
    Usuario(string, string, string, int);


    string listarDisciplinas();

    void adicionarDisciplina(int);

    void carregarDisciplinas(string);

    void criarDisciplina (string, GerenciaDisciplinas);

    void alterarDisciplina (string);//, listaTopicos*, listaQuizzes*);

    void deletarDisciplina (string, GerenciaDisciplinas);


    void criarQuiz (string, GerQuiz);

    void alterarQuiz (string, GerQuiz);

    void deletarQuiz (string, GerQuiz);
};
