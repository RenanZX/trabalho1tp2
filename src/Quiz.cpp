#include "Quiz.h"

const int Quiz::RESPONDER = 1;
const int Quiz::PULAR = 2;
const int Quiz::SAIR = 3;

void Pergunta::SetPergunta(string ind,string per,string res)throw(invalid_argument)
{
    string error = "Dados setados invalidos";/*verifica a veracidade dos dados e manda uma excessao*/
    if(atof(ind.c_str())==0) throw invalid_argument(error);
    index = ind;
    p = per;
    r = res;
}

string Pergunta::getIndex()
{
    return index;
}

string Pergunta::getPergunta()
{
    return p;
}

string Pergunta::getResposta()
{
    return r;
}

bool Pergunta::Comparar(Pergunta p)
{
    if((p.getIndex()==this->getIndex())&&(p.getPergunta()==this->getPergunta())&&(p.getResposta()==this->getResposta())){
        return true;
    }
    return false;
}

ELEMENTO::~ELEMENTO()
{
    delete p;
}

void listaPergunta::SetInicio(Pergunta* p)
{
    ELEMENTO *ptr = new ELEMENTO();
    ptr->p = p;
    ptr->prox = primeiro;
    primeiro->ant = ptr;
    primeiro = ptr;
    if(ultimo==NULL){
        ultimo = ptr;
    }
}

Pergunta* listaPergunta::getInicio()
{
    ELEMENTO *excluido = primeiro;
    Pergunta *p = excluido->p;
    primeiro = excluido->prox;
    delete excluido;
    return p;
}

void listaPergunta::SetFinal(Pergunta* p)
{
    ELEMENTO *novoel = new ELEMENTO();
    novoel->p = p;
    if(!EstaVazia()){
        ultimo->prox = novoel;
        novoel->ant = ultimo;
        ultimo = novoel;
    }else{
        primeiro = novoel;
        ultimo = novoel;
    }
}

Pergunta* listaPergunta::getFinal()
{
    ELEMENTO *exc = ultimo;
    Pergunta *ret = exc->p;
    ultimo = exc->ant;
    delete exc;
    return ret;
}

bool listaPergunta::EstaVazia()/*verifica se a lista esta vazia ou nao*/
{
    if(primeiro==NULL){
        return true;
    }
    return false;
}

listaPergunta::~listaPergunta()/*destroi a lista*/
{
    ELEMENTO* ptr = primeiro;
    ELEMENTO* excluido;

    while(ptr!=NULL){
        excluido = ptr;
        ptr = ptr->prox;
        delete excluido;
    }
}

int listaPergunta::ShowLista()/*mostra a lista de perguntas para o usuario*/
{
    ELEMENTO* ptr = primeiro;
    int counter = 0;

    cout << "Lista de perguntas" << endl;
    while(ptr!=NULL){/*mostra todos os elementos da lista de perguntas*/
        Pergunta* p = ptr->p;
        cout << p->getIndex() << ". " << p->getPergunta() << endl;
        ptr = ptr->prox;
        counter++;
    }

    return counter;
}

bool listaPergunta::deletarElemento(string ind)/*deleta um elemento da lista*/
{
    bool achou = false;
    ELEMENTO * ptr = primeiro;

    while((ptr!=NULL)&&(!achou)){
        if(ptr->p->getIndex()!=ind){
            ELEMENTO* exc = ptr;
            ptr = exc->prox;
            delete exc;
            achou = true;
        }
        ptr = ptr->prox;
    }

    return achou;
}


Quiz::Quiz()
{
    l = new listaPergunta();
}

Quiz::~Quiz()
{
    delete l;
}

void Quiz::OrganizarLista(string inds)/*organiza a lista com quiz apartir de uma string com indices separados por |*/
{
    listaPergunta *aux = new listaPergunta();/*cria uma lista nova*/
    int i = 0;
    int j = 0;
    int total = inds.length()-1;
    string* index = new string[total];
    Pergunta *p;

    while(j!=total){
        j = inds.find("|");
        index[i] = inds.substr(0,j);
        inds = inds.substr(j,total);
        i++;
    }
    i = 0;
    while(!l->EstaVazia()){/*enquanto a lista nao for vazia*/
         p = l->getInicio();/*pega a pergunta da lista*/
         if(p->getIndex()==index[i]){/*compara os indices*/
            aux->SetFinal(p);/*seta no final da lista*/
         }
         i++;
    }
    free(l);
    l = aux;
}

void Quiz::SetPergunta(string in,string per,string r)throw(invalid_argument)
{
    Pergunta *p = new Pergunta();/*aloca dinamicamente um ponteiro para o tipo abstrato pergunta*/
    try{    /*tenta setar a pergunta na variavel de classe alocada*/
        p->SetPergunta(in,per,r);
    }catch(invalid_argument &e){/*manda um feedback de erro caso nao consiga*/
        throw invalid_argument("Erro ao Carregar Pergunta");
    }
    l->SetFinal(p);/*insere a pergunta no final da lista*/
}

void Quiz::ComecarQuiz()throw(invalid_argument)
{
    string resposta;
    int acertos = 0;
    int erros = 0;
    int opcoes = 0;
    bool saiu = false;

    try{
        if(l->EstaVazia()){/*se a lista estiver vazia faz a leitura do arquivo do quiz*/
            lerQuiz();
        }
        Pergunta* p;
        system(CLEAR);
        while((!l->EstaVazia())&&(!saiu)){/*testa se o user saiu ou se a lista de perguntas ainda existem perguntas*/
            system(CLEAR);
            p = l->getInicio();
            cout << p->getIndex() << ". "<< p->getPergunta() << endl;
            cout << "\nOque deseja fazer?" << endl;
            cout << RESPONDER << ". Responder" << endl;
            cout << PULAR << ". Pular Questao" << endl;
            cout << SAIR << ". Sair do Quiz" << endl;
            cout << "Digite uma opcao" << endl;
            cin >> opcoes;
            getchar();

            switch(opcoes)/*opcoes do usuario*/
            {
                case RESPONDER:
                    cout << "Digite sua resposta:" << endl;
                    getline(cin,resposta,'\n');
                    if(resposta==p->getResposta()){/*compara as respostas e incrementa os acertos e os erros*/
                        acertos++;
                    }else{
                        erros++;
                    }
                    break;
                case PULAR:
                    l->SetFinal(p);
                    break;
                case SAIR:
                    saiu = true;
                    break;
            }
        }
        if(!saiu){
            cout << "Voce acertou " << acertos << "perguntas" << endl;
            cout << "Voce errou" << erros << "perguntas" << endl;
            if(acertos > erros){
                cout << "Parabéns!Sua pontuacao foi excelente" << endl;
            }else if(acertos < erros){
                cout << "Que pena,sua pontuacao foi terrivel mas voce pode tentar mais vezes" << endl;
            }else{
                cout << "Quase!voce quase conseguiu uma boa pontuacao" << endl;
            }
        }
        delete l;
    }catch(invalid_argument){
        throw invalid_argument("Erro nao foi possivel comecar o quiz");
    }
}

void Quiz::CarregarQuiz()throw(invalid_argument)
{
    int npergs;/*numero de perguntas*/

    try{
        lerQuiz();
        npergs = l->ShowLista();/*mostra os elementos da lista para o usuario*/
        cout << "Existem no Total" << npergs << "Perguntas" << endl;/*total de perguntas*/
        system("pause");
    }catch(invalid_argument &e){
        throw invalid_argument(e.what());
    }
}

void Quiz::SelecionarPergunta()throw(invalid_argument)
{
    if(!l->EstaVazia()){
        l->ShowLista();
        string ind;
        int i = 0;
        int j = 0;

        bool fechar = false;
        while(!fechar){
            cout << "Digite o(s) indice(s) da(s) pergunta(s) que deseja selecionar(separe os indices por , ex.:1,2.):" << endl;
            getline(cin,ind,'\n');
            j = ind.length();
            if((ind[j-1]!='.')||(!isdigit(ind[0]))){
                cout << "formato incorreto digite novamente" << endl;
            }else{
                fechar = true;
            }
        }
        ind[j-1] = '|';

        while(ind[i]!='|'){
            if(ind[i]==','){
                ind[i] = '|';
                i++;
            }else{
                i++;
            }
        }
        OrganizarLista(ind);
    }else{
        throw invalid_argument("nao existem perguntas a serem selecionadas.");
    }

}

void Quiz::lerQuiz()throw(invalid_argument)/*carregador de quiz*/
{
    GerQuiz g;/*cria uma variavel gerenciador de Quiz*/
    try{
        g.SelecionarArquivo();
    }catch(invalid_argument &e){
        system(CLEAR);
        string error = e.what();
        throw invalid_argument("Nao foi possivel ler o quiz pois "+error);
    }
    string file = g.getQuizFileName();/*pega o nome do arquivo contando o quiz*/
    char linha[100];
    int pos = 0;
    string entrada,ind,per,res;

    FILE *f = fopen(file.c_str(),"rt");/*abre o arquivo*/

    if(f!=NULL){
        try{
            while(fgets(linha,sizeof(linha),f)){
                entrada = linha;/*recebe uma pergunta lida do arquivo e joga na string entrada*/
                pos = 0;/*variavel de posicao*/
                ind = entrada.substr(0,entrada.find("|"));/*ind=index*/
                pos = entrada.find("|")+1;/*pos recebe a posicao do pipe +1*/
                entrada = entrada.substr(pos,entrada.length());/*per recebe o segundo dado lido da string de entrada*/
                per = entrada.substr(0,entrada.find("|"));
                pos = entrada.find("|")+1;
                entrada = entrada.substr(pos,entrada.length());/*res recebe o terceiro dado lido da string de entrada*/
                res = entrada.substr(0,entrada.find("|"));
                SetPergunta(ind,per,res);/*seta a pergunta lida no quiz*/
            }
        }catch(invalid_argument &e){
            throw invalid_argument("Erro Fatal!Dados lidos com problemas");
        }
    }else{
        fclose(f);
        throw invalid_argument("nao existem perguntas");/*caso nao existam perguntas no arquivo*/
    }
    fclose(f);
}
