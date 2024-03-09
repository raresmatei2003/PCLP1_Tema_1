#include <stdio.h>
#include <string.h>
// compar partea reala a doua numere
// a>b returneaza 1, a=b returneaza 0, a<b returneaza -1
int compReal(char a[1001], char b[1001], int n)
{
    for (int i = 1; i < n / 2; i++)
    {
        if (a[i] < b[i])
            return -1;
        if (a[i] > b[i])
            return 1;
    }
    return 0;
}
// compar partea imaginara a doua numere
// a>b returneaza 1, a=b returneaza 0, a<b returneaza -1
int compImag(char a[1001], char b[1001], int n)
{
    for (int i = n / 2 + 1; i < n - 1; i++)
    {
        if (a[i] < b[i])
            return -1;
        if (a[i] > b[i])
            return 1;
    }
    return 0;
}
void scadereReal(char a[1001], char b[1001], char c[1001], int n);
// aduna partea reala a doua numere
void adunareReal(char a[1001], char b[1001], char c[1001], int n)
{
    // a[0]='0' => partea reala a lui a este pozitiva
    // a[0]='1' => partea reala a lui a este negativa
    // analog pentru b
    if (a[0] == '0' && b[0] == '0')
    {
        int t = 0;
        int sum = 0;
        for (int i = n / 2 - 1; i > 0; i--)
        {
            sum = a[i] - '0' + b[i] - '0' + t;
            c[i] = (sum % 10) + '0';
            t = sum / 10;
        }
    }
    else if (a[0] == '1' && b[0] == '0')
    {
        a[0] = '0'; // trec partea reala a lui a in modul
        scadereReal(b, a, c, n);
    }
    else if (a[0] == '0' && b[0] == '1')
    {
        b[0] = '0'; // trec partea reala a lui b in modul
        scadereReal(a, b, c, n);
    }
    else
    {
        c[0] = '1'; // retin faptul ca partea reala a rezultatului e negativa
        a[0] = '0';
        b[0] = '0';
        adunareReal(a, b, c, n);
    }
}
// face scaderea partilor reale a doua numere
void scadereReal(char a[1001], char b[1001], char c[1001], int n)
{
    if (a[0] == '0' && b[0] == '0')
    {
        if (compReal(a, b, n) >= 0)
        {
            int t = 0;
            int dif = 0;
            for (int i = n / 2 - 1; i > 0; i--)
            {
                dif = a[i] - '0' - (b[i] - '0') + t;
                if (dif < 0)
                {
                    dif += 10;
                    t = -1;
                }
                else
                    t = 0;
                c[i] = dif + '0';
            }
        }
        else
        {
            c[0] = '1';
            scadereReal(b, a, c, n);
        }
    }
    else if (a[0] == '1' && b[0] == '0')
    {
        a[0] = '0';
        c[0] = '1';
        adunareReal(a, b, c, n);
    }
    else if (a[0] == '0' && b[0] == '1')
    {
        b[0] = '0';
        adunareReal(a, b, c, n);
    }
    else
    {
        a[0] = '0';
        b[0] = '0';
        scadereReal(b, a, c, n);
    }
}
void scadereImag(char a[1001], char b[1001], char c[1001], int n);
// adauga partea imaginara a doua numere
void adunareImag(char a[1001], char b[1001], char c[1001], int n)
{
    if (a[n / 2] == '0' && b[n / 2] == '0')
    {
        int t = 0;
        int sum = 0;
        for (int i = n - 2; i > n / 2; i--)
        {
            sum = a[i] - '0' + b[i] - '0' + t;
            c[i] = (sum % 10) + '0';
            t = sum / 10;
        }
    }
    else if (a[n / 2] == '1' && b[n / 2] == '0')
    {
        a[n / 2] = '0'; // trec partea imaginara a lui a in modul
        scadereImag(b, a, c, n);
    }
    else if (a[n / 2] == '0' && b[n / 2] == '1')
    {
        b[n / 2] = '0'; // trec partea imaginara a lui b in modul
        scadereImag(a, b, c, n);
    }
    else
    {
        // retin faptul ca partea imaginara a rezultatului e negativa
        c[n / 2] = '1';
        a[n / 2] = '0';
        b[n / 2] = '0';
        adunareImag(a, b, c, n);
    }
}
// scade partea imaginara a doua numere
void scadereImag(char a[1001], char b[1001], char c[1001], int n)
{
    if (a[n / 2] == '0' && b[n / 2] == '0')
    {
        if (compImag(a, b, n) >= 0)
        {
            int t = 0;
            int dif = 0;
            for (int i = n - 2; i > n / 2; i--)
            {
                dif = a[i] - '0' - (b[i] - '0') + t;
                if (dif < 0)
                {
                    dif += 10;
                    t = -1;
                }
                else
                    t = 0;
                c[i] = dif + '0';
            }
        }
        else
        {
            c[n / 2] = '1';
            scadereImag(b, a, c, n);
        }
    }
    else if (a[n / 2] == '1' && b[n / 2] == '0')
    {
        a[n / 2] = '0';
        c[n / 2] = '1';
        adunareImag(a, b, c, n);
    }
    else if (a[n / 2] == '0' && b[n / 2] == '1')
    {
        b[n / 2] = '0';
        adunareImag(a, b, c, n);
    }
    else
    {
        a[n / 2] = '0';
        b[n / 2] = '0';
        scadereImag(b, a, c, n);
    }
}
// realizeaza adunarea a doua numere
void adunare(char a[1001], char b[1001], char c[1001], int n)
{
    adunareReal(a, b, c, n);
    adunareImag(a, b, c, n);
}
// realizeaza scaderea a doua numere
void scadere(char a[1001], char b[1001], char c[1001], int n)
{
    scadereReal(a, b, c, n);
    scadereImag(a, b, c, n);
}
int main()
{
    int n;
    scanf("%d", &n);
    char a[1001], b[1001], semn;
    scanf("%s", a);
    getchar();
    semn = getchar();
    while (semn != '0')
    {
        char c[1001];
        // initializez tot vectorul c cu null-uri
        // apoi pun 0-uri in primele n-1 pozitii,
        // acestea urmand sa fie modificate
        memset(c, '\0', 1001);
        memset(c, '0', n - 1);
        scanf("%s", b);
        if (semn == '+')
        {
            adunare(a, b, c, n);
        }
        else
        {
            scadere(a, b, c, n);
        }
        strcpy(a, c);
        printf("%s\n", a);
        getchar();
        semn = getchar();
    }
    return 0;
}