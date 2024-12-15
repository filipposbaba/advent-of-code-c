#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool calculateSafety(char* numLine, bool tolerance) {
    int num1, num2;
    int difference;
    bool neg = false;       // Tracks whether the sequence is decreasing (= true) or increasing (= false)
    bool setNeg = true;     // Determines whether 'neg' needs to be initialized
    char *ptr = numLine;
    char *endptr;

    // Initialize num1 and num2 with the first two values
    num1 = (int) strtol(ptr, &endptr, 10);
    ptr = endptr;
    num2 = (int) strtol(ptr, &endptr, 10);

    // Loop until no nubmers left to parse (i.e. endptr doesn't move)
    while (ptr != endptr) {
        ptr = endptr;

        difference = num2 - num1;
        if (setNeg) {
            neg = (difference < 0);
        }
        if (neg) difference = -difference;
        if (difference < 1 || difference > 3) {
            if (!tolerance) return false;
            else {
                tolerance = false;
                num2 = num1; // Overwrite num2, effectively deleting/ignoring it
            }
        }
        // Prevent setNeg from being set to false if the second number should be
        // tolerated/deleted, so that 'neg' can be initialized on the next iteration
        if (setNeg && difference >= 1 && difference <= 3) setNeg = false;
        else if (setNeg && (difference < 1 || difference > 3)) printf("%s", numLine);
        
        num1 = num2;
        num2 = (int) strtol(ptr, &endptr, 10);
    }
       
    return true;
}

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
        if (calculateSafety(numLine, false)) {
            safe++;
            tolerantSafe++;
        } else if (calculateSafety(numLine, true)) {
            tolerantSafe++;
        }
        fgets(numLine, sizeof(numLine), inputFile);
    }

    printf("The total number of safe lines is: %d\n", safe);
    printf("The total number of safe lines with the Problem Dampener is: %d\n", tolerantSafe);

    fclose(inputFile);
    return 0;
}
