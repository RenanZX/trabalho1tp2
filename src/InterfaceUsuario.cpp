#include "InterfaceUsuario.hpp"

const int InterfaceUsuario::LOGAR = 1;
const int InterfaceUsuario::CADASTRAR = 2;
const int InterfaceUsuario::SAIR = 3;


void InterfaceUsuario::mostrarOpcoes()throw(runtime_error)
{
	bool fecha = false;
	int opt;
	//user = new Usuario();
	while(!fecha){
		try{
			system(CLEAR);

			cout << "Bem-vindo ao QuizTime. Por favor, entre com sua conta" << endl;/*opcoes mostradas ao usuario*/
			cout << LOGAR << " - Fazer login" << endl;
			cout << CADASTRAR << " - Cadastrar-se" << endl;
			cout << SAIR << " - Sair" << endl;
			cout << "Escolha a opção:" << endl;
			cin  >> opt;
			getchar();

			if (opt != SAIR){
				executarOpcao(opt);
			} else {
				fecha = true;
				free(user);
				return;
			}

		}catch(invalid_argument &e){
			system(CLEAR);
			cout << "Houve um erro na seleção:" << endl;
			cout << e.what() << endl;/*manda um feedback se algo der errado*/
			PAUSE;
		}
	}
}


void InterfaceUsuario::executarOpcao(int opt)throw(runtime_error)
{
	switch(opt){

		case LOGAR:

			string l, s;
			cout << "Digite o usuário: ";
			cin >> l;
			cout << "Digite a senha: ";
			cin >> s;

			try{
				if (Login(l, s)){
					if (user.getPerfil()){
						InterfaceAdmin adm = new InterfaceAdmin();
						adm.mostrarOpcoes();
					} else {
						InterfaceEstudo est = new InterfaceEstudo();
						est.mostrarOpcoes();
					}
				} else {
					cout << "Dados inválidos." << endl;
				}
			} catch (runtime_error &e){
				cout << "Erro no login." << endl;
			}
			break;

		case CADASTRAR:

			string l, s, n;
			cout << "Digite o usuário: ";
			cin >> l;
			cout << "Digite a senha: ";
			cin >> s;
			cout << "Digite o nome: ";
			cin >> n;

			try{
				Cadastrar(l, s, n, 0);
			} catch (runtime_error &e){
				cout << "Erro no cadastro." << endl;
			}
			break;

		default:
			return;
			break;
	}
}

//Faz o login de um usuario
bool InterfaceUsuario::Login(string l, string s)throw(runtime_error){
	string loginLeitura;
	string senhaLeitura;
	string nomeLeitura;
	string perfilLeitura;
	string disciplinasLeitura;
	
	string f = "usuarios.bin";
	FILE *file = fopen(f, r);

	if(file==NULL){
		throw runtime_error("Arquivo Nulo");
	}
	//StreamReader^ file = File::OpenText(f);
	
	do {
		fscanf(file, "%[^|]%[^|]%[^|]%[^|]%[^\n]",
			&loginLeitura, 
			&senhaLeitura, 
			&nomeLeitura,
			&perfilLeitura,
			&disciplinasLeitura);
			
		if (loginLeitura == l) && (senhaLeitura == s){
			user.setNome(nomeLeitura);
			user.setLogin(l);
			user.setSenha(s);
			((perfilLeitura == 1) ? user.setPerfil('a') : user.setPerfil('e'));
			
			//Adicionar disciplinas
			user.carregarDisciplinas(disciplinasLeitura);
			
			//user.setLogado(true);
			file.close();
			return true;
		}
	} while (loginLeitura != EOF);

	file.close();
	return false;
}

//Adiciona um usuario no arquivo de usuarios, para que ele possa, futuramente,
//logar e utilizar o sistema
void InterfaceUsuario::Cadastrar(string l, string s, string n, int p)throw(runtime_error){
	
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