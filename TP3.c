#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define BLANK 0b01000000 // Valeur #
#define ZERO 0b00000000  // Valeur 0
#define ONE 0b00100000   // Valeur 1

#define LEFT 0b00000000  // Déplacement à gauche
#define RIGHT 0b10000000 // Déplacement à droite

#define STOP 31

#define ROUGE "\x1b[31m"
#define VERT "\x1b[32m"
#define BLEU "\x1b[34m"
#define RESET "\x1b[0m"

int Head = 0;
uint8_t Tape[32] = {2, 0, 0, 0, 1, 1, 1, 2};

int State = 0;

uint8_t Prog[] =
        {
                // Exemple de programme
                ZERO | RIGHT | STOP, ONE | RIGHT | STOP, BLANK | RIGHT | 1, // Si état 0
                ZERO | RIGHT | 1, ONE | RIGHT | 1, BLANK | LEFT | 2,        // Si état 1
                ONE | LEFT | 3, ZERO | LEFT | 2, BLANK | LEFT | STOP,       // Si état 2
                ZERO | LEFT | 3, ONE | LEFT | 3, BLANK | LEFT | STOP        // Si état 3
        };

/*
    Lecture
*/

int read(int i)
{

    return Tape[i];
}

/*
    Affichage
*/
void print()
{
    for (int i = 0; i < 32; i++)
    {
        if (read(i) == 0)
        {
            printf(" 0 ");
        }
        else if (read(i) == 1)
        {
            printf(BLEU " 1 " RESET);
        }
        else if (read(i) == 2)
        {
            printf(ROUGE " # " RESET);
        }
    }
    printf("   [%d]\n", State);
    for (int i = 0; i < 32; i++)
    {
        if (Head == i)
        {
            printf(VERT " T " RESET);
        }
        else
        {
            printf("   ");
        }
    }
    printf("\n");
}

/*
    Ecriture sur la bande
*/

void write(int i, int val)
{
    Tape[i] = val;
}

/*
    Recherche de la prochaine action
*/

uint8_t nextAction()
{
    int indice = (3 * State) + Tape[Head];
    return Prog[indice];
}

void operate(uint8_t action)
{
    /*
        Ecriture sur la bande - Working
    */

    uint8_t ecriture = action & 0b01100000;
    if (ecriture == BLANK)
    {
        write(Head, 2);
    }
    else if (ecriture == ZERO)
    {
        write(Head, 0);
    }
    else if (ecriture == ONE)
    {
        write(Head, 1);
    }

    /*
        Modification de l'état - Working
    */

    State = action & 0b00011111;

    printf("%d + %d + %d\n", action, State, ecriture);

    /*
        Déplacement de la tête de bande - Working
    */

    uint8_t direction = action & 0b10000000;

    if (direction == RIGHT && Head < 31)
    {
        Head++;
    }
    else if (direction == LEFT && Head > 0)
    {
        Head--;
    }
}

void run()
{
    print();
    while (State != STOP)
    {
        uint8_t action = nextAction();
        operate(action);
        print();
        getchar(); // Il faut presser la touche entrée pour continuer
    }
    printf("Exécution terminée\n");
}

