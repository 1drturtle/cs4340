#include <stdio.h>

char *SUITS[] = {"Diamonds", "Clubs", "Hearts", "Spades"};
char *FACES[] = {"Deuce", "Crab", "Sharp Top", "Nickel", "Sax", "Fishhook", "Snowman", "Niner", "Dime", "Boy", "Stenographer", "Cowboy", "Seed"};
int FACE_COUNT = 13;
int SUIT_COUNT = 4;

// print_card(deck[X])
void print_card(int card_index);

// make it a Type
typedef struct test
{
    int x;
    char y;
} Test;
typedef struct test2
{
    long long x;
    int z;
} Test2;
// Real Name ^^
// type def after shown below

// typedef struct test Test;

int main_9_15(int argc, char *argv[])
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

    // custom data structures
    struct test var = {42, 'k'};
    Test var2;
    var2.x = var.x;
    Test *varPtr = &var;
    printf("%d %c\n", var.x, var.y);
    // -> to access variable of a pointer of a struct
    printf("%d %c\n", var2.x, varPtr->y);
    // all structs are typedef'd
    printf("%zu\n", sizeof(var));
    Test2 var3 = {4, 3};
    // longest element is 8 bytes, so Every element has 8 bytes allocated
    // size of 16 bytes vs 12.
    printf("%zu\n", sizeof(var3));

    return 0;
}

void print_card(int card_index)
{
    printf("%s of %s\n", FACES[card_index % FACE_COUNT], SUITS[card_index / FACE_COUNT]);
}