#ifndef INTERFACES_H
#define INTERFACES_H
#include <string>

using namespace std;

class Quiz
{
    public:
    virtual void SetPerg(string in,string p,string r) = 0;
};

#endif // INTERFACES_H
