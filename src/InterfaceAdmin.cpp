#include "InterfaceAdmin.hpp"

const char InterfaceAdmin::USUARIOS = 'u';
const char InterfaceAdmin::DISCIPLINAS = 'd';
const char InterfaceAdmin::QUIZ = 'q';

const int InterfaceAdmin::CRIAR = 1;
const int InterfaceAdmin::ALTERAR = 2;
const int InterfaceAdmin::DELETAR = 3;
const int InterfaceAdmin::ADDTOPICO = 4;

const int InterfaceAdmin::VOLTAR = 9;
const int InterfaceAdmin::SAIR = 0;


void InterfaceAdmin::mostrarOpcoes(Usuario u, bool* fechar)throw(runtime_error)
{
	fechaSessao = false;
	int opt;
	while(!fechaSessao){
		try{
			//system(CLEAR);

			cout << "Bem-vindo, " << u.getNome() << ". Escolha uma função: " << endl;/*opcoes mostradas ao usuario*/
			cout << USUARIOS << " - Administrar usuários" << endl;
			cout << DISCIPLINAS << " - Administrar disciplinas" << endl;
			cout << QUIZ << " - Administrar quiz" << endl;
			cout << VOLTAR << " - Deslogar" << endl;
			cout << SAIR << " - Sair" << endl;
			cout << "Escolha a opção:" << endl;
			cin  >> opt;
			getchar();

			if (opt == VOLTAR)
			{
				fechaSessao = true;
				return;
			}
			if (opt == SAIR)
			{
				*fechar = true;
				return;
			}
			fechaCategoria = false;
			switch(opt){

				case 'u':
					while(!fechaCategoria){
						cout << "Administração de usuários." << endl;
						cout << CRIAR << " - Criar usuário" << endl;
						cout << ALTERAR << " - Alterar usuário" << endl;
						cout << DELETAR << " - Deletar usuário" << endl;
						cout << VOLTAR << " - Voltar" << endl;
						cout << SAIR << " - Sair" << endl;
						cout << "Escolha a opção:" << endl;
						cin  >> opt;
						getchar();

						if (opt == VOLTAR)
						{
							fechaCategoria = true;
							break;
						}
						if (opt == SAIR)
						{
							*fechar = true;
							return;
						}
						opt += 10;
					}
					break;

				case 'd':
					while(!fechaCategoria){
						cout << "Administração de disciplinas." << endl;
						cout << CRIAR << " - Criar disciplina" << endl;
						cout << ALTERAR << " - Alterar disciplina" << endl;
						cout << DELETAR << " - Deletar disciplina" << endl;
						cout << ADDTOPICO << " - Adicionar tópico" << endl;
						cout << VOLTAR << " - Voltar" << endl;
						cout << SAIR << " - Sair" << endl;
						cout << "Escolha a opção:" << endl;
						cin  >> opt;
						getchar();

						if (opt == VOLTAR)
						{
							fechaCategoria = true;
							break;
						}
						if (opt == SAIR)
						{
							*fechar = true;
							return;
						}
						opt += 20;
					}
					break;

				case 'q':
					while(!fechaCategoria){
						cout << "Administração de quiz." << endl;
						cout << CRIAR << " - Criar quiz" << endl;
						cout << ALTERAR << " - Alterar quiz" << endl;
						cout << DELETAR << " - Deletar quiz" << endl;
						cout << VOLTAR << " - Voltar" << endl;
						cout << SAIR << " - Sair" << endl;
						cout << "Escolha a opção:" << endl;
						cin  >> opt;
						getchar();

						if (opt == VOLTAR)
						{
							fechaCategoria = true;
							break;
						}
						if (opt == SAIR)
						{
							*fechar = true;
							return;
						}
						opt += 30;
					}
					break;

				default:
					
					break;
			}
			executarOpcao(opt);

		}catch(invalid_argument &e){
			system(CLEAR);
			cout << "Houve um erro na seleção:" << endl;
			cout << e.what() << endl;/*manda um feedback se algo der errado*/
			PAUSE;
		}
	}
}


void InterfaceAdmin::executarOpcao(int opcao)throw(runtime_error)
{
	switch(opcao){

		case 11:

			string l, s, n;
			int p;
			cout << "Digite o usuário: ";
			cin >> l;
			cout << "Digite a senha: ";
			cin >> s;
			cout << "Digite o nome: ";
			cin >> n;
			cout << "Digite a permissão (0 = estudante, 1 = administrador): ";
			cin >> p;
			try{
				criarUsuario(l, s, n, p);
			} catch (runtime_error &e){
				cout << "Erro na criação." << endl;
			}

			break;

		case 12:

			listarUsuarios();
			string l, s, n;
			int p;

			break;

		case 13:

			listarUsuarios();

			break;

		case 21:

			while(!fechaAcao){
				string d;
				cout << "Digite o nome da disciplina (9 = voltar, 0 = sair): ";
				cin >> d;
				criarDisciplina(d);

				if (opt == VOLTAR)
				{
					fechaAcao = true;
					break;
				}
				if (opt == SAIR)
				{
					*fechar = true;
					return;
				}
			}

			break;

		case 22:

			listarDisciplinas();
			int id;
			cout << "Digite o código da disciplina a ser alterada: "
			cin >> id;
			alterarDisciplina(id);

			break;

		case 23:

			listarDisciplinas();
			int id;
			cout << "Digite o código da disciplina a ser deletada: "
			cin >> id;
			deletarDisciplina(id);

			break;

		case 24:

			listarDisciplinas();
			int id;
			cout << "Digite o código da disciplina a receber tópicos: "
			cin >> id;
			while(!fechaAcao){
				string t;
				cout << "Digite o nome do tópico (9 = voltar, 0 = sair): ";
				cin >> t;
				adicionarTopico(id, t);

				if (opt == VOLTAR)
				{
					fechaAcao = true;
					break;
				}
				if (opt == SAIR)
				{
					*fechar = true;
					return;
				}
			}
			

			break;

		case 31:

			break;

		case 32:

			break;

		case 33:

			listarQuiz();
			int d, t, q;
			cout << "Digite o código da disciplina: "
			cin >> d;
			cout << "Digite o código do tópico: "
			cin >> t;
			cout << "Digite o código do quiz a ser deletado: "
			cin >> q;
			deletarQuiz(d, t, q);

			break;

		default:
			return;
			break;
	}
}

void InterfaceAdmin::criarUsuario(string l, string s, string n, int p)throw(runtime_error){
	
	FILE *f = fopen("usuarios.bin", a);

	if(f==NULL){
		throw runtime_error("Arquivo Nulo");
	}

	//StreamWriter^ f = gcnew StreamWriter("usuarios.bin");
	f.Write( l + "|" + s + "|" + n + "|" + p );
	
	/*listaDisciplinas* ld = disc;
	while (ld != NULL){
		f.Write("|");
		f.Write(ld->d.getCodigo());
		ld = ld->prox;
	}*/
	f.Write("\n");
	
	f.close();
	return;

}
void InterfaceAdmin::alterarUsuario(string l, string s, string n, int p);
void InterfaceAdmin::deletarUsuario(string l);

void InterfaceAdmin::criarDisciplina(string n);
void InterfaceAdmin::alterarDisciplina(int i);
void InterfaceAdmin::deletarDisciplina(int i);
void InterfaceAdmin::adicionarTopico(int i, string t);

void InterfaceAdmin::criarQuiz(int d, int t, Quiz q);
void InterfaceAdmin::alterarQuiz(int d, int t, int q, Quiz qn);
void InterfaceAdmin::deletarQuiz(int d, int t, int q);

void InterfaceAdmin::listarUsuarios();
void InterfaceAdmin::listarDisciplinas();
void InterfaceAdmin::listarQuiz();
