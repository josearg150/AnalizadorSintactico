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

int cima = -1;
Pila<string> *pilac = new Pila<string>(MAX);
//char pilac[MAX][10]; Uso de clase pila propia

void vanalisislexico();
void vanalisis_sintactico();
void viniedos();
int edoActesacept();
void vmuestra();
void falla();
void recuperaerror();
int esId();

void insertapila(string elem); // (char *elem);  // (char elem[]);
int buscaTabla(char a[], char x[]);
void eliminapila();
int estoken(char x[]);

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

//
//
//      LÉXICO
//
// 
void vanalisislexico()
{
    char cCarent;
    indice = iniToken = k = 0;
    viniedos();
    while (indice < numBytesArch || edoActesacept())
    {
        switch (edoAct)
        {
        case 0:
            cCarent = Fd->nextchar(indice);
            if (strchr(non, cCarent))
                edoAct = 1;
            else if (strchr(par, cCarent))
                edoAct = 2;
            else
                falla();
            break;
        case 1:
            cCarent = Fd->nextchar(indice);
            if (strchr(non, cCarent))
                edoAct = 1;
            else if (strchr(par, cCarent))
                edoAct = 2;
            else
                falla();
            break;
        case 2:
            cCarent = Fd->nextchar(indice);
            if (strchr(non, cCarent))
                edoAct = 1;
            else if (strchr(par, cCarent))
                edoAct = 2;
            else
                edoAct = 3;
            break;
        case 3:
            Fd->vretract(indice);
            strcpy(asTokens[k++], "num"); //Estaba en mayusucula
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 4:
            cCarent = Fd->nextchar(indice);
            switch (cCarent)
            {
            case '+':
                edoAct = 5;
                break;
            case '-':
                edoAct = 6;
                break;
            case '*':
                edoAct = 7;
                break;
            case '/':
                edoAct = 8;
                break;
            default:
                falla();
            }
            break;
        case 5:
            strcpy(asTokens[k++], "+");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 6:
            strcpy(asTokens[k++], "-");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 7:
            strcpy(asTokens[k++], "*");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 8:
            strcpy(asTokens[k++], "/");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
            //. OTRA VEZ NON - PAR
        case 9:
            cCarent = Fd->nextchar(indice);
            if (strchr(par, cCarent))
                edoAct = 10;
            else if (strchr(non, cCarent))
                edoAct = 11;
            else
                falla();
            break;
        case 10:
            cCarent = Fd->nextchar(indice);
            if (strchr(par, cCarent))
                edoAct = 10;
            else if (strchr(non, cCarent))
                edoAct = 11;
            else
                falla();
            break;
        case 11:
            cCarent = Fd->nextchar(indice);
            if (strchr(non, cCarent))
                edoAct = 11;
            else if (strchr(par, cCarent))
                edoAct = 10;
            else
                edoAct = 12;
            break;
            // NON - PAR
        case 12:
            Fd->vretract(indice);
            strcpy(asTokens[k++], "num");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 13:
            cCarent = Fd->nextchar(indice);
            if ((isalpha(cCarent) || cCarent == '_'))
                edoAct = 14;
            else
                falla();
            break;
        case 14:
            cCarent = Fd->nextchar(indice);
            if ((isalpha(cCarent) || cCarent == '_') || isdigit(cCarent))
                edoAct = 14;
            else
                edoAct = 15;
            break;
        case 15:
            Fd->vretract(indice);
            if (esId())
                strcpy(asTokens[k++], "id"); // Estaba escrito diferente al arreglo
            else
                strcpy(asTokens[k++], sLexema);
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
            // <<<-- en este case
        case 16:
            cCarent = Fd->nextchar(indice);
            if (cCarent == ';')
                edoAct = 17;
            else
                falla();
            break;
            /* Al encontrar el caracter ';' , que indica fin de linea,
                 Se copia el caracter '$' al fin del arreglo astokens
                 */
        case 17:
            strcpy(asTokens[k++], ";");
            strcpy(asTokens[k], "$");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 18:
            cCarent = Fd->nextchar(indice);
            if (cCarent == '[')
                edoAct = 19;
            else
                falla();
            break;
        case 19:
            strcpy(asTokens[k++], "[");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 20:
            cCarent = Fd->nextchar(indice);
            if (cCarent == ']')
                edoAct = 21;
            else
                falla();
            break;
        case 21:
            strcpy(asTokens[k++], "]");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 22:
            cCarent = Fd->nextchar(indice);
            if (cCarent == ',')
                edoAct = 23;
            else
                falla();
            break;
        case 23:
            strcpy(asTokens[k++], ",");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 24:
            cCarent = Fd->nextchar(indice); // funcion que lee el siguiente caracter
            if (('"' == cCarent) && cCarent)
                edoAct = 25;
            else
                falla();
            break;
        case 25:
            cCarent = Fd->nextchar(indice); // funcion que lee el siguiente caracter
            if (('"' != cCarent) && cCarent)
                edoAct = 25;
            else if (cCarent)
                edoAct = 26;
            break;
        case 26:
            strcpy(asTokens[k++], "Cte.Lit");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 27:
            cCarent = Fd->nextchar(indice);
            if (cCarent == '(')
                edoAct = 28;
            else
                falla();
            break;
        case 28:
            strcpy(asTokens[k++], "(");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 29:
            cCarent = Fd->nextchar(indice);
            if (cCarent == ')')
                edoAct = 30;
            else
                falla();
            break;
        case 30:
            strcpy(asTokens[k++], ")");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 31:
            cCarent = Fd->nextchar(indice);
            if (cCarent == '=')
                edoAct = 32;
            else
                falla();
            break;
        case 32:
            cCarent = Fd->nextchar(indice);
            if (cCarent == '=')
                edoAct = 34;
            else
                edoAct = 33;
            break;
        case 33:
            strcpy(asTokens[k++], "asign");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 34:
            strcpy(asTokens[k++], "op.rel");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 35:
            cCarent = Fd->nextchar(indice);
            if (cCarent == '!')
                edoAct = 36;
            else
                falla();
            break;
        case 36:
            cCarent = Fd->nextchar(indice);
            if (cCarent == '=')
                edoAct = 37;
            else
                falla();
            break;
        case 37:
            strcpy(asTokens[k++], "op.rel");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break; //Hasta aqui jala bien
        case 38:
            cCarent = Fd->nextchar(indice);
            if (cCarent == '<' || cCarent == '>')
                edoAct = 39;
            else
                falla();
            break;
        case 39:
            cCarent = Fd->nextchar(indice);
            if (cCarent == '=')
                edoAct = 40; //37?
            else
                edoAct = 40;
            break;
        case 40:
            strcpy(asTokens[k++], "op.rel");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
            /*case 41: strcpy(asTokens[k++], "op.rel");
                if (indice>=numBytesArch)
                 return;
                iniToken=indice;
                viniedos();
                break;*/

        } /*switch*/
    }     /*while*/
}

void viniedos()
{
    //variable inicar estados
    edoAct = 0;
    edoIni = 0;
}

int edoActesacept()
{
    switch (edoAct)
    {
    case 8:
    case 5:
    case 7:
    case 6:
    case 3:
    case 12:
    case 15:
    case 17:
    case 19:
    case 21:
    case 23:
    case 26:
    case 28:
    case 30:
    case 33:
    case 34:
    case 37:
    case 40:
        return true;
    default:
        return false;
    }
}

void falla()
{
    switch (edoIni)
    {
    case 0:
        edoIni = 4;
        indice = iniToken;
        fseek(Fd->Fd, (long)iniToken, SEEK_SET);
        break;//no hay case 1
    case 4:
        edoIni = 9;
        indice = iniToken;
        fseek(Fd->Fd, (long)iniToken, SEEK_SET);
        break;
    case 9:
        edoIni = 13;
        indice = iniToken;
        fseek(Fd->Fd, (long)iniToken, SEEK_SET);
        break;
    case 13:
        edoIni = 16;
        indice = iniToken;
        fseek(Fd->Fd, (long)iniToken, SEEK_SET);
        break;
    case 16:
        edoIni = 18;
        indice = iniToken;
        fseek(Fd->Fd, (long)iniToken, SEEK_SET);
        break;
    case 18:
        edoIni = 20;
        indice = iniToken;
        fseek(Fd->Fd, (long)iniToken, SEEK_SET);
        break;
    case 20:
        edoIni = 22;
        indice = iniToken;
        fseek(Fd->Fd, (long)iniToken, SEEK_SET);
        break;
    case 22:
        edoIni = 24;
        indice = iniToken;
        fseek(Fd->Fd, (long)iniToken, SEEK_SET);
        break;
    case 24:
        edoIni = 27;
        indice = iniToken;
        fseek(Fd->Fd, (long)iniToken, SEEK_SET);
        break;
    case 27:
        edoIni = 29;
        indice = iniToken;
        fseek(Fd->Fd, (long)iniToken, SEEK_SET);
        break;
    case 29:
        edoIni = 31;
        indice = iniToken;
        fseek(Fd->Fd, (long)iniToken, SEEK_SET);
        break;
    case 31:
        edoIni = 35;
        indice = iniToken;
        fseek(Fd->Fd, (long)iniToken, SEEK_SET);
        break;
    case 35:
        edoIni = 38;
        indice = iniToken;
        fseek(Fd->Fd, (long)iniToken, SEEK_SET);
        break;
        /*case 36:  edoIni=39;
            indice = iniToken;
            fseek(Fd, (long)iniToken, SEEK_SET);
            break;
        case 38:  edoIni=41;
            indice = iniToken;
            fseek(Fd, (long)iniToken, SEEK_SET);
            break;*/
    case 38:
        recuperaerror();
    }
    edoAct = edoIni;
}

void recuperaerror()
{
    iniToken = indice;
    viniedos();
}

int esId()
{
    int n, m, found = false;
    fseek(Fd->Fd, (long)iniToken, SEEK_SET);
    for (m = iniToken, n = 0; m < indice; m++, n++)
        fread(&sLexema[n], sizeof(char), 1, Fd->Fd);
    sLexema[n] = '\0';
    for (m = 0; m < NUMPALRES && !found;)
        if (strcmp(PalRes[m], sLexema) == 0)
            found = true;
        else
            m++;
    return (found ? 0 : 1);
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
