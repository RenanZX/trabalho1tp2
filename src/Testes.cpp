#include "Testes.h"


bool TesteArquivo::TesteArquivoQuiz()
{
    gerente.CriaQuiz(nomearquivo);
    FILE *f = fopen(nomearquivo.c_str(),"r");
    if(f==NULL){
        fclose(f);
        return false;
    }
    fclose(f);
    gerente.SetQuiz(nomearquivo);
    gerente.DeletarQuizSetado();
    return true;
}

void TesteArquivo::executar()throw(runtime_error)
{
    if(!TesteArquivoQuiz()) throw runtime_error("Erro,arquivo "+nomearquivo+" vazio!");
}

TesteArquivo::TesteArquivo()
{
    nomearquivo = "teste";
}

const int TesteModuloGerenteQuiz::SUCESSO = 1;
const int TesteModuloGerenteQuiz::FALHA = 0;

const string TesteModuloGerenteQuiz::CASOSUCESSO_BUSCARPERGUNTA = "1";
const string TesteModuloGerenteQuiz::CASOFALHA_BUSCARPERGUNTA = "";
const string TesteModuloGerenteQuiz::SAIDASUCESSO_BUSCARPERGUNTA = "pergunta";
const string TesteModuloGerenteQuiz::SAIDAFALHA_BUSCARPERGUNTA = "";

void TesteModuloGerenteQuiz::TesteIniciarBuscarPergunta()
{
    gerenteTeste = new GerQuiz();
    gerenteTeste->CriaQuiz("teste");
    gerenteTeste->SetQuiz("teste");
    gerenteTeste->SetPerguntaQuiz("0-0.1|pergunta|3|opt1|opt2|opt3|opt4|3");
    estadoTeste = SUCESSO;
}
void TesteModuloGerenteQuiz::TesteSucessoBuscarPergunta()
{
    try{
        if(SAIDASUCESSO_BUSCARPERGUNTA!=gerenteTeste->BuscarPergunta(CASOSUCESSO_BUSCARPERGUNTA)){
            estadoTeste = FALHA;
        }
    }catch(invalid_argument &e){
        estadoTeste = FALHA;
    }
}
void TesteModuloGerenteQuiz::TesteFalhaBuscarPergunta()
{
    try{
        gerenteTeste->BuscarPergunta(CASOFALHA_BUSCARPERGUNTA))
        estadoTeste = FALHA;
    }catch(invalid_argument &e){
        if(e.what()!=SAIDAFALHA_BUSCARPERGUNTA){
            estadoTeste = FALHA;
        }
    }
}
void TesteModuloGerenteQuiz::TesteTerminarBuscarPergunta()
{
    gerenteTeste->DeletarQuizSetado();
    delete gerenteTeste;
}
int TesteModuloGerenteQuiz::TesteExecutarBuscarPergunta()
{
    TesteIniciarBuscarPergunta();
    TesteSucessoBuscarPergunta();
    TesteFalhaBuscarPergunta();
    TesteTerminarBuscarPergunta();
    return estadoTeste;
}

const string TesteModuloGerenteQuiz::CASOSUCESSO_SETINDEXTOPICDISC = "0-0";
const string TesteModuloGerenteQuiz::CASOFALHA_SETINDEXTOPICDISC = "";
const string TesteModuloGerenteQuiz::SAIDAFALHA_SETINDEXTOPICDISC = "Indice Invalido";

void TesteModuloGerenteQuiz::TesteIniciarSetTopicDisc()
{
    gerenteTeste = new GerQuiz();
}
void TesteModuloGerenteQuiz::TesteSucessoSetTopicDisc()
{
    try{
        gerenteTeste->SetIndexTopicDisc(CASOSUCESSO_SETINDEXTOPICDISC);
    }catch(invalid_argument &e){
        estadoTeste = FALHA;
    }
}
void TesteModuloGerenteQuiz::TesteFalhaSetTopicDisc()
{
    try{
        gerenteTeste->SetIndexTopicDisc(CASOFALHA_SETINDEXTOPICDISC);
    }catch(invalid_argument &e){
        estadoTeste = FALHA;
    }
}
void TesteModuloGerenteQuiz::TesteTerminarSetTopicDisc()
{
    delete gerenteTeste;
}
int TesteModuloGerenteQuiz::TesteExecutarSetTopicDisc()
{
    TesteIniciarSetTopicDisc();
    TesteSucessoSetTopicDisc();
    TesteFalhaSetTopicDisc();
    TesteTerminarSetTopicDisc();
    return estadoTeste;
}

const string TesteModuloGerenteQuiz::CASOSUCESSO_EDITARPERGUNTA_INDICE = "1";
const string TesteModuloGerenteQuiz::CASOSUCESSO_EDITARPERGUNTA_PERGUNTA = "pergunta";
const string TesteModuloGerenteQuiz::CASOFALHA_EDITARPERGUNTA_INDICE = "0";
const string TesteModuloGerenteQuiz::CASOFALHA_EDITARPERGUNTA_PERGUNTA = "";

void TesteModuloGerenteQuiz::TesteIniciarEditarPergunta()
{
    gerenteTeste = new GerQuiz();
    gerenteTeste->CriaQuiz("teste");
    gerenteTeste->SetQuiz("teste");
    gerenteTeste->SetPerguntaQuiz("0-0.1|pergunta|4|opt1|opt2|opt3|opt4|2");
    gerenteTeste->SetIndexTopicDisc("0-0");
}
void TesteModuloGerenteQuiz::TesteSucessoEditarPergunta()
{
    try{
        gerenteTeste->EditarPergunta(CASOSUCESSO_EDITARPERGUNTA_INDICE,CASOSUCESSO_EDITARPERGUNTA_PERGUNTA);
    }catch(invalid_argument &e){
        estadoTeste = FALHA;
    }
}
void TesteModuloGerenteQuiz::TesteFalhaEditarPergunta()
{
    try{
        gerenteTeste->EditarPergunta(CASOFALHA_EDITARPERGUNTA_INDICE,CASOFALHA_EDITARPERGUNTA_PERGUNTA);
        estadoTeste = FALHA;
    }catch(invalid_argument &e){
        return;
    }
}
void TesteModuloGerenteQuiz::TesteTerminarEditarPergunta()
{
    gerenteTeste->DeletarQuizSetado();
    delete gerenteTeste;
}
int TesteModuloGerenteQuiz::TesteExecutarEditarPergunta()
{
    TesteIniciarEditarPergunta();
    TesteSucessoEditarPergunta();
    TesteFalhaEditarPergunta();
    TesteTerminarEditarPergunta();
    return estadoTeste;
}

const string TesteModuloGerenteQuiz::CASOSUCESSO_SETPERGUNTAQUIZ_PERGUNTA = "0-0.1|pergunta|5|opt1|opt2|opt3|opt4|3";
const string TesteModuloGerenteQuiz::CASOFALHA_SETPERGUNTAQUIZ_PERGUNTA = "";
const string TesteModuloGerenteQuiz::SAIDAFALHA_SETPERGUNTAQUIZ_PERGUNTA = "Erro!Pergunta Nula!";
const string TesteModuloGerenteQuiz::SAIDAFALHA_SETPERGUNTAQUIZ_ARQUIVO = "Erro Fatal!Quiz nao selecionado!";

void TesteModuloGerenteQuiz::TesteIniciarSetPerguntaQuiz()
{
    gerenteTeste = new GerQuiz();
    gerenteTeste->CriaQuiz("teste");
    gerenteTeste->SetQuiz("teste");
}
void TesteModuloGerenteQuiz::TesteSucessoSetPerguntaQuiz()
{
    try{
        gerenteTeste->SetPerguntaQuiz(CASOSUCESSO_SETPERGUNTAQUIZ_PERGUNTA);
    }catch(invalid_argument &e){
        estadoTeste = FALHA;
    }
}
void TesteModuloGerenteQuiz::TesteFalhaSetPerguntaQuiz()
{
    try{
        gerenteTeste->SetPerguntaQuiz(CASOFALHA_SETPERGUNTAQUIZ_PERGUNTA);
        estadoTeste = FALHA;
    }catch(invalid_argument &e){
        if(SAIDAFALHA_SETPERGUNTAQUIZ_PERGUNTA!=e.what()){
            estadoTeste = FALHA;
        }
    }
    try{
        gerenteTeste->DeletarQuizSetado();
        gerenteTeste->SetPerguntaQuiz(CASOSUCESSO_SETPERGUNTAQUIZ_PERGUNTA);
        estadoTeste = FALHA;
    }catch(invalid_argument &e){
        if(SAIDAFALHA_SETPERGUNTAQUIZ_ARQUIVO!=e.what()){
            estadoTeste = FALHA;
        }
    }
}
void TesteModuloGerenteQuiz::TesteTerminarSetPerguntaQuiz()
{
    delete gerenteTeste;
}
int TesteModuloGerenteQuiz::TesteExecutarSetPerguntaQuiz()
{
    TesteIniciarSetPerguntaQuiz();
    TesteSucessoSetPerguntaQuiz();
    TesteFalhaSetPerguntaQuiz();
    TesteTerminarSetPerguntaQuiz();
    return estadoTeste;
}

const string TesteModuloGerenteQuiz::CASOSUCESSO_CRIARQUIZ = "quiz";
const string TesteModuloGerenteQuiz::CASOFALHA_CRIARQUIZ = "quiz";
const string TesteModuloGerenteQuiz::SAIDAFALHA_CRIARQUIZ = "Erro Quiz ja Existe!";

void TesteModuloGerenteQuiz::TesteIniciarCriarQuiz()
{
    gerenteTeste = new GerQuiz();
}
void TesteModuloGerenteQuiz::TesteSucessoCriarQuiz()
{
    try{
        gerenteTeste->CriaQuiz(CASOSUCESSO_CRIARQUIZ);
    }catch(invalid_argument &e){
        estadoTeste = FALHA;
    }
}
void TesteModuloGerenteQuiz::TesteFalhaCriarQuiz()
{
    try{
        gerenteTeste->CriaQuiz(CASOFALHA_CRIARQUIZ);
        estadoTeste = FALHA;
    }catch(invalid_argument &e){
        if(CASOFALHA_CRIARQUIZ != e.what()){
            estadoTeste = FALHA;
        }
    }
}
void TesteModuloGerenteQuiz::TesteTerminarCriarQuiz()
{
    gerenteTeste->SetQuiz(CASOSUCESSO_CRIARQUIZ);
    gerenteTeste->DeletarQuizSetado();
    delete gerenteTeste;
}
int TesteModuloGerenteQuiz::TesteExecutarCriarQuiz()
{
    TesteIniciarCriarQuiz();
    TesteSucessoCriarQuiz();
    TesteFalhaCriarQuiz();
    TesteTerminarCriarQuiz();
    return estadoTeste;
}

const string TesteModuloGerenteQuiz::CASOSUCESSO_SETQUIZ = "quiz";
const string TesteModuloGerenteQuiz::CASOFALHA_SETQUIZ = "";
const string TesteModuloGerenteQuiz::SAIDAFALHA_SETQUIZ = "Erro,Nao e possivel setar o quiz";

void TesteModuloGerenteQuiz::TesteIniciarSetQuiz()
{
    gerenteTeste = new GerQuiz();
    gerenteTeste->CriaQuiz(CASOSUCESSO_SETQUIZ);
}
void TesteModuloGerenteQuiz::TesteSucessoSetQuiz()
{
    try{
        gerenteTeste->SetQuiz(CASOSUCESSO_SETQUIZ);
    }catch(invalid_argument &e){
        estadoTeste = FALHA;
    }
}
void TesteModuloGerenteQuiz::TesteFalhaSetQuiz()
{
    try{
        gerenteTeste->SetQuiz(CASOFALHA_SETQUIZ);
        estadoTeste = FALHA;
    }catch(invalid_argument &e){
        if(e.what()!=SAIDAFALHA_SETQUIZ){
            estadoTeste = FALHA;
        }
    }
}
void TesteModuloGerenteQuiz::TesteTerminarSetQuiz()
{
    gerenteTeste->DeletarQuizSetado();
    delete gerenteTeste;
}
int TesteModuloGerenteQuiz::TesteExecutarSetQuiz()
{
    TesteIniciarSetQuiz();
    TesteSucessoSetQuiz();
    TesteFalhaSetQuiz();
    TesteTerminarSetQuiz();
    return estadoTeste;
}


const string TesteModuloGerenteQuiz::CASOSUCESSO_DELETARPERGUNTAQUIZ = "3";
const string TesteModuloGerenteQuiz::CASOFALHA_DELETARPERGUNTAQUIZ = "-1";
const string TesteModuloGerenteQuiz::SAIDAFALHA_DELETARPERGUNTAQUIZ = "Erro!Pergunta Inexistente!";
const string TesteModuloGerenteQuiz::SAIDAFALHA_DELETARPERGUNTAQUIZ_ARQUIVO = "Erro!Quiz nao Selecionado";

void TesteModuloGerenteQuiz::TesteIniciarDeletarPerguntaQuiz()
{
    gerenteTeste = new GerQuiz();
    gerenteTeste->CriaQuiz("teste");
    gerenteTeste->SetQuiz("teste");
    gerenteTeste->SetPerguntaQuiz("0-0.3|pergunta|opt1|opt2|opt3|opt4|3");
}
void TesteModuloGerenteQuiz::TesteSucessoDeletarPerguntaQuiz()
{
    try{
        gerenteTeste->DeletarPerguntaQuiz(CASOSUCESSO_DELETARPERGUNTAQUIZ);
    }catch(invalid_argument &e){
        estadoTeste = FALHA;
    }
}
void TesteModuloGerenteQuiz::TesteFalhaDeletarPerguntaQuiz()
{
    try{
        gerenteTeste->DeletarPerguntaQuiz(CASOFALHA_DELETARPERGUNTAQUIZ);
        estadoTeste = FALHA;
    }catch(invalid_argument &e){
        if(e.what()!=SAIDAFALHA_DELETARPERGUNTAQUIZ){
            estadoTeste = FALHA;
        }
    }
    try{
        gerenteTeste->DeletarQuizSetado();
        gerenteTeste->DeletarPerguntaQuiz(CASOFALHA_DELETARPERGUNTAQUIZ);
        estadoTeste = FALHA;
    }catch(invalid_argument &e){
        if(e.what()!=SAIDAFALHA_DELETARPERGUNTAQUIZ_ARQUIVO){
            estadoTeste = FALHA;
        }
    }
}
void TesteModuloGerenteQuiz::TesteTerminarDeletarPerguntaQuiz()
{
    delete gerenteTeste;
}
int TesteModuloGerenteQuiz::TesteExecutarDeletarPerguntaQuiz()
{
    TesteIniciarDeletarPerguntaQuiz();
    TesteSucessoDeletarPerguntaQuiz();
    TesteFalhaDeletarPerguntaQuiz();
    TesteTerminarDeletarPerguntaQuiz();
    return estadoTeste;
}

const string TesteModuloGerenteQuiz::CASOSUCESSO_DELETARQUIZSETADO = "quiz";
const string TesteModuloGerenteQuiz::CASOFALHA_DELETARQUIZSETADO = "";
const string TesteModuloGerenteQuiz::SAIDAFALHA_DELETARQUIZSETADO = "Erro Quiz nao selecionado!";
const string TesteModuloGerenteQuiz::SAIDAFALHA_DELETARQUIZSETADO_ARQUIVO = "Erro Quiz nao existe!";

void TesteModuloGerenteQuiz::TesteIniciarDeletarQuizSetado()
{
    gerenteTeste = new GerQuiz();
    gerenteTeste->CriaQuiz(CASOSUCESSO_DELETARQUIZSETADO);
    gerenteTeste->SetQuiz(CASOSUCESSO_DELETARQUIZSETADO);
}
void TesteModuloGerenteQuiz::TesteSucessoDeletarQuizSetado()
{
    try{
        gerenteTeste->DeletarQuizSetado();
    }catch(invalid_argument &e){
        estadoTeste = FALHA;
    }
}
void TesteModuloGerenteQuiz::TesteFalhaDeletarQuizSetado()
{
    try{
        gerenteTeste->DeletarQuizSetado();
        estadoTeste = FALHA;
    }catch(invalid_argument &e){
        if(e.what!=SAIDAFALHA_DELETARQUIZSETADO){
            estadoTeste = FALHA;
        }
    }

    try{
        gerenteTeste->SetQuiz(CASOSUCESSO_DELETARQUIZSETADO);
        gerenteTeste->DeletarQuizSetado();
        estadoTeste = FALHA;
    }catch(invalid_argument &e){
        if(e.what()!=SAIDAFALHA_DELETARQUIZSETADO_ARQUIVO){
            estadoTeste = FALHA;
        }
    }
}
void TesteModuloGerenteQuiz::TesteTerminarDeletarQuizSetado()
{
    delete gerenteTeste;
}
int TesteModuloGerenteQuiz::TesteExecutarDeletarQuizSetado()
{
    TesteIniciarDeletarQuizSetado();
    TesteSucessoDeletarQuizSetado();
    TesteFalhaDeletarQuizSetado();
    TesteTerminarDeletarQuizSetado();
    return estadoTeste;
}

TesteModuloGerenteQuiz::TesteModuloGerenteQuiz()
{

}

int TesteModuloGerenteQuiz::executar()
{
    TesteExecutarBuscarPergunta();
    TesteExecutarCriarQuiz();
    TesteExecutarDeletarPerguntaQuiz();
    TesteExecutarDeletarQuizSetado();
    TesteExecutarEditarPergunta();
    TesteExecutarSetPerguntaQuiz();
    TesteExecutarSetQuiz();
    TesteExecutarSetTopicDisc();
    return estadoTeste;
}
