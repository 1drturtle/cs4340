#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// max length of string for question 2. See comment in main file.
#define MAX 100

void question_1(int stars);
void question_2(char strings[][MAX], size_t length);
bool question_3(int num);
double question_4(char *word);
int question_5(int (*f)(int), int n);

// helpers
char *str_bool(bool x);
// question 5, test functions
int double_n(int n);
int do_nothing(int n);

// Lab Practical #1
// Chris Agrella
// 10/20/2022
int main(int argc, char *argv[])
{
    puts("Lab Practical 1");

    puts("Question 1)");
    puts("0 stars");
    question_1(0);
    puts("3 stars");
    question_1(3);

    puts("Question 2)");
    // MUST be defined as [][MAX] to not seg fault. change line 7 if.
    // strings larger than 100 characters are needed to test
    char strings[][MAX] = {"zzz", "yyy", "bbb", "aaa"};
    puts("input: [zzz, yyy, bbb, aaa]");
    question_2(strings, 4);
    for (size_t i = 0; i < 4; i++)
    {
        printf("%s\n", strings[i]);
    }

    puts("Question 3)");
    printf("n=1; %s\n", str_bool(question_3(1)));
    printf("n=6; %s\n", str_bool(question_3(6)));
    printf("n=28; %s\n", str_bool(question_3(28)));

    puts("Question 4)");
    printf("word=0, %lf\n", question_4("0"));
    printf("word=-100.34 %lf\n", question_4("-100.34"));
    printf("word=400.1145, %lf\n", question_4("400.1145"));

    puts("Question 5)");
    printf("func=double, n=1 (0, 1): %d\n", question_5(double_n, 1));
    printf("func=double, n=2 (0, 1, 2): %d\n", question_5(double_n, 2));
    printf("func=do_nothing, n=2 (0, 1, 2): %d\n", question_5(do_nothing, 2));
}
char *str_bool(bool x)
{
    return x ? "true" : "false";
}

void question_1(int stars)
{
    // set up a helper variable to hold the starting amount
    static int starting = -999;
    if (starting == -999)
    {
        starting = stars;
    }
    // if we have the same amount backwards as we do forwards, break
    if (-stars == (starting + 1))
    {
        starting = -999;
        return;
    }
    // print forwards
    if (stars > 0)
    {
        for (size_t i = 0; i < stars; i++)
            printf("*");
        puts("");
    }
    // print backwards! (ignore i=-1 since we print it already)
    else if (stars < -1)
    {
        for (size_t i = -stars; i > 0; i--)
            printf("*");
        puts("");
    }
    // go again!
    question_1(stars - 1);
}

void question_2(char a[][MAX], size_t n)
{
    char tmp[30]; // hopefully biggest word is <30 :)
    bool sorted;
    int i, j;
    // bubble sort
    for (i = 0, sorted = false; !sorted && i < n - 1; ++i)
    {
        sorted = true;
        for (int j = 0; j < n - 1 - i; ++j)
        {
            // strcmp returns >0 if true
            if (strcmp(a[j], a[j + 1]) > 0)
            {
                strcpy(tmp, a[j + 1]);
                // copy new into old
                strcpy(a[j + 1], a[j]);
                strcpy(a[j], tmp);
                sorted = false;
            }
        }
    }
}
bool question_3(int num)
{
    int sum = 0;
    // starting at 1, until num-1
    for (int i = 1; i < num; ++i)
    {
        // if num is divisible by i
        if (num % i == 0)
        {
            // add factor to sum
            sum += i;
        }
    }
    // return if perfect number (sum == number)
    return sum == num;
}
double question_4(char *word)
{
    char cur = word[0];
    bool pos = true;
    int encountered_decimal = 0;
    double out = 0;
    int i = 0;
    // check sign
    if (cur == '-')
    {
        // negative number
        pos = false;
        // next letter
        cur = word[1];
        i++;
    }
    else if (cur == '+')
    {
        // positive number
        pos = true;
        // next letter
        cur = word[1];
        i++;
    }
    while (cur != '\0')
    {
        // keep track of where we find the decimal
        if (cur == '.')
        {
            encountered_decimal = i;
        }
        // if we've already found it
        else if (encountered_decimal != 0)
        {
            // using distance from decimal we can find the place of this current number
            double divisor = pow(10, (i - encountered_decimal));
            // ex: 0.3 -> divisior = 10
            // 3 / 10 -> 0.3
            double new = (double)(cur - '0') / (divisor);
            out = out + new;
        }
        else
        {
            // still in normal numbers
            // multiply existing by 10 and add current to one's place
            out = out * 10 + (cur - '0');
        }
        // always go to next letter
        i++;
        cur = word[i];
    }
    // if we are negative, switch sign
    if (!pos)
        out *= -1;
    return out;
}

// question 5, test function
int double_n(int n)
{
    return n * 2;
}
int do_nothing(int n)
{
    return n;
}

int question_5(int (*f)(int), int n)
{
    int total = 0;
    // From k=0 to N
    for (int k = 0; k <= n; k++)
    {
        // add the value of the function at k
        total += (*f)(k);
    }
    return total;
}