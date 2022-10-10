#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int roll_die(unsigned int size);

void main_8_25(void) {
    // printf("INT %d -> %d\n", INT_MAX, INT_MIN);
    // printf("%zu\n", sizeof(int));
    // printf("%zu\n", sizeof(size_t));
    // printf("%zu\n", sizeof(short));
    // printf("%zu\n", sizeof(long));
    // printf("%zu\n", sizeof(long long));
    // printf("%zu\n", sizeof(char));

    // bool test = 2;
    // printf("%d\n", test);

    unsigned int grades[5] = {};
    char grade;
    // while ((grade = getchar()) != EOF)
    // {
    //     // my iteration
    //     if (grade >= 'A' && grade <= 'E') {
    //         ++grades[grade - 'A'];
    //     }
    //     else if (grade >= 'a' && grade <= 'e') {
    //         ++grades[grade - 'a'];
    //     } else if (grade != '\n') {
    //         puts("Enter a Letter A-E.");
    //     }
    // }
    for (size_t i = 0; i < 5; ++i)
    {
        printf("%i ", grades[i]);
    }
    puts("");
    printf("%c\n", 'a' ^ 32);

    srand(42);
    printf("%llu\n", RAND_MAX%6);
    printf("%u\n", roll_die(100));
    unsigned long long die_rolls[6] = {};
    int die_size = 6;
    for (unsigned long long i = 0; i < 1000000; i++)
    {
        ++die_rolls[roll_die(6)];
    }
    for (size_t i = 0; i < 6; i++)
    {
        printf("%llu\n", die_rolls[i]);
    }
}

unsigned int roll_die(unsigned int size) {
    return (rand() % size);
}