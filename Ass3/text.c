#include <stdio.h>

int main() {
    char str[2] = "7";  // Change this to the single-digit character you want to convert
    printf("%s\n", str);

    // Convert the character to an integer
    int num = str[0] - '0';
    printf("%d\n", num);

    return 0;
}
