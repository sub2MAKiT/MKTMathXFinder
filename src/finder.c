#include "headers/finder.h"
#include <MKTmisc/MKTSimpleErrorHandling.h>

short goUntilNotACoreNumber(char * charArray, size_t sizeOfArray, short number)
{
    bool isNotCoreNumber = false;
    bool isANumber = false;

    for(int i = number+1; i < sizeOfArray;i++)
    {
        if(isANumber)
        {
            if(!isNotCoreNumber)
                return i;
            else
                isNotCoreNumber = false;
            isANumber = false;
        }

        if(charArray[i] == addChar || charArray[i] == subChar)
            isANumber = true;
        if(charArray[i] == mulChar || charArray[i] == divChar || charArray[i] == powChar || charArray[i] == sqrChar)
            isNotCoreNumber = true;
    }

    return sizeOfArray;
}

size_t mulParsing(char * charArray, size_t sizeOfArray)
{
    size_t finalSize;
    finalSize = sizeOfArray;
    for(int i = 0; i < sizeOfArray;i++)
    {
        bool phaseTwo = false;
        if(charArray[i] == mulChar)
        {
            // bool isDivToo = false; // check if the number is multiplied and divided by x
            // short end = goUntilNotACoreNumber(charArray, finalSize, i);
            // bool numberToCheckX = false;
            // MKTDOUBLE numberToCheck = numberChecker(charArray,i+1, numberToCheckX, finalSize);
            // for(int a = i+2; a < end; a++)
            // {
            //     MKTDOUBLE numberForChecking;
            //     if(charArray[a] == addChar || charArray[a] == subChar)
            //     {
            //         bool numberForCheckingX = false;
            //         numberForChecking = numberChecker(charArray,a, numberForCheckingX, finalSize);
            //         if(numberForChecking == numberToCheck && numberToCheckX == numberForCheckingX)
            //         {
            //             // delete the numbers
            //             phaseTwo = false;
            //         } else {

            //         }
            //     }
            // }
            // if(phaseTwo)
            // {
                bool isLeftX = false;
                bool isRightX = false;
                MKTDOUBLE Left = 1;
                MKTDOUBLE Right = 1;

                if(charArray[i+1] == 'x')
                    isRightX = true;
                
                Right = numberChecker(charArray,i+1, &isRightX, finalSize);

                short aPlace = 0;
                for(int a = i; charArray[a]!=addChar && charArray[a]!= subChar;a--)
                {
                    if(charArray[a] == 'x')
                        isLeftX = true;
                    aPlace = a;
                }
                aPlace--;

                if(charArray[aPlace-1]!=divChar&&charArray[aPlace-1]!=mulChar)
                {
                    Left = numberChecker(charArray,aPlace, &isLeftX, finalSize);
                    if(!isLeftX && !isRightX)
                    {
                        finalSize = numberRemover(charArray, finalSize,i+1);
                        finalSize = numberRemover(charArray, finalSize,aPlace);
                        for(int a = aPlace;a < sizeOfArray - 1;a++)
                        {
                            charArray[a] = charArray[a+1];
                        }
                        finalSize--;
                        finalSize = smartCharacterPlacer(charArray,finalSize,aPlace, Left*Right, false, false);
                    } else if (isLeftX && isRightX) {
                        // empty for now :D
                    } else {
                        finalSize = numberRemover(charArray, finalSize,i+1);
                        finalSize = numberRemover(charArray, finalSize,aPlace);
                        for(int a = aPlace;a < sizeOfArray - 1;a++)
                        {
                            charArray[a] = charArray[a+1];
                        }
                        finalSize--;
                        charArray = realloc(charArray,finalSize);
                        finalSize = smartCharacterPlacer(charArray,finalSize,aPlace, Left*Right, true, false);
                    }
                // }
                if(aPlace != 0)
                    i = aPlace;
            }
        }
    }

    return finalSize;
}

size_t multiplierInSpace(char * charArray, size_t sizeOfArray, MKTDOUBLE Mul, bool isX, bool isNegative)
{
    size_t finalSize;
    finalSize = sizeOfArray;
    bool notCoreNumber = false;
    bool numberDetected = true;

    for(int i = 0; i < finalSize;i++)
    {
        if(numberDetected && (charArray[i] == addChar || charArray[i] == subChar))
        {
            printf("\n%d");
                arrayPrinter(charArray,finalSize);
            i++;
            if(notCoreNumber) {notCoreNumber = false;} else {
                while(charArray[i] != addChar && charArray[i]!= subChar && charArray[i]!= mulChar && charArray[i]!= divChar && charArray[i]!= '=')
                    i++;
                finalSize++;
                charArray = realloc(charArray,finalSize);
                for(int a = finalSize; a > i; a--)
                {
                    charArray[a] = charArray[a-1];
                }
                charArray[i] = mulChar;
                i++;
                finalSize = smartCharacterPlacer(charArray, finalSize,i, Mul, isX, isNegative);
                numberDetected = false;
            }
        }

        if(charArray[i] == divChar || charArray[i] == mulChar)
            notCoreNumber = true;

        if(charArray[i] == subChar || charArray[i] == addChar)
            numberDetected = true;       
    }


    return finalSize;
}

size_t smartMultiply(char * charArray, size_t sizeOfArray, MKTDOUBLE number)
{
    size_t finalSize;
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
        if((charArray[startingCharacter+1] == subChar ||charArray[startingCharacter+1] == addChar ||charArray[startingCharacter+1] == '='||charArray[startingCharacter+1] == divChar || charArray[startingCharacter+1] == mulChar) || startingCharacter+1 >= sizeOfArray-1)
            return finalResult;
    }
    long long fractionDivider = 1;

    finalResult = (charArray[startingCharacter+1] - '0') * (isNegative?-1:1);
   
    if(charArray[startingCharacter+2] != 0)
    {
        for(int i = startingCharacter+2;charArray[i]!=subChar && charArray[i]!=addChar && charArray[i]!='=' && i < sizeOfArray && charArray[i]!=divChar && charArray[i]!=mulChar && charArray[i]!=0;i++)
        {
            if(charArray[i] == sidChar)
            {
                fractionDivider *= 10;
            } else if (fractionDivider != 1)
            {
                double tempDouble = ((charArray[i] - '0') * (isNegative?-1:1));
                finalResult += tempDouble/fractionDivider;
                fractionDivider *= 10;
            } else {
                finalResult *= 10;
                finalResult += (charArray[i] - '0') * (isNegative?-1:1);
            }

        }
    }
    return finalResult;
}

size_t finalPlacer(char * charArray, size_t sizeOfArray)
{
    size_t finalSize;
    finalSize = sizeOfArray;
    bool isX;
    bool leftSide = true;
    MKTDOUBLE movingChar;
    for(int i = 0; i < finalSize;i++)
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
                    i += checkForNumberSize(movingChar);
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
    for(int i = 0; i < finalSize; i++)
    {
        if(charArray[i] == divChar || charArray[i] == mulChar)
        {
            if(charArray[i+1] != subChar)
            {
                finalSize++;
                charArray = realloc(charArray,finalSize);
                for(int a = finalSize;a > i+1;a--)
                {
                    charArray[a] = charArray[a-1];
                }
                charArray[i+1] = addChar;
            }
        }
    }

    return finalSize;
}

size_t simpleEquationParser(char * charArray, size_t sizeOfArray)
{
    size_t finalSize;
    finalSize = sizeOfArray;
    bool afterEqual= false;

    MKTDOUBLE XVALUE = 0;
    MKTDOUBLE INTVALUE = 0; // comedy
    bool isIntEmpty = true;

    MKTDOUBLE movingChar;
    for(int i = 0; i < sizeOfArray;i++)
    {
        if(charArray[i] == '=')
        { afterEqual = true; } else if((charArray[i] == subChar || charArray[i] == addChar) && !afterEqual)
        {
            bool isX = true;
            movingChar = numberChecker(charArray,i,&isX,finalSize);
            XVALUE += movingChar * (charArray[i]==subChar?-1:1);
        } else if((charArray[i] == subChar || charArray[i] == addChar) && afterEqual) {
            bool isX = false;
            movingChar = numberChecker(charArray,i,&isX,finalSize);
            isIntEmpty = false;
            INTVALUE += movingChar;
        }
    }
        size_t sizeOfFinalArray = 0;

    if(XVALUE != 0 && INTVALUE != 0)
    {
        sizeOfFinalArray = 2;

        INTVALUE = INTVALUE / XVALUE;

        sizeOfFinalArray += checkForNumberSize(INTVALUE);

        charArray = realloc(charArray,sizeOfFinalArray);

        snprintf(charArray,sizeOfFinalArray,"x=%f",INTVALUE );
    } else if(XVALUE == 0 && isIntEmpty)
    {
        sizeOfFinalArray = 7;
        charArray = realloc(charArray,sizeOfFinalArray);
        snprintf(charArray,sizeOfFinalArray,"\nx ∈ R\n");
    } else if((XVALUE == 0 && !isIntEmpty) || (XVALUE != 0 && isIntEmpty))
    {
        sizeOfFinalArray = 16;
        charArray = realloc(charArray,sizeOfFinalArray);
        snprintf(charArray,sizeOfFinalArray,"\nwrong equation\n");
    }
    return sizeOfFinalArray;
}


size_t checkForDivision(char * charArray,size_t sizeOfArray) {
    size_t FinalSize;
    FinalSize = sizeOfArray;

    for(int i = 0; i < sizeOfArray;i++)
    {
        // if(charArray[i] == divChar)
        // {
        //     bool leftIsX = false;
        //     bool rightIsX = false;
        //     for(int a = i; charArray[a] != addChar && charArray[a] != subChar && charArray[a-1] != mulChar && charArray[a-1]!= divChar;a--)
        //     {
        //         if(charArray[a] == 'x')
        //         {
        //             leftIsX = true;
        //             break;
        //         }
        //     }
        //     for(int a = i+2; charArray[a] != addChar && charArray[a] != subChar && a < FinalSize;a++)
        //     {
        //         if(charArray[a] == 'x')
        //         {
        //             rightIsX = true;
        //             break;
        //         }
        //     }
        //     if(!leftIsX && !rightIsX)
        //     {
        //         printf("\ndetected divide int by int %d",i);

        //         MKTDOUBLE left = 1;
        //         MKTDOUBLE right = 1;
        //         short aPlace = 0;
        //         bool isX = false;
        //         for(int a = i; a >= 0 ;a--)
        //         {
        //             if(charArray[a] == addChar || charArray[a] == subChar)
        //             {
        //                 left = numberChecker(charArray,a,&isX,FinalSize);
        //                 aPlace = a;
        //                 break;
        //             }
        //         }
        //         right = numberChecker(charArray,i+1,&isX,FinalSize);
        //         FinalSize = numberRemover(charArray,FinalSize,i+1);
        //         FinalSize = numberRemover(charArray,FinalSize,aPlace);
        //         for(int a = aPlace; a < sizeOfArray-1;a++)
        //         {
        //             charArray[a] = charArray[a+1];
        //         }
        //         FinalSize--;
        //         charArray = realloc(charArray,FinalSize);
        //         FinalSize = smartCharacterPlacer(charArray,FinalSize,aPlace,left/right,isX,false);
        //         i = 0;
        //         arrayPrinter(charArray,sizeOfArray);
        //     } else if(leftIsX && !rightIsX) {
        //         printf("\ndetected divide x by int %d",i);
        //         MKTDOUBLE right = 1;
        //         bool isX = false;
        //         right = numberChecker(charArray,i+1,&isX,FinalSize);
        //         FinalSize = multiplierInSpace(charArray, FinalSize, right,false,false);


        //         arrayPrinter(charArray,sizeOfArray);


        //     } else if(!leftIsX && rightIsX) {

        //         printf("\ndetected divide int by x %d",i);
        //     } else {
                
        //         printf("\ndetected divide x by x %d",i);
        //     }
        // }



        // arrayPrinter(charArray,FinalSize); //+x*+3/+3+4*+3+1*+3/+1=+x*+3/+2+2*+3/+2 ++9/+3+4*+3+1*+3/+1=+x*+3/+2+2*+3/+2
        FinalSize = mulParsing(charArray, FinalSize);
    }

    return FinalSize;
}

size_t bracketCopywriter(char ** charArray, short * currentCharacter, short start, short end)
{
    size_t finalInt;


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

// size_t bracketCopywriterBuffer(char * copy,char * charArray, size_t sizeOfArray)
// {
//     size_t finalInt;
//     short currentCharacter = 0;
//     short ABrackets = 0;
//     for(int i = 0; i < sizeOfArray;i++)
//     {
//         if(charArray[i]=='(')
//         {
//             short nBrackets = 1;
//             short start = i+1;
//             while(nBrackets != 0)
//             {
//                 i++;
//                 if(charArray[i] == '(')
//                 {
//                     nBrackets++;
//                 }
//                 else if(charArray[i] == ')')
//                     nBrackets--;
//             }
//             bracketCopywriter(&copy,&currentCharacter,start, i-1);
//             ABrackets++;
//             i++;
//         }
//         copy = realloc(copy,currentCharacter+1);
//         copy[currentCharacter] = charArray[i];
//         currentCharacter++;
//     }

//     printf("\nnumber of brackets: %d",ABrackets);
//     return currentCharacter;
// }