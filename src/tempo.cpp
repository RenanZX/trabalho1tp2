#include "tempo.h"

tempo::tempo(){

}

tempo::~tempo(){

}

void tempo::inciaContagem(){
    time(&inicio);
}

void tempo::terminaContagem(){
    time(&fim);
}

double tempo::tempoGasto(){
    return fim - inicio;
}
