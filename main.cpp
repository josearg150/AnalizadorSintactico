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

#define MAXTOKEN 50 // límite original para hacer pruebas
#define NUMPALRES 4
#define MAX 50
char PalRes[5][10] = {"char", "float", "int", "puts"}; //printf
// Arreglo para identificadores de variables y puts de archivo

char sLexema[127]; // arreglos para los lexemas y lineas que se utilizaran
char sLinea[127];

char non[6] = "13579", par[6] = "24680"; // Arreglo para identificar pares y nones
char asTokens[MAXTOKEN][10];             // Arreglo para los tokens usando la constante definida
int indice = 0, edoAct, edoIni, iniToken = 0, k, numBytesArch;


//char pilac[MAX][10]; Uso de clase pila propia


void vmuestra();

bool finarch = false;

//char asTkns[50][10];
char **asTkns;

Archivo *Fd = new Archivo();
AnalisisLexico *al;
AnalisisSintactico *as;


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

int main(void)
{
    Pila<string> *pilac = new Pila<string>(MAX);
    asTkns = new char *[10];
    for(int i = 0; i <50; i++)
        asTkns[i] = new char[10];
    al = new AnalisisLexico(Fd, asTkns);
    as = new AnalisisSintactico(asTkns, pilac);

    char resp; // variable para la respuesta de s o no
    do         // Se entra en un ciclo
    {
        cout << "Generar el archivo? (s/n): ";
        resp = cin.get();
        if (strchr("Ss", resp))
            Fd->generararch();
        Fd->vabrirarch();
        // se guarda el tamaño de kb o bytes del archivo para saber si contiene texto

        numBytesArch = Fd->bytesarch();
        //cout << numBytesArch;

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
            al->vanalisislexico(numBytesArch);//vanalisislexico();
        //Fd->cerrararch();

        printf("Salida del Analizador Lexico (asTokens):");
        vmuestra();

        printf("\nPulsa una tecla para continuar.");
        if (cin.get() == 0) // getch()==0)
            cin.get();      // getch();
        as->vanalisis_sintactico();//vanalisis_sintactico();
        cin.get();
        printf("Presiona (sS) para continuar: ");
        cin >> resp;
    } while (strchr("Ss", resp));

    return 0;
}

void vmuestra()
{
    int iJ;
    // Se muestran los contenidos del arreglo asTokens introducidos en el analisis lexico
    puts("\nTokens reconocidos:\n");
    for (iJ = 0; iJ < al->k; iJ++) //,Ren++)
    {
        puts(asTkns[iJ]);
    }
}

//
//
//      SINTÁCTICO
//
// 
/*
void vanalisis_sintactico()
{

    int ip = 0, i, j;
    int renglon, iast;
    char x[10], a[10];//Arreglos de 10 porque el asTokens posee una cadena de 7 caracteres
    pilac->push("$");
    if (strcmp(asTokens[ip], "puts") == 0) //si el elemento de asTokens en indice ip es puts, entonces insertamos f
        pilac->push("F");
    else
        pilac->push("D");

    printf("\nSalida del analizador sintactico (asTokens):\n\n");
    printf("Arreglo de tokens:\n\n");
    for (i = 0; strcmp(asTokens[i], "$") != 0; i++)//si la tabla no ha quedado vacia, mostramos los tokens
        printf("%s ", asTokens[i]);
    printf("\n\nProducciones:\n\n");
    do
    {
        strcpy(x,pilac->Tope().c_str());
        strcpy(a, asTokens[ip]);//copiamos a a el token asignado por puts (F) o D
        if (estoken(x) || (strcmp(x, "$") == 0))
        {
            if (strcmp(x, a) == 0) //si x y a son iguales significa que podemos eliminar ambos ejemplo;  ID = ID a
            {                       //Ambos se eliminan
                //eliminapila();
                pilac->pop();
                ip++; //y pasasmos al siguiente indice para asTokens
            }
            else //de lo contrario
            {
                if (strcmp(asTokens[ip], "puts") == 0) //Realizamos la comprobacion anterior
                    pilac->push("F");
                else
                    pilac->push("D");

                strcpy(x,pilac->Tope().c_str());
            }
        }
        else //si no es token
        {
            renglon = buscaTabla(a, x);
            if (renglon != 999)
            {
                pilac->pop();
                iast = 0;
                printf("%-3s -> ", varsint[tablaM[renglon][0]]);
                for (j = 3; iast != 999; j++)//incrementa al final de cada iteracion 
                {
                    iast = tablaM[renglon][j]; //999
                    if (iast < 0)
                    {
                        iast *= -1;
                        printf("%s ", token[iast]);
                    }
                    else
                    {
                        if (iast != 999)
                            printf("%s", varsint[iast]);
                    }
                }
                printf("\n");
                for (i = j - 2; i > 2; i--)
                {
                    iast = tablaM[renglon][i];
                    if (iast < 0)
                    {
                        iast *= -1;
                        pilac->push(token[iast]);
                    }
                    else
                        pilac->push(varsint[iast]);
                }
            }
            else
            {
                printf("\n\nError de sintaxis.");
                return;
            }
        }
    } while (strcmp(x, "$") != 0);
}

int estoken(char x[])
{   //Comparacion para saber si lo que contiene x esta en el arreglo de tokens
    int i;
    for (i = 0; i < 15; i++)
    {
        if (strcmp(x, token[i]) == 0)
            return 1;
    }
    return 0;
}

int buscaTabla(char a[], char x[])
{
    // se usan dos indices para representar x y a que seran comparados
    int indx = 0, inda = 0, i;
    for (i = 0; i < 17; i++)          // el primer ciclo compara contra el arreglo token  para compara si contiene
        if (strcmp(a, token[i]) == 0) // un identificador
            inda = i;                 // break;
    for (i = 0; i < 13; i++)
        if (strcmp(x, varsint[i]) == 0) // compara contra el arreglo de tablas de producciones
            indx = i;
    for (i = 0; i < 25; i++)
    {
        if (indx == tablaM[i][0])     // si la posicion del indice x se encuentra en la matriz
            if (inda == tablaM[i][1]) // comparamos si el token tambien se encuentra
                return i;             // se regresa el indice
    }
    return 999;
}
*/
