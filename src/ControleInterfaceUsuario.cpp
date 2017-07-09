#include "ControleInterfaceUsuario.h"

const int InterfaceGerenteQuiz::ADICIONARP = 1;  /*constantes*/
const int InterfaceGerenteQuiz::EDITARP = 2;
const int InterfaceGerenteQuiz::DELELETARP = 3;
const int InterfaceGerenteQuiz::SAIRP = 4;
const int InterfaceGerenteQuiz::CREATEQUIZ = 1;
const int InterfaceGerenteQuiz::LOGQUIZ = 2;
const int InterfaceGerenteQuiz::EDITQUIZ = 4;
const int InterfaceGerenteQuiz::SELQUIZ = 3;
const int InterfaceGerenteQuiz::DELQUIZ = 5;
const int InterfaceGerenteQuiz::SAIR = 6;
const int InterfaceQuiz::COMECARQUIZ = 1;
const int InterfaceQuiz::CARREGAP = 2;
const int InterfaceQuiz::SELP = 3;
const int InterfaceQuiz::SAIR = 4;
const int InterfaceQuiz::RESPONDER = 1;
const int InterfaceQuiz::PULAR = 2;
const int InterfaceQuiz::SAIRP = 3;
const int InterfaceQuiz::SELECIONARQUIZ = 3;

void InterfaceGerenteQuiz::AdicionarPerguntas()throw(runtime_error)
{
    /*declaracao de variaveis*/
    string saida,strread;
    string respostas;
    char verificar;
    std::stringstream saidastream;
    string disciplina,topico;
    string index;

    cout << "Digite a disciplina que deseja adicionar ou ja existente:" << endl;
    getline(cin,disciplina,'\n');
    tabela.setTableDisc(disciplina);
    cout << "Digite um topico relacionado a esta disciplina:" << endl;
    getline(cin,topico,'\n');
    tabela.setTableTopics(topico);

    index = tabela.getGeneratedIndex();

    gerente->SetIndexTopicDisc(index);
    system(CLEAR);/*limpa a tela*/
    CarregarQuiz();/*carrega o quiz*/
    double menor = lastIndexFile; /*converte a ultima variavel lida ao carregar o quiz em menor*/
    double maior;/*declara double maior*/
    int i = 0,j = 0;

    try{/*testa se o arquivo existe*/
        while((verificar!='N')&&(verificar!='n')){
            cout << "Digite o indice da pergunta que deseja adicionar:" << endl;
            getline(cin,strread,'\n');
            maior = atof(strread.c_str());

            if(maior > menor){/*verifica se o usuario digitou o index da pergunta corretamente*/
                saida = index;
                saida.append(strread);
                saida.append("|");/*prepara a string de saida a ser escrita no arquivo*/
                cout << "Digite a pergunta que deseja adicionar:" << endl;
                getline(cin,strread,'\n');
                saida.append(strread);
                saida.append("|");
                cout << "Deseja adicionar uma pontuacao?(S/N)" << endl;
                cin >> verificar;
                cin.ignore(1000,'\n');
                if((verificar!='n')&&(verificar!='N')){
                    cout << "Digite a pontuacao que valera esta questao:" << endl;
                    getline(cin,strread,'\n');
                }else{
                    strread = "1";
                }
                saida.append(strread);
                saida.append("|");
                verificar = 0;
                while((verificar!='n')&&(verificar!='N')){
                    cout << "Digite a opcao " << i+1 << " de resposta para essa questao:" << endl;
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
                cout << "Escolha a opcao correspondente a resposta correta(1 - " << i << "):" << endl;
                getline(cin,strread,'\n');
                if((atof(strread.c_str()) <= 0)&&(atof(strread.c_str()) > i)){
                    throw invalid_argument("Opcao inexistente");
                }
                saida.append(strread);
                saida.append("|\n");
                gerente->SetPerguntaQuiz(saida);
                cout << "Deseja adicionar mais perguntas?(S/N)" << endl;
                cin >> verificar;
                cin.ignore(1000,'\n');
            }else{
                cout << "Dados Inseridos incorretamente!" << endl;/*caso o usuario nao insira os dados corretamente*/
            }
        }
    }catch(invalid_argument &e){
        throw invalid_argument(e.what()); /*feedback de erro*/
    }
}

void InterfaceGerenteQuiz::EditarPerguntas()throw(runtime_error)
{
    string erro;
    string disciplina,topico;
    string data,ind;
    string pergunta;
    std::stringstream inteiro;
    int i = 0;

    try{
        tabela.showTableDisc();
        cout << "Digite a disciplina na qual deseja editar a pergunta:" << endl;
        getline(cin,disciplina,'\n');
        tabela.findTableDisc(disciplina);
        tabela.showTableTopics();
        cout << "Digite o topico no qual deseja editar a pergunta:" << endl;
        getline(cin,topico,'\n');
        tabela.findTableTopics(topico);
        string indice = tabela.getGeneratedIndex();

        gerente->SetIndexTopicDisc(indice);
        system(CLEAR);

        CarregarQuiz();
        cout << "Indique o indice da pergunta que deseja editar:" << endl;
        getline(cin,data,'\n');
        ind = data;
        pergunta.append(indice+data);
        pergunta.append("|");
        data = gerente->BuscarPergunta(data);/*busca a pergunta no arquivo*/
        if(data == ""){/*testa se a pergunta e nula e lança uma excessao*/
            throw invalid_argument("Erro!Pergunta Inexistente.");
        }else{
            system(CLEAR);
            cout << FormularPerguntaImprimir(data) << endl;
            limiterespostas = atoi((PegaAtributo(data,8)).c_str());
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
            gerente->EditarPergunta(ind,pergunta);
        }
    }catch(invalid_argument &e){
        erro = e.what();
        throw runtime_error(erro);
    }

}

string InterfaceGerenteQuiz::FormularPerguntaImprimir(string pergunta) /*formula uma pergunta do arquivo a ser imprimida ao usuario*/
{
    string index,dadopergunta,nota,retorne;
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
    retorne = retorno.str();
    retorno.str("");
    return retorne;
}

void InterfaceGerenteQuiz::DeletarPergunta()throw(runtime_error)
{
    string disciplina,topico;

    try{
        tabela.showTableDisc();
        cout << "Digite a disciplina na qual deseja deletar a pergunta:" << endl;
        getline(cin,disciplina,'\n');
        tabela.findTableDisc(disciplina);
        tabela.showTableTopics();
        cout << "Digite o topico no qual deseja deletar a pergunta:" << endl;
        getline(cin,topico,'\n');
        tabela.findTableTopics(topico);
        CarregarQuiz();

        string indstr;/*indice da pergunta*/

        cout << "Digite o indice da pergunta que deseja excluir:" << endl;
        cin >> indstr;
        cout << "Deletando Pergunta..." << endl;
        gerente->DeletarPerguntaQuiz(indstr);
        cout << "Pergunta deletada com sucesso!" << endl;/*feedback ao usuario*/
        PAUSE;
    }catch(invalid_argument &e){
        throw runtime_error(e.what());
    }
}

void InterfaceGerenteQuiz::CriarQuiz()throw(runtime_error) /*cria um novo arquivo com quiz*/
{
    string nomfile;
    char confirma;

    try{
        while((confirma!='N')&&(confirma!='n')){
            cout << "Digite o nome do Quiz que deseja criar:" << endl;
            getline(cin,nomfile,'\n');/*faz a leitura do nome do arquivo*/
            gerente->CriaQuiz(nomfile);
            cout << "Deseja criar mais quizes?(S/N)" << endl;/*pergunta ao usuario se ele quer criar mais quizes*/
            cin >> confirma;/*recebe a confirmacao*/
            cin.ignore(1000,'\n');
        }
    }catch(invalid_argument &e){
        cout << e.what() << endl;
    }
}

string InterfaceGerenteQuiz::PegaAtributo(string dado,int atributo)
{
    int pos = 0;
    string data1;
    int i = 0;

    if(atributo == 0){
        pos = dado.find(".")+1;
        data1 = dado.substr(pos,dado.find("|")); /*indice da questao*/
        data1 = data1.substr(0,data1.find("|"));
        return data1;
    }

    for(i=1;i<=atributo;i++){
        pos = dado.find("|")+1;
        dado = dado.substr(pos,dado.length());
        data1 = dado.substr(0,dado.find("|"));/*pergunta*/
    }

    return data1;
}

void InterfaceGerenteQuiz::CarregarQuiz()throw(runtime_error)
{
    string strread;/*string a ser lida*/
    string index,pergunta,resposta;
    char read[1000];
    FILE* f = fopen(gerente->getQuizFileNameSeted().c_str(),"rt");/*faz a leitura do arquivo*/

    fseek(f,0,SEEK_END);
    int tam = ftell(f);
    rewind(f);
    if((f!=NULL)&&(tam>0)){/*e necessario saber se o arquivo existe,e se existe e necessario saber se ele nao esta vazio*/
        cout << "Perguntas" << endl;
        while(fgets(read,sizeof(read),f)){
            strread = read;
            cout << PegaAtributo(strread,0) << ". " << PegaAtributo(strread,1) << "   Res.:" << PegaAtributo(strread,2) << endl;
            lastIndexFile = atoi(PegaAtributo(strread,0).c_str());
        }
    }else{
        fclose(f);
        throw invalid_argument("nao existem perguntas");/*printa a mensagem para o usuario*/
    }
}

void InterfaceGerenteQuiz::SelecionarQuiz()throw(runtime_error)
{
    DIR *pasta;
    struct dirent *lsdir;
    pasta = opendir((root+gerente->getFolderFilesName()).c_str());/*abre um diretorio de arquivos contendo quizes*/
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
        gerente->SetQuiz(saida);/*encontrando o nome do arquivo e setado juntamente com o diretorio onde ele sera armazenado*/
        cout << "Quiz selecionado com sucesso!" << endl;/*caso de sucesso imprime para o usuario*/
        PAUSE;
    }else{
        throw invalid_argument("Erro!Falha na seleção do Quiz");/*caso de falha lanca uma excessão*/
    }
}

void InterfaceGerenteQuiz::EditarQuiz()throw(runtime_error)
{
    int opcao;
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
            cin >> opcao;
            getchar();

            switch(opcao)
            {
               case ADICIONARP:
                    AdicionarPerguntas();
                    break;
               case EDITARP:
                    EditarPerguntas();
                    break;
               case DELELETARP:
                    DeletarPergunta();
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
            PAUSE;
        }
    }
}

void InterfaceGerenteQuiz::ApagarQuiz()throw(runtime_error)
{
    char confirma;

    system(CLEAR);
    while((confirma!='S')&&(confirma!='s')&&(confirma!='N')&&(confirma!='n')){
        cout << "Voce realmente deseja apagar o quiz?(S/N)" << endl;
        cin >> confirma;
        cin.ignore(1000,'\n');
    }
    if((confirma=='s')||(confirma=='S')){
        gerente->DeletarQuizSetado();
        cout << "Quiz Apagado com sucesso" << endl;
    }
}

void InterfaceGerenteQuiz::executarOpcao(int opcao)throw(runtime_error)
{
    if(gerente == NULL) {
        gerente = new GerQuiz();
    }

    switch(opcao){/*opcoes do usuario*/
        case CREATEQUIZ:
            CriarQuiz();
            break;
        case LOGQUIZ:
             CarregarQuiz();
             break;
        case SELQUIZ:
             SelecionarQuiz();
             break;
        case EDITQUIZ:
             EditarQuiz();
             break;
        case DELQUIZ:
             ApagarQuiz();
             break;
    }
}

void InterfaceGerenteQuiz::MostrarOpcoes()throw(runtime_error)
{
    bool fecha = false;
    int opcao;
    gerente = new GerQuiz();
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
            cin  >> opcao;
            getchar();

            if(opcao==SAIR){
                free(gerente);
                fecha = true;
            }else{
                executarOpcao(opcao);
            }

        }catch(invalid_argument &e){
            system(CLEAR);
            free(gerente);
            cout << e.what() << endl;/*manda um feedback se algo der errado*/
            PAUSE;
        }
    }
}

void InterfaceEstudo::executarOpcao(int opcao)throw(runtime_error)
{
    if(quiz == NULL) { quiz = new Quiz(); }

    switch(opcao){/*chama um metodo dependendo da opcao recebida*/
        case COMECARQUIZ:
            ComecarQuiz();/*comeca o quiz do usuario*/
            break;
        case CARREGAP:
            CarregarQuiz();/*carrega o quiz para o usuario*/
            break;
        case SELP:
            SelecionarPergunta();/*seletor de perguntas*/
            break;
    }
}


void InterfaceEstudo::MostrarOpcoes()throw(runtime_error)
{
    bool fecha = false;
    int opcao;
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
            cin >> opcao;/*recebe a opcao do usuario*/
            cin.ignore(1000,'\n');

            if(opcao==SAIR){
                free(quiz);
                fecha = true;
            }else{
                executarOpcao(opcao);
            }


        }catch(invalid_argument &e){
            system(CLEAR);
            cout << e.what() << endl;
            PAUSE;
        }
    }
}

void InterfaceEstudo::selecionarTopicosDisciplinas()throw(invalid_argument)
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
    strstream << (entrada - 1);
    quiz->SelecionarDisciplina(strstream.str());
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
    strstream.str("");
    strstream << (entrada - 1);
    quiz->SelecionarTopico(strstream.str());
    strstream.str("");
    fclose(f);
}

string InterfaceEstudo::SelecionarQuiz()throw(invalid_argument)
{
    GerQuiz *gerente = new GerQuiz();
    DIR *pasta;
    struct dirent *lsdir;
    pasta = opendir((root+gerente->getFolderFilesName()).c_str());/*abre um diretorio de arquivos contendo quizes*/
    int nroarquivo=1;
    string saida;   /*string saida que servira para armazenar o input do usuario*/
    string nomesarquivos;   /*string nomesarquivos que contem todos os nomes de arquivos da pasta*/
    free(gerente);

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
        cout << "Quiz selecionado com sucesso!" << endl;/*caso de sucesso imprime para o usuario*/
        PAUSE;
    }else{
        throw invalid_argument("Erro!Falha na seleção do Quiz");/*caso de falha lanca uma excessão*/
    }
    return saida;
}

void InterfaceEstudo::ComecarQuiz()throw(invalid_argument)
{
    std::vector<string> relatorioquestoes;
    string nome;
    //tempo tempoquestao;
    int resposta;
    int opcoes = 0;
    bool saiu = false;

    try{
        nome = SelecionarQuiz();
        quiz->lerQuiz(nome);
        Pergunta *p;
        system(CLEAR);
        while((!quiz->QuizTerminou())&&(!saiu)){/*testa se o user saiu ou se a lista de perguntas ainda existem perguntas*/
            system(CLEAR);
            p = quiz->QuizgetPergunta();
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
                    quiz->QuizResponderPergunta(p,resposta);
                    free(p);
                    break;
                case PULAR:
                    quiz->QuizPularPergunta(p);
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
            relatorioquestoes = quiz->QuizgetRelatorio();
            for(std::vector<string>::const_iterator relatquestao=relatorioquestoes.begin();relatquestao!=relatorioquestoes.end();relatquestao++){
                cout << *relatquestao << endl;
            }
            cout << "Voce acertou " << quiz->getNumeroAcertos() << " perguntas" << endl;/*mostra a pontuacao do usuario*/
            cout << "Voce errou " << quiz->getNumeroErros() << " perguntas" << endl;
            cout << "Voce conseguiu" << quiz->getPontosUsuario() << " pontos" << endl;
            if(quiz->getNumeroAcertos() > quiz->getNumeroErros()){
                cout << "Parabens!Sua pontuacao foi excelente" << endl;/*feedback para o usuario*/
            }else if(quiz->getNumeroAcertos() < quiz->getNumeroErros()){
                cout << "Que pena,sua pontuacao foi terrivel mas voce pode tentar mais vezes" << endl;
            }else{
                cout << "Quase!voce quase conseguiu uma boa pontuacao" << endl;
            }
            PAUSE;
        }
        delete quiz;
    }catch(invalid_argument){
        throw invalid_argument("Erro nao foi possivel comecar o quiz");
    }
}

void InterfaceEstudo::CarregarQuiz()throw(invalid_argument)
{
    int perguntas = 0;

    try{
        perguntas = quiz->ImprimirPerguntas();
        cout << "Existem no Total " << perguntas << " Perguntas" << endl;/*total de perguntas*/
        PAUSE;
    }catch(invalid_argument &e){
        throw invalid_argument(e.what());
    }
}

void InterfaceEstudo::SelecionarPergunta()throw(invalid_argument)
{
    string ind;
    try{
        bool fechar = false;
        while(!fechar){
            try{
                cout << "Digite o(s) indice(s) da(s) pergunta(s) que deseja selecionar(separe os indices por , ex.:1,2.):" << endl;
                getline(cin,ind,'\n');
                quiz->SelecionarPerguntas(ind);
            }catch(invalid_argument &e){
                throw invalid_argument(e.what());
                fechar = true;
            }
        }
        cout << "Perguntas Selecionadas com Sucesso!" << endl;
        PAUSE;
    }catch(invalid_argument &e){
        throw invalid_argument(e.what());
    }
}
