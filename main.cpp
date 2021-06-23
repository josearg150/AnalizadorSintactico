#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

// #define TRUE 1
// #define FALSE 0

// constantes
#define MAXTOKEN 50 // límite original para hacer pruebas
#define NUMPALRES 4
#define MAX 50

//char *PalRes[] = {"char", "float","int","puts"}; //printf

char PalRes[5][10] = {"char", "float", "int", "puts"}; //printf
// Arreglo para identificadores de variables y puts de archivo

// si se usa objeto string, cambiar el uso de strcmp
// string PalRes[10] = {"char", "float", "int", "puts"}; //printf

char sLexema[127]; // arreglos para los lexemas y lineas que se utilizarán
char sLinea[127];

//char *non = "13579", *par = "24680";

char non[6] = "13579", par[6] = "24680"; //Arreglo para identificar pares y nones
char asTokens[MAXTOKEN][10];             //Arreglo para los tokens usando la constante definida
int indice = 0, edoAct, edoIni, iniToken = 0, k, numBytesArch;

int cima = -1;
char pilac[MAX][10];

void generararch();
void vabrirarch();
int bytesarch();

void vanalisislexico();
void vanalisis_sintactico();
void viniedos();
char nextchar();
void vretract();
int edoActesacept();
void vmuestra();
void falla();
void recuperaerror();
int esId();

void insertapila(string elem); //(char *elem);  //(char elem[]);
int buscaTabla(char a[], char x[]);
void eliminapila();
int estoken(char x[]);

bool finarch = false;
FILE *Fd; // puntero a un archivo file

char token[17][8] = {"x", ";", ",", "*", "id", "[", "]", "num", "char", "int", "float", "puts", "(", ")", "Cte.Lit",
                     "asign", "op.rel"};

char varsint[13][3] = {"x", "D", "L", "L'", "I", "I'", "A", "A'", "K", "T", "F", "E", "P"};

int tablaM[25][8] = {{1, 8, 1, 9, 2, -1, 999, 999},
                     {1, 9, 1, 9, 2, -1, 999, 999},
                     {1, 10, 1, 9, 2, -1, 999, 999},
                     {2, 3, 2, 4, 3, 999, 999, 999},
                     {2, 4, 2, 4, 3, 999, 999, 999},
             /* 5 */ {3, 1, 3, 999, 999, 999, 999, 999},
                     {3, 2, 3, -2, 4, 3, 999, 999},
                     {4, 3, 4, -3, -4, 5, 999, 999},
                     {4, 4, 4, -4, 5, 999, 999, 999},
                     {5, 1, 5, 999, 999, 999, 999, 999},
            /* 10 */ {5, 2, 5, 999, 999, 999, 999, 999},
                     {5, 5, 5, 6, 999, 999, 999, 999},
                     {6, 5, 6, -5, 8, -6, 7, 999},
                     {7, 1, 7, 999, 999, 999, 999, 999},
                     {7, 2, 7, 999, 999, 999, 999, 999},
            /* 15 */ {7, 5, 6, -5, 8, -6, 7, 999},
                     {8, 4, 8, -4, 999, 999, 999, 999},
                     {8, 7, 8, -7, 999, 999, 999, 999},
                     {9, 8, 9, -8, 999, 999, 999, 999},
            /* -> */ {9, 9, 9, -9, 999, 999, 999, 999},
            /* 20 */ {9, 10, 9, -10, 999, 999, 999, 999},
                     /* segunda gramática */
                     {10, 11, 10, -11, -11, -1, 999, 999},
                     {11, 12, 11, -12, 12, -13, 999, 999},
                     {12, 14, 12, -14, 999, 999, 999, 999},
                     {12, 4, 12, -4, 999, 999, 999, 999}};

int main(void)
{
    char resp; // variable para la respuesta de s o no
    do         // Se entra en un ciclo
    {
        // puts("Generar el Archivo (s/n) : ");

        cout << "¿Generar el archivo? (s/n): ";
        //cin>>resp;
        resp = cin.get();

        // cin.get();  //USAR CUANDO SE REQUIERA ELIMINAR EL ENTER

        // if(resp==0)  //NULL
        //   cin.get();

        if (strchr("Ss", resp))
            generararch();
        vabrirarch();
        // se guarda el tamaño de kb o bytes del archivo para saber si contiene texto

        numBytesArch = bytesarch();

        if (numBytesArch == 0)
        {
            printf("El archivo no tiene datos. Pulsa una tecla.");
            if (cin.get() == 0)
            {
                cin.get(); // getch();
                exit(-1);
            }
        }
        // fclose(Fd);

        else
            vanalisislexico();
        fclose(Fd);

        printf("Salida del Analizador Léxico (asTokens):");
        vmuestra();

        printf("\nPulsa una tecla para continuar.");
        if (cin.get() == 0) // getch()==0)
            cin.get();      // getch();
        vanalisis_sintactico();
        cin.get();
        printf("Presiona (sS) para continuar: ");
        cin >> resp;
    } while (strchr("Ss", resp));

    return 0;
}

void generararch()
{
    char car;          // variable para lectura del archivo
    char nomArch[100]; // nombre para archivo de maximo 100 caracteres

    // char *nombre = new char[100];
    // cin.getline(nombre,100,'\n');

    string nombre;
    printf("Nombre del archivo a generar (sin extensión): ");
    // gets(Nombre);  // <--- ERROR CON ESTE METODO
    cin >> nombre;

    // cin.get();    // ELIMINAR ENTER

    sprintf(nomArch, "%s.dat", nombre.c_str()); // se concatena el nombre del archivo en el arreglo
    Fd = fopen(nomArch, "w+b");                 // se dan permisos de escritura "write " y para escribir en binario
    if (Fd == NULL)
    {
        cout << "No se puede abrir el archivo." << nomArch;
        exit(-1);
    }
    // imprime en consola la entrada del usuario

    puts("Teclea el nombre del archivo: ");
    // cin.get();  // eliminar el enter
    // printf("Teclea <ESC> -USAR UNICODE DEL ESC -para terminar el archivo \n");

    printf("Teclea @ para terminar el archivo \n");

    //LA INFO ESTA EN EL BUFFER
    do
    {
        car = cin.get();
        // cin>>car;
        if (car == '\n') //13)
        {
            car = '\n';
            printf("\n");
        }
        if (car == 0) //NULL
            car = cin.get();
        if (car != '@') //27 && car != 8)
            fwrite(&car, sizeof(car), 1, Fd);

    } while (car != '@');

    fclose(Fd);
}

void vabrirarch()
{
    char nomArch[100];
    //char nombre[100];
    char *nombre = new char[100];

    printf("\nNombre del archivo a abrir (sin extensión): ");
    //gets(nombre);
    //cin>>nombre;
    cin.get(); //ELIMINAR EL ENTER
    cin.getline(nombre, 100, '\n');

    //sprintf(nomArch,"/Users/martinos/Desktop/appASintactico_XCode/%s.dat",nombre);  //,'\0');
    sprintf(nomArch, "%s.dat", nombre); //,'\0');

    Fd = fopen(nomArch, "r+b");

    if (Fd == NULL)
    {
        printf("No se puede abrir el archivo.");
        exit(-1); //cin.get();
    }
    else
    {
        printf("El archivo está abierto.\n");
    }
}

int bytesarch()
{
    // Metodo para saber si el archivo contiene datos
    int aux;
    // Abrimos el archivo desde la posicion requerida
    //   archivo, , posicion respecto al final del archivo
    fseek(Fd, 0L, SEEK_END);
    // auxiliar retorna la posicion del indicador
    aux = (int)ftell(Fd);
    //   archivo, posicion 0, a partir del inicio del archivo
    fseek(Fd, 0L, SEEK_SET);
    return aux;
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
            cCarent = nextchar();
            if (strchr(non, cCarent))
                edoAct = 1;
            else if (strchr(par, cCarent))
                edoAct = 2;
            else
                falla();
            break;
        case 1:
            cCarent = nextchar();
            if (strchr(non, cCarent))
                edoAct = 1;
            else if (strchr(par, cCarent))
                edoAct = 2;
            else
                falla();
            break;
        case 2:
            cCarent = nextchar();
            if (strchr(non, cCarent))
                edoAct = 1;
            else if (strchr(par, cCarent))
                edoAct = 2;
            else
                edoAct = 3;
            break;
        case 3:
            vretract();
            strcpy(asTokens[k++], "num"); //Estaba en mayusucula
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 4:
            cCarent = nextchar();
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
            cCarent = nextchar();
            if (strchr(par, cCarent))
                edoAct = 10;
            else if (strchr(non, cCarent))
                edoAct = 11;
            else
                falla();
            break;
        case 10:
            cCarent = nextchar();
            if (strchr(par, cCarent))
                edoAct = 10;
            else if (strchr(non, cCarent))
                edoAct = 11;
            else
                falla();
            break;
        case 11:
            cCarent = nextchar();
            if (strchr(non, cCarent))
                edoAct = 11;
            else if (strchr(par, cCarent))
                edoAct = 10;
            else
                edoAct = 12;
            break;
            // NON - PAR
        case 12:
            vretract();
            strcpy(asTokens[k++], "num");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 13:
            cCarent = nextchar();
            if ((isalpha(cCarent) || cCarent == '_'))
                edoAct = 14;
            else
                falla();
            break;
        case 14:
            cCarent = nextchar();
            if ((isalpha(cCarent) || cCarent == '_') || isdigit(cCarent))
                edoAct = 14;
            else
                edoAct = 15;
            break;
        case 15:
            vretract();
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
            cCarent = nextchar();
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
            cCarent = nextchar();
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
            cCarent = nextchar();
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
            cCarent = nextchar();
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
            cCarent = nextchar(); // funcion que lee el siguiente caracter
            if (('"' == cCarent) && cCarent)
                edoAct = 25;
            else
                falla();
            break;
        case 25:
            cCarent = nextchar(); // funcion que lee el siguiente caracter
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
            cCarent = nextchar();
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
            cCarent = nextchar();
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
            cCarent = nextchar();
            if (cCarent == '=')
                edoAct = 32;
            else
                falla();
            break;
        case 32:
            cCarent = nextchar();
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
            cCarent = nextchar();
            if (cCarent == '!')
                edoAct = 36;
            else
                falla();
            break;
        case 36:
            cCarent = nextchar();
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
            cCarent = nextchar();
            if (cCarent == '<' || cCarent == '>')
                edoAct = 39;
            else
                falla();
            break;
        case 39:
            cCarent = nextchar();
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

char nextchar()
{
    char cAux;
    fread(&cAux, sizeof(cAux), 1, Fd);
    indice++;
    return cAux;
}

void vretract()
{
    indice--;
    fseek(Fd, (long)indice, SEEK_SET);
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
        fseek(Fd, (long)iniToken, SEEK_SET);
        break;
    case 4:
        edoIni = 9;
        indice = iniToken;
        fseek(Fd, (long)iniToken, SEEK_SET);
        break;
    case 9:
        edoIni = 13;
        indice = iniToken;
        fseek(Fd, (long)iniToken, SEEK_SET);
        break;
    case 13:
        edoIni = 16;
        indice = iniToken;
        fseek(Fd, (long)iniToken, SEEK_SET);
        break;
    case 16:
        edoIni = 18;
        indice = iniToken;
        fseek(Fd, (long)iniToken, SEEK_SET);
        break;
    case 18:
        edoIni = 20;
        indice = iniToken;
        fseek(Fd, (long)iniToken, SEEK_SET);
        break;
    case 20:
        edoIni = 22;
        indice = iniToken;
        fseek(Fd, (long)iniToken, SEEK_SET);
        break;
    case 22:
        edoIni = 24;
        indice = iniToken;
        fseek(Fd, (long)iniToken, SEEK_SET);
        break;
    case 24:
        edoIni = 27;
        indice = iniToken;
        fseek(Fd, (long)iniToken, SEEK_SET);
        break;
    case 27:
        edoIni = 29;
        indice = iniToken;
        fseek(Fd, (long)iniToken, SEEK_SET);
        break;
    case 29:
        edoIni = 31;
        indice = iniToken;
        fseek(Fd, (long)iniToken, SEEK_SET);
        break;
    case 31:
        edoIni = 35;
        indice = iniToken;
        fseek(Fd, (long)iniToken, SEEK_SET);
        break;
    case 35:
        edoIni = 38;
        indice = iniToken;
        fseek(Fd, (long)iniToken, SEEK_SET);
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
    fseek(Fd, (long)iniToken, SEEK_SET);
    for (m = iniToken, n = 0; m < indice; m++, n++)
        fread(&sLexema[n], sizeof(char), 1, Fd);
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
    for (iJ = 0; iJ < k; iJ++) //,Ren++)
    {
        puts(asTokens[iJ]);
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
    char x[10], a[10];
    insertapila("$");
    if (strcmp(asTokens[ip], "puts") == 0)
        insertapila("F");
    else
        insertapila("D");

    printf("\nSalida del analizador sintáctico (asTokens):\n\n");
    printf("Arreglo de tokens:\n\n");
    for (i = 0; strcmp(asTokens[i], "$") != 0; i++)
        printf("%s ", asTokens[i]);
    printf("\n\nProducciones:\n\n");
    do
    {
        strcpy(x, pilac[cima]);
        strcpy(a, asTokens[ip]);
        if (estoken(x) || (strcmp(x, "$") == 0))
        {
            if (strcmp(x, a) == 0)
            {
                eliminapila();
                ip++;
            }
            else
            {
                if (strcmp(asTokens[ip], "puts") == 0)
                    insertapila("F");
                else
                    insertapila("D");
                strcpy(x, pilac[cima]);
            }
        }
        else //si no es token
        {
            renglon = buscaTabla(a, x);
            if (renglon != 999)
            {
                eliminapila();
                iast = 0;
                printf("%-3s -> ", varsint[tablaM[renglon][0]]);
                for (j = 3; iast != 999; j++)
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
                        insertapila(token[iast]);
                    }
                    else
                        insertapila(varsint[iast]);
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

void insertapila(string elem) // (char *elem) // (char elem[])
{
    if (cima == -1)
    {
        cima = 0;
        strcpy(pilac[cima], elem.c_str());
    }
    else
    {
        if (cima == MAX - 1)
            puts("Pila llena.");
        else
        {
            cima++;
            strcpy(pilac[cima], elem.c_str());
        } // pilac[cima+1][0]='\0';
    }
}

void eliminapila()
{
    // comparacion para saber cantidad de la pila (si esta vacia
    if (cima == -1)
        puts("Pila vacía.");
    else
    {
        strcpy(pilac[cima], ""); // en la cima se pone cadena vacia y se decrementa
        cima--;                  // elimninar cuando x = a
    }
}

int estoken(char x[])
{
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
