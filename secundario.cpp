#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "pila.h"
//#include "pila.cpp"
#include "archivo.h"
//#include "archivo.cpp"
#include "analisislexico.h"
#include "analisissintactico.h"

using namespace std;

#define MAX 10

int numBytesArch;
char **asTkns = asTkns = new char *[MAX];

Pila<string> *pilac = new Pila<string>(MAX);
Archivo *Fd = new Archivo();;
AnalisisLexico *al = new AnalisisLexico(Fd, asTkns);;
AnalisisSintactico *as = new AnalisisSintactico(asTkns, pilac);

void analisisSin() {
        //printf("\nPulsa una tecla para continuar.");
        //if (cin.get() == 0) // getch()==0)
        //    cin.get();      // getch();
        as->vanalisis_sintactico();
        Fd->cerrararch();
        /*cin.get();
        printf("Presiona (sS) para continuar: ");
        resp = cin.get();
        cin.get();*/
    //} while (strchr("Ss", resp));

}

int analisisLex(string archivoAbierto) {
    for (int i = 0; i <MAX; i++) {
        asTkns[i] = new char[10];
    }

    //char resp; // variable para la respuesta de s o n
    //do
    //{
        /*cout << "Generar el archivo? (s/n): ";
        resp = cin.get();
        if (strchr("Ss", resp))
            Fd->generararch();*/
        int status = Fd->vabrirarch(archivoAbierto);
        if (status != 0) {
            return 1;
        }

        numBytesArch = Fd->bytesarch();// se guarda el tamaño de kb o bytes del archivo para saber si contiene texto

        if (numBytesArch == 0) {
            return 2;/*
            printf("El archivo no tiene datos. Pulsa una tecla.");
            if (cin.get() == 0)
            {
                cin.get(); // getch();
                exit(-1);
            }*/
        } else {
            al->vanalisislexico(numBytesArch);
        }

        //printf("Salida del Analizador Lexico (asTokens):");
        //al->vmuestra();
        //Fd->cerrararch();
     return 0;
}

void cerrarArchivo() {
    Fd->cerrararch();
}

char** returnAsTokens() {
    return al->getAsTokens();
}

int returnK() {
    return al->getK();
}
