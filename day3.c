#include <stdio.h>
#include <string.h>
#include <math.h>

// ----------------------------------------
int getDigitLength(int num) {
    if (num == 0) return 1;
    return (floor(log10((double) num)) + 1);
}

int mulParser(char *instructions) {
    int num1, num2, length;
    int product = 0, i = 0;

    while (instructions[i] != '\0') {
        if (sscanf(&instructions[i], "mul(%d,%d)%n", &num1, &num2, &length) == 2) {
            if (length == 6 + getDigitLength(num1) + getDigitLength(num2)) {
                product += num1 * num2;
                i += length - 1;
            }
        }

        i++;
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
    char instructionLine[4000];

    fgets(instructionLine, sizeof(instructionLine), inputFile);
    while (!feof(inputFile)) {
        product += mulParser(instructionLine);
        fgets(instructionLine, sizeof(instructionLine), inputFile);
    }

    printf("The product of all the instructions is %d\n", product);
    return 0;
}
