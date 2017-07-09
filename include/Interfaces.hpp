#ifndef INTERFACES_H
#define INTERFACES_H
#include <stdexcept>

using namespace std;

/*classes abstratas que serao implementadas no controle de interface*/
class InterfacePrograma
{
public:
    virtual void mostrarOpcoes()throw(runtime_error) = 0;
    virtual void executarOpcao(int opt)throw(runtime_error) = 0;
};
#endif // INTERFACES_H
