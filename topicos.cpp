ValidarAdmin::validar(){
  Usuario user;
  Senha senha;

  string entrada;

  try{
    cout << "Digite seu login: " << endl;
    cin >> entrada;
    user.setUsuario(entrada);
    cout << "Digite sua senha" << endl;
    cin >> entrada;
    senha.setSenha(entrada);
    break;
  }catch(const invalid_argument exp&){
    cout << endl << "Dado incorreto" << endl;
  }

}

GerenciadorDeTopicos::incluir(){

}

GerenciadorDeTopicos::remover(){

}

GerenciadorDeTopicos::editar(){

}
