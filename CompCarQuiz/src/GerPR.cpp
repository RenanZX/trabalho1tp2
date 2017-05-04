#include "GerPR.h"

void Perg::setPerg(string x,int ind)
{
    p = x;
    index = ind;
}

string Perg::getPerg()
{
    return p;
}

int Perg::getIndex()
{
    return index;
}

void Resp::setResp(string x,int ind)
{
    res = x;
    index = ind;
}

string Resp::getResp()
{
    return res;
}

int Resp::getIndex()
{
    return index;
}
