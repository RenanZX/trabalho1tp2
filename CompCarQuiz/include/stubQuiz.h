#ifndef STUBQUIZ_H
#define STUBQUIZ_H
#include <iostream>

using namespace std;


class Quiz
{
public:
    Quiz();
    ~Quiz();
    void setInd(int ind);
    void setPerg(string per);
    void setResp(string res);
    void setElem(string ind,string per,string res);
};

#endif // STUBQUIZ_H
