#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define equation "x*2=1/x"

#define subChar '-'
#define addChar '+'
#define mulChar '*'
#define divChar '/'
#define powChar '^'
#define sqrChar '|'
#define sidChar ','

struct xFlags {
    bool canBeNegative;
    bool canBeAFraction;
    int * cantBe;
};

typedef struct xFlags MKTXFLAGS;

int main()
{
    char a[] = equation;
    int errorCode = 0;
    MKTXFLAGS XFlags;

    XFlags = checkForX(a, sizeof(a), &errorCode);

    printf("x ∈ R");

    return 0;
}

MKTXFLAGS checkForX(char * charArray, size_t sizeOfArray, int *errorCode)
{
    MKTXFLAGS XFlags;
    XFlags.canBeNegative = true;
    XFlags.canBeAFraction = true;
    
    bool detectedEqual = false;

    for(int i = 0; i < sizeOfArray;i++)
    {
        if(charArray[i] == '=' && !detectedEqual)
            detectedEqual = true;
        else if(charArray[i] == '=' && detectedEqual)
            *errorCode = 2;
    }
    if(!detectedEqual)
        *errorCode = 2;
}