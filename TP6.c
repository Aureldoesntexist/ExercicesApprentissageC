//
// Created by aurel on 15/03/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NBMAX 52

const char *Enseigne[] =
        {
                "", "Carreau", "Coeur", "Pique", "Trefle"
        };

const char *ValFig[] =
        {
                "", "1", "2", "3", "4", "5", "6", "7", "8",
                "9", "10", "Valet", "Dame", "Roi"
        };


typedef struct
{
    int enseigne;
    int figure;
} carte;

void afficheCarte(carte c)
{
    printf("%s de %s\n", ValFig[c.figure], Enseigne[c.enseigne]);
}

typedef struct
{
    int nbr;
    carte tab[NBMAX];
} paquet;

void videPaquet(paquet *p)
{
    p->nbr = 0;
}

void affichePaquet(paquet *p)
{
    for (int i = 0; i < p->nbr; ++i)
    {
        afficheCarte(p->tab[i]);
    }
}

void produitJeu52(paquet *p)
{
    videPaquet(p);

    for (int e = 1; e <= 4; e++)
    {
        for (int f = 1; f <= 13; f++)
        {
            p->tab[p->nbr].enseigne = e;
            p->tab[p->nbr].figure = f;
            p->nbr++;
        }
    }
}

void melangePaquet(paquet *p)
{
    carte tmp;
    int alea;

    for (int i = 0; i < p->nbr; i++)
    {
        alea = i + rand() % (p->nbr - i);
        tmp = p->tab[i];
        p->tab[i] = p->tab[alea];
        p->tab[alea] = tmp;
    }
}

carte tireCarte(paquet *p)
{
    carte carteRetiree = p->tab[p->nbr - 1];
    p->nbr--;
    return carteRetiree;
}

void ajouteCarte(paquet *p, carte c)
{
    int carteExistante = 0;
    for (int i = 0; i < p->nbr; ++i)
    {
        if (p->tab[i].figure == c.figure && p->tab[i].enseigne == c.enseigne)
        {
            carteExistante = 1;
        }
    }
    if (!carteExistante)
    {
        p->tab[p->nbr] = c;
        p->nbr++;
        printf("Carte ajoutee au paquet.\n");
    }
    else
    {
        printf("La carte se trouve deja dans le paquet.\n");
    }

}

typedef struct
{
    int capacite;
    int nbr;
    carte *tab;
} paquext;

void initPaquext(paquext *p, int capacite)
{
    p->tab = (carte *) calloc(capacite, sizeof(int));
}

void liberePaquext(paquext *p)
{
    free(p->tab);
}

int main()
{
    srand((unsigned) time(NULL));
    paquet p[NBMAX];
    produitJeu52(p);
    affichePaquet(p);
    printf("--------------------Paquet melange-----------------------\n");
    melangePaquet(p);
    affichePaquet(p);
    printf("--------------------Derniere carte------------------------\n");
    afficheCarte(tireCarte(p));
    printf("--------------------Ajout carte---------------------------\n");
    carte c = {3, 3};
    afficheCarte(c);
    ajouteCarte(p, c);
}