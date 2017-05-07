#include "GerCarQuiz.h"

const int GerQuiz::ADICIONARP = 1;  /*constantes*/
const int GerQuiz::EDITARP = 2;
const int GerQuiz::DELELETARP = 3;
const int GerQuiz::LOGQUIZ = 1;
const int GerQuiz::EDITQUIZ = 2;
const int GerQuiz::DELQUIZ = 3;
const int GerQuiz::SAIR = 5;

void GerQuiz::PegaAttr(string dado) /*pega atributos da string lida do arquivo*/
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

void GerQuiz::carregaQuiz() /*carrega o arquivo com o quiz*/
{
    string str;
    char read[100];
    FILE* f = fopen(arquivo.c_str(),"rt");/*faz a leitura do arquivo*/

    if(f!=NULL){
        while(fgets(read,sizeof(read),f)){
            str = read;
            PegaAttr(str);
            cout << dat1 << " " << dat2 << " " << dat3 << endl;
        }
    }else{
        fclose(f);/*caso o arquivo nao exista ele e fechado e aberto novamente para escrita*/
        f = fopen(arquivo.c_str(),"wt");/*e assim e criado um novo arquivo no diretorio do usuario*/
        cout << "nao existem perguntas" << endl;
    }
    fclose(f);
}

void GerQuiz::AddPerguntas()/*adiciona perguntas ao arquivo com quiz*/
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

void GerQuiz::ReorganizarPerArq(string ind,string p,string r)/*reorganiza o arquivo com o quiz*/
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
/*funçoes providas da interface com o usuario pelo gerenciador*/
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
/*construtor*/
GerQuiz::GerQuiz()
{
    arquivo = "tkq/Quiz.bin";/*seta o nome do arquivo contendo o quiz junto ao seu destino*/
}

GerQuiz::~GerQuiz()
{

}

void GerQuiz::GerIU()/*gerenciador de interface com o usuario*/
{
    bool tr = true;
    int opt;
    mkdir("tkq"); /*cria um diretorio na raiz do usuario*/

    while(tr){
        system(CLEAR);

        cout << "Gerenciador de Quiz" << endl;/*opcoes mostradas ao usuario*/
        cout << LOGQUIZ << ".Carregar Quiz" << endl;
        cout << EDITQUIZ << ".Editar Quiz" << endl;
        cout << DELQUIZ << ".Apagar Quiz" << endl;
        cout << SAIR << ".Sair" << endl;
        cout << "Escolha a opcao:" << endl;
        cin  >> opt;

        switch(opt){/*opcoes do usuario*/
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

void GerQuiz::ApagarQuiz()/*apaga um arquivo contendo um quiz ja existente*/
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

Quiz* GerQuiz::getQuiz()
{
    Quiz* q = new StubQuiz();
    char arr[100];
    FILE *f = fopen(arquivo.c_str(),"rt");
    try{
        if(f!=NULL){
            while(fgets(arr,sizeof(arr),f)){
                PegaAttr(arr);
                q->SetPerg(dat1,dat2,dat3);
            }
            fclose(f);
            return q;
        }else{
            fclose(f);
        }
    }catch(runtime_error &e){
        fclose(f);
    }
    return q;
}
