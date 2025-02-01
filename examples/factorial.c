#include <stdio.h>

unsigned long long factorial(unsigned int n) {
    unsigned long long result = 1;
    for (unsigned int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main(void) {
    unsigned int number;
    
    printf("Enter a non-negative integer: ");
    if (scanf("%u", &number) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    
    printf("Factorial of %u is %llu\n", number, factorial(number));
    return 0;
}

