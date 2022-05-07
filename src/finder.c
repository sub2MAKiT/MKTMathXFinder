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

#define equationString "x+3+1-2=x3+1+x-x2"//   x*(2+3)=1/(x+1)+2+4+(9*659/4)

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
    size_t * sizeOfResult;
};

typedef struct xFlags MKTXFLAGS;

void arrayPrinter(char * charArray, size_t SizeOfArray);
size_t checkForNumberSize(MKTDOUBLE number);
size_t characterPlacer(char * charArray, size_t sizeOfArray,bool placeOnLeft, MKTDOUBLE number, bool isX, bool isNegative);
MKTDOUBLE numberChecker(char * charArray,short startingCharacter, bool * isX, size_t sizeOfArray);
size_t finalPlacer(char * charArray, size_t sizeOfArray);
size_t characterChangerAddSub(char * charArray, size_t sizeOfArray);
size_t simpleEquationParser(char * charArray, size_t sizeOfArray);
MKTDOUBLE checkForDivision(char * charArray,size_t sizeOfArray);
size_t bracketCopywriter(char ** charArray, short * currentCharacter, short start, short end);
size_t bracketCopywriterBuffer(char * copy,char * charArray, size_t sizeOfArray);
char * Copywriter(char * charArray, size_t sizeOfArray, size_t *sizeOfResult);
MKTXFLAGS checkForX(char * charArray, size_t sizeOfArray, int *errorCode);


void arrayPrinter(char * charArray, size_t SizeOfArray)
{
    printf("\n");

    for(int i = 0; i < SizeOfArray;i++)
    {
        printf("%c",charArray[i]);
    }

    return;
}

size_t checkForNumberSize(MKTDOUBLE number)
{
    size_t finalSize;
    MKTDOUBLE fractpart, intpart;
    fractpart = modf(number*(1-(2*(number<0))),&intpart);
    int powersOfTen=1;
    finalSize = 1;
    for(int i = 1; powersOfTen < intpart;i++,powersOfTen *= 10)
    {
        finalSize = i;
    }
    if(fractpart != 0)
    {
        finalSize++;
        powersOfTen=0;
        
    while(fractpart-floor(fractpart+0.1)>0)
    {
        fractpart *= 10;
        powersOfTen++;
    }

        finalSize += powersOfTen;
    }
    finalSize++;
    return finalSize;
}



size_t characterPlacer(char * charArray, size_t sizeOfArray,bool placeOnLeft, MKTDOUBLE number, bool isX, bool isNegative)
{
    short place = 0;
    if(!placeOnLeft)
    {
        for(int i = 0; i < sizeOfArray;i++)
        {
            if(charArray[i] == '=')
            {
                place = i+1;
                break;
            }
        }
    }

    size_t finalSize;
    size_t sizeOfCharacter;

    sizeOfCharacter = checkForNumberSize(number);

    if(isX)
        sizeOfCharacter++;

    sizeOfArray += sizeOfCharacter;
    charArray = realloc(charArray,sizeOfArray);
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

        char * numberOfCharacter;
        numberOfCharacter = malloc(sizeOfCharacter);

        snprintf(numberOfCharacter,sizeOfCharacter,"%f",fabs(number) );
        for(int i = 0;i < sizeOfCharacter-2;i++)
        {
            charArray[place + i + 2] = numberOfCharacter[i];
        }
        free(numberOfCharacter);

        return finalSize;
    } else {
        if(number >= 0)
            charArray[place] = '+';
        else
            charArray[place] = '-';
        char * numberOfCharacter;
        numberOfCharacter = malloc(sizeOfCharacter);

        // MKTDOUBLE tempNumber = number;
        // char * cantBeAnInt = &tempNumber;
        // cantBeAnInt[0] = cantBeAnInt[0]&127;

        snprintf(numberOfCharacter,sizeOfCharacter,"%f",fabs(number) );
        for(int i = 0;i < sizeOfCharacter-1;i++)
        {
            charArray[place + i + 1] = numberOfCharacter[i];
        }
        free(numberOfCharacter);
    }
    finalSize = sizeOfArray;
    return finalSize;
}

MKTDOUBLE numberChecker(char * charArray,short startingCharacter, bool * isX, size_t sizeOfArray)
{
    MKTDOUBLE finalResult;
    bool isNegative = false;

        finalResult = 1;
    if(!*isX)
    {

        if(charArray[startingCharacter] == subChar)
            isNegative = true;

        finalResult *= isNegative?-1:1;

        if(charArray[startingCharacter+1]=='x')
        {
            *isX = true;
            return finalResult;
        } else {
            *isX = false;
        }
    } else {
    startingCharacter++;
        if(charArray[startingCharacter+1] == subChar ||charArray[startingCharacter+1] == addChar ||charArray[startingCharacter+1] == '=')
            return finalResult;
    }
    long long fractionDivider = 1;

    finalResult = (charArray[startingCharacter+1] - '0') * (isNegative?-1:1);
    for(int i = startingCharacter+2;charArray[i]!=subChar && charArray[i]!=addChar && charArray[i]!='=' && i < sizeOfArray;i++)
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

size_t numberRemover(char * charArray,size_t sizeOfArray, short number)
{
    size_t finalSize;
    finalSize = 0;
    short sizeOfNumber;
    
    for(int i = 1; i < sizeOfArray-number;i++)
    {
        sizeOfNumber = i;
        if(charArray[i+number] == subChar || charArray[i+number] == addChar || charArray[i+number] == mulChar || charArray[i+number] == divChar || charArray[i+number] == powChar || charArray[i+number] == sqrChar || charArray[i+number] == '=')
            break;
    }

    finalSize = sizeOfArray - sizeOfNumber;

    for(int i = 0; i < finalSize;i++)
    {
        charArray[i+number] = charArray[i+sizeOfNumber+number];
    }


    charArray = realloc(charArray,finalSize);

    return finalSize;
}

size_t finalPlacer(char * charArray, size_t sizeOfArray)
{
    size_t finalSize;
    finalSize = sizeOfArray;
    bool isX;
    bool leftSide = true;
    MKTDOUBLE movingChar;
    for(int i = 0; i < sizeOfArray;i++)
    {
        if(charArray[i] == '=')
            leftSide = false;
        if(charArray[i] == subChar || charArray[i] == addChar)
        {
            isX = false;
            movingChar = numberChecker(charArray,i,&isX,sizeOfArray);
            if(isX)
            {
                if(!leftSide)
                {
                    bool isNotNegative;
                    if(charArray[i] == subChar)
                        isNotNegative = false;
                    else
                        isNotNegative = true;
                    movingChar = numberChecker(charArray,i,&isX,sizeOfArray);
                    finalSize = numberRemover(charArray,finalSize,i);
                    finalSize = characterPlacer(charArray, finalSize,true, movingChar, true, isNotNegative);
                    i--;
                }
            } else {
                if(leftSide)
                {
                    movingChar *= -1;
                    finalSize = numberRemover(charArray,finalSize,i);
                    finalSize = characterPlacer(charArray, finalSize,false, movingChar, false, false);
                    i--;
                }
            }
        }
    }


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
    bool afterEqual= false;

    MKTDOUBLE XVALUE = 0;
    MKTDOUBLE INTVALUE = 0; // comedy

    MKTDOUBLE movingChar;
    for(int i = 0; i < sizeOfArray;i++)
    {
        if(charArray[i] == '=')
        { afterEqual = true; } else if((charArray[i] == subChar || charArray[i] == addChar) && !afterEqual)
        {
            bool isX = true;
            movingChar = numberChecker(charArray,i,&isX,finalSize);
            if(charArray[i] == subChar)
                XVALUE -= movingChar;
            else
                XVALUE += movingChar;
        } else if((charArray[i] == subChar || charArray[i] == addChar) && afterEqual) {
            bool isX = false;
            movingChar = numberChecker(charArray,i,&isX,finalSize);
            INTVALUE += movingChar;
        }
    }

    printf("\n%fx=%f",XVALUE,INTVALUE);
        size_t sizeOfFinalArray = 0;

    if(XVALUE != 0 && INTVALUE != 0)
    {
        sizeOfFinalArray = 2;

        INTVALUE = INTVALUE / XVALUE;

        sizeOfFinalArray += checkForNumberSize(INTVALUE);

        charArray = realloc(charArray,sizeOfFinalArray);

        snprintf(charArray,sizeOfFinalArray,"x=%f",INTVALUE );
    } else if(XVALUE == 0 && INTVALUE == 0)
    {
        sizeOfFinalArray = 7;
        charArray = realloc(charArray,sizeOfFinalArray);
        snprintf(charArray,sizeOfFinalArray,"\nx ∈ R\n");
    } else if((XVALUE == 0 && INTVALUE != 0) || (XVALUE != 0 && INTVALUE == 0))
    {
        sizeOfFinalArray = 16;
        charArray = realloc(charArray,sizeOfFinalArray);
        snprintf(charArray,sizeOfFinalArray,"\nwrong equation\n");
    }
    return sizeOfFinalArray;
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
    size_t tempSizeOfResult = 0;

    *sizeOfResult = bracketCopywriterBuffer(copy,charArray, sizeOfArray); // removes brackets
    arrayPrinter(copy, *sizeOfResult);

    *sizeOfResult = characterChangerAddSub(copy, *sizeOfResult); // places '+' characters before numbers
    arrayPrinter(copy, *sizeOfResult);

    *sizeOfResult = finalPlacer(copy,*sizeOfResult); // places 'x' on the left, and the numbers on the right
    arrayPrinter(copy, *sizeOfResult);
    // *sizeOfResult = characterPlacer(copy, *sizeOfResult,true, 420.70, false, false);
    // *sizeOfResult = characterPlacer(copy, *sizeOfResult,false, -420.70, false, false);
    
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
    XFlags.sizeOfResult = malloc(8);
    XFlags.result = Copywriter(charArray, sizeOfArray,XFlags.sizeOfResult);
    
    return XFlags;
}

int main()
{
    char a[] = equationString;
    int errorCode = 0;
    MKTXFLAGS XFlags;

    size_t * sizeOfArray = malloc(8);

    *sizeOfArray = sizeof(a);

    XFlags = checkForX(a, *sizeOfArray, &errorCode);

    if(MKTDEBUGBOOL)
    {
        if(errorCode == 2)
            printf("equation is not correct\n");
        for(int i = 0; i < *XFlags.sizeOfResult;i++)
        {
            printf("\n%d.%c",i,XFlags.result[i]);
        }
    }
    
    printf("\n");
    
    for(int i = 0; i < *XFlags.sizeOfResult;i++)
    {
        printf("%c",XFlags.result[i]);
    }
    return 0;
}