#include "digits.h"

int main(){
    int inputNum;

    printf("Enter a number between %d and %d: ", MIN_VALUE, MAX_VALUE);
    scanf("%d", &inputNum);

    while(inputNum < MIN_VALUE || inputNum > MAX_VALUE){
        printf("Number not in range: 111 - 999. Choose again: ");
        scanf("%d", &inputNum);
    }

    printf("Sum of digits: %d\n", sumOfDigits(inputNum));

    return 0;
}