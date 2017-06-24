#include "GerenciadorQuiz.h"

void GerQuiz::PegaAttributo(string dado) /*pega atributos da string lida do arquivo*/
{
    int pos = 0;

    pos = dado.find(".")+1;
    data1 = dado.substr(pos,dado.find("|")); /*indice da questao*/
    data1 = data1.substr(0,data1.find("|"));
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
    char read[1000];
    bool carregou = true;/*verifica se carregou o arquivo ou nao*/
    FILE* f = fopen(arquivo.c_str(),"rt");/*faz a leitura do arquivo*/

    fseek(f,0,SEEK_END);
    int tam = ftell(f);
    rewind(f);
    if((f!=NULL)&&(tam>0)){/*e necessario saber se o arquivo existe,e se existe e necessario saber se ele nao esta vazio*/
        cout << "Perguntas" << endl;
        while(fgets(read,sizeof(read),f)){
            strread = read;
            PegaAttributo(strread);
            cout << data1 << ". " << data2 << "   Res.:" << data3 << endl;
        }
    }else{
        cout << "nao existem perguntas" << endl;/*printa a mensagem para o usuario*/
        carregou = false;/*nao foi possivel carregar o arquivo logo carregou recebe false*/
    }
    fclose(f);
    return carregou;
}

void GerQuiz::CarregaQuizEditar()throw(invalid_argument)   /*verifica se o arquivo com o quiz esta selecionado para as devidas modificacoes do usuario*/
{
    if(arquivo!=""){    /*caso o arquivo do quiz tenha sido setado,o quiz e carregado na tela do usuario*/
        carregaQuiz();
        system("pause");
    }else{
        throw invalid_argument("selecione o quiz,antes de carrega-lo"); /*caso contrario e mostrada uma mensagem de erro*/
    }
}

void GerQuiz::CriarQuiz()throw(invalid_argument)/*cria um novo arquivo com quiz*/
{
    string nomfile;
    char confirma;
    FILE * f;
    while((confirma!='N')&&(confirma!='n')){
        cout << "Digite o nome do Quiz que deseja criar:" << endl;
        getline(cin,nomfile,'\n');/*faz a leitura do nome do arquivo*/
        f = fopen((diretorio+"/"+nomfile).c_str(),"rt");/*verifica se o arquivo existe*/
        if(f!=NULL){
            fclose(f);
            throw invalid_argument("Erro Quiz ja existente");/*caso exista lança uma excessao*/
        }
        fclose(f);
        f = fopen((diretorio+"/"+nomfile).c_str(),"wt");/*caso contrario sera gravado um novo arquivo*/
        cout << "Deseja criar mais quizes?(S/N)" << endl;/*pergunta ao usuario se ele quer criar mais quizes*/
        cin >> confirma;/*recebe a confirmacao*/
        cin.ignore(1000,'\n');
        fclose(f);
    }
}

void GerQuiz::AdicionarPerguntas()throw(invalid_argument)/*adiciona perguntas ao arquivo com quiz*/
{   /*declaracao de variaveis*/
    string saida,strread;
    string respostas;
    char verificar;
    std::stringstream saidastream;

    system(CLEAR);/*limpa a tela*/
    carregaQuiz();/*carrega o quiz*/
    double menor = atof(data1.c_str()); /*converte a ultima variavel lida ao carregar o quiz em menor*/
    double maior;/*declara double maior*/
    FILE *f = fopen(arquivo.c_str(),"r+");
    int i = 0,j = 0;

    if(f!=NULL){/*testa se o arquivo existe*/
        while((verificar!='N')&&(verificar!='n')){
            cout << "Digite o indice da pergunta que deseja adicionar:" << endl;
            getline(cin,strread,'\n');
            maior = atof(strread.c_str());

            if(maior > menor){/*verifica se o usuario digitou o index da pergunta corretamente*/
                saida = indice;
                saida.append(strread);
                saida.append("|");/*prepara a string de saida a ser escrita no arquivo*/
                cout << "Digite a pergunta que deseja adicionar:" << endl;
                getline(cin,strread,'\n');
                saida.append(strread);
                saida.append("|");
                cout << "Digite a pontuacao que valera esta questao:" << endl;
                getline(cin,strread,'\n');
                saida.append(strread);
                saida.append("|");
                while((verificar!='n')&&(verificar!='N')){
                    cout << "Digite a " << i+1 << "º opcao de resposta para essa questao:" << endl;
                    getline(cin,strread,'\n');
                    respostas.append(strread);
                    respostas.append("|");
                    i++;
                    j++;
                    if(j==4){
                        cout << "deseja adicionar mais opcoes?(S/N)" << endl;
                        cin >> verificar;
                        cin.ignore(1000,'\n');
                        j = 0;
                    }
                }
                saidastream << i << "|" << respostas;
                saida.append(saidastream.str());
                saidastream.str("");
                cout << "Escolha a opcao correspondente a resposta correta:" << endl;
                getline(cin,strread,'\n');
                if((atof(strread.c_str()) <= 0)&&(atof(strread.c_str()) > i)){
                    fclose(f);
                    throw invalid_argument("Opcao inexistente");
                }
                saida.append(strread);
                saida.append("|\n");
                fseek(f,0,SEEK_END);/*procura a ultima posicao do arquivo lido*/
                fputs(saida.c_str(),f);/*escreve a string de saida no arquivo*/
                cout << "Deseja adicionar mais perguntas?(S/N)" << endl;
                cin >> verificar;
                cin.ignore(1000,'\n');
            }else{
                cout << "Dados Inseridos incorretamente!" << endl;/*caso o usuario nao insira os dados corretamente*/
            }
        }
    }else{
        fclose(f);
        throw invalid_argument("Erro Fatal!o Quiz selecionado nao existe!"); /*feedback de erro*/
    }
    fclose(f);
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

/*funçoes providas da interface com o usuario pelo gerenciador*/
void GerQuiz::EditarPergunta()throw(invalid_argument)/*edita a pergunta no arquivo*/
{
    string data,ind;
    string pergunta;
    bool carregou;
    int i = 0;
    system(CLEAR);

    carregou = carregaQuiz();
    if(carregou){
        cout << "Indique o indice da pergunta que deseja editar:" << endl;
        getline(cin,data,'\n');
        ind = data;
        pergunta.append(indice+data);
        pergunta.append("|");
        data = BuscarPergunta(data);/*busca a pergunta no arquivo*/
        if(data == ""){/*testa se a pergunta e nula e lança uma excessao*/
            throw invalid_argument("Erro!Pergunta Inexistente.");
        }else{
            system(CLEAR);
            cout << FormularPerguntaImprimir(data) << endl;
            cout << "Digite sua nova pergunta:" << endl;
            getline(cin,data,'\n');
            pergunta.append(data);
            pergunta.append("|");
            cout << "Digite sua nova pontuacao:" << endl;
            getline(cin,data,'\n');
            pergunta.append(data);
            pergunta.append("|");
            for(i=0; i < limiterespostas ; i++){
                cout << "Digite sua "<< i+1 <<" nova opcao:" << endl;
                getline(cin,data,'\n');
                pergunta.append(data);
                pergunta.append("|");
                i++;
            }
            ReorganizarPerguntaArquivo(indice+ind,pergunta);
        }
    }
}

void GerQuiz::DeletarPergunta()throw(invalid_argument)/*deleta a pergunta do arquivo*/
{
    system(CLEAR);
    carregaQuiz();
    string indstr;/*indice da pergunta*/

    cout << "Digite o indice da pergunta que deseja excluir:" << endl;
    cin >> indstr;
    if((atof(indstr.c_str()) > 0)&&(atof(indstr.c_str()) <= atof(data1.c_str()))){/*ao converter o indice para double faz comparaçoes para validaçao*/
        indstr = indice+indstr;
        cout << "Deletando Pergunta..." << endl;
        ReorganizarPerguntaArquivo(indstr,"");/*reorganiza o arquivo com uma string nula juntamente com o indice da pergunta apagada*/
        data1 = "";
        data2 = "";
        data3 = "";
        cout << "Pergunta deletada com sucesso!" << endl;/*feedback ao usuario*/
    }else{
        throw invalid_argument("Erro!Pergunta Inexistente!");
    }
    system("pause");
}

string GerQuiz::FormularPerguntaImprimir(string pergunta)
{
    string index,dadopergunta,nota;
    std::stringstream retorno;
    int i = 0,limite = 0;

    index = pergunta.substr(pergunta.find(".")+1,pergunta.find("|"));
    pergunta = pergunta.substr(pergunta.find("|")+1,pergunta.length());
    dadopergunta = pergunta.substr(0,pergunta.find("|"));
    pergunta = pergunta.substr(pergunta.find("|")+1,pergunta.length());
    nota = pergunta.substr(0,pergunta.find("|"));
    pergunta = pergunta.substr(pergunta.find("|")+1,pergunta.length());
    retorno << index << "." << dadopergunta << " nota: " << nota << endl;
    limite = atoi(pergunta.substr(0,pergunta.find("|")).c_str()) - 1;
    pergunta = pergunta.substr(pergunta.find("|"),pergunta.length());
    limiterespostas = limite;
    while(i < limite){
        retorno << i+1 << ") " << pergunta.substr(0,pergunta.find("|")) << endl;
        pergunta = pergunta.substr(pergunta.find("|")+1,pergunta.length());
        i++;
    }
    return retorno.str();
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
}

GerQuiz::~GerQuiz()
{

}

string GerQuiz::getQuizesFilesName()
{
    DIR *pasta;
    struct dirent *lsdir;
    pasta = opendir((".\\"+diretorio).c_str());/*abre um diretorio de arquivos contendo quizes*/
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

void GerQuiz::SelecionarArquivo()throw(invalid_argument)    /*metodo selecionar arquivo*/
{
    DIR *pasta;
    struct dirent *lsdir;
    pasta = opendir((".\\"+diretorio).c_str());/*abre um diretorio de arquivos contendo quizes*/
    int nroarquivo=1;
    string saida;   /*string saida que servira para armazenar o input do usuario*/
    string nomesarquivos;   /*string nomesarquivos que contem todos os nomes de arquivos da pasta*/

    system(CLEAR);
    cout << "Lista de Quizes" << endl;
    while((lsdir=readdir(pasta))!=NULL){/*faz a leitura dos quizes disponiveis*/
        saida = lsdir->d_name;
        if((saida!=".")&&(saida!="..")){
            saida = saida.substr(0,saida.find(".txt"));/*imprime somente os nomes*/
            cout << nroarquivo << "." << saida << endl;
            nomesarquivos = nomesarquivos+saida+"|";
            nroarquivo++;
        }
    }
    closedir(pasta);/*fecha a pasta*/
    int total = nroarquivo;/*total de arquivos na pasta*/
    int nextindex = 0; /*proximo indice*/

    cout << "Digite numero do quiz ao qual deseja selecionar:" << endl;
    cin >> nroarquivo;
    getchar();

    if((nroarquivo > 0)&&(nroarquivo <= total)){
        int counter = 0;
        while(counter != nroarquivo){/*percorre a string com os nomes dos arquivos ate encontrar o selecionado pelo usuario*/
            saida = nomesarquivos;
            nextindex = saida.find("|");/*pipes divisores de strings*/
            saida = saida.substr(0,nextindex);
            nextindex++;
            nomesarquivos = nomesarquivos.substr(nextindex,nomesarquivos.length());
            counter++;
        }
        arquivo = diretorio+"/"+saida;/*encontrando o nome do arquivo e setado juntamente com o diretorio onde ele sera armazenado*/
        cout << "Quiz selecionado com sucesso!" << endl;/*caso de sucesso imprime para o usuario*/
        system("pause");
    }else{
        throw invalid_argument("Erro!Falha na seleção do Quiz");/*caso de falha lanca uma excessão*/
    }
}

void GerQuiz::ApagarQuiz()throw(invalid_argument)/*apaga um arquivo contendo um quiz ja existente*/
{
    char confirma;
    bool existe = false;
    char linha[1000];
    string verificar,comparar,saida;

    system(CLEAR);
    while((confirma!='S')&&(confirma!='s')&&(confirma!='N')&&(confirma!='n')){
        cout << "Voce realmente deseja apagar o quiz?(S/N)" << endl;
        cin >> confirma;
        cin.ignore(1000,'\n');
    }
    if((confirma=='s')||(confirma=='S')){
        FILE* f = fopen(arquivo.c_str(),"rt");
        if(f!=NULL){/*faz a leitura do arquivo,se ele existe ele pode ser deletado,caso contrario nao*/
            existe = true;
        }
        fclose(f);
        if(existe){
            remove(arquivo.c_str());/*remove o arquivo pelo nome setado*/
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
        }else{
            throw invalid_argument("Erro!Quiz inexistente,verifique se o mesmo foi selecionado corretamente e/ou criado");
        }
        data1 = "";/*reinicia as variaveis data*/
        data2 = "";
        data3 = "";
    }
}

void GerQuiz::SetIndexTopicDisc(string index)
{
    indice = index+".";
    FILE *f = fopen(tabelarelationquiz.c_str(),"r+");
    char linha[1000];
    int nrolinhas = 0;
    bool escreva = true;
    std::stringstream nroquiz;
    string verificar,arquivonome,verificarind;
    arquivonome = arquivo.substr(arquivo.find("/")+1,arquivo.length());

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

string GerQuiz::getQuizFileName()/*retorna o destino juntamente ao nome do ultimo arquivo setado*/
{
    return arquivo;
}

string GerQuiz::getFolderFilesName()
{
    return diretorio;
}
