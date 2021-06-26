#include "analisissintactico.h"

AnalisisSintactico::AnalisisSintactico()
{

}

AnalisisSintactico::AnalisisSintactico(char *asTkns[], Pila<string> *pila)
{
    asTokens = asTkns;
    pilac = pila;
}

void AnalisisSintactico::vanalisis_sintactico()
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

int AnalisisSintactico::buscaTabla(char a[], char x[])
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

int AnalisisSintactico::estoken(char x[])
{
    int i;
    for (i = 0; i < 15; i++)
    {
        if (strcmp(x, token[i]) == 0)
            return 1;
    }
    return 0;
}

