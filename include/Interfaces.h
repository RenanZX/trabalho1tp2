#ifndef INTERFACES_H
#define INTERFACES_H
#include <string>

using namespace std;

/*verifica qual a versao do SO*/
#ifdef _WIN32
#define CLEAR "cls"
#elif LINUX
#define CLEAR "clear"
#endif


class IQuiz
{
    public:
    virtual void SetPerg(string in,string p,string r) = 0;
    virtual void executar() = 0;
};

class IGQuiz
{
public:
    virtual Quiz* getQuiz() = 0;
    virtual void executar() = 0;
};

#endif // INTERFACES_H
