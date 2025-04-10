#include "digits.h"

int sumOfDigits(int num1) {
    int sum = 0;

    while (num1 > 0) {
        sum += num1 % 10;
        num1 /= 10;
    }
    
    return sum;
}