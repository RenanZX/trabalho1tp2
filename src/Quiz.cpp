#include "Quiz.hpp"

const int Quiz::RESPONDER = 1;
const int Quiz::PULAR = 2;
const int Quiz::SAIR = 3;

Resposta::~Resposta()
{

}

void Resposta::SetRespostasArquivo(string respostas) /*seta as respostas no formato do arquivo*/
{
    int limite = atoi(respostas.substr(0,respostas.find("|")).c_str());
    int i =0;
    string resposta;

    respostas = respostas.substr(respostas.find("|")+1,respostas.length());
    for(i=0;i<limite;i++){
        resposta = respostas.substr(0,respostas.find("|"));
        opcoes.push_back(resposta);
        respostas = respostas.substr(respostas.find("|")+1,respostas.length());
    }
    respostacorreta = atoi(respostas.substr(0,respostas.find("|")).c_str());
}

void Resposta::MostrarOpcoes() /*mostra as opcoes de resposta para o usuario*/
{
    int j =1;
    for(std::vector<string>::const_iterator opcao=opcoes.begin();opcao!=opcoes.end();opcao++){
        cout << j << ") " << *opcao << endl;
        j++;
    }
}

bool Resposta::VerificarRespostaCorreta(int resposta) /*verica se a resposta esta correta verificando o indice de resposta*/
{
    if(resposta == respostacorreta){
        return true;
    }
    return false;
}

int Resposta::getRespostaCorreta()
{
    return respostacorreta;
}

bool Resposta::CompararResposta(Resposta res) /*compara duas classes resposta*/
{
    if((equal(res.opcoes.begin(),res.opcoes.end(),opcoes.begin()))&&(res.respostacorreta==respostacorreta)){
        return true;
    }
    return false;
}

void Pergunta::SetPergunta(string ind,string per,Resposta *res)throw(invalid_argument)
{
    string error = "Dados setados invalidos";/*verifica a veracidade dos dados e manda uma excessao*/
    if((atoi(ind.c_str())==0)&&(ind=="")&&(per=="")&&(res==NULL)) throw invalid_argument(error);
    index = ind;
    strpergunta = per;
    resposta = *res;
}

string Pergunta::getIndex()
{
    return index;
}

string Pergunta::getPergunta()
{
    return strpergunta;
}

Resposta Pergunta::getResposta()
{
    return resposta;
}

int Pergunta::getRespostaCorreta()
{
    return resposta.getRespostaCorreta();
}

void Pergunta::ImprimirOpcoes()
{
    resposta.MostrarOpcoes();
}

bool Pergunta::Comparar(Pergunta p)/*compara duas perguntas e retorna verdadeiro ou falso,depedendo se sao iguais ou nao*/
{
    if((p.getIndex()==this->getIndex())&&(p.getPergunta()==this->getPergunta())&&(this->resposta.CompararResposta(p.getResposta()))){
        return true;
    }
    return false;
}

bool Pergunta::CompararResposta(int respostaverificar)
{
    if(resposta.VerificarRespostaCorreta(respostaverificar)){
        return true;
    }
    return false;
}

ELEMENTO::~ELEMENTO()
{

}

void listaPergunta::SetInicio(Pergunta* p)/*insere no inicio da lista*/
{
    ELEMENTO *ptr = new ELEMENTO();/*novo espaco e alocado*/
    ptr->p = p;
    ptr->prox = primeiro;
    primeiro->ant = ptr;
    primeiro = ptr;/*ponteiro novo passa a ser o primeiro elemento da lista*/
    if(ultimo==NULL){/*se o ultimo for nulo*/
        ultimo = ptr;/*ultimo recebe o primeiro elemento*/
    }
}

Pergunta* listaPergunta::getInicio()
{
    ELEMENTO *excluido = primeiro;/*pega um ponteiro do elemento excluido*/
    Pergunta *p = excluido->p;/*p e a pergunta que sera retornada da funcao*/
    primeiro = excluido->prox;/*proximo elemento agora e o primeiro*/
    delete excluido;/*deleta o ponteiro*/
    return p;/*retorna a pergunta*/
}

void listaPergunta::SetFinal(Pergunta* p)
{
    ELEMENTO *novoelemento = new ELEMENTO();
    novoelemento->p = p;
    if(!EstaVazia()){
        ultimo->prox = novoelemento;
        novoelemento->ant = ultimo;
        ultimo = novoelemento;
    }else{
        primeiro = novoelemento;
        ultimo = novoelemento;
    }
}

Pergunta* listaPergunta::getFinal()
{
    ELEMENTO *excluido = ultimo;
    Pergunta *retorne = excluido->p;
    ultimo = excluido->ant;
    delete excluido;
    return retorne;
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
    Pergunta* excluida;

    while(ptr!=NULL){
        excluido = ptr;
        ptr = ptr->prox;
        excluida = excluido->p;
        delete excluida;
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
            Pergunta* p = exc->p;
            ptr = exc->prox;
            delete p;
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
    int total = inds.length();
    std::vector<string> index;
    Pergunta *p;

    while(i!=total-1){
        i = inds.find("|");
        index.push_back(inds.substr(0,i));
        inds = inds.substr(i+1,total);
    }
    while(!l->EstaVazia()){/*enquanto a lista nao for vazia*/
         p = l->getInicio();/*pega a pergunta da lista*/
         if(p->getIndex()==index[i]){/*compara os indices*/
            aux->SetFinal(p);/*seta no final da lista*/
         }
         i++;
    }
    l = aux;
}

void Quiz::SetPergunta(string in,string per,Resposta r)throw(invalid_argument)
{
    Pergunta *p = new Pergunta();/*aloca dinamicamente um ponteiro para o tipo abstrato pergunta*/
    try{    /*tenta setar a pergunta na variavel de classe alocada*/
        p->SetPergunta(in,per,&r);
    }catch(invalid_argument &e){/*manda um feedback de erro caso nao consiga*/
        throw invalid_argument("Erro ao Carregar Pergunta");
    }
    l->SetFinal(p);/*insere a pergunta no final da lista*/
}

void Quiz::ComecarQuiz()throw(invalid_argument)
{
    std::vector<string> relatorioquestoes;
    std::stringstream streamrelatorio;
    string relatorioquestao;
    //tempo tempoquestao;
    int resposta;
    int acertos = 0;
    int erros = 0;
    int opcoes = 0;
    bool saiu = false;

    try{
        if(l->EstaVazia()){/*se a lista estiver vazia faz a leitura do arquivo do quiz*/
            lerQuiz();
        }
        Pergunta *p;
        system(CLEAR);
        while((!l->EstaVazia())&&(!saiu)){/*testa se o user saiu ou se a lista de perguntas ainda existem perguntas*/
            system(CLEAR);
            p = l->getInicio();
            cout << p->getIndex() << ". "<< p->getPergunta() << endl;/*opcoes do usuario*/
            p->ImprimirOpcoes();
            cout << "\nOque deseja fazer?" << endl;
            cout << RESPONDER << ". Responder" << endl;
            cout << PULAR << ". Pular Questao" << endl;
            cout << SAIR << ". Sair do Quiz" << endl;
            cout << "Digite uma opcao" << endl;
            cin >> opcoes;
            cin.ignore(1000,'\n');

            switch(opcoes)/*opcoes do usuario*/
            {
                case RESPONDER:
                    //tempoquestao.inciaContagem();
                    cout << "Digite a opcao correspondente a sua resposta:" << endl;
                    cin >> resposta;
                    cin.ignore(1000,'\n');
                    if(p->CompararResposta(resposta)){/*compara as respostas e incrementa os acertos e os erros*/
                        streamrelatorio << p->getIndex() << ". Resp.:" << resposta << ") resposta correta";
                        acertos++;
                    }else{
                        streamrelatorio << p->getIndex() << ". Resp.:" << p->getRespostaCorreta() << ") resposta errada voce respondeu " << resposta << ")";
                        erros++;
                    }
                    //tempoquestao.terminaContagem();
                    //streamrelatorio << "voce demorou " << tempoquestao.tempoGasto() << "segundos para esta questao";
                    relatorioquestao = streamrelatorio.str();
                    streamrelatorio.str("");
                    relatorioquestoes.push_back(relatorioquestao);
                    free(p);
                    break;
                case PULAR:
                    l->SetFinal(p);
                    break;
                case SAIR:
                    free(p);
                    saiu = true;
                    break;
                default:
                    break;
            }
        }
        if(!saiu){
            for(std::vector<string>::const_iterator relatquestao=relatorioquestoes.begin();relatquestao!=relatorioquestoes.end();relatquestao++){
                cout << *relatquestao << endl;
            }
            cout << "Voce acertou " << acertos << " perguntas" << endl;/*mostra a pontuacao do usuario*/
            cout << "Voce errou " << erros << " perguntas" << endl;
            if(acertos > erros){
                cout << "Parabens!Sua pontuacao foi excelente" << endl;/*feedback para o usuario*/
            }else if(acertos < erros){
                cout << "Que pena,sua pontuacao foi terrivel mas voce pode tentar mais vezes" << endl;
            }else{
                cout << "Quase!voce quase conseguiu uma boa pontuacao" << endl;
            }
            PAUSE;
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
        cout << "Existem no Total " << npergs << " Perguntas" << endl;/*total de perguntas*/
        PAUSE;
    }catch(invalid_argument &e){
        throw invalid_argument(e.what());
    }
}

void Quiz::SelecionarPergunta()throw(invalid_argument) /*usuario pode selecionar as perguntas que deseja responder*/
{
    if((file!="")&&(!l->EstaVazia())){/*testa se a lista nao esta vazia*/
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
        OrganizarLista(ind);/*organiza as perguntas na lista de perguntas*/
        cout << "Perguntas Selecionadas com Sucesso!" << endl;
        PAUSE;
    }else{
        throw invalid_argument("nao existem perguntas a serem selecionadas.");
    }

}

void Quiz::selectTopicosDisciplinas()throw(invalid_argument) /*faz a seleçao de topicos e disciplinas do usuario*/
{
    FILE *f = fopen("tabledisc","r+");/*faz a leitura das tabelas*/
    char linha[1000];
    string print;
    int i = 0;
    int total = 0,entrada = 0;
    std::stringstream strstream;

    cout << "Disciplinas disponíveis" << endl;/*mostra as disciplinas disponiveis*/
    while(fgets(linha,sizeof(linha),f)){
        print = linha;
        i = atoi(print.substr(0,print.find("|")).c_str()) +1;
        cout << i << "." << print.substr(print.find("|")+1,print.length()) << endl;
        total++;
    }
    cout << "Digite uma disciplina de acordo com o numero indicado:" << endl;/*solicita ao usuario selecionar uma*/
    cin >> entrada;
    getchar();
    if((entrada < 1)||(entrada > total)){ /*testa se o usuario digitou algo errado*/
        throw invalid_argument("entrada invalida!");
    }
    strstream << (entrada - 1) << "-";
    fclose(f);
    f = fopen("tabletop","r+");
    cout << "Topicos disponíveis" << endl;
    while(fgets(linha,sizeof(linha),f)){/*abre a tabela e topicos e solicita ao usuario selecionar tambem*/
        print = linha;
        i = atoi(print.substr(0,print.find("|")).c_str()) +1;
        cout << i << "." << print.substr(print.find("|")+1,print.length()) << endl;
        total++;
    }
    cout << "Digite um topico de acordo com o numero indicado:" << endl;
    cin >> entrada;
    getchar();
    if((entrada < 1)||(entrada > total)){
        throw invalid_argument("entrada invalida!");
    }
    strstream << (entrada - 1);
    topicosdisciplinas = strstream.str();
    strstream.str("");
    fclose(f);
}

void Quiz::lerQuiz()throw(invalid_argument)/*carregador de quiz*/
{

    GerQuiz gerente;/*cria uma variavel gerenciador de Quiz*/
    try{
        gerente.SelecionarArquivo();/*o usuario seleciona o arquivo contendo o quiz*/
        selectTopicosDisciplinas();/*seleciona os topicos e disciplinas que irá responder*/
    }catch(invalid_argument &e){
        system(CLEAR);
        string error = e.what();
        throw invalid_argument("Nao foi possivel ler o quiz pois "+error);
    }
    file = gerente.getQuizFileName();/*pega o nome do arquivo contando o quiz*/
    char linha[1000];
    int pos = 0;
    string entrada,ind,per,nota;
    Resposta res;

    FILE *f = fopen(file.c_str(),"rt");/*abre o arquivo*/

    if(f!=NULL){
        try{
            while(fgets(linha,sizeof(linha),f)){
                entrada = linha;/*recebe uma pergunta lida do arquivo e joga na string entrada*/
                pos = 0;/*variavel de posicao*/
                ind = entrada.substr(0,entrada.find("."));/*ind=index*/
                pos = entrada.find(".")+1;
                entrada = entrada.substr(pos,entrada.length());
                if(ind == topicosdisciplinas){
                    ind = entrada.substr(0,entrada.find("|"));
                    pos = entrada.find("|")+1;/*pos recebe a posicao do pipe +1*/
                    entrada = entrada.substr(pos,entrada.length());/*per recebe o segundo dado lido da string de entrada*/
                    per = entrada.substr(0,entrada.find("|"));
                    pos = entrada.find("|")+1;
                    entrada = entrada.substr(pos,entrada.length());/*nota recebe o terceiro dado lido da string de entrada*/
                    nota = entrada.substr(0,entrada.find("|"));
                    pos = entrada.find("|")+1;
                    entrada = entrada.substr(pos,entrada.length());
                    res.SetRespostasArquivo(entrada);/*e por fim os dados sao organizados pela classe resposta a qual ja consegue organizar e reconhecer as respostas do arquivo*/
                    SetPergunta(ind,per,res);/*seta a pergunta com a resposta o indice e a pergunta*/
                }
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
