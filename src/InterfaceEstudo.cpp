#include "InterfaceEstudo.hpp"

const int InterfaceEstudo::ADDDISC = 1;
const int InterfaceEstudo::RESPONDER = 2;
const int InterfaceEstudo::SAIR = 0;


void InterfaceEstudo::mostrarOpcoes(Usuario& u, bool* fecha)throw(runtime_error){
	fecha = false;
	int opt;
	//user = new Usuario();
	while(!fecha){
		try{
			system(CLEAR);
			cout << "Bem-vindo, " << u.getNome() << ". Escolha uma função: " << endl;/*opcoes mostradas ao usuario*/
			cout << ADDDISC << " - Adicionar disciplinas" << endl;
			cout << RESPONDER << " - Responder Quiz" << endl;
			cout << SAIR << " - Sair" << endl;
			cout << "Escolha a opção:" << endl;
			cin  >> opt;
			getchar();
			int c;

			switch (opt){

				case ADDISC:
					listarDisciplinas();
					cout << "Digite o código de uma disciplina" << endl;
					cin >> c;
					u.adicionarDisciplina(c);
					break;

				case RESPONDER:
					cout << u.listarDisciplinas(); << endl;
					cout << "Digite o código de uma disciplina" << endl;
					cin >> c;
					listarQuiz(c);
					Quiz* q = new Quiz();
					q->CarregarQuiz();
					q->ComeçarQuiz();
					//cout << "Digite o código de um quiz" << endl;
					//cin >> c;
					break;

				case default:
					fecha = true;
					break;
			}

		} catch(invalid_argument &e){
			system(CLEAR);
			cout << "Houve um erro na seleção:" << endl;
			cout << e.what() << endl;/*manda um feedback se algo der errado*/
			PAUSE;
		}
	}
}

void InterfaceEstudo::executarOpcao(int opt)throw(runtime_error)
{
	
}

void InterfaceEstudo::listarUsuarios(){
	FILE * fusers = fopen ("usuarios.bin", "r");

	string l, s, n;
	int p;

		fscanf (fusers, "%s|%s|%s|%d|", &l, &s, &n, &p);
	do{
		cout << "Nome: " << n << "; Login: " << l; //<< "; Senha: " << s;
		cout << "; Admin: " << ((p) ? "SIM" : "NÃO") << endl;
		fscanf (fusers, "%s|%s|%s|%d|", &l, &s, &n, &p);
	} while (l != "");
	fclose(fusers);
}
void InterfaceEstudo::listarDisciplinas(){
	FILE * fdisc = fopen ("disciplinas.bin", "r");

	string d;
	int c;

		fscanf (fdisc, "%d|%s", &c, &d);
	do{
		cout << "Código: " << c << "; Nome: " << d << endl;;
		fscanf (fdisc, "%d|%s", &c, &d);
	} while (c != NULL);
	fclose(fdisc);
}
void InterfaceEstudo::listarQuiz(){
	FILE * fquiz = fopen ("quiz.bin", "r");

	int d, t, q;
	string p;

		fscanf (fquiz, "%d|%d|%d|%s|", &d, &t, &q, &p);
	do{
		cout << "Disciplina: " << d << "; Tópico: " << t << "; Número: " << q << "; Pergunta: " << p << endl;
		fscanf (fquiz, "%d|%d|%d|%s|", &d, &t, &q, &p);
	} while (d != NULL);
	fclose(fquiz);
}