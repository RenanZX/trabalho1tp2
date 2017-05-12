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
                    g->AddPerguntas();
                    break;
               case EDITARP:
                    g->EditPer();
                    break;
               case DELELETARP:
                    g->DelPer();
                    break;
                case SAIRP:
                    fecha = true;
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
                    g->CarregaQuizEd();
                    break;
                case SELQUIZ:
                    g->SelecionarArq();
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
            cout << e.what() << endl;
            system("pause");
        }
    }
}
