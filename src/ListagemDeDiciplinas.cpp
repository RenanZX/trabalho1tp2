#include <iostream>
#include <stdio.h>
#include "ListagemDeDiciplinas.h"

const int ListagemDeDiciplinas::CONTINUAR = 1;
const int ListagemDeDiciplinas::SAIR = 0;


ListagemDeDiciplinas::ListagemDeDiciplinas(){
}

void ListagemDeDiciplinas::listarTopicos() {
    string diciplina_a_listar;
    opcao = CONTINUAR;
    while(opcao != SAIR) {
        cout << "Insira o nome da Diciplina a ter os topicos apresentados." << endl;
		cin>> diciplina_a_listar;
		nome_arquivo = diciplina_a_listar +".txt";
		arquivo_diciplina = fopen(nome_arquivo.c_str(), "r");
		if(arquivo_diciplina == NULL) {
			cout << "A diciplina nao existe" << endl;
		}
		else {

		}
        cout << "Aperte 1 para continuar ou 0 para sair." << endl;
		cin >> opcao;
    }
}

void ListagemDeDiciplinas::listarDiciplinas() {
    typedef struct {
        char nome_diciplina[30];
        char codigo[2];
    } elemento_diciplina;

    elemento_diciplina lista_de_diciplinas[50];
    lista_diciplinas = fopen("lista_diciplinas.txt", "r");
    indice = 0;
    numero_de_diciplinas = 0;

    if (lista_diciplinas == NULL) {
        cout << "Lista de diciplinas vazia." << endl;
    }
    else {
        while ((fscanf(lista_diciplinas, "%s|%s", lista_de_diciplinas[indice].codigo, lista_de_diciplinas[indice].nome_diciplina))!= EOF) {
            indice++;
            numero_de_diciplinas++;
        }
        for (indice=0;indice < numero_de_diciplinas;indice++){
            cout << lista_de_diciplinas[indice].codigo << "|" << lista_de_diciplinas[indice].nome_diciplina << endl;
        }
    }
}
