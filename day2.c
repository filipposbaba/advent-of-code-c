#include <stdio.h>
#include <stdbool.h>

bool calculateSafety(char* numLine) {
    int num1, num2;
    int difference;
    bool neg = false;
    char *ptr = numLine; 
    // while (sscanf(ptr, "%d", &num1) == 1) { 
    //     printf("%d\n", num1);
    //     while (*ptr && *ptr != ' ') { ptr++; } 
    //     if (*ptr) ptr++; 
    //     }
    
    // check out strtok() as well

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
    int count = 0;

    fgets(numLine, sizeof(numLine), inputFile);
    while (!feof(inputFile)) {
        if (calculateSafety(numLine)) count++;
        fgets(numLine, sizeof(numLine), inputFile);
    }
    printf("The total number of safe lines is: %d\n", count);

    fclose(inputFile);
    return 0;
}
