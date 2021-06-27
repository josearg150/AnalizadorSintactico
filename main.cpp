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
#include "mainwindow.h"
#include <QApplication>

using namespace std;

#define MAX 50

int numBytesArch;
char **asTkns;

Archivo *Fd;
AnalisisLexico *al;
AnalisisSintactico *as;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    MainWindow w;
    w.show();
	/*
    Fd = new Archivo();
    Pila<string> *pilac = new Pila<string>(MAX);
    asTkns = new char *[MAX];
    for(int i = 0; i <MAX; i++){
        asTkns[i] = new char[10];
    }
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
        resp = cin.get();
        cin.get();
    } while (strchr("Ss", resp));
	*/
    return a.exec();
}
