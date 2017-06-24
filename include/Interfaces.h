/////////////////////////////////////////
///     Descrição do arquivo:
///     @author     Renan Godoi de Medeiros
///     @since      ??/04/2017
///     @version    1.0
/////////////////////////////////////////

#ifndef INTERFACES_H
#define INTERFACES_H
#include <stdexcept>

using namespace std;

//////////////////////////////////////////////////////////////////////////////////
///		@brief Classes abstratas que serão implementadas no controle de interface
//////////////////////////////////////////////////////////////////////////////////
class InterfaceUsuarioGerQuiz
{
public:
    virtual void executar()throw(runtime_error) = 0;
};

class InterfaceUsuarioQuiz
{
public:
    virtual void executar()throw(runtime_error) = 0;
};

#endif // INTERFACES_H
