#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// one
unsigned int zeroes_from_coins(unsigned int n);
// two
unsigned int matching_dice(unsigned int n);
// three
bool recursive_palindrome(char *word, int length);
// four
unsigned int lowest_base(char *word);
// five
char *caesar_shift(char *word, int shift);

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
    puts("zeroes rolled from coin flip");
    printf("zeroes (n=10_000): %d\n", zeroes_from_coins(10000));
    printf("zeroes (n=0): %d\n", zeroes_from_coins(0));

    puts("2)");
    srand(42);
    puts("rolls required to roll all of the same number for nd6");
    printf("rolls required, n=1: %d\n", matching_dice(1));
    printf("rolls required, n=10: %d\n", matching_dice(10));
    // takes a while after 10
    // printf("# required, n=11: %d\n", matching_dice(11));

    puts("3)");
    puts("palindromes");
    printf("racecar -> %s\n", str_bool(recursive_palindrome("racecar", 7)));
    printf("mmmm -> %s\n", str_bool(recursive_palindrome("mmmm", 4)));
    printf("abcd -> %s\n", str_bool(recursive_palindrome("abcd", 4)));
    printf("\"\" -> %s\n", str_bool(recursive_palindrome("", 0)));

    puts("4)");
    // lowest possible base (char[] letters)
    puts("lowest possible base of a string");
    printf("1010 -> %d\n", lowest_base("1010"));
    printf("9999 -> %d\n", lowest_base("9999"));
    printf("Z500 -> %d\n", lowest_base("Z500"));

    puts("5)");
    // Caesar shift (char[] letters, int shift)
    // ideally these are assigned and then free'd but this is just a proof of concept.
    puts("Caesar shift");
    printf("aaaa, n=1: %s\n", caesar_shift("aaaa", 1));
    printf("aaaa, n=2: %s\n", caesar_shift("aaaa", 2));
    printf("aaaa, n=25: %s\n", caesar_shift("aaaa", 25));
    printf("aaaa, n=0: %s\n", caesar_shift("aaaa", 0));
    printf("xyz, n=1: %s", caesar_shift("xyz", 1));
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

// two
unsigned int roll_random(unsigned int sides)
{
    unsigned int roll;
    unsigned int diff = RAND_MAX % sides;
    do
    {
        roll = rand();
    } while (roll >= RAND_MAX - diff);

    return roll % sides + 1;
}
unsigned int matching_dice(unsigned int n)
{
    bool matching = false;
    int roll = -1;
    int cur;
    unsigned int match_count = 0;
    unsigned int total_rolls = 0;
    // roll n die
    while (match_count != n)
    {
        match_count = 0;
        roll = roll_random(6);
        do
        {
            match_count++;
            total_rolls++;
            cur = roll_random(6);
        } while (cur == roll);
    }
    return total_rolls;
}

// three
bool recursive_palindrome(char *word, int length)
{
    if (length <= 1)
        return true;

    char last = word[length - 1];

    if (word[0] == last)
        return recursive_palindrome(word + 1, length - 2);
    else
        return false;
}
// four
unsigned int lowest_base(char *word)
{
    // examples
    // 1010 -> 2
    // Z5   -> 36
    // 9999 -> 10

    char cur;
    unsigned int base = 0;

    for (size_t i = 0; i < strlen(word); i++)
    {
        cur = word[i];
        // if we have a letter
        if (cur >= 65 && cur <= 90 && (cur - 65) > base)
            base = cur - 64 + 10;
        // if we have a number
        else if (cur >= 48 && cur <= 57 && (cur - 48) > base)
            base = cur - 47;
    }
    return base;
}
// five
char *caesar_shift(char *word, int shift)
{
    char *new_word = (char *)malloc(strlen(word));
    int letter_i;

    for (size_t i = 0; i < strlen(word); i++)
    {
        letter_i = (((int)word[i] - 97 + shift) % 26) + 65;
        new_word[i] = (char)letter_i;
    }
    return new_word;
}