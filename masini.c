#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// citeste de la tastatura un cuvant si il introduce intr-o variabila
// alocata dinamic care v-a fi returnata
char *getString()
{
    char aux[21], *s;
    scanf("%s", aux);
    s = (char *)malloc((strlen(aux) + 1) * sizeof(char));
    strcpy(s, aux);
    return s;
}
void citire(char **brand, char **numar, char **combustibil,
            double *consum, int *km, int n)
{
    for (int i = 0; i < n; i++)
    {
        brand[i] = getString();
        numar[i] = getString();
        combustibil[i] = getString();
        scanf("%lf%d", &consum[i], &km[i]);
    }
}
// rezolva task-ul a, vectorul nr contorizeaza masinile in functie
// de tipul de combustibil folosit
void taska(char **combustibil, char comb[4][9], int nr[4], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (strcmp(combustibil[i], comb[0]) == 0)
            nr[0]++;
        else if (strcmp(combustibil[i], comb[1]) == 0)
            nr[1]++;
        else if (strcmp(combustibil[i], comb[2]) == 0)
            nr[2]++;
        else
            nr[3]++;
    }
}
// cauta si returneaza brand-urile fara sa se repete
char **findBrands(char **brand, int n, int *nrm)
{
    char **brand2;
    brand2 = malloc(0);
    for (int i = 0; i < n; i++)
    {
        int found = 0;
        // verific daca am mai gasit brand-ul retinut in brand[i]
        for (int j = 0; j < i; j++)
        {
            if (strcmp(brand[i], brand[j]) == 0)
                found = 1;
        }
        if (found == 0)
        {
            // retin brand-ul gasit pentru prima oara
            (*nrm)++;
            brand2 = realloc(brand2, *nrm * sizeof(brand2));
            brand2[*nrm - 1] = malloc((strlen(brand[i]) + 1) * sizeof(char));
            strcpy(brand2[*nrm - 1], brand[i]);
        }
    }
    return brand2;
}
// calculeaza si returneaza consumul total al fiecarui brand de masini
double *calcConsum(char **brand, char **brandm, double *consum,
                   int *km, int n, int nrm)
{
    double *consum2 = (double *)malloc(nrm * sizeof(double));
    for (int i = 0; i < nrm; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (strcmp(brandm[i], brand[j]) == 0)
                consum2[i] += (consum[j] * km[j]) / 100;
        }
    }
    return consum2;
}
// calculeaza si returneaza suma platita pentru combustibilul
// folosit de fiecare brand de masini
double *calcPret(char **brand, char **brandm, char **combustibil,
                 double *consum, int *km, int n, int nrm)
{
    double costb = 8.02, costm = 9.29;
    double *pret2 = (double *)malloc(nrm * sizeof(double));
    for (int i = 0; i < nrm; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (strcmp(brandm[i], brand[j]) == 0)
            {
                if (strcmp(combustibil[j], "benzina") == 0 ||
                    strcmp(combustibil[j], "hibrid") == 0)
                    pret2[i] += ((consum[j] * km[j]) / 100) * costb;
                else
                    pret2[i] += ((consum[j] * km[j]) / 100) * costm;
            }
        }
    }
    return pret2;
}
// rezolva task-ul b
void taskb(char ***brandm, double **consumm, double **pretm, int *nrm,
           char **brand, char **combustibil, double *consum, int *km, int n)
{
    *brandm = findBrands(brand, n, &*nrm);
    *consumm = calcConsum(brand, *brandm, consum, km, n, *nrm);
    *pretm = calcPret(brand, *brandm, combustibil, consum, km, n, *nrm);
}
// returneaza 1 daca e numar valid, 0 in caz contrar
int verificNr(char *numar)
{
    int poz = 0;
    // un numar nu poate sa inceapa cu o cifra
    if (numar[poz++] <= '9')
        return 0;
    if (numar[poz++] <= '9')
    {
        // daca al doilea caracter din numar este o cifra,
        // atunci obligatoriu si al treilea trebuie sa fie tot o cifra
        if (numar[poz++] > '9')
            return 0;
        // daca al patrulea caracter e cifra, atunci urmatoarele trei
        // trebuie sa fie litere, daca al patrulea caracter e litera
        // atunci urmatoarele 2 caractere trebuie sa fie litere
        if (numar[poz] <= '9')
        {
            poz++; // de pe poz asta incep ultimele 3 litere
        }
    }
    else
    {
        // daca al doilea caracter este litera
        // atunci urmatoarele 2 sunt neaparat cifre
        if (numar[poz++] > '9' || numar[poz++] > '9')
            return 0;
        // daca al cincilea caracter e cifra atunci urmatoarele 3
        // trebuie sa fie litere, altfel doar urmatoarele 2 trebuie
        // sa fie litere
        if (numar[poz] <= '9')
        {
            poz++; // de pe poz asta incep ultimele 3 litere
        }
    }
    // verific daca numarul are 3 litere dupa prefixul gasit precedent
    for (int i = poz; i < poz + 3; i++)
        if (numar[i] < 'A')
            return 0;
    // daca mai extista caractere neverificate numarul nu e bun
    if (poz + 3 < strlen(numar))
        return 0;
    return 1;
}
// rezolva task-ul c
void taskc(char **numar, int *pozg, int n, int *nrg)
{
    for (int i = 0; i < n; i++)
    {
        if (!verificNr(numar[i]))
        {
            (*nrg)++;
            pozg = (int *)realloc(pozg, *nrg * sizeof(int));
            pozg[*nrg - 1] = i;
        }
    }
}
int main()
{
    int n;
    scanf("%d", &n);
    char **brand, **numar, **combustibil;
    double *consum;
    int *km;

    brand = malloc(n * sizeof(brand));
    numar = malloc(n * sizeof(numar));
    combustibil = malloc(n * sizeof(combustibil));
    consum = (double *)malloc(n * sizeof(double));
    km = (int *)malloc(n * sizeof(int));

    citire(brand, numar, combustibil, consum, km, n);

    getchar(); // trec pe ultima linie
    char task = getchar();

    if (task == 'a')
    {
        int nr[4] = {0, 0, 0, 0};
        char comb[4][9] = {"benzina", "motorina", "hibrid", "electric"};
        taska(combustibil, comb, nr, n);
        for (int i = 0; i < 4; i++)
            printf("%s - %d\n", comb[i], nr[i]);
    }
    else if (task == 'b')
    {
        // numarul de marci unice din lista citita
        int nrm = 0;
        // vector in care retin pretul platit de fiecare marca de masini
        double *pretm = malloc(0);
        // vector in care retin consumul fiecarei marci de masini
        double *consumm = malloc(0);
        // vector de pointeri la cuvinte in care retin brand-urile
        // fara sa se repete, in ordinea citirii lor
        char **brandm;
        brandm = malloc(0);
        taskb(&brandm, &consumm, &pretm, &nrm,
              brand, combustibil, consum, km, n);
        for (int i = 0; i < nrm; i++)
            printf("%s a consumat %.2lf - %.2lf lei\n",
                   brandm[i], consumm[i], pretm[i]);
        free(pretm);
        free(consumm);
        for (int i = 0; i < nrm; i++)
            free(brandm[i]);
        free(brandm);
    }
    else if (task == 'c')
    {
        // numarul numerelor de inmatriculare gresite
        int nrg = 0;
        // vector in care retin pozitiile din lista a masinilor
        // cu numarul de inmatriculare gresit
        int *pozg = (int *)malloc(0);
        taskc(numar, pozg, n, &nrg);
        if (nrg == 0)
            printf("Numere corecte!\n");
        else
        {
            for (int i = 0; i < nrg; i++)
                printf("%s cu numarul %s: numar invalid\n",
                       brand[pozg[i]], numar[pozg[i]]);
        }
        free(pozg);
    }
    for (int i = 0; i < n; i++)
        free(brand[i]);
    free(brand);
    free(numar);
    free(combustibil);
    free(consum);
    free(km);
    return 0;
}