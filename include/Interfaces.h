#ifndef INTERFACES_H
#define INTERFACES_H
#include <stdexcept>

using namespace std;

/*classes abstratas que serao implementadas no controle de interface*/
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
