/* StudentScoresB.c
   Practical 6, Part 1 (b)
   Using constants for array size
   Aakriti Thakuri */

#include <stdio.h>

#define NUM_STUDENTS 5    // This statement defines a constant

int main() {
    int scores[NUM_STUDENTS];
    int sum = 0;
    double average;
    
    // Read in scores
    printf("Enter %d student scores:\n", NUM_STUDENTS);
    for (int i = 0; i < NUM_STUDENTS; i++) {
        printf("Score %d: ", i + 1);
        scanf("%d", &scores[i]);
    }
    
    // Calculate sum
    for (int i = 0; i < NUM_STUDENTS; i++) {
        sum += scores[i];
    }
    
    // Calculate average
    average = (double)sum / NUM_STUDENTS;
    
    // Display individual scores
    printf("\nIndividual Scores:\n");
    for (int i = 0; i < NUM_STUDENTS; i++) {
        printf("Student %d: %d\n", i + 1, scores[i]);
    }
    
    // Display results
    printf("\nSum: %d\n", sum);
    printf("Average: %.2lf\n", average);
    
    return 0;
}
