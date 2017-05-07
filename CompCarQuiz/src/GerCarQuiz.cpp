#include "GerCarQuiz.h"

const int GerQuiz::ADICIONARP = 1;
const int GerQuiz::EDITARP = 2;
const int GerQuiz::DELELETARP = 3;
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
    char read[100];
    FILE* f = fopen(arquivo.c_str(),"rt");

    if(f!=NULL){
        while(fgets(read,sizeof(read),f)){
            str = read;
            PegaAttr(str);
            cout << dat1 << " " << dat2 << " " << dat3 << endl;
        }
    }else{
        fclose(f);
        f = fopen(arquivo.c_str(),"wt");
        cout << "nao existem perguntas" << endl;
    }
    fclose(f);
}

void GerQuiz::AddPerguntas()
{
    string saida,str;
    char ver;

    system(CLEAR);
    cout << "Perguntas" << endl;
    carregaQuiz();
    double menor = atof(dat1.c_str());
    FILE *f = fopen(arquivo.c_str(),"wt");

    while((ver!='N')&&(ver!='n')){
        cout << "Digite o numero da pergunta que deseja adicionar:" << endl;
        cin >> str;
        double maior = atof(str.c_str());

        if((maior > 0)&&(maior > menor)){
            saida = str;
            saida.append("|");
            cout << "Digite a pergunta que deseja adicionar:" << endl;
            cin >> str;
            saida = str;
            saida.append("|");
            cout << "Digite a resposta para essa pergunta:" << endl;
            cin >> str;
            saida = str;
            saida.append("|\n");
            cout << "Deseja adicionar mais perguntas?(S/N)" << endl;
            cin >> ver;
            fputs(saida.c_str(),f);
         }else{
            cout << "dados inseridos invalidos digite novamente" << endl;
        }
    }
    fclose(f);
}

void GerQuiz::ReorganizarPerArq(string ind,string p,string r)
{
    FILE *f = fopen(arquivo.c_str(),"rt");
    FILE *f2 = fopen("novo","w");
    char linha[100];
    string str,compind,repl;
    repl = ind;
    repl.append(p);
    repl.append(r);
    repl.append("\n");

    while(fgets(linha,sizeof(linha),f)){
        str = linha;
        compind = str.substr(0,str.find("|"));
        if(ind == compind){
            fputs(repl.c_str(),f2);
        }else{
            fputs(str.c_str(),f2);
        }
    }

    fclose(f);
    fclose(f2);
    remove(arquivo.c_str());
    rename("novo",arquivo.c_str());
}

void GerQuiz::EditPer()
{
    string data;
    char ch;
    string ind,p,r;

    system(CLEAR);
    carregaQuiz();

    cout << "Indique o indice da pergunta que deseja editar:" << endl;
    cin >> data;
    data = BuscPer(data);
    if(data == ""){
        cout << "pergunta nao existe" << endl;
    }else{
        system(CLEAR);
        cout << data << endl;
        ind = data.substr(0,data.find("|"));
        cout << "Digite sua nova pergunta:" << endl;
        cin >> p;
        cout << "Digite sua nova resposta:" << endl;
        cin >> r;
        while((ch!='s')&&(ch!='S')&&(ch!='N')&&(ch!='n')){
            cout << "deseja alterar o indice da pergunta?(S/N)" << endl;
            cin >> ch;
        }
        if((ch=='s')||(ch=='S')){
            cout << "Digite um novo indice:" << endl;
            cin >> ind;
        }
        ReorganizarPerArq(ind,p,r);
    }
}

void GerQuiz::DelPer()
{

}

string GerQuiz::BuscPer(string ind)
{
    char read[100];
    bool achou = false;
    string ask,comp;
    FILE *f = fopen(arquivo.c_str(),"rt");

    if(f!=NULL){
        while((fgets(read,sizeof(read),f))&&(achou!=true)){
            ask = read;
            comp = ask.substr(0,ask.find("|"));
            if(comp == ind){
                achou = true;
            }
        }
        fclose(f);
        return ask;
    }
    return NULL;
}

GerQuiz::GerQuiz()
{
    mkdir("tkq");
    arquivo = "tkq/Quiz.bin";
}

GerQuiz::~GerQuiz()
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
        FILE* f = fopen(arquivo.c_str(),"rt");
        if(f!=NULL){
            existe = true;
        }
        fclose(f);
        if(existe){
            remove(arquivo.c_str());
        }
    }
}
