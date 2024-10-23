#include <stdio.h>
#define SIZE_STRING 200
int main() {
    // Character pointers to copy the input string
    char *p1, *p2;

    // A) Define the string variables string and string2 
    char string[SIZE_STRING], string2[SIZE_STRING];

    // B) Read string in the console 
    scanf("%[^\n]s", string);
    
    // C) Convert to uppercase
    p1 = string;
    p2 = string2;

    while (*p1 != '\0') {
        // Copy p1 to p2 subtracting 32 if necessary
        //This is one option
        // *p2 = toupper(*p1);
        //
        //But this also works;
        if('a' <= *p1 && *p1 <= 'z'){
            *p2 = *p1 - 32;
        }else {
            *p2 = *p1;
        }

        p2++; p1++;
    }
    // Remember to append the null value at the end of string2
    // 
    // This is one option:
    // int n = strlen(string2);
    // string2[n++] = '\0';
    //
    // But this also works:
    *p2 = '\0';

    // D) Out in the console string2.
    printf("%s\n", string2);

    return 0;
}
