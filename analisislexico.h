#ifndef ANALISISLEXICO_H
#define ANALISISLEXICO_H
#include "analizador.h"
#include "analizador.cpp"

class AnalisisLexico
{
public:
    AnalisisLexico();
    void vanalisislexico();
    void viniedos();
    int edoActesacept();
    void falla();
    void recuperaerror();
private:
    int edoAct;
    int edoIni;
    int indice;
    int iniToken;
    int k;

};

#endif // ANALISISLEXICO_H
