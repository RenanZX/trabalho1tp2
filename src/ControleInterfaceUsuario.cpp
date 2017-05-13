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
const int InterfaceUserQuiz::SELP = 3;
const int InterfaceUserQuiz::SAIR = 4;

void InterfaceUserGerQuiz::EditarQuiz()throw(runtime_error)
{
    int opt;
    bool fecha = false;

    while(!fecha){/*enquanto o usuario nao fechar as opcoes o loop ainda perpetuara*/
        try{
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
                    g->AdicionarPerguntas();
                    break;
               case EDITARP:
                    g->EditarPergunta();
                    break;
               case DELELETARP:
                    g->DeletarPergunta();
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
    g = new GerQuiz();
    mkdir((g->getFolderFilesName()).c_str()); /*cria um diretorio na raiz do usuario*/
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
                    g->CriarQuiz();
                    break;
                case LOGQUIZ:
                    g->CarregaQuizEditar();
                    break;
                case SELQUIZ:
                    g->SelecionarArquivo();
                    break;
                case EDITQUIZ:
                    EditarQuiz();
                    break;
                case DELQUIZ:
                    g->ApagarQuiz();
                    break;
                case SAIR:
                    fecha = true;
                    free(g);
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
    Quiz *q = new Quiz();

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

            switch(opt){/*chama um metodo dependendo da opcao recebida*/
                case COMECARQUIZ:
                    q->ComecarQuiz();/*comeca o quiz do usuario*/
                    break;
                case CARREGAP:
                    q->CarregarQuiz();/*carrega o quiz para o usuario*/
                    break;
                case SELP:
                    q->SelecionarPergunta();/*seletor de perguntas*/
                    break;
                case SAIR:
                    fecha = true;
                    free(q);
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
