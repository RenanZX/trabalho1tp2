#include "Quiz.h"

void Perg::setPerg(string x)
{
    p = x;
}

string Perg::getPerg()
{
    return p;
}

void Resp::setResp(string x)
{
    res = x;
}

string Resp::getResp()
{
    return res;
}

elemPR::~elemPR()
{
    delete p;
    delete res;
}

listaPR::~listaPR()
{
    elemPR* ptr;
    elemPR* ptr2;
    ptr = primeiro;

    while(ptr!=NULL){
        ptr2 = ptr;
        ptr = ptr->proximo;
        delete ptr2;
    }
}

void listaPR::InsereInicio(Perg* per,Resp* respos,float ind)
{
    elemPR* ptr = new elemPR();

    ptr->p = per;
    ptr->res = respos;
    ptr->index = ind;
    if(primeiro==NULL){
        ultimo = ptr;
    }
    ptr->proximo = primeiro;
    primeiro = ptr;
}

void listaPR::InsereFinal(Perg* per,Resp* respos,float ind)
{
    elemPR* ptr = new elemPR();

    ptr->p = per;
    ptr->res = respos;
    ptr->index = ind;
    if(primeiro==NULL){
        primeiro = ptr;
        ultimo = ptr;
    }else{
        ultimo->proximo = ptr;
        ultimo = ptr;
    }
}

Perg* listaPR::getPerg(float ind)
{
    int achou = 0;
    elemPR* el = primeiro;
    while((el!=NULL)&&(achou!=1)){
        if(el->index==ind){
            achou = 1;
        }else{
            el = el->proximo;
        }
    }
    return el->p;
}

Resp* listaPR::getResp(float ind)
{
    int achou = 0;
    elemPR* el = primeiro;
    while((el!=NULL)&&(achou!=1)){
        if(el->index==ind){
            achou = 1;
        }else{
            el = el->proximo;
        }
    }
    return el->res;
}

void listaPR::DelElem(float ind)
{
    int achou = 0;
    elemPR* el = primeiro;
    while((el!=NULL)&&(achou!=1)){
        if(el->index==ind){
            achou = 1;
        }else{
            el = el->proximo;
        }
    }
    delete el;
}

Quiz::Quiz()
{
    l = new listaPR();
    FILE* f = fopen("arQ.dat","wt");
    if(f!=NULL){
     //   arq = fread(arq,sizeof(string),1,f);
    }
    fclose(f);
}

void Quiz::EditPergResp(Perg novap,Resp novar,float ind)
{
   // l->SetAttrEl(&novap,&novar,ind);
}

void Quiz::deletarPerg(float ind)
{
    l->DelElem(ind);
}

void Quiz::CarregarPerguntas()
{
    FILE *f = fopen(arq.c_str(),"rt");
    int ind;
    Perg p;
    Resp r;

    if(f!=NULL){
        while(!feof(f)){
            //ind = fread(ind,sizeof(int),)
        }
    }
}
