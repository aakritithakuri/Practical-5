#include <stdio.h>
#include <stdbool.h>     // needed for bool, true, false

#define NUM_STUDENTS 5
#define MIN_SCORE 0
#define MAX_SCORE 100

// Function declarations
void readScores(int scores[], int size);
int calculateSum(int scores[], int size);
double calculateAverage(int scores[], int size);
int findMaximum(int scores[], int size);
int findMinimum(int scores[], int size);
void displayScores(int scores[], int size);
void displayStatistics(int scores[], int size);
void clearInputBuffer();
bool validateScore(int score);   // new function declaration

int main() {
    int scores[NUM_STUDENTS];

    readScores(scores, NUM_STUDENTS);
    displayScores(scores, NUM_STUDENTS);
    displayStatistics(scores, NUM_STUDENTS);

    return 0;
}

// Clears leftover bad input from buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// NEW: validates score is between MIN_SCORE and MAX_SCORE
bool validateScore(int score) {
    if (score >= MIN_SCORE && score <= MAX_SCORE) {
        return true;   // valid score
    } else {
        return false;  // invalid score
    }
}

// readScores using validateScore function
void readScores(int scores[], int size) {
    printf("Enter %d student scores:\n", size);
    for (int i = 0; i < size; i++) {
        int valid = 0;
        while (!valid) {
            printf("Score %d (%d-%d): ", i + 1, MIN_SCORE, MAX_SCORE);

            int result = scanf("%d", &scores[i]);

            if (result != 1) {
                // User typed letters or symbols
                printf("Error: please enter a number only!\n");
                clearInputBuffer();
            } else if (!validateScore(scores[i])) {
                // validateScore returned false
                printf("Error: score must be between %d and %d!\n",
                       MIN_SCORE, MAX_SCORE);
            } else {
                // validateScore returned true
                printf("Score accepted.\n");
                valid = 1;
            }
        }
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
