#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZESTR 10

char *saisie()
{
    static char buffer[SIZESTR + 1];
    fgets(buffer, SIZESTR + 1, stdin);
    buffer[strlen(buffer) - 1] = 0;
    return buffer;
}

int estVide(int *pile)
{
    if (pile[1] == 0)
    {
        return 1;
    }
    return 0;
}

int *creePile(int i)
{
    int *stack = (int *) calloc(i + 2, sizeof(int));
    stack[0] = i;
    stack[1] = 0;
    return stack;
}

void empile(int *pile, int val)
{
    pile[1]++;
    pile[pile[1] + 1] = val;
}

int sommet(int *pile)
{
    if (estVide(pile))
    {
        return 0;
    }
    return pile[pile[1] + 1];
}

int depile(int *pile)
{
    if (estVide(pile))
    {
        return 0;
    }
    pile[1]--;
    int val = sommet(pile);
    return val;
}


int capaDispo(const int *pile)
{
    int dispo = pile[0] - pile[1];
    return dispo;
}

void detruitPile(int *pile)
{
    free(pile);
}

void prinTab(int *pile, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", pile[i]);
    }
    printf("\n");
}

void calcul()
{
    int *pile = creePile(1000);
    char *str = saisie();
    int val = 0;
    while (str[0])
    {
        int c = str[0];
        if ((c == '+') || (c == '-') || (c == '*') || (c == '/'))
        {
            switch (c)
            {
                case '+':
                    val += depile(pile);
                    break;
                case '-':
                    val -= depile(pile);
                    break;
                case '*':
                    val = val * depile(pile);
                    break;
                case '/':
                    val = val / depile(pile);

                    break;
                default:
                    break;
            }
            printf("Valeur totale actuelle : %d\n", val);
        }
        else
        {
            sscanf(str, "%d", &val);
        }
        empile(pile, val);
        str = saisie();

    }

    printf("Résultat : %d\n", sommet(pile));
    free(pile);
}

int main()
{
    calcul();
    int capa = 10;
    int *pile = creePile(capa);
    printf("Début\n");
    prinTab(pile, capa + 2);
    empile(pile, 5);
    prinTab(pile, capa + 2);
    empile(pile, 9);
    prinTab(pile, capa + 2);
    depile(pile);
    empile(pile, 15);
    prinTab(pile, capa + 2);
    depile(pile);
    empile(pile, 112);
    prinTab(pile, capa + 2);
    detruitPile(pile);
}
