#include <iostream>
#include <stdio.h>
#include "ListagemDeDiciplinas.h"

const int ListagemDeDiciplinas::CONTINUAR = 1;
const int ListagemDeDiciplinas::SAIR = 0;


ListagemDeDiciplinas::ListagemDeDiciplinas(){
}



void ListagemDeDiciplinas::listarDiciplinas() {
    typedef struct {
        char nome_diciplina[15];
        char codigo[2];
    } elemento_diciplina;

    char linha[15];
    elemento_diciplina lista_de_diciplinas[50];
    lista_diciplinas = fopen("lista_diciplinas.txt", "r");
    indice = 0;
    numero_de_diciplinas = 0;

    if (lista_diciplinas == NULL) {
        cout << "Lista de diciplinas vazia." << endl;
    }
    else {
        while ((fscanf(lista_diciplinas, "%[^\n]s", linha))!= EOF) {
            indice++;
            numero_de_diciplinas++;
            printf("%s\n",linha);
        }
    }
    fclose(lista_diciplinas);
}
