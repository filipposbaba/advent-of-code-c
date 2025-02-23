#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ----------------------------------------
// int getDigitLength(int num) {
//     if (num == 0) return 1;
//     return (floor(log10((double) num)) + 1);
// }

int checkSubstringMatch(char* substring, char* target) {
    int i = 0;
    if (strlen(substring) < strlen(target)) return strlen(substring);

    while (i < strlen(target)) {
        if (*(substring + i) == target[i]) i++;
        else if (*(substring + i) == '\0') return i - 1;
        else return i;
    }

    return i;
}

int mulParser(char *instructions) {
    int num1, num2;
    int product = 0, i = 0;

    while (instructions[i] != '\0') {
        // First, check for the fixed substring 'mul('
        int j = checkSubstringMatch(instructions + i, "mul(");
        i += j;
        if (j != 4) {
            if (j == 0) i++;
            continue;
        }

        // Then, look for and try to parse numbers

        char *endptr;
        num1 = (int) strtol(&instructions[i], &endptr, 10);
        if (endptr == &instructions[i] || *endptr != ',') {
            i += endptr - &instructions[i];
            continue;
        }

        // Skip over ','
        i++;

        num2 = (int) strtol(&instructions[i], &endptr, 10);
        if (endptr == &instructions[i]) {
            i += endptr - &instructions[i];
            continue;
        }

        if (instructions[i] == ')') product += num1 * num2;
        
        i++;
        
        // if (sscanf(&instructions[i], "mul(%d,%d)%n", &num1, &num2, &length) == 2) {
        //     if (length == 6 + getDigitLength(num1) + getDigitLength(num2)) {
        //         product += num1 * num2;
        //         i += length - 1;
        //     }
        // }
        // i++;
    }


    return product;
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

    int product = 0;
    char instructionLine[8000];

    fgets(instructionLine, sizeof(instructionLine), inputFile);
    while (!feof(inputFile)) {
        product += mulParser(instructionLine);
        fgets(instructionLine, sizeof(instructionLine), inputFile);
    }

    printf("The product of all the instructions is %d\n", product);
    return 0;

}
