#ifndef ARCHIVO_H
#define ARCHIVO_H

#include <string>
#include <string.h>
#include <stdio.h>
#include <iostream>
using namespace std;
class Archivo
{
public:
    Archivo();
    void generararch();
    int vabrirarch(string nombreArchivo);
    int bytesarch();
    char nextchar(int &indice);
    void vretract(int &indice);
    void cerrararch();
    FILE *Fd;
private:

};

#endif // ARCHIVO_H
