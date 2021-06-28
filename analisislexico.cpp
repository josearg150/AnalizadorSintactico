#include "analisislexico.h"
#include "mainwindow.h"

AnalisisLexico::AnalisisLexico()
{

}

AnalisisLexico::AnalisisLexico( Archivo *F, char **asTkns){
    asTokens = asTkns;
    Fd = F;
}

int AnalisisLexico::edoActesacept()
{
    switch (edoAct)
    {
    case 2:
    case 4:
    case 5:
    case 6:
    case 7:
    case 10:
    case 13:
    case 15:
    case 17:
    case 19:
    case 21:
    case 24:
    case 26:
    case 28:
    case 31:
    case 32:
    case 35:
    case 38:
    case 39:
    case 42:
    case 43:
    case 45:
    case 47:
        return true;
    default:
        return false;
    }
}

void AnalisisLexico::falla()
{
    switch (edoIni)
    {
    case 0:
        edoIni = 3;
        indice = iniToken;
        fseek(Fd->Fd, (long)iniToken, SEEK_SET);
        break;//no hay case 1
    case 3:
        edoIni = 8;
        indice = iniToken;
        fseek(Fd->Fd, (long)iniToken, SEEK_SET);
        break;
    case 8:
        edoIni = 11;
        indice = iniToken;
        fseek(Fd->Fd, (long)iniToken, SEEK_SET);
        break;
    case 11:
        edoIni = 14;
        indice = iniToken;
        fseek(Fd->Fd, (long)iniToken, SEEK_SET);
        break;
    case 14:
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
        edoIni = 25;
        indice = iniToken;
        fseek(Fd->Fd, (long)iniToken, SEEK_SET);
        break;
    case 25:
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
        edoIni = 33;
        indice = iniToken;
        fseek(Fd->Fd, (long)iniToken, SEEK_SET);
        break;
    case 33:
        edoIni = 36;
        indice = iniToken;
        fseek(Fd->Fd, (long)iniToken, SEEK_SET);
        break;
    case 36:
        edoIni = 40;
        indice = iniToken;
        fseek(Fd->Fd, (long)iniToken, SEEK_SET);
        break;
    case 40:
        edoIni = 44;
        indice = iniToken;
        fseek(Fd->Fd, (long)iniToken, SEEK_SET);
        break;
    case 44:
        edoIni = 46;
        indice = iniToken;
        fseek(Fd->Fd, (long)iniToken, SEEK_SET);
        break;
    /*case 46:
        edoIni = 48;
        indice = iniToken;
        fseek(Fd->Fd, (long)iniToken, SEEK_SET);
        break;*/
    case 46:recuperaerror();
    }
    edoAct = edoIni;
}

void AnalisisLexico::recuperaerror()
{
    iniToken = indice;
    viniedos();
}

void AnalisisLexico::vmuestra()
{
    // Se muestran los contenidos del arreglo asTokens introducidos en el analisis lexico
    //puts("\nTokens reconocidos:\n");
    for (int i = 0; i < k; i++) //,Ren++)
    {
        puts(asTokens[i]);
    }
}

int AnalisisLexico::esId()
{
    int n, m, found = false;
    fseek(Fd->Fd, (long)iniToken, SEEK_SET);
    for (m = iniToken, n = 0; m < indice; m++, n++)
        fread(&sLexema[n], sizeof(char), 1, Fd->Fd);
    sLexema[n] = '\0';
    for (m = 0; m < NUMPALRES && !found;)
        if (strcmp(PalRes[m], sLexema) == 0){
            found = true;
            break;
        }
        else
            m++;
    return (found ? 0 : 1);
}

void AnalisisLexico::vanalisislexico(int numBytesArch)
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
            if(isdigit(cCarent))
                edoAct = 1;
            else
                falla();
            break;
        case 1:
            cCarent = Fd->nextchar(indice);
             if(isdigit(cCarent))
                edoAct = 1;
                else if(cCarent == '.')
                    edoAct = 3;
             else
                 edoAct = 2;
            break;

        case 2:
            Fd->vretract(indice);
            strcpy(asTokens[k++], "num"); //Estaba en mayusucula
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 3:
            cCarent = Fd->nextchar(indice);
            switch (cCarent)
            {
            case '+':
                edoAct = 4;
                break;
            case '-':
                edoAct = 5;
                break;
            case '*':
                edoAct = 6;
                break;
            case '/':
                edoAct = 7;
                break;
            default:
                falla();
            }
            break;
        case 4:
            strcpy(asTokens[k++], "+");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 5:
            strcpy(asTokens[k++], "-");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 6:
            strcpy(asTokens[k++], "*");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 7:
            strcpy(asTokens[k++], "/");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
            //. OTRA VEZ NON - PAR
        case 8:
            cCarent = Fd->nextchar(indice);
            if(isdigit(cCarent))
                edoAct = 9;
            else
                falla();
            break;
        case 9:
            cCarent = Fd->nextchar(indice);
            if(isdigit(cCarent))
                edoAct = 9;
            else
                edoAct = 10;
            break;
        case 10:
            Fd->vretract(indice);
            strcpy(asTokens[k++], "num");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 11:
            cCarent = Fd->nextchar(indice);
            if ((isalpha(cCarent) || cCarent == '_'))
                edoAct = 12;
            else
                falla();
            break;
        case 12:
            cCarent = Fd->nextchar(indice);
            if ((isalpha(cCarent) || cCarent == '_') || isdigit(cCarent))
                edoAct = 12;
            else
                edoAct = 13;
            break;
        case 13:
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
        case 14:
            cCarent = Fd->nextchar(indice);
            if (cCarent == ';')
                edoAct = 15;
            else
                falla();
            break;
            /* Al encontrar el caracter ';' , que indica fin de linea,
                 Se copia el caracter '$' al fin del arreglo astokens
                 */
        case 15:
            strcpy(asTokens[k++], ";");
            strcpy(asTokens[k], "$");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 16:
            cCarent = Fd->nextchar(indice);
            if (cCarent == '[')
                edoAct = 17;
            else
                falla();
            break;
        case 17:
            strcpy(asTokens[k++], "[");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 18:
            cCarent = Fd->nextchar(indice);
            if (cCarent == ']')
                edoAct = 19;
            else
                falla();
            break;
        case 19:
            strcpy(asTokens[k++], "]");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 20:
            cCarent = Fd->nextchar(indice);
            if (cCarent == ',')
                edoAct = 21;
            else
                falla();
            break;
        case 21:
            strcpy(asTokens[k++], ",");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 22:
            cCarent = Fd->nextchar(indice); // funcion que lee el siguiente caracter
            if (('"' == cCarent) && cCarent)
                edoAct = 23;
            else
                falla();
            break;
        case 23:
            cCarent = Fd->nextchar(indice); // funcion que lee el siguiente caracter
            if (('"' != cCarent) && cCarent)
                edoAct = 23;
            else if (cCarent)
                edoAct = 24;
            break;
        case 24:
            strcpy(asTokens[k++], "Cte.Lit");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 25:
            cCarent = Fd->nextchar(indice);
            if (cCarent == '(')
                edoAct = 26;
            else
                falla();
            break;
        case 26:
            strcpy(asTokens[k++], "(");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 27:
            cCarent = Fd->nextchar(indice);
            if (cCarent == ')')
                edoAct = 28;
            else
                falla();
            break;
        case 28:
            strcpy(asTokens[k++], ")");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 29:
            cCarent = Fd->nextchar(indice);
            if (cCarent == '=')
                edoAct = 30;
            else
                falla();
            break;
        case 30:
            cCarent = Fd->nextchar(indice);
            if (cCarent == '=')
                edoAct = 32;
            else
                edoAct = 31;
            break;
        case 31:
            strcpy(asTokens[k++], "=");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 32:
            strcpy(asTokens[k++], "==");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 33:
            cCarent = Fd->nextchar(indice);
            if (cCarent == '!')
                edoAct = 34;
            else
                falla();
            break;
        case 34:
            cCarent = Fd->nextchar(indice);
            if (cCarent == '=')
                edoAct = 35;
            else
                falla();
            break;
        case 35:
            strcpy(asTokens[k++], "!=");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break; //Hasta aqui jala bien
        case 36:
            cCarent = Fd->nextchar(indice);
            if (cCarent == '<')
                edoAct = 37;
            else
                falla();
            break;
        case 37:
            cCarent = Fd->nextchar(indice);
            if (cCarent == '=')
                edoAct = 38; //37?
            else
                edoAct = 39;
            break;
        case 38:
            strcpy(asTokens[k++], "<=");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 39:
            strcpy(asTokens[k++], "<");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 40:
            cCarent = Fd->nextchar(indice);
            if (cCarent == '>')
                edoAct = 41;
            else
                falla();
            break;
        case 41:
            cCarent = Fd->nextchar(indice);
            if (cCarent == '=')
                edoAct = 42; //37?
            else
                edoAct = 43;
            break;
        case 42:
            strcpy(asTokens[k++], ">=");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 43:
            strcpy(asTokens[k++], ">");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 44:
            cCarent = Fd->nextchar(indice);
            if (cCarent == '{')
                edoAct = 45;
            else
                falla();
            break;
        case 45:
            strcpy(asTokens[k++], "{");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 46:
            cCarent = Fd->nextchar(indice);
            if (cCarent == '}')
                edoAct = 47;
            else
                falla();
            break;
        case 47:
            strcpy(asTokens[k++], "}");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;

        } /*switch*/
    }     /*while*/
}

void AnalisisLexico::viniedos()
{
    //variable inicar estados
    edoAct = 0;
    edoIni = 0;
}

char** AnalisisLexico::getAsTokens() {
    return this->asTokens;
}

int AnalisisLexico::getK() {
    return this->k;
}
