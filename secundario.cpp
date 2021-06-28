#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "pila.h"
#include "pila.cpp"
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
        as->vanalisis_sintactico();
}

int analisisLex(string archivoAbierto) {
    for (int i = 0; i <MAX; i++) {
        asTkns[i] = new char[10];
    }

    int status = Fd->vabrirarch(archivoAbierto);
    if (status != 0) {
        return 1;
    }
    numBytesArch = Fd->bytesarch(); // se guarda el tamaño de kb o bytes del archivo para saber si contiene texto

    if (numBytesArch == 0) {
        return 2;
    } else {
        al->vanalisislexico(numBytesArch);
    }
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
