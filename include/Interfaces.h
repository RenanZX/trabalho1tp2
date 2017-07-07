#ifndef INTERFACES_H
#define INTERFACES_H
#include <stdexcept>

using namespace std;

/*classes abstratas que serao implementadas no controle de interface*/
class Interface
{
public:
    virtual void MostrarOpcoes()throw(runtime_error) = 0;
    virtual void executarOpcao(int opcao)throw(runtime_error) = 0;
};
#endif // INTERFACES_H
