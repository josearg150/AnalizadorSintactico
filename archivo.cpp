#include "archivo.h"

using namespace std;

Archivo::Archivo()
{

}

void Archivo::generararch()
{
    char car;          // variable para lectura del archivo
    char nomArch[100]; // nombre para archivo de maximo 100 caracteres

    string nombre;
    printf("Nombre del archivo a generar (sin extension): ");
    cin >> nombre;

    sprintf(nomArch, "%s.dat", nombre.c_str()); // se concatena el nombre del archivo en el arreglo
    Fd = fopen(nomArch, "w+b");                 // se dan permisos de escritura "write " y para escribir en binario
    if (Fd == NULL)
    {
        cout << "No se puede abrir el archivo." << nomArch;
        exit(-1);
    }

    puts("Teclea el nombre del archivo: ");

    printf("Teclea @ para terminar el archivo \n");

    //LA INFO ESTA EN EL BUFFER
    do
    {
        car = cin.get();
        // cin>>car;
        if (car == '\n') //13)
        {
            car = '\n';
        }
        if (car == 0) //NULL
            car = cin.get();
        if (car != '@') //27 && car != 8)
            fwrite(&car, sizeof(car), 1, Fd);

    } while (car != '@');

    fclose(Fd);
}

int Archivo::vabrirarch(string nombreArchivo)
{
        char nomArch[100];
        const char *cstr = nombreArchivo.c_str();
        sprintf(nomArch, cstr);

        Fd = fopen(nomArch, "r+b");

        if (Fd == NULL)
        {
            return 1;
        }
        return 0;
}

int Archivo::bytesarch()
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

void Archivo::vretract(int &indice)
{
    indice--;
    fseek(Fd, (long)indice, SEEK_SET);
}

char Archivo::nextchar(int &indice)
{
    char cAux;
    fread(&cAux, sizeof(cAux), 1, Fd);
    indice++;
    return cAux;
}

void Archivo::cerrararch()
{
   fclose(Fd);
}
