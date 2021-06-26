#ifndef ANALIZADOR_H
#define ANALIZADOR_H
#include "pila.h"
#include "pila.cpp"
#include "archivo.h"
#include "archivo.cpp"
#define MAXTOKEN 50 // límite original para hacer pruebas
#define NUMPALRES 4
#define MAX 50

class Analizador
{
public:
    Analizador();
private:
    Archivo *Fd;
    char PalRes[5][10] = {"char", "float", "int", "puts"}; //printf
    // Arreglo para identificadores de variables y puts de archivo

    char sLexema[127]; // arreglos para los lexemas y lineas que se utilizaran
    char sLinea[127];

    char non[6] = "13579", par[6] = "24680"; // Arreglo para identificar pares y nones
    char asTokens[MAXTOKEN][10];             // Arreglo para los tokens usando la constante definida
    int indice = 0, edoAct, edoIni, iniToken = 0, k, numBytesArch;

    int cima = -1;
    Pila<string> *pilac = new Pila<string>(MAX);
    char token[17][8] = {"x", ";", ",", "*", "id", "[", "]", "num", "char", "int", "float", "puts", "(", ")", "Cte.Lit",
                         "asign", "op.rel"};

    char varsint[13][3] = {"x", "D", "L", "L'", "I", "I'", "A", "A'", "K", "T", "F", "E", "P"};
    //Cambiamos -4[24][3] a -8 y un -11[21][3] a 11
    int tablaM[25][8]= {{1, 8 , 1, 9, 2, -1, 999,999},  //D->TL;       8=char
                        {1, 9 , 1, 9, 2, -1, 999,999},  //D->TL;       9=int
                        {1, 10, 1, 9, 2, -1, 999,999},  //D->TL;      10=float
                        {2, 3 , 2, 4, 3, 999, 999, 999},//L->IL'       3=*
                        {2, 4 , 2, 4, 3, 999, 999, 999},//L->IL'       4=id
             /* 5 */    {3, 1 , 3, 999,999,999,999,999},//L'->         1=;
                        {3, 2 , 3, -2, 4, 3, 999,999},  //L'->,IL'     2=,
                        {4, 3, 4, -3, -4, 5, 999,999},  //I->ID I'     3=*
                        {4, 4, 4, -4, 5, 999,999,999},  //I->ID I'      4=ID
                        {5, 1, 5, 999,999,999,999,999}, //I'->         1=;
            /* 10 */    {5, 2, 5,999,999,999,999,999},  //I'->         2=,
                        {5, 5, 5, 6, 999,999,999,999},  //I'->A        5=[
                        {6, 5, 6, -5, 8,-6, 7, 999 },   //A->[K]A'     5=[
                        {7, 1, 7, 999,999,999,999,999}, //A'->         1=;
                        {7, 2, 7, 999,999,999,999,999}, //A'->         2=,
            /* 15 */    {7, 5, 6, -5, 8, -6, 7, 999},   //A'->[K]A'    5=[
                        {8, 4, 8, -4, 999, 999,999,999},//K->ID        4=ID
                        {8, 7, 8, -7, 999,999,999,999}, //K->num       7=num
                        {9, 8, 9, -8,999,999,999,999},  //T->char      8=char
             /* -> */   {9, 9, 9, -9,999,999,999,999},  //T->int       9=int
            /* 20 */    {9,10,9,-10,999,999,999,999},   //T->float    10=float
        /*segunda gramatica */
                        {10,11,10,-11, 11,-1,999,999},  //F->E puts;   11=puts
                        {11, 12, 11,-12,12,-13,999,999},//E->(P)       12=(
                        {12,14,12,-14,999,999,999,999}, //P->Cte.Lit   14=Cte.Lit
                        {12, 4, 12, -8,999,999,999,999} //P->char        4=ID
    };

};

#endif // ANALIZADOR_H
