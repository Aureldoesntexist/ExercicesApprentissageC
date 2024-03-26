
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fonction pour afficher une valeur sous forme binaire jusqu'à k bits
void printBin(uint8_t valeur, int k)
{
    uint8_t masque =
            1 << (k - 1); // On initialise un masque avec le bit le plus à gauche à 1
    while (masque > 0)
    {   // Tant que le masque n'est pas nul
        if (masque & valeur) // Si le bit actuel est un 1
            printf("1");
        else
            printf("0"); // Sinon, c'est un 0
        masque = masque >>
                        1; // On décale le masque vers la droite pour passer au bit suivant
    }
    printf("\n");
}

uint8_t f_4_0_3(uint8_t m)
{
    // Extraction des bits au position souhaitée
    uint8_t bit_pos0 = (m >> 0) & 1;
    uint8_t bit_pos3 = (m >> 3) & 1;
    // Calcul du nouveau bit avec un XOR
    uint8_t new_bit = bit_pos0 ^ bit_pos3;
    // Décalage vers la droite
    m = m >> 1;
    // Creation de nouveau mot avec le nouveau bit en position 3
    uint8_t newMot = m | (new_bit << 3);
    // Affichage
    printBin(newMot, 8);
    // Renvoi
    return newMot;
}

uint32_t gen2(uint32_t m, int k, int pos1, int pos2)
{

    uint32_t bit_pos1 = (m >> pos1) & 1;
    uint32_t bit_pos2 = (m >> pos2) & 1;
    uint32_t new_bit = bit_pos1 ^ bit_pos2;
    m = m >> 1;
    uint32_t newMot = m | (new_bit << pos2);
    printBin(newMot, k);
    return newMot;
}

int main()
{
    uint32_t mot = 0b001101;
    for (int i = 0; i < 10; i++)
    {
        mot = gen2(mot, 6, 0, 5);
    }
    return 0;
}
