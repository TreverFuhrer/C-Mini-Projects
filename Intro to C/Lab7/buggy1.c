#include <stdio.h>

int main() {
    int b;
    
    printf("Enter a number: ");
    scanf("%d", &b); // Bug: intentionally missing &

    printf("%d\n", b);
    return 0;
}