#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "pila.h"
#include "pila.cpp"
#include "archivo.h"
#include "archivo.cpp"
#include "analisislexico.h"
#include "analisissintactico.h"

using namespace std;

#define MAX 50

int numBytesArch;
char **asTkns;

Archivo *Fd;
AnalisisLexico *al;
AnalisisSintactico *as;

int main(void)
{
    Fd = new Archivo();
    Pila<string> *pilac = new Pila<string>(MAX);
    asTkns = new char *[10];
    for(int i = 0; i <50; i++)
        asTkns[i] = new char[10];
    al = new AnalisisLexico(Fd, asTkns);
    as = new AnalisisSintactico(asTkns, pilac);

    char resp; // variable para la respuesta de s o n
    do
    {
        cout << "Generar el archivo? (s/n): ";
        resp = cin.get();
        if (strchr("Ss", resp))
            Fd->generararch();
        Fd->vabrirarch();

        numBytesArch = Fd->bytesarch();// se guarda el tamaño de kb o bytes del archivo para saber si contiene texto

        if (numBytesArch == 0)
        {
            printf("El archivo no tiene datos. Pulsa una tecla.");
            if (cin.get() == 0)
            {
                cin.get(); // getch();
                exit(-1);
            }
        }

        else
            al->vanalisislexico(numBytesArch);

        printf("Salida del Analizador Lexico (asTokens):");
        al->vmuestra();

        printf("\nPulsa una tecla para continuar.");
        if (cin.get() == 0) // getch()==0)
            cin.get();      // getch();
        as->vanalisis_sintactico();
        cin.get();
        printf("Presiona (sS) para continuar: ");
        cin >> resp;
    } while (strchr("Ss", resp));

    return 0;
}
