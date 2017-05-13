#include "GerenciadorQuiz.h"

const int GerQuiz::ADICIONARP = 1;  /*constantes*/
const int GerQuiz::EDITARP = 2;
const int GerQuiz::DELELETARP = 3;
const int GerQuiz::LOGQUIZ = 1;
const int GerQuiz::EDITQUIZ = 2;
const int GerQuiz::DELQUIZ = 3;
const int GerQuiz::SAIR = 4;

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

bool GerQuiz::carregaQuiz() /*carrega o arquivo com o quiz*/
{
    string str;
    char read[100];
    bool tr = true;
    FILE* f = fopen(arquivo.c_str(),"rt");/*faz a leitura do arquivo*/

    fseek(f,0,SEEK_END);
    int tam = ftell(f);
    rewind(f);
    if((f!=NULL)&&(tam>0)){
        cout << "Perguntas" << endl;
        while(fgets(read,sizeof(read),f)){
            str = read;
            PegaAttr(str);
            cout << dat1 << ". " << dat2 << "   Res.:" << dat3 << endl;
        }
    }else{
        fclose(f);/*caso o arquivo nao exista ele e fechado e aberto novamente para escrita*/
        f = fopen(arquivo.c_str(),"wt");/*e assim e criado um novo arquivo no diretorio do usuario*/
        cout << "nao existem perguntas" << endl;
        tr = false;
    }
    fclose(f);
    system("pause");
    return tr;
}

void GerQuiz::AddPerguntas()/*adiciona perguntas ao arquivo com quiz*/
{
    string saida,str;
    char ver;

    system(CLEAR);
    carregaQuiz();
    double menor = atof(dat1.c_str());
    double maior;
    FILE *f = fopen(arquivo.c_str(),"r+");

    while((ver!='N')&&(ver!='n')){
        cout << "Digite o numero da pergunta que deseja adicionar:" << endl;
        getline(cin,str,'\n');
        maior = atof(str.c_str());

        if((maior > 0)&&(maior > menor)){
            saida = str;
            saida.append("|");
            cout << "Digite a pergunta que deseja adicionar:" << endl;
            getline(cin,str,'\n');
            saida.append(str);
            saida.append("|");
            cout << "Digite a resposta para essa pergunta:" << endl;
            getline(cin,str,'\n');
            saida.append(str);
            saida.append("|\n");
            cout << "Deseja adicionar mais perguntas?(S/N)" << endl;
            cin >> ver;
            cin.ignore(1000,'\n');
            fseek(f,0,SEEK_END);
            fputs(saida.c_str(),f);
         }else{
            cout << "dados inseridos invalidos digite novamente" << endl;
        }
    }
    fclose(f);
}

void GerQuiz::ReorganizarPerArq(string editind,string novap)/*reorganiza o arquivo com o quiz*/
{
    FILE *f = fopen(arquivo.c_str(),"rt");
    FILE *f2 = fopen((dir+"/novo").c_str(),"w");
    char linha[100];
    string str,compind;
    string antind,name;

    if(novap!=""){
        while(fgets(linha,sizeof(linha),f)){
            str = linha;
            compind = str.substr(0,str.find("|"));
            if(editind == compind){
                fputs(novap.c_str(),f2);
            }else{
                fputs(str.c_str(),f2);
            }
        }
    }else{
        while(fgets(linha,sizeof(linha),f)){
            str = linha;
            compind = str.substr(0,str.find("|"));
            if(editind == compind){
                antind = editind;
            }else if(antind!=""){
                str = str.substr(str.find("|"),str.length());
                antind.append(str);
                str = antind;
                antind = compind;
                fputs(str.c_str(),f2);
            }
        }
    }

    fclose(f);
    fclose(f2);
    remove(arquivo.c_str());
    rename((dir+"/novo").c_str(),arquivo.c_str());
}

string GerQuiz::FormularPergArq(string n1,string n2,string n3)
{
    n1.append("|");
    n2.append("|");
    n3.append("|\n");
    n2.append(n3);
    n1.append(n2);
    return n1;
}

/*funçoes providas da interface com o usuario pelo gerenciador*/
void GerQuiz::EditPer()
{
    string data;
    string ind,p,r;
    bool tr;

    system(CLEAR);

    tr = carregaQuiz();
    if(tr!=false){
        cout << "Indique o indice da pergunta que deseja editar:" << endl;
        getline(cin,data,'\n');
        data = BuscPer(data);
        if(data == ""){
            cout << "pergunta nao existe" << endl;
        }else{
            system(CLEAR);
            cout << data << endl;
            ind = data.substr(0,data.find("|"));
            cout << "Digite sua nova pergunta:" << endl;
            getline(cin,p,'\n');
            cout << "Digite sua nova resposta:" << endl;
            getline(cin,r,'\n');

            p = FormularPergArq(ind,p,r);
            ReorganizarPerArq(ind,p);
        }
    }
}

void GerQuiz::DelPer()
{
    system(CLEAR);
    carregaQuiz();
    string indstr;

    cout << "Digite o indice da pergunta que deseja excluir:" << endl;
    cin >> indstr;
    if((atof(indstr.c_str()) > 0)&&(atof(indstr.c_str()) <= atof(dat1.c_str()))){
        cout << "Deletando Pergunta..." << endl;
        ReorganizarPerArq(indstr,"");
        cout << "Pergunta deletada com sucesso!" << endl;
    }else{
        cout << "Pergunta inexistente" << endl;
    }
    system("pause");
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
    dir = "tkq";
    arquivo = dir+"/Quiz.bin";/*seta o nome do arquivo contendo o quiz junto ao seu destino*/
}

GerQuiz::~GerQuiz()
{

}

void GerQuiz::executar()/*gerenciador de interface com o usuario*/
{
    bool tr = true;
    int opt;
    mkdir(dir.c_str()); /*cria um diretorio na raiz do usuario*/

    while(tr){
        system(CLEAR);

        cout << "Gerenciador de Quiz" << endl;/*opcoes mostradas ao usuario*/
        cout << LOGQUIZ << ".Carregar Quiz" << endl;
        cout << EDITQUIZ << ".Editar Quiz" << endl;
        cout << DELQUIZ << ".Apagar Quiz" << endl;
        cout << SAIR << ".Sair" << endl;
        cout << "Escolha a opcao:" << endl;
        cin  >> opt;
        getchar();

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
        getchar();

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
        cin.ignore(1000,'\n');
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
        dat1 = "";
        dat2 = "";
        dat3 = "";
    }
}

Quiz* GerQuiz::getQuiz()    /*retorna um quiz de um arquivo no disco*/
{
    builderQuiz build;
    Quiz* q = build.construir();
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

void GerQuiz::getQuiz(Quiz *q)    /*retorna um quiz de um arquivo no disco*/
{
    char arr[100];
    FILE *f = fopen(arquivo.c_str(),"rt");
    try{
        if(f!=NULL){
            while(fgets(arr,sizeof(arr),f)){
                PegaAttr(arr);
                q->SetPerg(dat1,dat2,dat3);
            }
            fclose(f);
        }else{
            fclose(f);
        }
    }catch(runtime_error &e){
        fclose(f);
    }
}
