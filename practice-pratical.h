#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

unsigned int zeroes_from_coins(unsigned int n);
bool recursive_palindrome(char *word, int length);

// helpers
char *str_bool(bool x)
{
    if (x)
        return "true";
    return "false";
}

int main_practice(int argc, char *argv[])
{
    puts("1)");
    srand(42);
    printf("zeroes (n=10_000): %d\n", zeroes_from_coins(10000));
    printf("zeroes (n=0): %d\n", zeroes_from_coins(0));

    puts("2)");
    srand(42);
    // what does "rolls required until they all match" mean?

    puts("3)");
    printf("racecar -> %s\n", str_bool(recursive_palindrome("racecar", 7)));
    printf("mmmm -> %s\n", str_bool(recursive_palindrome("mmmm", 4)));
    printf("abcd -> %s\n", str_bool(recursive_palindrome("abcd", 4)));

    puts("4)");
    // lowest possible base (char[] letters)

    puts("5)");
    // Caesar shift (char[] letters, int shift)
}

unsigned int zeroes_from_coins(unsigned int n)
{
    unsigned int ones = 0;
    for (unsigned int i = 0; i < n; i++)
    {
        ones += rand() % 2;
    }
    return n - ones;
}

bool recursive_palindrome(char *word, int length)
{
    if (length == 1)
        return true;

    char last = word[length - 1];

    if (word[0] == last)
        return recursive_palindrome(word + 1, length - 2);
    else
        return false;
}