#include "Quiz.hpp"

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

void Pergunta::SetPontuacao(int pontos)
{
    pontuacao = pontos;
}

int Pergunta::getPontuacao()
{
    return pontuacao;
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

int Quiz::getNumeroAcertos()
{
    return acertos;
}

int Quiz::getNumeroErros()
{
    return erros;
}

int Quiz::getPontosUsuario()
{
    return pontuacao;
}

bool Quiz::QuizTerminou()
{
    if(l->EstaVazia()){
        return true;
    }
    return false;
}

Pergunta * Quiz::QuizgetPergunta()
{
    return l->getInicio();
}


Quiz::Quiz()
{
    acertos = 0;
    erros = 0;
    pontuacao = 0;
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

void Quiz::SetPergunta(string in,string per,Resposta r,int pontuacao)throw(invalid_argument)
{
    Pergunta *p = new Pergunta();/*aloca dinamicamente um ponteiro para o tipo abstrato pergunta*/
    try{    /*tenta setar a pergunta na variavel de classe alocada*/
        p->SetPergunta(in,per,&r);
        p->SetPontuacao(pontuacao);
    }catch(invalid_argument &e){/*manda um feedback de erro caso nao consiga*/
        throw invalid_argument("Erro ao Carregar Pergunta");
    }
    l->SetFinal(p);/*insere a pergunta no final da lista*/
}

void Quiz::QuizPularPergunta(Pergunta* p)throw(invalid_argument)
{
    if(p == NULL) throw invalid_argument("Erro pergunta nula");
    l->SetFinal(p);
}

void Quiz::QuizResponderPergunta(Pergunta* p,int resposta)throw(invalid_argument)
{
    std::stringstream streamrelatorio;
    string relatorioquestao;

    if((p == NULL)||(resposta == 0)) throw invalid_argument("Erro pergunta ou resposta nula");
    if(p->CompararResposta(resposta)){/*compara as respostas e incrementa os acertos e os erros*/
        streamrelatorio << p->getIndex() << ". Resp.:" << resposta << ") resposta correta";
        acertos++;
        pontuacao+=p->getPontuacao();
    }else{
        streamrelatorio << p->getIndex() << ". Resp.:" << p->getRespostaCorreta() << ") resposta errada voce respondeu " << resposta << ")";
        erros++;
    }
    //tempoquestao.terminaContagem();
    //streamrelatorio << "voce demorou " << tempoquestao.tempoGasto() << "segundos para esta questao";
    relatorioquestao = streamrelatorio.str();
    streamrelatorio.str("");
    relatorioquestoes.push_back(relatorioquestao);
}

std::vector<string> Quiz::QuizgetRelatorio()
{
    return relatorioquestoes;
}

int Quiz::ImprimirPerguntas()throw(invalid_argument)
{
    int nperguntas = 0;

    if(l->EstaVazia()) throw invalid_argument("Erro Nao Existem Perguntas na lista");

    nperguntas = l->ShowLista(); /*mostra os elementos da lista para o usuario*/
    return nperguntas;
}

void Quiz::SelecionarPerguntas(string indices)throw(invalid_argument)
{
    int i=0,j=0;
    if((file!="")&&(!l->EstaVazia())){/*testa se a lista nao esta vazia*/
        l->ShowLista();
        i = 0;
        j = indices.length();
    }else{
        throw invalid_argument("Nao Existem Perguntas a Serem selecionadas");
    }
    if((indices[j-1]!='.')||(!isdigit(indices[0]))){
        throw invalid_argument("formato incorreto digite novamente");
    }
    indices[j-1] = '|';

    while(indices[i]!='|'){
        if(indices[i]==','){
            indices[i] = '|';
            i++;
        }else{
            i++;
        }
    }
    OrganizarLista(indices);/*organiza as perguntas na lista de perguntas*/
}

void Quiz::SelecionarDisciplina(string Disciplina)throw(invalid_argument)
{
    topicosdisciplinas = Disciplina;
    topicosdisciplinas.append("-");
}

void Quiz::SelecionarTopico(string Topico)throw(invalid_argument)
{
    if(topicosdisciplinas!=""){
        topicosdisciplinas.append(Topico);
    }else{
        throw invalid_argument("Erro Disciplina nao selecionada!");
    }
}

void Quiz::lerQuiz(string nomequiz)throw(invalid_argument)/*carregador de quiz*/
{
    if(!l->EstaVazia()) throw invalid_argument("Erro lista de perguntas nao vazia!");
    file = nomequiz;
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
                    SetPergunta(ind,per,res,atoi(nota.c_str()));/*seta a pergunta com a resposta o indice e a pergunta*/
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
