#include <stdio.h>
#include <stdlib.h>

# define example 42 // most constant of constants

// global constants (uppercase)
int X = 42;

// enum
enum Status {CONTINUE, WON, LOST};

unsigned int roll_random(unsigned int size);

int main_8_26(void) {
    srand(42);
    unsigned long long die_rolls[6] = {};
    int die_size = 6;
    for (unsigned long long i = 0; i < 1000; i++)
    {
        ++die_rolls[roll_random(6)-1];
    }
    for (size_t i = 0; i < 6; i++)
    {
        printf("%d, %llu\n", i+1, die_rolls[i]);
    }
    // printf("%d\n", WON);
    
}

unsigned int roll_random(unsigned int sides) {
    unsigned int roll;
    unsigned int diff = RAND_MAX % sides;
    do {
        roll = rand();
    } while (roll >= RAND_MAX - diff);
    
    return roll % sides + 1;
}