#include <stdio.h>
// citesc numarul de prizonieri si continutul cutiilor
void inputRead(int *p, int c[501])
{
    scanf("%d", &*p);
    for (int i = 1; i <= *p; i++)
        scanf("%d", &c[i]);
}
// returneaza lungimea unui ciclu incepand de pe o pozitie data
int loopLength(int c[501], int pozStart, int fr[501])
{
    int poz = pozStart, l = 0;
    do
    {
        // marchez cutia de pe pozitia i ca apartinand unui ciclu
        fr[poz] = 1;
        poz = c[poz];
        l++;
    } while (poz != pozStart);
    return l;
}
// afiseaza un ciclu incepand de pe o pozitie data
void loopPrint(int c[501], int pozStart)
{
    int poz = c[pozStart];
    printf("%d", pozStart);
    while (poz != pozStart)
    {
        printf(" %d", poz);
        poz = c[poz];
    }
    printf("\n");
}
int main()
{
    int p, c[501], fr[501] = {0}, ls[501], lnr = 0, okWin = 1;
    inputRead(&p, c);
    for (int i = 1; i <= p; i++)
    {
        // daca cutia de pe poz i nu e marcata inseamna ca apartine
        // unui ciclu care nu a fost gaist
        if (fr[i] == 0)
        {
            ls[++lnr] = i;
            // daca lungimea unui ciclu depaseste jumatate din 
            // nr de prizonieri atunci jocul este pierdut
            if (loopLength(c, i, fr) > p / 2)
                okWin = 0;
        }
    }
    if (okWin == 1)
        printf("Da\n");
    else
        printf("Nu\n");
    for (int i = 1; i <= lnr; i++)
        loopPrint(c, ls[i]);
    return 0;
}