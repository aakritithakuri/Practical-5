#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define NUM_STUDENTS 5
#define MAX_STUDENTS 100
#define MIN_SCORE 0
#define MAX_SCORE 100
#define MAX_ATTEMPTS 3

// Function declarations
void readScores(int scores[], int size);
int calculateSum(int scores[], int size);
double calculateAverage(int scores[], int size);
int findMaximum(int scores[], int size);
int findMinimum(int scores[], int size);
void displayScores(int scores[], int size);
void displayStatistics(int scores[], int size);
void clearInputBuffer();
bool validateScore(int score);
bool validateParameters(int scores[], int size);
bool isSafeIndex(int index, int size);

int main() {
    int scores[MAX_STUDENTS];

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

// Validates score is between MIN and MAX
bool validateScore(int score) {
    return (score >= MIN_SCORE && score <= MAX_SCORE);
}

// Validates array pointer and size
bool validateParameters(int scores[], int size) {
    if (scores == NULL) {
        printf("Error: array pointer is NULL!\n");
        return false;
    }
    if (size <= 0) {
        printf("Error: size must be greater than 0! Got: %d\n", size);
        return false;
    }
    if (size > MAX_STUDENTS) {
        printf("Error: size %d exceeds maximum allowed %d!\n",
               size, MAX_STUDENTS);
        return false;
    }
    return true;
}

// Checks index is safe before accessing array[index]
bool isSafeIndex(int index, int size) {
    if (index < 0) {
        printf("Error: index %d is negative!\n", index);
        return false;
    }
    if (index >= size) {
        printf("Error: index %d is out of bounds! Max allowed: %d\n",
               index, size - 1);
        return false;
    }
    return true;
}

// readScores with MAX_ATTEMPTS limiting retries
void readScores(int scores[], int size) {
    if (!validateParameters(scores, size)) {
        return;
    }

    printf("Enter %d student scores:\n", size);
    for (int i = 0; i < size; i++) {
        if (!isSafeIndex(i, size)) {
            continue;
        }

        int valid = 0;
        int attempts = 0;                // track number of attempts

        while (!valid && attempts < MAX_ATTEMPTS) {
            printf("Score %d (%d-%d): ", i + 1, MIN_SCORE, MAX_SCORE);
            int result = scanf("%d", &scores[i]);
            attempts++;                  // increment attempt counter

            if (result != 1) {
                printf("Error: please enter a number only! "
                       "Attempts left: %d\n", MAX_ATTEMPTS - attempts);
                clearInputBuffer();
            } else if (!validateScore(scores[i])) {
                printf("Error: score must be between %d and %d! "
                       "Attempts left: %d\n", MIN_SCORE, MAX_SCORE,
                       MAX_ATTEMPTS - attempts);
            } else {
                printf("Score accepted.\n");
                valid = 1;
            }
        }

        // if max attempts reached without valid input, default to 0
        if (!valid) {
            scores[i] = 0;
            printf("Max attempts reached! Score %d set to 0.\n", i + 1);
        }
    }
}

// calculateSum with safe index checking
int calculateSum(int scores[], int size) {
    if (!validateParameters(scores, size)) {
        return 0;
    }
    int sum = 0;
    for (int i = 0; i < size; i++) {
        if (isSafeIndex(i, size)) {
            sum += scores[i];
        }
    }
    return sum;
}

// calculateAverage with safe index checking
double calculateAverage(int scores[], int size) {
    if (!validateParameters(scores, size)) {
        return 0.0;
    }
    int sum = calculateSum(scores, size);
    return (double)sum / size;
}

// findMaximum with safe index checking
int findMaximum(int scores[], int size) {
    if (!validateParameters(scores, size)) {
        return -1;
    }
    int max = scores[0];
    for (int i = 1; i < size; i++) {
        if (isSafeIndex(i, size)) {
            if (scores[i] > max) {
                max = scores[i];
            }
        }
    }
    return max;
}

// findMinimum with safe index checking
int findMinimum(int scores[], int size) {
    if (!validateParameters(scores, size)) {
        return -1;
    }
    int min = scores[0];
    for (int i = 1; i < size; i++) {
        if (isSafeIndex(i, size)) {
            if (scores[i] < min) {
                min = scores[i];
            }
        }
    }
    return min;
}

// displayScores with safe index checking
void displayScores(int scores[], int size) {
    if (!validateParameters(scores, size)) {
        return;
    }
    printf("\nIndividual Scores:\n");
    for (int i = 0; i < size; i++) {
        if (isSafeIndex(i, size)) {
            printf("Student %d: %d\n", i + 1, scores[i]);
        }
    }
}

// displayStatistics with safe index checking
void displayStatistics(int scores[], int size) {
    if (!validateParameters(scores, size)) {
        return;
    }
    printf("\nStatistics:\n");
    printf("Sum: %d\n", calculateSum(scores, size));
    printf("Average: %.2lf\n", calculateAverage(scores, size));
    printf("Highest score: %d\n", findMaximum(scores, size));
    printf("Lowest score: %d\n", findMinimum(scores, size));
}
