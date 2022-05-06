#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define equationString "x*(2+3)=1/(x+1)+2+4+(9*659/4)"//  x+2=3

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
    double * cantBe;
    size_t cantBeSize;
    char * result;
    size_t sizeOfResult;
};

typedef struct xFlags MKTXFLAGS;

double simpleEquationParser(char * charArray, size_t sizeOfArray)
{

}

double checkForDivision(char * charArray,size_t sizeOfArray, short character) {
    double FinalInt; // comedy



    return FinalInt;
}

size_t bracketCopywriter(char ** charArray, short * currentCharacter)
{
    size_t finalInt; // comedy strikes again
    char * copy = malloc(7);

    copy[0] = 'B';
    copy[1] = 'R';
    copy[2] = 'A';
    copy[3] = 'C';
    copy[4] = 'K';
    copy[5] = 'E';
    copy[6] = 'T';
    finalInt = 7;


    charArray[0]=realloc(charArray[0],*currentCharacter+finalInt);
    for(int i = 0; i < finalInt;i++)
    {
        charArray[0][*currentCharacter] = copy[i];
        *currentCharacter = *currentCharacter + 1;
    }
    free(copy);
    return finalInt;
}

char * Copywriter(char * charArray, size_t sizeOfArray, size_t *sizeOfResult)
{
    char * copy = malloc(sizeOfArray);
    short currentCharacter = 0;
    short ABrackets = 0;
    for(int i = 0; i < sizeOfArray;i++)
    {
        if(charArray[i]=='(')
        {
            short nBrackets = 1;
            short start = 0;
            while(nBrackets != 0)
            {
                i++;
                if(charArray[i] == '(')
                {
                    nBrackets++;
                }
                else if(charArray[i] == ')')
                    nBrackets--;
            }
            bracketCopywriter(&copy,&currentCharacter);
            ABrackets++;
            // copy[currentCharacter] = 'M';
            // currentCharacter++;
            // copy[currentCharacter] = 'A';
            // currentCharacter++;
            // copy[currentCharacter] = 'K';
            // currentCharacter++;
            // copy[currentCharacter] = 'i';
            // currentCharacter++;
            // copy[currentCharacter] = 'T';
            // currentCharacter++;



            i++;
        }
        copy = realloc(copy,currentCharacter+1);
        copy[currentCharacter] = charArray[i];
        currentCharacter++;
    }
    printf("\nnumber of brackets: %d",ABrackets);
    *sizeOfResult = currentCharacter;

    return copy;
    // charArray = realloc(charArray,currentCharacter);
    // for(int i = 0; i < currentCharacter;i++)
    // {
    //     charArray[i] = copy[i];
    // }
}


MKTXFLAGS checkForX(char * charArray, size_t sizeOfArray, int *errorCode)
{
    MKTXFLAGS XFlags;
    XFlags.canBeNegative = true;
    XFlags.canBeAFraction = true;
    XFlags.cantBe = malloc(1);
    XFlags.cantBeSize = 0;
    short isDivision = false;
    
    bool detectedEqual = false;

    if(charArray[0] == subChar, charArray[0] == addChar, charArray[0] == mulChar, charArray[0] == divChar, charArray[0] == powChar, charArray[0] == sqrChar, charArray[0] == sidChar)
    {
        *errorCode = 2;
        return XFlags;
    }
    for(int i = 0; i < sizeOfArray;i++)
    {
        if(charArray[i] == '=' && !detectedEqual)
            detectedEqual = true;
        else if(charArray[i] == '=' && detectedEqual)
            *errorCode = 2;
    }
    if(!detectedEqual)
    {
        *errorCode = 2;
        return XFlags;
    }
    XFlags.result = Copywriter(charArray, sizeOfArray,&XFlags.sizeOfResult);
    
    return XFlags;
}

int main()
{
    char a[] = equationString;
    int errorCode = 0;
    MKTXFLAGS XFlags;

    XFlags = checkForX(a, sizeof(a), &errorCode);

    if(errorCode == 2)
        printf("equation is not correct\n");

    for(int i = 0; i < XFlags.sizeOfResult;i++)
    {
        printf("\n%d.%c",i,XFlags.result[i]);
    }
    printf("\n");
    for(int i = 0; i < XFlags.sizeOfResult;i++)
    {
        printf("%c",XFlags.result[i]);
    }

    printf("\nx ∈ R\n");

    return 0;
}