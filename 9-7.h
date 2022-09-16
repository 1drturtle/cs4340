#include <stdio.h>
#include <string.h>

int main_9_7(void)
{
    char chr_array[5] = {'h', 'e', 'l', 'l', 'o'};
    /*
        Strings defined with double-quotes have an ASCII EOF appended to the end
        This allows C to print strings without knowing their size.
    */
    char string1[] = "hello";
    string1[0] = 'k';
    chr_array[0] = 'k';
    puts(string1);
    // extra value is printed due to no EOF.
    puts(chr_array);
    printf("length of string1: %zu\n", sizeof(string1));
    printf("length of chr_array: %zu\n", sizeof(chr_array));
    printf("%d\n", string1[5]);
    printf("%lu\n", strlen(string1));
    return 0;
}