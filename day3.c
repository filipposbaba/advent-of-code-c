#include <stdio.h>
#include <string.h>
#include <math.h>

// ----------------------------------------
int getDigitLength(int num) {
    if (num == 0) return 1;
    return (floor(log((double) num)) + 1);
}

int mulParser(char *instructions) {
    int num1, num2, product;


    return 0;
}
// ----------------------------------------


// ----------------------------------------
int main(int n, char *args[n]) {
    // if (n != 2) {
    //     printf("Please pass in a single file as an argument!\n");
    //     return -1;
    // }

    // FILE *inputFile = fopen((char*) args[1], "r");
    // if (inputFile == NULL) {
    //     printf("Error: File invalid, or not found!\n");
    //     return -1;
    // } 

    char input[] = "fjdksafhjkladsmul(  123,  456)extra";
    int a, b;
    int chars_processed;

    // Parse input and track the number of characters processed
    for (int i = 0; input[i] != '\0'; i++) {
        if (sscanf(&input[i], "mul(%d,%d)%n", &a, &b, &chars_processed) == 2) {
            printf("a: %d, b: %d, chars_procc: %d\n", a, b, chars_processed);
            i += chars_processed;
        }
    }

    return 0;
}
