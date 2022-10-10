#include <stdio.h>

// funcion prototype
double grade_average(void);

int main_8_22(void) {
  // int x = 1;

  // printf("%d\n", ++x);
  // printf("%d\n", x++);
  // printf("%d\n", x);

  // printf("%c\n", 'A' + 'B');
  // printf("%d\n", 'A' + 'B');

  // puts("Enter an Integer: ");
  // // scanf("%d", &x);
  // printf("You entered %d\n", x);

  // char c = 65; // or c = 'A'
  // printf("%c\n", c);
  // double grade = grade_average();
  // printf("Average: %f\n", grade);
  int x = 0b11010;
  printf("%d\n", x);
  // right-shift binary by 3 spaces
  // 0b11010 & 0b00001 - no match
  // 0b11010 & 0b00010 - 2
  // ~0b0 = -1, flips sign & all bits
  // ~0b0 unsigned = 4294967295
  x = x >> 4;
  // up shift places zeroes
  // 0b11010 -> 0b1
  // 0b1 -> 0b10000
  x = x << 4;
  printf("%d\n", x);
  x = -26;
  // 1b11010
  // 1b11010000
  x <<= 3;
  printf("%d\n", x);
  printf("%10.10f\n", 42.55);

  unsigned int y = -1;
  printf("%u\n", y);

  return 0;
}

double grade_average(void) {
  int total = 0, count = 0, grade;
  puts("Enter Grades: ");
  scanf("%d\n", &grade);
  do {
    total += grade;
    ++count;
    scanf("%d\n", &grade);
  } while (grade != EOF);
  return (double)total / count;
}