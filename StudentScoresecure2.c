#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define NUM_STUDENTS 5
#define MAX_STUDENTS 100
#define MIN_SCORE 0
#define MAX_SCORE 100
#define MAX_ATTEMPTS 3

// Function declarations
bool validateScore(int score);
bool validateArrayParams(int scores[], int size);
bool readScores(int scores[], int size);
bool readSingleScore(int *score);
int calculateSum(int scores[], int size);
double calculateAverage(int scores[], int size);
int findMaximum(int scores[], int size);
int findMinimum(int scores[], int size);
void displayScores(int scores[], int size);
void displayStatistics(int scores[], int size);

int main() {
    int scores[NUM_STUDENTS];

    if (NUM_STUDENTS <= 0 || NUM_STUDENTS > MAX_STUDENTS) {
        printf("Error: Invalid number of students.\n");
        return 1;
    }

    if (!readScores(scores, NUM_STUDENTS)) {
        printf("Error: Failed to read scores. Program terminated.\n");
        return 1;
    }

    displayScores(scores, NUM_STUDENTS);
    displayStatistics(scores, NUM_STUDENTS);

    return 0;
}

// Validate score is within acceptable range
bool validateScore(int score) {
    return (score >= MIN_SCORE && score <= MAX_SCORE);
}

// Validate array parameters
bool validateArrayParams(int scores[], int size) {
    if (scores == NULL) {
        printf("Error: NULL array pointer.\n");
        return false;
    }
    if (size <= 0 || size > MAX_STUDENTS) {
        printf("Error: Invalid array size.\n");
        return false;
    }
    return true;
}

// Read a single score with validation
bool readSingleScore(int *score) {
    if (score == NULL) {
        return false;
    }

    if (scanf("%d", score) != 1) {
        // clear input buffer on failure
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return false;
    }

    if (!validateScore(*score)) {
        return false;
    }

    return true;
}

// Read all scores with retry logic
bool readScores(int scores[], int size) {
    if (!validateArrayParams(scores, size)) {
        return false;
    }

    printf("Enter %d student scores (%d-%d):\n", size, MIN_SCORE, MAX_SCORE);

    for (int i = 0; i < size; i++) {
        int attempts = 0;
        bool validInput = false;

        while (attempts < MAX_ATTEMPTS && !validInput) {
            printf("Score %d: ", i + 1);

            if (!readSingleScore(&scores[i])) {
                attempts++;
                printf("Invalid input. ");

                if (attempts < MAX_ATTEMPTS) {
                    printf("Score must be between %d and %d. ",
                           MIN_SCORE, MAX_SCORE);
                    printf("Attempts remaining: %d\n",
                           MAX_ATTEMPTS - attempts);
                }
            } else {
                validInput = true;
            }
        }

        if (!validInput) {
            printf("Maximum attempts exceeded for score %d.\n", i + 1);
            return false;
        }
    }

    return true;
}

// Calculate sum with overflow checking
int calculateSum(int scores[], int size) {
    if (!validateArrayParams(scores, size)) {
        return -1;
    }

    int sum = 0;
    for (int i = 0; i < size; i++) {
        // check for overflow before adding
        if (sum > INT_MAX - scores[i]) {
            printf("Error: Sum overflow detected.\n");
            return -1;
        }
        sum += scores[i];
    }

    return sum;
}

// Calculate average
double calculateAverage(int scores[], int size) {
    if (!validateArrayParams(scores, size)) {
        return -1.0;
    }

    int sum = calculateSum(scores, size);
    if (sum < 0) {
        return -1.0;
    }

    return (double)sum / size;
}

// Find maximum score
int findMaximum(int scores[], int size) {
    if (!validateArrayParams(scores, size)) {
        return -1;
    }

    int max = scores[0];
    for (int i = 1; i < size; i++) {
        if (scores[i] > max) {
            max = scores[i];
        }
    }

    return max;
}

// Find minimum score
int findMinimum(int scores[], int size) {
    if (!validateArrayParams(scores, size)) {
        return -1;
    }

    int min = scores[0];
    for (int i = 1; i < size; i++) {
        if (scores[i] < min) {
            min = scores[i];
        }
    }

    return min;
}

// Display all scores
void displayScores(int scores[], int size) {
    if (!validateArrayParams(scores, size)) {
        return;
    }

    printf("\nIndividual Scores:\n");
    for (int i = 0; i < size; i++) {
        printf("Student %d: %d\n", i + 1, scores[i]);
    }
}

// Display statistics
void displayStatistics(int scores[], int size) {
    if (!validateArrayParams(scores, size)) {
        return;
    }

    printf("\nStatistics:\n");

    int sum = calculateSum(scores, size);
    if (sum >= 0) {
        printf("Sum: %d\n", sum);
    }

    double avg = calculateAverage(scores, size);
    if (avg >= 0) {
        printf("Average: %.2lf\n", avg);
    }

    int max = findMaximum(scores, size);
    if (max >= 0) {
        printf("Highest score: %d\n", max);
    }

    int min = findMinimum(scores, size);
    if (min >= 0) {
        printf("Lowest score: %d\n", min);
    }
}