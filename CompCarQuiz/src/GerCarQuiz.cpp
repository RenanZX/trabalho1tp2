#include "GerCarQuiz.h"

const int GerQuiz::ADICIONARP = 1;
const int GerQuiz::EDITARP = 2;
const int GerQuiz::DELELETARP = 3;
const int GerQuiz::BUSCARP = 4;
const int GerQuiz::LOGQUIZ = 1;
const int GerQuiz::EDITQUIZ = 2;
const int GerQuiz::DELQUIZ = 3;
const int GerQuiz::SAIR = 5;

void GerQuiz::PegaAttr(string dado)
{
    int pos = 0;

    dat1 = dado.substr(0,dado.find("|"));
    pos = dado.find("|")+1;
    dado = dado.substr(pos,dado.length());
    dat2 = dado.substr(0,dado.find("|"));
    pos = dado.find("|")+1;
    dado = dado.substr(pos,dado.length());
    dat3 = dado.substr(0,dado.find("|"));
}

void GerQuiz::carregaQuiz()
{
    string str;
    char ar[100];
    FILE* f = fopen("Quiz.txt","wt");

    if(f!=NULL){
        while(!str.empty()){
            str = fgets(ar,100,f);
            PegaAttr(str);
            cout << dat1 << dat2 << dat3 << endl;
        }
    }else{
        cout << "nao existem perguntas" << endl;
    }
    fclose(f);
}

void GerQuiz::AddPerguntas()
{

}

void GerQuiz::EditPer()
{

}

void GerQuiz::DelPer()
{

}

void GerQuiz::BuscPer()
{

}

void GerQuiz::GerIU()
{
    bool tr = true;
    int opt;

    while(tr){
        system(CLEAR);

        cout << "Gerenciador de Quiz" << endl;
        cout << LOGQUIZ << ".Carregar Quiz" << endl;
        cout << EDITQUIZ << ".Editar Quiz" << endl;
        cout << DELQUIZ << ".Apagar Quiz" << endl;
        cout << SAIR << ".Sair" << endl;
        cout << "Escolha a opcao:" << endl;
        cin  >> opt;

        switch(opt){
            case LOGQUIZ:
                carregaQuiz();
                break;
            case EDITQUIZ:
                EditarQuiz();
                break;
            case DELQUIZ:
                ApagarQuiz();
                break;
            case SAIR:
                tr = false;
                break;
            default:
                break;
        }
    }
}

void GerQuiz::EditarQuiz()
{
    int opt;
    bool tr = true;

    while(tr){
        system(CLEAR);

        cout << "Gerenciador de Quiz" << endl;
        cout << ADICIONARP << ".Adicionar Nova(s) Pergunta(s)" << endl;
        cout << EDITARP << ".Editar Pergunta(s)" << endl;
        cout << DELELETARP << ".Excluir Pergunta(s)" << endl;
        cout << BUSCARP << ".Buscar Pergunta(s)" << endl;
        cout << SAIR << ".Sair" << endl;
        cout << "Escolha uma opcao" << endl;
        cin >> opt;

        switch(opt)
        {
            case ADICIONARP:
                AddPerguntas();
                break;
            case EDITARP:
                EditPer();
                break;
            case DELELETARP:
                DelPer();
                break;
            case BUSCARP:
                BuscPer();
                break;
            case SAIR:
                tr = false;
                break;
            default:
                break;
        }
    }

}

void GerQuiz::ApagarQuiz()
{
    char ch;
    bool existe = false;

    system(CLEAR);
    while((ch!='S')&&(ch!='s')&&(ch!='N')&&(ch!='n')){
        cout << "Voce realmente deseja apagar o quiz?(S/N)" << endl;
        cin >> ch;
    }
    if((ch=='s')||(ch=='S')){
        FILE* f = fopen("Quiz.txt","rt");
        if(f!=NULL){
            existe = true;
        }
        fclose(f);
        if(existe){
            remove("Quiz.txt");
        }
    }
}
