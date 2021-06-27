#include "analisislexico.h"

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
        edoIni = 12;
        indice = iniToken;
        fseek(Fd->Fd, (long)iniToken, SEEK_SET);
        break;
    case 12:
        edoIni = 15;
        indice = iniToken;
        fseek(Fd->Fd, (long)iniToken, SEEK_SET);
        break;
    case 15:
        edoIni = 17;
        indice = iniToken;
        fseek(Fd->Fd, (long)iniToken, SEEK_SET);
        break;
    case 17:
        edoIni = 19;
        indice = iniToken;
        fseek(Fd->Fd, (long)iniToken, SEEK_SET);
        break;
    case 19:
        edoIni = 21;
        indice = iniToken;
        fseek(Fd->Fd, (long)iniToken, SEEK_SET);
        break;
    case 21:
        edoIni = 23;
        indice = iniToken;
        fseek(Fd->Fd, (long)iniToken, SEEK_SET);
        break;
    case 23:
        edoIni = 26;
        indice = iniToken;
        fseek(Fd->Fd, (long)iniToken, SEEK_SET);
        break;
    case 26:
        edoIni = 28;
        indice = iniToken;
        fseek(Fd->Fd, (long)iniToken, SEEK_SET);
        break;
    case 28:
        edoIni = 30;
        indice = iniToken;
        fseek(Fd->Fd, (long)iniToken, SEEK_SET);
        break;
    case 30:
        edoIni = 34;
        indice = iniToken;
        fseek(Fd->Fd, (long)iniToken, SEEK_SET);
        break;
    case 34:
        edoIni = 37;
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
    case 37:
        recuperaerror();
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
    int iJ;
    // Se muestran los contenidos del arreglo asTokens introducidos en el analisis lexico
    puts("\nTokens reconocidos:\n");
    for (iJ = 0; iJ < k; iJ++) //,Ren++)
    {
        puts(asTokens[iJ]);
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
        if (strcmp(PalRes[m], sLexema) == 0)
            found = true;
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
            if (strchr(par, cCarent))
                edoAct = 9;
            else if (strchr(non, cCarent))
                edoAct = 10;
            else
                falla();
            break;
        case 9:
            cCarent = Fd->nextchar(indice);
            if (strchr(par, cCarent))
                edoAct = 9;
            else if (strchr(non, cCarent))
                edoAct = 10;
            else
                falla();
            break;
        case 10:
            cCarent = Fd->nextchar(indice);
            if (strchr(non, cCarent))
                edoAct = 10;
            else if (strchr(par, cCarent))
                edoAct = 9;
            else
                edoAct = 11;
            break;
            // NON - PAR
        case 11:
            Fd->vretract(indice);
            strcpy(asTokens[k++], "num");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 12:
            cCarent = Fd->nextchar(indice);
            if ((isalpha(cCarent) || cCarent == '_'))
                edoAct = 13;
            else
                falla();
            break;
        case 13:
            cCarent = Fd->nextchar(indice);
            if ((isalpha(cCarent) || cCarent == '_') || isdigit(cCarent))
                edoAct = 13;
            else
                edoAct = 14;
            break;
        case 14:
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
        case 15:
            cCarent = Fd->nextchar(indice);
            if (cCarent == ';')
                edoAct = 16;
            else
                falla();
            break;
            /* Al encontrar el caracter ';' , que indica fin de linea,
                 Se copia el caracter '$' al fin del arreglo astokens
                 */
        case 16:
            strcpy(asTokens[k++], ";");
            strcpy(asTokens[k], "$");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 17:
            cCarent = Fd->nextchar(indice);
            if (cCarent == '[')
                edoAct = 18;
            else
                falla();
            break;
        case 18:
            strcpy(asTokens[k++], "[");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 19:
            cCarent = Fd->nextchar(indice);
            if (cCarent == ']')
                edoAct = 20;
            else
                falla();
            break;
        case 20:
            strcpy(asTokens[k++], "]");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 21:
            cCarent = Fd->nextchar(indice);
            if (cCarent == ',')
                edoAct = 22;
            else
                falla();
            break;
        case 22:
            strcpy(asTokens[k++], ",");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 23:
            cCarent = Fd->nextchar(indice); // funcion que lee el siguiente caracter
            if (('"' == cCarent) && cCarent)
                edoAct = 24;
            else
                falla();
            break;
        case 24:
            cCarent = Fd->nextchar(indice); // funcion que lee el siguiente caracter
            if (('"' != cCarent) && cCarent)
                edoAct = 24;
            else if (cCarent)
                edoAct = 25;
            break;
        case 25:
            strcpy(asTokens[k++], "Cte.Lit");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 26:
            cCarent = Fd->nextchar(indice);
            if (cCarent == '(')
                edoAct = 27;
            else
                falla();
            break;
        case 27:
            strcpy(asTokens[k++], "(");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 28:
            cCarent = Fd->nextchar(indice);
            if (cCarent == ')')
                edoAct = 29;
            else
                falla();
            break;
        case 29:
            strcpy(asTokens[k++], ")");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 30:
            cCarent = Fd->nextchar(indice);
            if (cCarent == '=')
                edoAct = 31;
            else
                falla();
            break;
        case 31:
            cCarent = Fd->nextchar(indice);
            if (cCarent == '=')
                edoAct = 33;
            else
                edoAct = 32;
            break;
        case 32:
            strcpy(asTokens[k++], "=");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 33:
            strcpy(asTokens[k++], "op.rel");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break;
        case 34:
            cCarent = Fd->nextchar(indice);
            if (cCarent == '!')
                edoAct = 35;
            else
                falla();
            break;
        case 35:
            cCarent = Fd->nextchar(indice);
            if (cCarent == '=')
                edoAct = 36;
            else
                falla();
            break;
        case 36:
            strcpy(asTokens[k++], "op.rel");
            if (indice >= numBytesArch)
                return;
            iniToken = indice;
            viniedos();
            break; //Hasta aqui jala bien
        case 37:
            cCarent = Fd->nextchar(indice);
            if (cCarent == '<' || cCarent == '>')
                edoAct = 38;
            else
                falla();
            break;
        case 38:
            cCarent = Fd->nextchar(indice);
            if (cCarent == '=')
                edoAct = 39; //37?
            else
                edoAct = 39;
            break;
        case 39:
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

void AnalisisLexico::viniedos()
{
    //variable inicar estados
    edoAct = 0;
    edoIni = 0;
}
