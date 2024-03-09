#include <stdio.h>
#include <string.h>
#include <math.h>
void getKey(char s[500])
{
    getchar();
    fgets(s, 50, stdin);
    s[strlen(s) - 1] = '\0';
}
void getInt(int *n)
{
    scanf("%d", &*n);
}
// schimba valorile a 2 variabile int intre ele
void swapInt(int *n1, int *n2)
{
    int aux = *n1;
    *n1 = *n2;
    *n2 = aux;
}
// schimba valorile a 2 variabile char intre ele
void swapChar(char *c1, char *c2)
{
    char aux = *c1;
    *c1 = *c2;
    *c2 = aux;
}
// schimba valorile a 2 vectori de caractere intre ele
void swapString(char s1[50], char s2[50])
{
    char aux[50];
    strcpy(aux, s1);
    strcpy(s1, s2);
    strcpy(s2, aux);
}
// algoritm sequential sort pentru ordonarea
// alfabetica a literelor din cheie, retine simultan pozitia initiala
// a fiecarei litere
void sortString(char s[50], int pozi[50])
{
    // salvez pozitiile initiale
    for (int i = 0; i < strlen(s); i++)
        pozi[i] = i;
    for (int i = 0; i < strlen(s) - 1; i++)
    {
        for (int j = i + 1; j < strlen(s); j++)
        {
            if (s[j] < s[i])
            {
                swapChar(&s[j], &s[i]);
                swapInt(&pozi[j], &pozi[i]);
            }
        }
    }
}
// permuta la dreapta nrc caractere din textul retinut in text
void permR(char text[500], int nrc)
{
    char aux[500];
    strcpy(aux, text + strlen(text) - nrc);
    strncat(aux, text, strlen(text) - nrc);
    strcpy(text, aux);
}
// permuta la stanga nrc caractere din textul retinut in text
void permL(char text[500], int nrc)
{
    char aux[500];
    strcpy(aux, text + nrc);
    strncat(aux, text, nrc);
    strcpy(text, aux);
}
// adauga la primele nrc caractere din text valoarea variabilei nrc
void sum(char text[500], int nrc)
{
    for (int i = 0; i < nrc; i++)
    {
        if (text[i] > ' ')
        {
            if (text[i] <= 'Z')
            {
                int dif = 'Z' - text[i];
                if (nrc > dif)
                {
                    text[i] = 'a' + (nrc - dif - 1);
                }
                else
                    text[i] += nrc;
            }
            else
            {
                int dif = 'z' - text[i];
                if (nrc > dif)
                {
                    text[i] = 'A' + (nrc - dif - 1);
                }
                else
                    text[i] += nrc;
            }
        }
    }
}
// scade din primele nrc caractere din text valoarea variabilei nrc
void dif(char text[500], int nrc)
{
    for (int i = 0; i < nrc; i++)
    {
        if (text[i] > ' ')
        {
            if (text[i] <= 'Z')
            {
                int dif = text[i] - 'A';
                if (nrc > dif)
                {
                    text[i] = 'z' - (nrc - dif - 1);
                }
                else
                    text[i] -= nrc;
            }
            else
            {
                int dif = text[i] - 'a';
                if (nrc > dif)
                {
                    text[i] = 'Z' - (nrc - dif - 1);
                }
                else
                    text[i] -= nrc;
            }
        }
    }
}
// relizeaza codificarea A
void codA(char text[500])
{
    char key[50], aux[500] = "", keyMat[500][500] = {""};
    getKey(key);
    int nrchar = 0, keyLen = strlen(key);
    int pozi[50]; // vector pozitii initiale pt fiecare caracter
    sortString(key, pozi);
    int l = 0;//
    while (nrchar < strlen(text))
    {
        int i = 0;
        for (i = 0; i < keyLen && nrchar < strlen(text); i++)
            keyMat[i][l] = text[nrchar++];
        // daca am introdus tot textul in matrice
        // completez ultima linie cu spatii
        if (nrchar == strlen(text))
        {
            for (; i < keyLen; i++)
                keyMat[i][l] = ' ';
        }
        l++;
    }
    strcpy(aux, keyMat[pozi[0]]);
    for (int i = 1; i < keyLen; i++)
        strcat(aux, keyMat[pozi[i]]);
    strcpy(text, aux);
}
// realizeaza decodificarea A
void decodA(char text[500])
{
    char key[50], keyMat[500][500], aux[500] = "";
    getKey(key);
    int pozi[50], keyLen = strlen(key);
    // cuvLen reprezinta numarul de caractere
    // de pe fiecare coloana a tabelului format la codificare
    int cuvLen = ceil((double)strlen(text) / strlen(key));

    // completez textul cu spatii pentru ca
    // matricea ce va fi formata sa fie completa
    for (int i = strlen(text); i < keyLen * cuvLen; i++)
        text[i] = ' ';

    sortString(key, pozi);
    // vectorul pozi retine coloanele in ordinea lor initiala,
    // nu in cea curenta din sirul text unde sunt ordonate dupa cheie

    // impart textul in subsiruri de cate cuvLen caractere
    // si folosind pozi pot pune fiecare subsir pe linia
    // sa initiala din matricea construita la codificare
    for (int i = 0; i < keyLen; i++)
        strncpy(keyMat[pozi[i]], text + i * cuvLen, cuvLen);

    // parcurgem matricea formata anterior pe coloane,
    // construind caracter cu caracter textul decodificat
    int nrchar = 0;
    for (int i = 0; i < cuvLen; i++)
    {
        for (int j = 0; j < keyLen && nrchar < strlen(text); j++)
        {
            aux[nrchar++] = keyMat[j][i];
        }
    }
    strcpy(text, aux);
}
// realizeaza codificarea B
void codB(char text[500])
{
    int key;
    getInt(&key);
    permR(text, key);
    sum(text, key);
}
// realizeaza decodificarea B
void decodB(char text[500])
{
    int key;
    getInt(&key);
    dif(text, key);
    permL(text, key);
}
int main()
{
    char text[500], cod[20];
    char coda[] = "CodificareA", codb[] = "CodificareB";
    char decoda[] = "DecodificareA", decodb[] = "DecodificareB";
    fgets(text, 500, stdin);
    text[strlen(text) - 1] = '\0';
    scanf("%s", cod);
    while (strcmp(cod, "STOP"))
    {
        if (strcmp(cod, coda) == 0)
            codA(text);
        else if (strcmp(cod, decoda) == 0)
            decodA(text);
        else if (strcmp(cod, codb) == 0)
            codB(text);
        else if (strcmp(cod, decodb) == 0)
            decodB(text);
        printf("%s\n", text);
        scanf("%s", cod);
    }
    return 0;
}