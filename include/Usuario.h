/////////////////////////////////////////
///		Descrição do arquivo:
///		@author		Vitor Moraes Dellamora
///		@since		??/04/2017
///		@version	1.0
/////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////
///		Inclusão de bibliotecas padrões e outros módulos de definição
//////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "GerenciaDisciplinas.h"
#include "GerenciadorQuiz.h"


/////////////////////////////////////////
///		Classe que diz respeito ao usuário, seja ele administrador
///		ou estudante.
/////////////////////////////////////////
class Usuario{
	private:

		/////////////////////////////////////////
		///		Atributos principais do usuário:
		///		Login: nome de login para acessar o programa
		///		Senha: senha de acesso, utilizada em conjunto com login
		///		Nome: nome do administrador ou estudante
		///		Perfil: define status de estudante ou administrador
		///		Logado: atributo de controle se o usuário pode, ou não, acessar
		/////////////////////////////////////////
		string nome;
		string login;
		string senha;
		enum PERFIL {admin, estudante} perfil;
		bool logado;


		/////////////////////////////////////////
		///		Lista encadeada com as Disciplinas
		///		escolhidas pelo usuário
		/////////////////////////////////////////
		typedef struct listaDisciplinas;

	public:

		/////////////////////////////////////////
		///		Propriedades da classe Usuário
		///		Cada uma respectivamente ao seu
		///		atributo, citados acima
		/////////////////////////////////////////
		string getNome();
		void setNome(string);
		string getLogin();
		void setLogin(string);
		string getSenha();
		void setSenha(string);
		int getPerfil();
		void setPerfil(char);

		//////////////////////////////////////////////////////////////////////////////////
		///		@brief Construtor da classe
		///		Construtor da classe usuário. Não contém código pois o usuário pode tanto
		///		fazer login e ser carregado na memória quanto ser cadastrado e possuir no-
		///		vas informações
		//////////////////////////////////////////////////////////////////////////////////

		Usuario();

		//////////////////////////////////////////////////////////////////////////////////
		///		@brief Método que retorna todas as disciplinas
		///		Retorna uma string, pulando linhas, de cada nome de disciplina na
		///		lista de disciplinas do usuario, de uma vez
		//////////////////////////////////////////////////////////////////////////////////
		string listarDisciplinas();

		//////////////////////////////////////////////////////////////////////////////////
		///		@brief Adiciona uma disciplina à lista encadeada de disciplinas
		///		@param codigo É o código da disciplina que será encontrada e adicionada
		///		Acrescenta uma disciplina na lista de disciplinas do usuario
		///		Procura-se uma disciplina no Gerenciador de Disciplinas,
		///		utilizando o codigo recebido por parametro
		//////////////////////////////////////////////////////////////////////////////////
		void adicionarDisciplina(int codigo);

		//////////////////////////////////////////////////////////////////////////////////
		///		@brief Permite acesso do usuário
		///		@param l É a cadeia de caracteres referente ao login
		///		@param s É a cadeia de caracteres referente à senha
		///		@return Retorna se o usuário está logado ou não (neste caso, não foi possível logar)
		///		Faz o login de um usuario
		//////////////////////////////////////////////////////////////////////////////////
		bool Login(string l, string s);


		//////////////////////////////////////////////////////////////////////////////////
		///		@brief Registra um novo usuário no arquivo com os parâmetros fornecidos
		///		@param l Login do novo usuário
		///		@param s Senha do novo usuário
		///		@param n Nome do novo usuário
		///		@param p Permissão do novo usuário (0 = estudante; 1 = Administrador)
		///		@param disc Lista de disciplinas do novo usuário
		///		Adiciona um usuario no arquivo de usuarios, para que ele possa, futuramente,
		///		logar e utilizar o sistema
		//////////////////////////////////////////////////////////////////////////////////
		void Cadastrar(string l, string s, string n, int p, listaDisciplinas* disc);


		//////////////////////////////////////////////////////////////////////////////////
		///		Metodos de "gerenciamento" de Disciplinas e Quizzes, onde o admin
		///		Pode fazer alteracoes nos arquivos de Disciplinas e Quizzes
		//////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////
		///		@param nome Nome da disciplina nova
		///		@param disc Objeto de Disciplina
		///		Cria uma nova disciplina, verificando se o usuário é administrador
		//////////////////////////////////////////////////////////////////////////////////
		void criarDisciplina (string nome, GerenciaDisciplinas disc);

		//////////////////////////////////////////////////////////////////////////////////
		///		@param nome Nome da disciplina a ser alterada
		///		@param lT Lista de tópicos a ser mudada na disciplina
		///		@param lQ Lista de quizes a ser mudada na disciplina
		///		Modifica a disciplina com uma nova lista de tópicos e quizes,
		///		verificando se o usuário é administrador
		//////////////////////////////////////////////////////////////////////////////////
		void alterarDisciplina (string nome);//, listaTopicos* lT, listaQuizzes* lQ);
		
		//////////////////////////////////////////////////////////////////////////////////
		///		@param nome Nome da disciplina
		///		@param disc Objeto da disciplina
		///		Remove a disciplina selecionada, verificando se o usuário é administrador
		//////////////////////////////////////////////////////////////////////////////////
		void deletarDisciplina (string nome, GerenciaDisciplinas disc);

		//////////////////////////////////////////////////////////////////////////////////
		///		Cria, altera e apaga quizes, verificando,
		///		antes, se o usuário é um administrador
		///		e chama os métodos referentes em suas
		///		devidas classes
		//////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////
		///		@param pergunta Titulo da pergunta
		///		@param resposta Resposta da pergunta
		///		@param nomeDisciplina Nome da disciplina pra onde vai a pergunta
		///		@param nomeTopico Nome do tópico para onde vai a pergunta
		///		@param quiz Objeto quiz para onde vai a pergunta
		///		Cria uma nova pergunta na disciplina e tópico selecionados, verificando
		///		se o usuário é administrador
		//////////////////////////////////////////////////////////////////////////////////
		void criarQuiz (string pergunta, bool resposta, string nomeDisciplina, string nomeTopico, GerQuiz quiz);

		//////////////////////////////////////////////////////////////////////////////////
		///		@param pergunta Pergunta selecionada
		///		@param resposta Resposta selecionada
		///		@param nomeDisciplina Nome da disciplina selecionada
		///		@param nomeTopico Nome do tópico selecionado
		///		@param quiz Quiz selecionado
		///		Edita uma pergunta com os parâmetros fornecidos, verificando se o usuário
		///		é administrador
		//////////////////////////////////////////////////////////////////////////////////
		void alterarQuiz (string pergunta, bool resposta, string nomeDisciplina, string nomeTopico, GerQuiz quiz);

		//////////////////////////////////////////////////////////////////////////////////
		///		@param pergunta Pergunta selecionada
		///		@param quiz Quiz selecionado
		///		Apaga a pergunta recebida por parâmetros, verificando se o usuário é
		///		administrador
		//////////////////////////////////////////////////////////////////////////////////
		void deletarQuiz (string pergunta, GerQuiz quiz);
};