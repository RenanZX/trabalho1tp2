class Usuario{
	private String^ nome;
	private String^ login;
	private String^ senha;
	private enum PERFIL {admin, estudante} perfil;
	private bool logado;

	private typedef struct listaDisciplinas;

	public String getNome();
	public void setNome(String^);
	public String^ getLogin();
	public void setLogin(String^);
	public String^ getSenha();
	public void setSenha(String^);
	public int getPerfil();
	public void setPerfil(char);

	public void Usuario();


	public String^ listarDisciplinas();

	public void adicionarDisciplina(int);

	public bool Login(String^, String^);

	public void Cadastrar(String^, String^, String^, int, Disciplinas*);


	public void criarDisciplina (String^);

	public void alterarDisciplina (String^, listaTopicos*, listaQuizzes*);

	public void deletarDisciplina (String^);


	public void criarQuiz (String^, bool, String^, String^);

	public void alterarQuiz (String^, bool, String^, String^);
	
	public void deletarQuiz (String^);
}