#include <stdio.h>
#include <stdlib.h>

// Craps
// Chris Agrella
// 9/1/2022

// Game Status. Only Won/Lost is returned
enum Status {CONTINUE, WON, LOST};

// functions

unsigned int roll_random(unsigned int size);
unsigned int roll_dice(unsigned int amount, unsigned int size);

enum Status craps(unsigned int* rolls);

int max(int a, int b, int c);

// Seed the random and run the game GAME_COUNT times.
int main_8_29(void) {
    srand(42);

    // games[0] = # of wins
    // games[1] = # of L's
    int games[2] = {0};

    // total number of rolls
    unsigned int rolls = 0;

    // how many times we play the game
    int GAME_COUNT = 1000;

    for (int i = 0; i < GAME_COUNT; i++)
    {
        // &rolls passed for game to increment
        // Win-1 = 0
        // Loss-1 = 1
        games[craps(&rolls) - 1]++;
    }

    // #.2llf = 2 decimal double
    printf("Chance of Winning %.2llf%%\n", ((double)games[0] / GAME_COUNT) * 100);
    printf("Average Amount of Rolls: %.2llf per game\n", (double)rolls / GAME_COUNT);

    return 0;
}

/*
Craps:
Roll 2d6
If 7 or 11, player wins
Else if 2, 3, 12, player loses
Else, record the sum as player's "Point"
Continue rolling until player rolls their "Point" and wins
OR, rolls a 7 and loses.
int* rolls = variable to increment for total roll count.
*/
enum Status craps(unsigned int* rolls) {
    enum Status game_state = CONTINUE;
    int roll;
    int point = roll_dice(2, 6);
    *rolls += 2;

    switch (point) {
        case 2:
        case 3:
        case 12:
            game_state = LOST;
            break;
        case 7:
        case 11:
            game_state = WON;
            break;
    }
    
    while (game_state == CONTINUE)
    {
        roll = roll_dice(2, 6);
        *rolls += 2;
        if (roll == 7)
            game_state = LOST;
        else if (roll == point)
            game_state = WON;
    }

    return game_state;
}

// roll (amount)d(sides)
unsigned int roll_dice(unsigned int amount, unsigned int sides) {
    unsigned int sum = 0;
    for (unsigned i = 1; i <= amount; i++)
    {
        sum += roll_random(sides);
    }
    return sum;
    
}

// roll 1d(sides)
unsigned int roll_random(unsigned int sides) {
    unsigned int roll;
    unsigned int diff = RAND_MAX % sides;
    do {
        roll = rand();
    } while (roll >= RAND_MAX - diff);
    
    return roll % sides + 1;
}

// return the max of three items
int max(int a, int b, int c) {
    // ternary = condition ? return if true : return if false
    // return a >= b && a >= c ? a : (b >= c ? b : c);
    if (b > a)
        a = b;
    if (c > a)
        a = c;
    return a;
}