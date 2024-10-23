#include <stdio.h>

int main(int argc, char *argv[])
{
    for(int i = 0; i < argc; i++){
        if(argv[i][1] == 'i')
            printf("  Argument %d is %s %s\n", i, "Include", argv[++i]);
        if(argv[i][1] == 'c')
            printf("  Argument %d is %s\n", i, "Compile");
        if(argv[i][1] == 'E')
            printf("  Argument %d is %s\n", i, "Preprocess");
    }
    return 0;
}
