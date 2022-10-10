#include <stdio.h>

unsigned int factorial_recursive(unsigned int n);
unsigned int factorial_iterative(unsigned int n);
unsigned int fibonacci_recursive(unsigned int n);
unsigned int fibonacci_iterative(unsigned int n);

unsigned int main_8_31(void) {
    printf("%u\n", factorial_recursive(5));
    printf("%u\n", factorial_iterative(5));
    for (unsigned int i = 0; i < 10; i++)
    {
        printf("%u\n", fibonacci_iterative(i));
    }
    
    return 0;
}

unsigned int factorial_recursive(unsigned int n) {
    if (n < 2)
        return 1;
    return n * factorial_recursive(n - 1);
}

unsigned int factorial_iterative(unsigned int n) {
    unsigned int i;
    for (i = 1; n > i; i *= n--);
    return i;
}

unsigned int fibonacci_recursive(unsigned int n) {
    // doesn't reset after first thing
    static unsigned int count = 0;
    ++count;
    if (n == 0)
        printf("%u\n", count);
    if (n < 2)
        return n;
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}
unsigned int fibonacci_iterative(unsigned int n) {
    unsigned int a, b, tmp;
    for (unsigned int i = 0; i < n; i++)
    {
        tmp = a;
        a = b;
        b = tmp + b;
    }

    return a;
    
}