#include "analisislexico.h"

AnalisisLexico::AnalisisLexico()
{

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

void AnalisisLexico::recuperaerror()
{
    iniToken = indice;
    viniedos();
}

void AnalisisLexico::vanalisislexico(int &numBytesArch)
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
