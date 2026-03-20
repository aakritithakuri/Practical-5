/* StudentScoresA.c
   Practical 6, Part 1 (a)
   Basic array operations - calculating average score
   Aakriti Thakuri */

#include <stdio.h>

int main() {
    int scores[5];
    int sum = 0;
    double average;

    printf("Enter 5 student scores:\n");
    for (int i = 0; i < 5; i++) {
        printf("Score %d: ", i + 1);
        scanf("%d", &scores[i]);
    }

    for (int i = 0; i < 5; i++) {
        sum += scores[i];
    }

    average = (double)sum / 5;

    printf("\nResults:\n");
    printf("Sum: %d\n", sum);
    printf("Average: %.2lf\n", average);

    return 0;
}
