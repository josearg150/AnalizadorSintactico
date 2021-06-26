#ifndef ANALISISSINTACTICO_H
#define ANALISISSINTACTICO_H

#define MAXTOKEN 50
#include "pila.h"
#include "string.h"
#include "string"
using namespace std;

class AnalisisSintactico
{
public:
    AnalisisSintactico();
    AnalisisSintactico(char **asTkns, Pila<string> *pila);
    void vanalisis_sintactico();
    int buscaTabla(char a[], char x[]);
    int estoken(char x[]);

private:
    Pila<string> *pilac;
    char **asTokens;
                        // 0   1   2   3   4    5   6   7       8      9     10     11    12 13      14     15   16   17   18   19  20   21
    char token[22][8] = {"x",";",",","*","id","[","]","num","char","int","float","puts","(",")","Cte.Lit","=", "+", "-", "/", "{", "}","$"};

    char varsint[13][3] = {"x", "D", "L", "L'", "I", "I'", "A", "A'", "K", "T", "F", "E", "P"};
    //Cambiamos -4[24][3] a -8 y un -11[21][3] a 11
    int tablaM[25][8]= {{1, 8 , 1, 9, 2, -1, 999,999},  //D->TL;       8=char
                        {1, 9 , 1, 9, 2, -1, 999,999},  //D->TL;       9=int
                        {1, 10, 1, 9, 2, -1, 999,999},  //D->TL;      10=float
                        {2, 3 , 2, 4, 3, 999, 999, 999},//L->IL'       3=*
                        {2, 4 , 2, 4, 3, 999, 999, 999},//L->IL'       4=id
             /* 5 */    {3, 1 , 3, 5, 999,999,999,999}, //L'-> I'        1=;
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

#endif // ANALISISSINTACTICO_H
