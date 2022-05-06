#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#ifdef _MKTDEBUGBOOL
#define MKTDEBUGBOOL true
#else
#define MKTDEBUGBOOL false
#endif

#define MKTDOUBLE double

#define equationString "1-x-2+1=x-1-2-x-x+1"//   x*(2+3)=1/(x+1)+2+4+(9*659/4)

#define subChar '-'
#define addChar '+'
#define mulChar '*'
#define divChar '/'
#define powChar '^'
#define sqrChar '|'
#define sidChar ','

struct xFlags {
    MKTDOUBLE * cantBe;
    size_t cantBeSize;
    char * result;
    size_t sizeOfResult;
};

typedef struct xFlags MKTXFLAGS;

size_t checkForNumberSize(MKTDOUBLE number);
size_t characterPlacer(char * charArray, size_t sizeOfArray,short place, MKTDOUBLE number, bool isX, bool isNegative);
MKTDOUBLE numberChecker(char * charArray,short startingCharacter, bool * isX, size_t sizeOfArray);
size_t finalPlacer(char * charArray, size_t sizeOfArray);
size_t characterChangerAddSub(char * charArray, size_t sizeOfArray);
size_t simpleEquationParser(char * charArray, size_t sizeOfArray);
MKTDOUBLE checkForDivision(char * charArray,size_t sizeOfArray);
size_t bracketCopywriter(char ** charArray, short * currentCharacter, short start, short end);
size_t bracketCopywriterBuffer(char * copy,char * charArray, size_t sizeOfArray);
char * Copywriter(char * charArray, size_t sizeOfArray, size_t *sizeOfResult);
MKTXFLAGS checkForX(char * charArray, size_t sizeOfArray, int *errorCode);

size_t checkForNumberSize(MKTDOUBLE number)
{
    size_t finalSize;
    MKTDOUBLE fractpart, intpart;

    fractpart = modf(number,&intpart);

    int powersOfTen=1;

    finalSize = 1;
    printf("\nfinalsize1: %d, %f",finalSize,number);

    for(int i = 1; powersOfTen < intpart;i++,powersOfTen *= 10)
    {
        finalSize = i;
    }
    printf("\nfinalsize2: %d, %f",finalSize,number);


    if(fractpart != 0)
    {
        finalSize++;
    printf("\nfinalsize3: %d, %f",finalSize,number);
        powersOfTen=0;
        
    printf("\nfinalsize4: %d, %f",finalSize,number);
    while(fractpart-floor(fractpart+0.1)>0)
    {
        printf("\nfractpart %d, %f, %f, %f",powersOfTen,fractpart,floor(fractpart+0.1),fractpart-floor(fractpart+0.1));
        if(fractpart == floor(fractpart+0.1))
            break;
        fractpart *= 10;
        powersOfTen++;
    }
    printf("\nfinalsize5: %d, %f",finalSize,number);

        finalSize += powersOfTen;
    printf("\nfinalsize6: %d, %f",finalSize,number);
    }
    finalSize++;
    finalSize++;
    printf("\nfinalsize7: %d, %f",finalSize,number);

    return finalSize;
}



size_t characterPlacer(char * charArray, size_t sizeOfArray,short place, MKTDOUBLE number, bool isX, bool isNegative)
{
    size_t finalSize;
    size_t sizeOfCharacter;
    if(isX)
    {
        sizeOfCharacter = 2;
    } else {
        sizeOfCharacter = checkForNumberSize(number);
    }
    //-------------------------------------------------------------------------------------------------------------------------------------------
    printf("\nsize: %d \narray: ",sizeOfArray);
    for(int i = 0; i < sizeOfArray;i++)
    {
        printf("%c",charArray[i]);
    }
    sizeOfArray += sizeOfCharacter;
    charArray = realloc(charArray,sizeOfArray);
        //-------------------------------------------------------------------------------------------------------------------------------------------
    printf("\nsize: %d \narray: ",sizeOfArray);
    for(int i = 0; i < sizeOfArray;i++)
    {
        printf("%c",charArray[i]);
    }
    for(int i = sizeOfArray; i >= place+sizeOfCharacter;i--)
    {
        charArray[i] = charArray[i-sizeOfCharacter];
    }
    if(isX)
    {
        if(isNegative)
            charArray[place] = '-';
        else
            charArray[place] = '+';

        charArray[place+1] = 'x';
    } else {
        if(number < 0)
            charArray[place] = '-';
        else
            charArray[place] = '+';
        char * numberOfCharacter;
        numberOfCharacter = malloc(sizeOfCharacter);
        snprintf(numberOfCharacter,sizeOfCharacter,"%f",number);
        printf("\narray");
        for(int i = 0;i < sizeOfCharacter-1;i++)
        {
            charArray[place + i + 1] = numberOfCharacter[i];
        }
        free(numberOfCharacter);
        //-------------------------------------------------------------------------------------------------------------------------------------------
        printf("\nsize: %d \narray: ",sizeOfArray);
        for(int i = 0; i < sizeOfArray;i++)
        {
            printf("%c",charArray[i]);
        }
    }
            //-------------------------------------------------------------------------------------------------------------------------------------------
        printf("\nsize: %d \narray: ",sizeOfArray);
        for(int i = 0; i < sizeOfArray;i++)
        {
            printf("%c",charArray[i]);
        }
    finalSize = sizeOfArray;
    return finalSize;
}

MKTDOUBLE numberChecker(char * charArray,short startingCharacter, bool * isX, size_t sizeOfArray)
{
    MKTDOUBLE finalResult;
    bool isNegative = false;


    finalResult = 1;
    if(charArray[startingCharacter] == subChar)
        isNegative = true;

    finalResult *= isNegative?-1:1;

    if(charArray[startingCharacter+1]=='x')
    {
        *isX = true;
        return finalResult;
    }

    long long fractionDivider = 1;

    finalResult = (charArray[startingCharacter+1] - '0') * (isNegative?-1:1);

    for(int i = startingCharacter+2;charArray[i]!=subChar && charArray[i]!=addChar && i < sizeOfArray;i++)
    {
        if(charArray[i] == sidChar)
        {
            fractionDivider *= 10;
        } else if (fractionDivider != 1)
        {
            finalResult = ((charArray[startingCharacter+1] - '0') * (isNegative?-1:1))/fractionDivider;
            fractionDivider *= 10;
        } else {
            finalResult *= 10;
            finalResult += (charArray[i] - '0') * (isNegative?-1:1);
        }
    }

    return finalResult;
}

size_t finalPlacer(char * charArray, size_t sizeOfArray)
{
    size_t finalSize;
    bool isX;
    bool leftSide = true;
    MKTDOUBLE movingChar;

    for(int i = 0; i < sizeOfArray;i++)
    {
        if(charArray[i] == '=')
            leftSide = false;
        if(charArray[i] == subChar || charArray[i] == addChar)
        {
            movingChar = numberChecker(charArray,i,&isX,sizeOfArray);
            if(isX)
            {
                if(leftSide)
                {} else {

                }
            }
        }
    }


    finalSize = sizeOfArray;
    return finalSize;
}



size_t characterChangerAddSub(char * charArray, size_t sizeOfArray)
{
    size_t finalSize;

    if(charArray[0] != subChar && charArray[0] != addChar)
    {
        sizeOfArray++;
        charArray = realloc(charArray,sizeOfArray);
        for(int i = sizeOfArray-1; i > 0;i--)
        {
            charArray[i] = charArray[i-1];
        }
        charArray[0] = addChar;
    }

    short afterEqual = -1;
    for(int i = 0; i < sizeOfArray && afterEqual < 0;i++)
    {
        if(charArray[i] == '=')
            afterEqual = i+1;
    }

    if(charArray[afterEqual] != subChar && charArray[afterEqual] != addChar)
    {
        sizeOfArray++;
        charArray = realloc(charArray,sizeOfArray);
        for(int i = sizeOfArray-1; i > afterEqual;i--)
        {
            charArray[i] = charArray[i-1];
        }
        charArray[afterEqual] = addChar;
    }

    finalSize = sizeOfArray;
    return finalSize;
}

size_t simpleEquationParser(char * charArray, size_t sizeOfArray)
{
    size_t finalSize;
    finalSize = sizeOfArray;

    return finalSize;
}


MKTDOUBLE checkForDivision(char * charArray,size_t sizeOfArray) {
    MKTDOUBLE FinalInt; // comedy



    return FinalInt;
}

size_t bracketCopywriter(char ** charArray, short * currentCharacter, short start, short end)
{
    size_t finalInt; // comedy strikes again


    finalInt = end-start+1;
    // MKTDOUBLE finalEquation = checkForDivision();
    char * copy = malloc(finalInt);



    for(int i = 0; i < finalInt;i++)
    {
        copy[i] = 'B';
    }



    charArray[0]=realloc(charArray[0],*currentCharacter+finalInt);
    for(int i = 0; i < finalInt;i++)
    {
        charArray[0][*currentCharacter] = copy[i];
        *currentCharacter = *currentCharacter + 1;
    }
    free(copy);
    return finalInt;
}


size_t bracketCopywriterBuffer(char * copy,char * charArray, size_t sizeOfArray)
{
    size_t finalInt;
    short currentCharacter = 0;
    short ABrackets = 0;
    for(int i = 0; i < sizeOfArray;i++)
    {
        if(charArray[i]=='(')
        {
            short nBrackets = 1;
            short start = i+1;
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
            bracketCopywriter(&copy,&currentCharacter,start, i-1);
            ABrackets++;
            i++;
        }
        copy = realloc(copy,currentCharacter+1);
        copy[currentCharacter] = charArray[i];
        currentCharacter++;
    }

    printf("\nnumber of brackets: %d",ABrackets);
    return currentCharacter;
}







char * Copywriter(char * charArray, size_t sizeOfArray, size_t *sizeOfResult)
{
    char * copy = malloc(sizeOfArray);

    *sizeOfResult = bracketCopywriterBuffer(copy,charArray, sizeOfArray); // removes brackets

    *sizeOfResult = characterChangerAddSub(copy, *sizeOfResult); // places '+' characters before numbers

    // *sizeOfResult = finalPlacer(copy,*sizeOfResult); // places 'x' on the left, and the numbers on the right
    printf("\nwe have");
    *sizeOfResult = characterPlacer(copy, *sizeOfResult,2, 420.70, false, false);
    printf(" a problem");
    
    *sizeOfResult = simpleEquationParser(copy, *sizeOfResult);

    return copy;
}








MKTXFLAGS checkForX(char * charArray, size_t sizeOfArray, int *errorCode)
{
    MKTXFLAGS XFlags;
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

    if(MKTDEBUGBOOL)
    {
        if(errorCode == 2)
            printf("equation is not correct\n");
        for(int i = 0; i < XFlags.sizeOfResult;i++)
        {
            printf("\n%d.%c",i,XFlags.result[i]);
        }
    }
    
    printf("\n");
    
    for(int i = 0; i < XFlags.sizeOfResult;i++)
    {
        printf("%c",XFlags.result[i]);
    }

    printf("\nx ∈ R\n");

    return 0;
}