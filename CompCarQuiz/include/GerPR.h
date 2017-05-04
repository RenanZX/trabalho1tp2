#ifndef GERPR_H
#define GERPR_H

class Perg
{
private:
    string p;
    int index;
public:
    void setPerg(string x,int ind);
    string getPerg();
    int getIndex();
};

class Resp
{
private:
    string res;
    int index;
public:
    void setResp(string x,int ind);
    string getResp();
    int getIndex();
};
#endif // GERPR_H
