#include "GerenciadorQuiz.h"

const int GerQuiz::ADICIONARP = 1;  /*constantes*/
const int GerQuiz::EDITARP = 2;
const int GerQuiz::DELELETARP = 3;
const int GerQuiz::SAIRP = 4;
const int GerQuiz::CREATEQUIZ = 1;
const int GerQuiz::LOGQUIZ = 2;
const int GerQuiz::EDITQUIZ = 4;
const int GerQuiz::SELQUIZ = 3;
const int GerQuiz::DELQUIZ = 5;
const int GerQuiz::SAIR = 6;

void GerQuiz::PegaAttr(string dado) /*pega atributos da string lida do arquivo*/
{
    int pos = 0;

    data1 = dado.substr(0,dado.find("|")); /*indice da questao*/
    pos = dado.find("|")+1;
    dado = dado.substr(pos,dado.length());
    data2 = dado.substr(0,dado.find("|"));/*pergunta*/
    pos = dado.find("|")+1;
    dado = dado.substr(pos,dado.length());
    data3 = dado.substr(0,dado.find("|")); /*resposta*/
}

bool GerQuiz::carregaQuiz() /*carrega o arquivo com o quiz*/
{
    string strread;/*string a ser lida*/
    char read[100];
    bool carregou = true;/*verifica se carregou o arquivo ou nao*/
    FILE* f = fopen(arquivo.c_str(),"rt");/*faz a leitura do arquivo*/

    fseek(f,0,SEEK_END);
    int tam = ftell(f);
    rewind(f);
    if((f!=NULL)&&(tam>0)){
        cout << "Perguntas" << endl;
        while(fgets(read,sizeof(read),f)){
            strread = read;
            PegaAttr(strread);
            cout << data1 << ". " << data2 << "   Res.:" << data3 << endl;
        }
    }else{
        cout << "nao existem perguntas" << endl;/*printa a mensagem para o usuario*/
        carregou = false;/*nao foi possivel carregar o arquivo logo carregou recebe false*/
    }
    fclose(f);
    system("pause");
    return carregou;
}

void GerQuiz::CarregaQuizEd()   /*verifica se o arquivo com o quiz esta selecionado para as devidas modificacoes do usuario*/
{
    if(arquivo!=""){    /*caso o arquivo do quiz tenha sido setado,o quiz e carregado na tela do usuario*/
        carregaQuiz();
        return;
    }else{  /*caso contrario e mostrada uma mensagem de erro*/
        cout << "selecione o quiz,antes de carrega-lo" << endl;
        system("pause");
    }
}

void GerQuiz::CriarQuiz()
{
    string nomfile;
    char confirma;

    while((confirma!='N')&&(confirma!='n')){
        cout << "Digite o nome do Quiz que deseja criar:" << endl;
        getline(cin,nomfile,'\n');
        FILE* f = fopen((diretorio+"/"+nomfile+".bin").c_str(),"wt");
        fclose(f);
        cout << "Deseja criar mais quizes?(S/N)" << endl;
        cin >> confirma;
        cin.ignore(1000,'\n');
    }
}

void GerQuiz::AddPerguntas()/*adiciona perguntas ao arquivo com quiz*/
{
    string saida,strread;
    char verificar;

    system(CLEAR);
    carregaQuiz();
    double menor = atof(data1.c_str());
    double maior;
    FILE *f = fopen(arquivo.c_str(),"r+");

    while((verificar!='N')&&(verificar!='n')){
        cout << "Digite o index da pergunta que deseja adicionar:" << endl;
        getline(cin,strread,'\n');
        maior = atof(strread.c_str());

        if((maior > 0)&&(maior > menor)){
            saida = strread;
            saida.append("|");
            cout << "Digite a pergunta que deseja adicionar:" << endl;
            getline(cin,strread,'\n');
            saida.append(strread);
            saida.append("|");
            cout << "Digite a resposta para essa pergunta:" << endl;
            getline(cin,strread,'\n');
            saida.append(strread);
            saida.append("|\n");
            cout << "Deseja adicionar mais perguntas?(S/N)" << endl;
            cin >> verificar;
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
    FILE *f2 = fopen((diretorio+"/novo").c_str(),"w");
    char linha[100];
    string strread,compind;
    string antind,name;

    if(novap!=""){/*testa se a pergunta e nula*/
        while(fgets(linha,sizeof(linha),f)){/*faz a leitura de cada linha do arquivo*/
            strread = linha;/*faz a leitura da linha e joga em uma string de leitura*/
            compind = strread.substr(0,strread.find("|"));/*joga na variavel de comparacao o indice da pergunta*/
            if(editind == compind){ /*compara os dois indices*/
                fputs(novap.c_str(),f2);/*se forem iguais,escreve a nova pergunta no novo arquivo*/
            }else{
                fputs(strread.c_str(),f2);/*caso contrario escreve a pergunta lida do antigo arquivo*/
            }
        }
    }else{
        while(fgets(linha,sizeof(linha),f)){
            strread = linha;
            compind = strread.substr(0,strread.find("|"));
            if(editind == compind){
                antind = editind;/*indice anterior recebe o indice a ser editado*/
            }else if(antind!=""){/*se o indice anterior nao for nulo*/
                strread = strread.substr(strread.find("|"),strread.length());/*faz a leitura da pergunta,juntamente a resposta*/
                antind.append(strread);/*junta o indice anterior a essa pergunta+resposta*/
                strread = antind;/*string de leitura recebe a string formada no comando anterior*/
                antind = compind;/*indice anterior passa a ter o valor do indice comparativo*/
                fputs(strread.c_str(),f2);/*grava no arquivo*/
            }
        }
    }

    fclose(f);/*fclose*/
    fclose(f2);
    remove(arquivo.c_str());/*remove o antigo arquivo*/
    rename((diretorio+"/novo").c_str(),arquivo.c_str());/*renomeia o novo arquivo criado*/
}

string GerQuiz::FormularPergArq(string form1,string form2,string form3)
{
    form1.append("|");/*concatena um pipe em cada string com o index a pergunta e a resposta*/
    form2.append("|");
    form3.append("|\n");
    form2.append(form3);/*junta a pergunta com a resposta*/
    form1.append(form2);/*a seguir junta a string formada em form2 e junta a n1 formulando a pergunta completa*/
    return form1;/*retorna a pergunta formulada com o formato correto*/
}

/*funçoes providas da interface com o usuario pelo gerenciador*/
void GerQuiz::EditPer()/*edita a pergunta no arquivo*/
{
    string data;
    string ind,p,r;
    bool carregou;

    system(CLEAR);

    carregou = carregaQuiz();
    if(carregou){
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

void GerQuiz::DelPer()/*deleta a pergunta do arquivo*/
{
    system(CLEAR);
    carregaQuiz();
    string indstr;/*indice da pergunta*/

    cout << "Digite o indice da pergunta que deseja excluir:" << endl;
    cin >> indstr;
    if((atof(indstr.c_str()) > 0)&&(atof(indstr.c_str()) <= atof(data1.c_str()))){
        cout << "Deletando Pergunta..." << endl;
        ReorganizarPerArq(indstr,"");
        cout << "Pergunta deletada com sucesso!" << endl;
    }else{
        cout << "Pergunta inexistente" << endl;
    }
    system("pause");
}

string GerQuiz::BuscPer(string ind)/*busca a pergunta no arquivo*/
{
    char read[100];
    bool achou = false;
    string ask,comp;/*ask=pergunta comp=indice a comparar*/
    FILE *f = fopen(arquivo.c_str(),"rt");

    if(f!=NULL){
        while((fgets(read,sizeof(read),f))&&(achou!=true)){/*passa pelo arquivo lendo as perguntas ate encontrar a pergunta desejada*/
            ask = read;
            comp = ask.substr(0,ask.find("|"));
            if(comp == ind){/*caso os indices sejam iguais,logo a pergunta foi encontrada*/
                achou = true;
            }
        }
        fclose(f);/*fecha o arquivo e retorna a pergunta*/
        return ask;
    }
    return "";
}
/*construtor*/
GerQuiz::GerQuiz()
{
    diretorio = "tkq";/*pasta de destino aonde estarao os quizes*/
}

GerQuiz::~GerQuiz()
{

}

void GerQuiz::SelecionarArq()
{
    DIR *pasta;
    struct dirent *lsdir;
    pasta = opendir((".\\"+diretorio).c_str());
    int nroarquivo=1;
    string saida;
    string nomesarquivos;

    cout << "Lista de Quizes" << endl;
    while((lsdir=readdir(pasta))!=NULL){
        saida = lsdir->d_name;
        if((saida!=".")&&(saida!="..")){
            saida = saida.substr(0,saida.find(".bin"));
            cout << nroarquivo << "." << saida << endl;
            nomesarquivos = saida+"|";
            nroarquivo++;
        }
    }
    closedir(pasta);
    int total = nroarquivo;
    int antindex = 0;
    int nextindex = 0;

    cout << "Digite numero do quiz ao qual deseja selecionar:" << endl;
    cin >> nroarquivo;
    getchar();

    if((nroarquivo > 0)&&(nroarquivo <= total)){
        int counter = 0;
        while(counter != nroarquivo){
            saida = nomesarquivos;
            nextindex = saida.find("|");
            saida = saida.substr(antindex,nextindex);
            antindex = nextindex+1;
            counter++;
        }
        arquivo = diretorio+"/"+saida+".bin";
        cout << "Quiz selecionado com sucesso!" << endl;
    }else{
        cout << "Erro!Falha na seleção do Quiz" << endl;
    }
    system("pause");
}

void GerQuiz::executar()/*gerenciador de interface com o usuario*/
{
    bool fecha = false;
    int opt;
    mkdir(diretorio.c_str()); /*cria um diretorio na raiz do usuario*/
    while(!fecha){
        system(CLEAR);

        cout << "Gerenciador de Quiz" << endl;/*opcoes mostradas ao usuario*/
        cout << CREATEQUIZ << ".Criar Quiz" << endl;
        cout << LOGQUIZ << ".Carregar Quiz" << endl;
        cout << SELQUIZ << ".Selecionar Quiz" << endl;
        cout << EDITQUIZ << ".Editar Quiz" << endl;
        cout << DELQUIZ << ".Apagar Quiz" << endl;
        cout << SAIR << ".Sair" << endl;
        cout << "Escolha a opcao:" << endl;
        cin  >> opt;
        getchar();

        switch(opt){/*opcoes do usuario*/
            case CREATEQUIZ:
                CriarQuiz();
                break;
            case LOGQUIZ:
                CarregaQuizEd();
                break;
            case SELQUIZ:
                SelecionarArq();
                break;
            case EDITQUIZ:
                EditarQuiz();
                break;
            case DELQUIZ:
                ApagarQuiz();
                break;
            case SAIR:
                fecha = true;
                break;
            default:
                break;
            }
        }
}

void GerQuiz::EditarQuiz()
{
    int opt;
    bool fecha = false;

    while(!fecha){/*enquanto o usuario nao fechar as opcoes o loop ainda perpetuara*/
        system(CLEAR);/*interage com o usuario mostrando as opcoes*/

        cout << "Gerenciador de Quiz" << endl;
        cout << ADICIONARP << ".Adicionar Nova(s) Pergunta(s)" << endl;
        cout << EDITARP << ".Editar Pergunta(s)" << endl;
        cout << DELELETARP << ".Excluir Pergunta(s)" << endl;
        cout << SAIRP << ".Sair" << endl;
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
            case SAIRP:
                fecha = true;
                break;
            default:
                break;
        }
    }

}

void GerQuiz::ApagarQuiz()/*apaga um arquivo contendo um quiz ja existente*/
{
    char confirma;
    bool existe = false;

    system(CLEAR);
    while((confirma!='S')&&(confirma!='s')&&(confirma!='N')&&(confirma!='n')){
        cout << "Voce realmente deseja apagar o quiz?(S/N)" << endl;
        cin >> confirma;
        cin.ignore(1000,'\n');
    }
    if((confirma=='s')||(confirma=='S')){
        FILE* f = fopen(arquivo.c_str(),"rt");
        if(f!=NULL){
            existe = true;
        }
        fclose(f);
        if(existe){
            remove(arquivo.c_str());
        }else{
            cout << "Erro!Quiz inexistente,verifique se o mesmo foi selecionado corretamente e/ou criado" << endl;
            system("pause");
        }
        data1 = "";
        data2 = "";
        data3 = "";
    }
}

string GerQuiz::getQuizFileName()/*retorna o nome do ultimo arquivo setado*/
{
    return arquivo;
}

string GerQuiz::getFolderFilesName()
{
    return diretorio;
}
