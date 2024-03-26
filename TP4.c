#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isDec(const char *str)
{
    int etat = 0;
    int curseur = 0;
    char c = str[curseur];

    while (1)
    {
        if (c == 0)
        {
            return ((etat == 1) || (etat == 2));
        }
        else if (etat == 0)
        {
            if (c == '0')
                etat = 2;
            else if ((c >= '1') && (c <= '9'))
                etat = 1;
            else
                return 0;
        }
        else if (etat == 1)
        {
            if ((c >= '0') && (c <= '9'))
                etat = 1;
            else
                return 0;
        }
        else if (etat == 2)
        {
            if (curseur < strlen(str))
                return 1;
            else
                return 0;
        }
        else
        {
            printf("ERREUR : état inconnu %d\n", etat);
            exit(1);
        }
        curseur++;
        c = str[curseur];
    }
}

void test_isDec()
{
    char *data[] = {"0", "00", "075", "71", "45A2", "120x", "9900"};
    int expect[] = {1, 0, 0, 1, 0, 0, 1};
    int nbData = 7;
    int compteurValidation = 0;
    int compteurErreur = 0;

    for (int i = 0; i < nbData; ++i)
    {
        printf("Résultat : %d\t Donnée : %s\t Donnée attendue : %d\n", isDec(data[i]), data[i], expect[i]);
        if (isDec(data[i]) != expect[i]) // Received != waited
        {
            printf("Erreur : %s acceptée a tort\n", data[i]); // Print Error
            compteurErreur++;                                 // Incrementation error counter
        }
        else
        {
            compteurValidation++; // Incrementation validation
        }
    }
    if (compteurErreur > 0) // Print Error
    {
        printf("%d erreurs et %d correctes\n", compteurErreur, compteurValidation);
    }
    else // Print no error
    {
        printf("Test OK\n");
    }
}

int isBinHex(const char *str)
{
    int etat = 0;
    int curseur = 0;
    char c = str[curseur];
    while (1)
    {
        if (c == 0)
        {
            return ((etat == 3) || (etat == 5)); // return true if 3 or 5
        }
        else if (etat == 0)
        {
            if (c == '0')
                etat = 1;
            else
                return 0;
        }
        else if (etat == 1)
        {
            if (c == 'x')
                etat = 2;
            else if (c == 'b')
                etat = 4;
            else
                return 0;
        }
        else if (etat == 2 || etat == 3) // Hexadecimal pattern
        {
            if (isxdigit(c))
                etat = 3;
            else
                return 0;
        }
        else if (etat == 4 || etat == 5) // Binary pattern
        {
            if (c == '0' || c == '1')
                etat = 5;
            else
                return 0;
        }
        else
        {
            printf("ERREUR : état inconnu %d\n", etat);
            exit(1);
        }
        curseur++;
        c = str[curseur];
    }
}

void test_isBinHex()
{
    char *data[] = {"0", "17", "0z75", "0b1110001", "0b1", "0b11111", "0b000", "0b002011", "0b10011tt", "0x123",
                    "0xABD", "0xAB47", "0x04AA", "0x11G1", "0xH110", "1x67AB"};
    int expect[] = {0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0};
    int nbData = 16;
    int compteurValidation = 0;
    for (int i = 0; i < nbData; ++i)
    {
        if (isBinHex(data[i]) == expect[i])
        {
            printf("Résultat : %d\t Donnée : %s\t Donnée attendue : %d\n", isBinHex(data[i]), data[i], expect[i]);
            compteurValidation++; // Incrémentation
        }
    }
    if (compteurValidation == nbData)
    {
        printf("Test Ok");
    }
}

int main()
{
    test_isDec();
    printf("--------------------------------------------------------------------------------------------------\n");
    test_isBinHex();
    return 0;
}
