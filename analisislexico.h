#ifndef ANALISISLEXICO_H
#define ANALISISLEXICO_H
#include "archivo.h"
#define NUMPALRES 4
#define MAXTOKEN 50

class AnalisisLexico
{
public:
    AnalisisLexico();
    AnalisisLexico(Archivo *F, char *asTkns[10]);
    void vanalisislexico(int );
    void viniedos();
    int edoActesacept();
    void falla();
    void recuperaerror();
    int esId();
private:
    int edoAct;
    int edoIni;
    int indice;
    int iniToken;
    int k;

    Archivo *Fd;
    char PalRes[5][10] = {"char", "float", "int", "puts"}; //printf
    char sLexema[127]; // arreglos para los lexemas y lineas que se utilizaran
    char non[6] = "13579", par[6] = "24680";
    char **asTokens;
};

#endif // ANALISISLEXICO_H
