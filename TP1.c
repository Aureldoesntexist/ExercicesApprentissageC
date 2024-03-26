#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 50
#define P1 22
#define P2 23

// Affiche les particules
void affiche(int a, int b)
{
    printf("O");
    for (int i = 0; i < SIZE; i++)
    {
        if (i == a)
            printf("A");
        else if (i == b)
            printf("B");
        else
            printf(" ");
    }
    printf("O\n");
}

// Simule n états successifs
void simule(int n)
{
    int A = P1;                 // Position initiale de A
    int B = P2;                 // Position initiale de B
    for (int i = 0; i < n; i++) // Boucle des tours
    {
        affiche(A, B);

        if (i % 2 == 0) // Mouvement de A
        {
            if (A + 1 == B) // Si B est à coté de A
            {
                if (A != 0)
                {
                    A--; // On recule s'il n'est pas à la case départ
                } // Sinon on ne fait rien
            }
            else if (A == 0 && A + 1 != B) // Si A est à la case départ et qu'il y a pas B alors on avance
            {
                A++; // Avnce
            }
            else
            {
                int alea = 1 + rand() % 2; // Soit gauche soit droite
                if (alea % 2 == 0)
                {
                    A++; // Avance
                }
                else
                {
                    A--; // Recul
                }
            }
        }
        else // Mouvement de B
        {

            if (B == SIZE && B - 1 != A) // Si B est à la case de fin et qu'il y a pas A alors on recule
            {
                B--;
            }
            else if (B != SIZE && B - 1 != A) // Si B n'est pas à la fin et qu'il y a pas A alors
                // on prend une direction aleatoire
            {
                int alea = 1 + rand() % 2; // Soit gauche soit droite
                if (alea % 2 == 0)
                {
                    B--; // Recule
                }
                else
                {
                    B++; // Avance
                }
            }
            else // Si A est à gauche et que B n'est pas à la fin alors il avance
            {
                B++;
            }

        }

    }
    affiche(A, B);

}

int main()
{
    srand((unsigned) time(NULL));
    simule(20);
    return 0;
}
