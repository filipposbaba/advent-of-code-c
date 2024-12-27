#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// ----------------------------------------
// Initializes a list of the differences between consecutive elements, and returns the number of differences
int findDifferences(char* numLine, int* differences) {
    int num1, num2;
    int i;
    char* ptr = numLine;
    char* endptr;

    num1 = (int) strtol(ptr, &endptr, 10);
    ptr = endptr;
    num2 = (int) strtol(ptr, &endptr, 10);

    for (i = 0; ptr != endptr; i++) {
        ptr = endptr;
        differences[i] = num2 - num1;
        
        num1 = num2;
        num2 = (int) strtol(ptr, &endptr, 10);
    }

    return i;
}

// Determines whether a sequence should be increasing (returns false) or decreasing (returns true)
bool determineSign(int* differences) {
    int product = differences[0] * differences[1];
    if (product == 0) {
        if (differences[0] == 0) return (differences[1] < 0); else return (differences[0] < 0);
    }
    else if (product > 0) return (differences[0] < 0);
    else return (differences[2] < 0);
    
}

// Calculates whether a level is safe or not
bool calculateSafety(int* differences, int numDifferences, bool tolerance) {
    bool neg;
    int i = 0;
    int diff; // Holds the current difference so that its sign may be safely flipped if necessary


    neg = determineSign(differences);
    printf("neg = %d\n", neg);

    diff = differences[0];
    if (neg) diff = -diff;
    if (diff >= 1 && diff <= 3) i = 1; // If valid, start loop from differences[1]
    else {
        if (tolerance) tolerance = false; else return false;
        diff = differences[1];
        if (neg) diff = -diff;

        if (diff >= 1 && diff <= 3) i = 2; // If this passes, we can skip/tolerate the first level
        else { // Otherwise, check if we can skip/tolerate the *second* level by adding the first two differences
            diff = differences[0] + differences[1];
            if (neg) diff = -diff;

            if (diff >= 1 && diff <= 3) i = 2;
            else return false;
        }
    }

    // // if the first difference is valid
    // if (abs(differences[0]) >= 1 && abs(differences[0]) <= 3 && (differences[0] * differences[1] > 0)) neg = differences[0] < 0;
    // // if the first difference is invalid, but the second one is valid (i.e. first value should be omitted)
    // else if ((abs(differences[1]) >= 1 && abs(differences[1]) <= 3) || (abs(differences[0] + differences[1]) >= 1 && abs(differences[0] + differences[1]) <= 3)) {
    //     if (tolerance) tolerance = false; else return false;
    //     neg = (differences[2]) < 0;
    //     i = 2;
    // } 
    // // if all above are invalid, then entire level is invalid - return false
    // else return false;
    
    for ( ; i <= numDifferences - 1; i++) {
        diff = differences[i];
        if (neg) diff = -diff;
        if (diff < 1 || diff > 3) {
            if (tolerance) tolerance = false; else return false;
            // First check using the previous difference
            diff = differences[i] + differences[i - 1];
            if (neg) diff = -diff;
            if (diff < 1 || diff > 3) {
                // then, check using the next one, if it exists
                if (i < numDifferences - 1) {
                    diff = differences[i] + differences[i + 1];
                    if (neg) diff = -diff;
                    if (diff < 1 || diff > 3) return false; else i++;
                }
            }
        }
    }

    return true;
}
// ----------------------------------------


// ----------------------------------------
int main(int n, char *args[n]) {
    if (n != 2) {
        printf("Please pass in a single file as an argument!\n");
        return -1;
    }

    FILE *inputFile = fopen((char*) args[1], "r");
    if (inputFile == NULL) {
        printf("Error: File invalid, or not found!\n");
        return -1;
    } 

    char numLine[30]; // 30 chars = 10 2-digit numbers + 9 spaces + 1 null terminator
    int safe = 0;
    int tolerantSafe = 0;

    fgets(numLine, sizeof(numLine), inputFile);
    while (!feof(inputFile)) {
        int differences[9]; // For (assuming) 10 elements, there are 9 differences
        int numDifferences = 0;

        numDifferences = findDifferences(numLine, differences); // Also initializes differences

        if (calculateSafety(differences, numDifferences, false)) {
            safe++;
            tolerantSafe++;
        } else if (calculateSafety(differences, numDifferences, true)) {
            tolerantSafe++;
        } 
        fgets(numLine, sizeof(numLine), inputFile);
    }

    printf("The total number of safe lines is: %d\n", safe);
    printf("The total number of safe lines with the Problem Dampener is: %d\n", tolerantSafe);

    fclose(inputFile);
    return 0;
}
