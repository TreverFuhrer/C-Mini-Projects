/*******************************************************************
* Description: This program tests the functionality of text encryption and decryption.
*
* How to Run:
* Run make to compile the program. 
* After compiling, run the executable with ./out
*******************************************************************/

#include "utils.h"
#include <string.h>
#include <assert.h>

void custom_assert(int condition, char *msg, char* expected, char* actual) {
    if (condition) {
        printf("Assertion succeeded: %s (Expected: %s, Actual: %s)\n\n", msg, expected, actual);
    } else {
        printf("\033[31mAssertion failed: %s (Expected: %s, Actual: %s)\033[0m\n\n", msg, expected, actual);
        assert(condition); 
    }
}

int main() {
    printf("*******************************************************************************************************\n                            TESTING ENCRYPTION\n*******************************************************************************************************\n\n");
    
    char *test1 = encrypt("good luck");
    custom_assert(strcmp(test1, "pxxm udlt") == 0, "Test 1: Encrypting 'good luck' should yield 'pxxm udlt'.", "pxxm udlt", test1);

    char *test2 = encrypt("She scored 95.");
    custom_assert(strcmp(test2, "Gvs gqcfsr 95.") == 0, "Test 2: The phrase 'He scored 95 on the test.' should encrypt to 'Gvs gqcfsr 95.'.", "Gvs gqcfsr 95.", test2);

    char *test3 = encrypt("keep #smiling");
    custom_assert(strcmp(test3, "xrrc #fzvyvat") == 0, "Test 3: The phrase 'keep smiling' should become 'xrrc #fzvyvat'.", "xrrc #fzvyvat", test3);

    char *test4 = encrypt("");
    custom_assert(test4 == NULL, "Test 4: Blank string, expects an error message", "NULL", test4);

    char *test5 = encrypt("h");
    custom_assert(test5 == NULL, "Test 5: Length is too small, expects an error message", "NULL", test5);

    char *test6 = encrypt("The sun sets behind the mountains, painting the sky with vibrant hues");
    custom_assert(test6 == NULL, "Test 6: Length is too large, expects an error message", "NULL", test6);

    char *test7 = encrypt("12345!@#$");
    custom_assert(strcmp(test7, "12345!@#$") == 0, "Test 7: The phrase '12345!@#$' should return unchanged.", "12345!@#$", test7);
    
    printf("*******************************************************************************************************\n                            TESTING DECRYPTION\n*******************************************************************************************************\n\n");
    
    char *decrypted1 = decrypt(test1);
    custom_assert(strcmp(decrypted1, "good luck") == 0, "Test 8: Decrypting 'pxxm udlt' should yield 'good luck'.", "good luck", decrypted1);

    char *decrypted2 = decrypt(test2);
    custom_assert(strcmp(decrypted2, "She scored 95.") == 0, "Test 9: Decrypting 'Gvs gqcfsr 95.' should yield 'She scored 95.'.", "She scored 95.", decrypted2);

    char *decrypted3 = decrypt(test3);
    custom_assert(strcmp(decrypted3, "keep #smiling") == 0, "Test 10: Decrypting 'xrrc #fzvyvat' should yield 'keep #smiling'.", "keep #smiling", decrypted3);
    
    char *decrypted4 = decrypt("");
    custom_assert(decrypted4 == NULL, "Test 11: Blank string, expects an error message", "NULL", decrypted4);

    char *decrypted5 = decrypt("a");
    custom_assert(decrypted5 == NULL, "Test 12: Length is too small, expects an error message", "NULL", decrypted5);

    char *decrypted6 = decrypt("This string is way toooooooooooo long.");
    custom_assert(decrypted6 == NULL, "Test 13: Length is too large, expects an error message", "NULL", decrypted6);
    
    char *decrypted7 = decrypt("#516755(>)");
    custom_assert(strcmp(decrypted7, "#516755(>)") == 0, "Test 14: The phrase '#516755(>)' should return unchanged.", "#516755(>)", decrypted7);

    free(test1);
    free(test2);
    free(test3);
    free(decrypted1);
    free(decrypted2);
    free(decrypted3);

    return 0;
}