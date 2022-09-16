#include <stdio.h>

char *SUITS[] = {"Diamonds", "Clubs", "Hearts", "Spades"};
char *FACES[] = {"Deuce", "Crab", "Sharp Top", "Nickel", "Sax", "Fishhook", "Snowman", "Niner", "Dime", "Boy", "Stenographer", "Cowboy", "Seed"};
int FACE_COUNT = 13;
int SUIT_COUNT = 4;

// print_card(deck[X])
void print_card(int card_index);
int shuffle_main(int argc, char *argv[])
{
    int deck[52] = {};
    for (int i = 0; i < FACE_COUNT * SUIT_COUNT; i++)
    {
        deck[i] = i;
    }
    print_card(1);

    // shuffle (3/2 * log_2(# of cards)) of times (9 for 52)

    // generate two indexes and swap those positions X amount of times (excludes possibility of something staying in place)
    // fisher-yates shuffling
    // for each element, pick a random index equal to or greater than current, and then swap.
}

void print_card(int card_index)
{
    printf("%s of %s\n", FACES[card_index % FACE_COUNT], SUITS[card_index / FACE_COUNT]);
}