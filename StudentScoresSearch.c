/* StudentScoresModular.c
   Practical 6, Part 2 (a)
   Modular array operations with functions
   Aakriti Thakuri */

#include <stdio.h>

#define NUM_STUDENTS 5

// Function declarations
void readScores(int scores[], int size);
int calculateSum(int scores[], int size);
double calculateAverage(int scores[], int size);
int findMaximum(int scores[], int size);
int findMinimum(int scores[], int size);
void displayScores(int scores[], int size);
void displayStatistics(int scores[], int size);
int linearSearch(int scores[], int size, int target);
int countAboveThreshold(int scores[], int size, int threshold);

int main() {
    int scores[NUM_STUDENTS];
    
    readScores(scores, NUM_STUDENTS);
    displayScores(scores, NUM_STUDENTS);
    displayStatistics(scores, NUM_STUDENTS);

    int searchScore;
    printf("\nEnter a score to search for: ");
    scanf("%d", &searchScore);
    
    int index = linearSearch(scores, NUM_STUDENTS, searchScore);
    if (index != -1) {
        printf("Score %d found at position %d (Student %d)\n", searchScore, index, index + 1);
    } else {
        printf("Score %d not found\n", searchScore);
    }

    printf("\nNumber of students scoring above 80: %d\n", countAboveThreshold(scores, NUM_STUDENTS, 80));
    
    return 0;
}

void readScores(int scores[], int size) {
    printf("Enter %d student scores:\n", size);
    for (int i = 0; i < size; i++) {
        printf("Score %d: ", i + 1);
        scanf("%d", &scores[i]);
    }
}

int calculateSum(int scores[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += scores[i];
    }
    return sum;
}

double calculateAverage(int scores[], int size) {
    int sum = calculateSum(scores, size);
    return (double)sum / size;
}

int findMaximum(int scores[], int size) {
    int max = scores[0];
    for (int i = 1; i < size; i++) {
        if (scores[i] > max) {
            max = scores[i];
        }
    }
    return max;
}

int findMinimum(int scores[], int size) {
    int min = scores[0];
    for (int i = 1; i < size; i++) {
        if (scores[i] < min) {
            min = scores[i];
        }
    }
    return min;
}

void displayScores(int scores[], int size) {
    printf("\nIndividual Scores:\n");
    for (int i = 0; i < size; i++) {
        printf("Student %d: %d\n", i + 1, scores[i]);
    }
}

void displayStatistics(int scores[], int size) {
    printf("\nStatistics:\n");
    printf("Sum: %d\n", calculateSum(scores, size));
    printf("Average: %.2lf\n", calculateAverage(scores, size));
    printf("Highest score: %d\n", findMaximum(scores, size));
    printf("Lowest score: %d\n", findMinimum(scores, size));
}

int linearSearch(int scores[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (scores[i] == target) {
            return i;
        }
    }
    return -1;
}

int countAboveThreshold(int scores[], int size, int threshold) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (scores[i] > threshold) {
            count++;
        }
    }
    return count;
}