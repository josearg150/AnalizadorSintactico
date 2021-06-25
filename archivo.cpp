#include "archivo.h"

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
    // imprime en consola la entrada del usuario

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
            printf("\n");
        }
        if (car == 0) //NULL
            car = cin.get();
        if (car != '@') //27 && car != 8)
            fwrite(&car, sizeof(car), 1, Fd);

    } while (car != '@');

    fclose(Fd);
}

void Archivo::vabrirarch()
{
        char nomArch[100];
        char *nombre = new char[100];

        printf("\nNombre del archivo a abrir (sin extension): ");
        cin.get(); //ELIMINAR EL ENTER
        cin.getline(nombre, 100, '\n');
        sprintf(nomArch, "%s.dat", nombre); //,'\0');

        Fd = fopen(nomArch, "r+b");

        if (Fd == NULL)
        {
            printf("No se puede abrir el archivo.");
            exit(-1); //cin.get();
        }
        else
        {
            printf("El archivo esta abierto.\n");
        }

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
