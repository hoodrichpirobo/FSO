#include <stdio.h>          /* Include libraries */

int Number;                 // Define global variables

int main()
{   // main function
    int i;
    int Number;
    printf("Write the number to be displayed: ");
    scanf("%d", &Number);

    printf("\n The first %d natural numbers are:\n", Number);
    for(i = 0; i < Number; i++)
    {
        printf("    %d\n", i);
    }
    printf("BYE\n");
    return(0);
}
