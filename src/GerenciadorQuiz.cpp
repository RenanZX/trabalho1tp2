#include "GerenciadorQuiz.h"

const string TabelaDisciplinasTopicos::TABLETOPICOS = "tabletop"; /*constantes*/
const string TabelaDisciplinasTopicos::TABLEDISCIPLINAS = "tabledisc";

void TabelaDisciplinasTopicos::setTableTopics(string topico)
{
    FILE *f = fopen(TABLETOPICOS.c_str(),"r+");
    int i = 0;
    bool existe = false;
    char linha[1000];
    string strlinha;
    std::stringstream ss;

    if(f!=NULL){
        while((fgets(linha,sizeof(linha),f))&&(!existe)){
            strlinha = linha;
            strlinha = strlinha.substr(strlinha.find("|")+1,strlinha.length());
            strlinha = strlinha.substr(0,strlinha.find("\n"));
            if(topico == strlinha){
                existe = true;
            }else{
                i++;
            }
        }
    }else{
        fclose(f);
        f = fopen(TABLETOPICOS.c_str(),"w");
    }
    ss << index << "-" << i;
    index = ss.str();
    if(!existe){
        ss.str("");
        ss << i << "|" << topico << endl;
        topico = ss.str();
        fseek(f,0,SEEK_END);
        fputs(topico.c_str(),f);
    }
    fclose(f);
}

void TabelaDisciplinasTopicos::setTableDisc(string disciplina)
{
    FILE *f = fopen(TABLEDISCIPLINAS.c_str(),"r+");
    int i = 0;
    bool existe = false;
    char linha[1000];
    string strlinha;
    std::stringstream ss;

    if(f!=NULL){
        while((fgets(linha,sizeof(linha),f))&&(!existe)){
            strlinha = linha;
            strlinha = strlinha.substr(strlinha.find("|")+1,strlinha.length());
            strlinha = strlinha.substr(0,strlinha.find("\n"));
            if(disciplina == strlinha){
                existe = true;
            }else{
                i++;
            }
        }
    }else{
        fclose(f);
        f = fopen(TABLEDISCIPLINAS.c_str(),"w");
    }
    ss << i;
    index = ss.str();
    if(!existe){
        ss.str("");
        ss << i << "|" << disciplina << endl;
        disciplina = ss.str();
        fseek(f,0,SEEK_END);
        fputs(disciplina.c_str(),f);
    }

    fclose(f);
}

void TabelaDisciplinasTopicos::findTableTopics(string topico)throw(invalid_argument)
{
    FILE *f = fopen(TABLETOPICOS.c_str(),"r+");
    bool achou = false;
    char linha[1000];
    string comparar;
    std::stringstream ss;

    while((fgets(linha,sizeof(linha),f))&&(!achou)){
        comparar = linha;
        comparar = comparar.substr(comparar.find("|")+1,comparar.length());
        comparar = comparar.substr(0,comparar.find("\n"));
        if(comparar == topico){
            achou = true;
            comparar = linha;
            comparar = comparar.substr(0,comparar.find("|"));
            ss << index << comparar;
            index = ss.str();
        }
    }
    if(!achou){
        fclose(f);
        throw invalid_argument("Erro topico nao existe");
    }

    fclose(f);
}

void TabelaDisciplinasTopicos::findTableDisc(string disciplina)throw(invalid_argument)
{
    FILE *f = fopen(TABLEDISCIPLINAS.c_str(),"r+");
    bool achou = false;
    char linha[1000];
    string comparar;
    std::stringstream ss;

    while((fgets(linha,sizeof(linha),f))&&(!achou)){
        comparar = linha;
        comparar = comparar.substr(comparar.find("|")+1,comparar.length());
        comparar = comparar.substr(0,comparar.find("\n"));
        if(comparar == disciplina){
            achou = true;
            comparar = linha;
            comparar = comparar.substr(0,comparar.find("|"));
            ss << comparar;
            index = ss.str();
        }
    }
    if(!achou){
        fclose(f);
        throw invalid_argument("Erro disciplina nao existe");
    }

    fclose(f);
}

void TabelaDisciplinasTopicos::showTableDisc()
{
    FILE *f = fopen(TABLEDISCIPLINAS.c_str(),"r+");
    char linha[1000];
    string print;

    cout << "Disciplinas disponiveis:" << endl;
    while(fgets(linha,sizeof(linha),f)){
        print = linha;
        print = print.substr(print.find("|")+1,print.length());
        cout << print << endl;
    }
    fclose(f);
}

void TabelaDisciplinasTopicos::showTableTopics()
{
    FILE *f = fopen(TABLETOPICOS.c_str(),"r+");
    char linha[1000];
    string print;

    cout << "Topicos disponiveis:" << endl;
    while(fgets(linha,sizeof(linha),f)){
        print = linha;
        print = print.substr(print.find("|")+1,print.length());
        cout << print << endl;
    }
    fclose(f);
}

string TabelaDisciplinasTopicos::getGeneratedIndex()
{
    string retornar;

    retornar = index;
    index = "";
    return retornar;
}

void GerQuiz::CriaQuiz(string nomequiz)throw(invalid_argument)
{
    FILE * f = fopen((diretorio+"/"+nomequiz).c_str(),"rt");
    if(f!=NULL){ /*verifica se o arquivo existe*/
        fclose(f);
        throw invalid_argument("Erro Quiz ja Existe!"); /*caso exista lança uma excessao*/
    }
    fclose(f);
    f = fopen((diretorio+"/"+nomequiz).c_str(),"wt"); /*caso contrario sera gravado um novo arquivo*/
    fclose(f);
}

void GerQuiz::SetQuiz(string nomequiz)throw(invalid_argument)
{
    if(nomequiz == "") throw invalid_argument("Erro,Nao e possivel setar o quiz");
    arquivo = diretorio+"/"+nomequiz;
}

void GerQuiz::SetPerguntaQuiz(string perguntarquivo)throw(invalid_argument)
{
    FILE *f = fopen(arquivo.c_str(),"r+");
    if(perguntarquivo=="") throw invalid_argument("Erro!Pergunta Nula!");
    if(f!=NULL){
        fseek(f,0,SEEK_END);/*procura a ultima posicao do arquivo lido*/
        fputs(perguntarquivo.c_str(),f);/*escreve a string de saida no arquivo*/
    }else{
        throw invalid_argument("Erro Fatal!Quiz nao selecionado!");
    }
}

void GerQuiz::ReorganizarPerguntaArquivo(string editind,string novap)/*reorganiza o arquivo com o quiz*/
{
    FILE *f = fopen(arquivo.c_str(),"rt");
    FILE *f2 = fopen((diretorio+"/novo").c_str(),"w");
    char linha[1000];
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

void GerQuiz::DeletarPerguntaQuiz(string index)throw(invalid_argument)
{
    index = indice+index;
    if(arquivo=="") throw invalid_argument("Erro Quiz Nao selecionado!");
    if((atof(index.c_str()) < 0)||(atof(index.c_str()) >= 50000000)) throw invalid_argument("Erro!Pergunta Inexistente!");/*ao converter o indice para double faz comparaçoes para validaçao*/
    ReorganizarPerguntaArquivo(index,""); /*reorganiza o arquivo com uma string nula juntamente com o indice da pergunta apagada*/
}

void GerQuiz::mkdir(const char* nome){
    std::stringstream ss;
    std::string output;
    ss << "mkdir " << nome;
    output = ss.str();
    system(output.c_str());
    ss.clear();
}

string GerQuiz::BuscarPergunta(string ind)/*busca a pergunta no arquivo*/
{
    char linha[1000];
    bool achou = false;
    string ask,comp;/*ask=pergunta comp=indice a comparar*/
    FILE *f = fopen(arquivo.c_str(),"rt");
    ind = indice+ind;

    if(f!=NULL){
        while((fgets(linha,sizeof(linha),f))&&(achou!=true)){/*passa pelo arquivo lendo as perguntas ate encontrar a pergunta desejada*/
            ask = linha;
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
    diretorio = "Quizzes";/*pasta de destino aonde estarao os quizes*/
    tabelarelationquiz = "tabquizes"; /*tabela de quizes relacionados*/
    limiterespostas = 0;
    mkdir(diretorio.c_str()); /*cria um diretorio na raiz do usuario*/
}

GerQuiz::~GerQuiz()
{

}

string GerQuiz::getQuizesFilesName()
{
    DIR *pasta;
    struct dirent *lsdir;
    pasta = opendir((root+diretorio).c_str());/*abre um diretorio de arquivos contendo quizes*/
    string saida,nomesarquivos;
    int nroarquivo=1;

    while((lsdir=readdir(pasta))!=NULL){/*faz a leitura dos quizes disponiveis*/
        saida = lsdir->d_name;
        if((saida!=".")&&(saida!="..")){
            saida = saida.substr(0,saida.find(".txt"));/*imprime somente os nomes*/
            nomesarquivos = nomesarquivos+saida+"|";
            nroarquivo++;
        }
    }
    closedir(pasta);/*fecha a pasta*/
    return nomesarquivos;
}

void GerQuiz::EditarPergunta(string index,string pergunta)throw(invalid_argument)
{
    if((pergunta == "")||(index == "")) throw invalid_argument("Erro indice ou pergunta invalidos");
    ReorganizarPerguntaArquivo(indice+index,pergunta);
}

void GerQuiz::DeletarQuizSetado()throw(invalid_argument)
{
    char linha[1000];
    string verificar,comparar,saida;

    if(arquivo=="")throw invalid_argument("Erro Quiz nao selecionado!");
    FILE* f = fopen(arquivo.c_str(),"rt");
    arquivo = "";
    if(f==NULL){ /*faz a leitura do arquivo,se ele existe ele pode ser deletado,caso contrario nao*/
        fclose(f);
        throw invalid_argument("Erro Quiz nao existe!");
    }else{
        fclose(f);
        remove(arquivo.c_str()); /*remove o arquivo pelo nome setado*/
        f = fopen(tabelarelationquiz.c_str(),"r+");
            FILE *f2 = fopen("novo","w");
            comparar = arquivo.substr(arquivo.find("/")+1,arquivo.length());
            if(f!=NULL){
                while(fgets(linha,sizeof(linha),f)){
                    verificar = linha;
                    verificar = verificar.substr(verificar.find("|")+1,verificar.length());
                    verificar = verificar.substr(0,verificar.find("|"));
                    if(verificar != comparar){
                        fputs(linha,f2);
                    }
                }
            }
            fclose(f);
            fclose(f2);
            remove(tabelarelationquiz.c_str());
            rename("novo",tabelarelationquiz.c_str());
    }
}

void GerQuiz::SetIndexTopicDisc(string index)throw(invalid_argument)
{
    indice = index+".";
    FILE *f = fopen(tabelarelationquiz.c_str(),"r+");
    char linha[1000];
    int nrolinhas = 0;
    bool escreva = true;
    std::stringstream nroquiz;
    string verificar,arquivonome,verificarind;
    arquivonome = arquivo.substr(arquivo.find("/")+1,arquivo.length());

    if(index == "") {
        throw invalid_argument("Indice invalido");
    }
    if(f==NULL){
        fclose(f);
        f = fopen(tabelarelationquiz.c_str(),"w+");
    }

    while((fgets(linha,sizeof(linha),f))&&(escreva)){
        verificar = linha;
        verificarind = verificar.substr(0,verificar.find("."));
        verificar = verificar.substr(verificar.find("|")+1,verificar.length());
        verificar = verificar.substr(0,verificar.find("|"));
        if((verificar == arquivonome)&&(verificarind == index)){
            escreva = false;
         }
         nrolinhas++;
    }
    if(escreva){
        nroquiz << nrolinhas;
        fputs((index+"."+nroquiz.str()+"|"+arquivonome+"|\n").c_str(),f);
        nroquiz.str("");
    }
    fclose(f);
}

string GerQuiz::getQuizFileNameSeted()/*retorna o destino juntamente ao nome do ultimo arquivo setado*/
{
    return arquivo;
}

string GerQuiz::getFolderFilesName()
{
    return diretorio;
}
