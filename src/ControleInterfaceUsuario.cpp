#include "ControleInterfaceUsuario.h"

const int InterfaceUserGerQuiz::ADICIONARP = 1;  /*constantes*/
const int InterfaceUserGerQuiz::EDITARP = 2;
const int InterfaceUserGerQuiz::DELELETARP = 3;
const int InterfaceUserGerQuiz::SAIRP = 4;
const int InterfaceUserGerQuiz::CREATEQUIZ = 1;
const int InterfaceUserGerQuiz::LOGQUIZ = 2;
const int InterfaceUserGerQuiz::EDITQUIZ = 4;
const int InterfaceUserGerQuiz::SELQUIZ = 3;
const int InterfaceUserGerQuiz::DELQUIZ = 5;
const int InterfaceUserGerQuiz::SAIR = 6;
const int InterfaceUserQuiz::COMECARQUIZ = 1;
const int InterfaceUserQuiz::CARREGAP = 2;
const string InterfaceUserGerQuiz::TABLETOPICS = "tabletop";
const string InterfaceUserGerQuiz::TABLEDISC = "tabledisc";
const int InterfaceUserQuiz::SELP = 3;
const int InterfaceUserQuiz::SAIR = 4;

void InterfaceUserGerQuiz::setTableTopics(string topico)
{
    FILE *f = fopen(TABLETOPICS.c_str(),"r+");
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
        f = fopen(TABLETOPICS.c_str(),"w");
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

void InterfaceUserGerQuiz::setTableDisc(string disciplina)
{
    FILE *f = fopen(TABLEDISC.c_str(),"r+");
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
        f = fopen(TABLEDISC.c_str(),"w");
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


string InterfaceUserGerQuiz::AddTopDisc()throw(runtime_error)
{
    index = "";
    string disciplina,topico;

    cout << "Digite a disciplina que deseja adicionar ou ja existente:" << endl;
    getline(cin,disciplina,'\n');
    setTableDisc(disciplina);
    cout << "Digite um topico relacionado a esta disciplina:" << endl;
    getline(cin,topico,'\n');
    setTableTopics(topico);

    return index;
}

void InterfaceUserGerQuiz::findTableTopics(string topico)throw(invalid_argument)
{
    FILE *f = fopen(TABLETOPICS.c_str(),"r+");
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

void InterfaceUserGerQuiz::findTableDisc(string disciplina)throw(invalid_argument)
{
    FILE *f = fopen(TABLEDISC.c_str(),"r+");
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

void InterfaceUserGerQuiz::showTableDisc()
{
    FILE *f = fopen(TABLEDISC.c_str(),"r+");
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

void InterfaceUserGerQuiz::showTableTopics()
{
    FILE *f = fopen(TABLETOPICS.c_str(),"r+");
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

string InterfaceUserGerQuiz::EditarTopDisc()throw(runtime_error)
{
    index = "";
    string erro;
    string disciplina,topico;

    try{
        showTableDisc();
        cout << "Digite a disciplina na qual deseja editar a pergunta:" << endl;
        getline(cin,disciplina,'\n');
        findTableDisc(disciplina);
        showTableTopics();
<<<<<<< HEAD
    }
string InterfaceUserGerQuiz::EditarTopDisc()throw(runtime_error)
{
    index = "";
    string disciplina,topico;

    try{
        cout << "Digite a disciplina na qual deseja editar a pergunta:" << endl;
        getline(cin,disciplina,'\n');
        findTableDisc(disciplina);
=======
>>>>>>> b667ceef3fed65dbdc4f880e8f53c7153813a487
        cout << "Digite o topico no qual deseja editar a pergunta:" << endl;
        getline(cin,topico,'\n');
        findTableTopics(topico);
    }catch(invalid_argument &e){
        erro = e.what();
        throw runtime_error(erro);
    }
    return index;
}

string InterfaceUserGerQuiz::ExcluirTopDisc()throw(runtime_error)
{
    index = "";
    string disciplina,topico;

    try{
        showTableDisc();
        cout << "Digite a disciplina na qual deseja deletar a pergunta:" << endl;
        getline(cin,disciplina,'\n');
        findTableDisc(disciplina);
        showTableTopics();
        cout << "Digite o topico no qual deseja deletar a pergunta:" << endl;
        getline(cin,topico,'\n');
        findTableTopics(topico);
    }catch(invalid_argument &e){
        throw runtime_error(e.what());
    }
    return index;
}

void InterfaceUserGerQuiz::EditarQuiz()throw(runtime_error)
{
    int opcao;
    bool fecha = false;
    string dadoindice;

    while(!fecha){/*enquanto o usuario nao fechar as opcoes o loop ainda perpetuara*/
        try{
            system(CLEAR);/*interage com o usuario mostrando as opcoes*/
            cout << "Gerenciador de Quiz" << endl;
            cout << ADICIONARP << ".Adicionar Nova(s) Pergunta(s)" << endl;
            cout << EDITARP << ".Editar Pergunta(s)" << endl;
            cout << DELELETARP << ".Excluir Pergunta(s)" << endl;
            cout << SAIRP << ".Sair" << endl;
            cout << "Escolha uma opcao" << endl;
            cin >> opcao;
            getchar();

            switch(opcao)
            {
               case ADICIONARP:
                    dadoindice = AddTopDisc();
                    gerente->SetIndexTopicDisc(dadoindice);
                    gerente->AdicionarPerguntas();
                    break;
               case EDITARP:
                    dadoindice = EditarTopDisc();
                    gerente->SetIndexTopicDisc(dadoindice);
                    gerente->EditarPergunta();
                    break;
               case DELELETARP:
                    dadoindice = ExcluirTopDisc();
                    gerente->SetIndexTopicDisc(dadoindice);
                    gerente->DeletarPergunta();
                    break;
                case SAIRP:
                    fecha = true;
                    break;
                default:
                    break;
            }
        }catch(invalid_argument &e){
            system(CLEAR);
            cout << e.what() << endl;/*manda um feedback se algo der errado*/
            system("pause");
        }
    }

}

void InterfaceUserGerQuiz::executar()throw(runtime_error)
{
    bool fecha = false;
    int opt;
    gerente = new GerQuiz();
    mkdir((gerente->getFolderFilesName()).c_str()); /*cria um diretorio na raiz do usuario*/
    while(!fecha){
        try{
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
                    gerente->CriarQuiz();
                    break;
                case LOGQUIZ:
                    gerente->CarregaQuizEditar();
                    break;
                case SELQUIZ:
                    gerente->SelecionarArquivo();
                    break;
                case EDITQUIZ:
                    EditarQuiz();
                    break;
                case DELQUIZ:
                    gerente->ApagarQuiz();
                    break;
                case SAIR:
                    fecha = true;
                    free(gerente);
                    break;
                default:
                    break;
                }
        }catch(invalid_argument &e){
            system(CLEAR);
            cout << e.what() << endl;/*manda um feedback se algo der errado*/
            system("pause");
        }
    }
}


void InterfaceUserQuiz::executar()throw(runtime_error)
{
    bool fecha = false;
    int opt;
    Quiz *quiz = new Quiz();

    while(!fecha){
        try{
            system(CLEAR);/*interage com o usuario*/
            cout << "Quiz" << endl;
            cout << COMECARQUIZ << ". Comecar Quiz" << endl;
            cout << CARREGAP << ". Carregar Perguntas" << endl;
            cout << SELP << ". Selecionar Perguntas" << endl;
            cout << SAIR << ". Sair" << endl;
            cout << "Escolha uma opcao" << endl;
            cin >> opt;/*recebe a opcao do usuario*/
            cin.ignore(1000,'\n');

            switch(opt){/*chama um metodo dependendo da opcao recebida*/
                case COMECARQUIZ:
                    quiz->ComecarQuiz();/*comeca o quiz do usuario*/
                    break;
                case CARREGAP:
                    quiz->CarregarQuiz();/*carrega o quiz para o usuario*/
                    break;
                case SELP:
                    quiz->SelecionarPergunta();/*seletor de perguntas*/
                    break;
                case SAIR:
                    fecha = true;
                    free(quiz);
                    break;
                default:
                    break;
            }
        }catch(invalid_argument &e){
            system(CLEAR);
            cout << e.what() << endl;
            system("pause");
        }
    }
}
