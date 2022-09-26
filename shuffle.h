#include <stdio.h>
#include <stdlib.h>

const int FACE_COUNT = 13;
const int SUIT_COUNT = 4;

typedef struct card
{
    char *face;
    char *suit;
    int value;
} Card;

void fillDeck(Card deck[], char *faces[], char *suits[]);
void shuffle(Card deck[]);
void deal(Card deck[]);
int randRange(int lower, int upper);

int shuffle_main(int argc, char *argv[])
{
    char *FACES[] = {"Deuce", "Crab", "Sharp Top", "Nickel", "Sax", "Fishhook", "Snowman", "Niner", "Dime", "Boy", "Stenographer", "Cowboy", "Seed"};
    char *SUITS[] = {"Diamonds", "Clubs", "Hearts", "Spades"};

    srand(42);

    Card cards[52];

    // fill the deck with cards in order
    fillDeck(cards, FACES, SUITS);

    // deal (print) the cards
    deal(cards);

    // shuffle the cards ONCE using fisher-yates
    shuffle(cards);

    deal(cards);

    // shuffle (3/2 * log_2(# of cards)) of times (9 for 52)

    // generate two indexes and swap those positions X amount of times (excludes possibility of something staying in place)
    // fisher-yates shuffling
    // for each element, pick a random index equal to or greater than current, and then swap.
}
void fillDeck(Card deck[52], char *faces[], char *suits[])
{
    for (size_t i = 0; i < FACE_COUNT * SUIT_COUNT; i++)
    {
        deck[i].face = faces[i % FACE_COUNT];
        deck[i].suit = suits[i / FACE_COUNT];
        deck[i].value = i;
    }
}
void deal(Card deck[])
{
    for (size_t i = 0; i < FACE_COUNT * SUIT_COUNT; i++)
    {
        printf("%s of %s (%d)\n", deck[i].face, deck[i].suit, deck[i].value);
    }
}

int randRange(int lower, int upper)
{
    // minimum is 0 + lower.
    // max is upper

    // ex: lower 3, upper 6
    // rand % 4 + 3
    // 0-3 + 3

    int mod = (upper - lower + 1);

    return (rand() % mod) + lower;
}

void shuffle(Card deck[])
{
    int random;
    for (int i = 0; i < 52; i++)
    {
        // we never want index 52
        // and all indexes must be >= i
        random = randRange(i, 52 - 1);

        Card tmp = deck[random];
        deck[random] = deck[i];
        deck[i] = tmp;
    }
}