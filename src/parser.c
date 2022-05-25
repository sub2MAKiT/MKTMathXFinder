#include "headers/parser.h"
#include <MKTgnubasedlibrary.h>



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

size_t smartCharacterPlacer(char * charArray, size_t sizeOfArray,short place, MKTDOUBLE number, bool isX, bool isNegative)
{
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
        snprintf(numberOfCharacter,sizeOfCharacter,"%f",MKTfabs(number) );
        for(int i = 0;i < sizeOfCharacter-2;i++)
        {
            charArray[place + i + 2] = numberOfCharacter[i];
        }
        free(numberOfCharacter);
        finalSize = sizeOfArray;
        return finalSize;
    } else {
        if(number >= 0)
            charArray[place] = '+';
        else
            charArray[place] = '-';
        char * numberOfCharacter;
        numberOfCharacter = malloc(sizeOfCharacter);
        snprintf(numberOfCharacter,sizeOfCharacter,"%f",MKTfabs(number) );
        for(int i = 0;i < sizeOfCharacter-1;i++)
        {
            charArray[place + i + 1] = numberOfCharacter[i];
        }
        free(numberOfCharacter);
    }
    finalSize = sizeOfArray;
    return finalSize;
}

size_t checkForNumberSize(MKTDOUBLE number)
{
    size_t finalSize;
    MKTDOUBLE fractpart;
    long long intpart;
    fractpart = MKTmodf(number*(1-(2*(number<0))),&intpart);
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
        
    while(fractpart-MKTfloor(fractpart+0.1)>0)
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

        snprintf(numberOfCharacter,sizeOfCharacter,"%f",MKTfabs(number) );
        for(int i = 0;i < sizeOfCharacter-2;i++)
        {
            charArray[place + i + 2] = numberOfCharacter[i];
        }
        free(numberOfCharacter);

    finalSize = sizeOfArray;
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

        snprintf(numberOfCharacter,sizeOfCharacter,"%f",MKTfabs(number) );
        for(int i = 0;i < sizeOfCharacter-1;i++)
        {
            charArray[place + i + 1] = numberOfCharacter[i];
        }
        free(numberOfCharacter);
    }
    finalSize = sizeOfArray;
    return finalSize;
}

size_t basicFirstChecker(char * charArray, size_t sizeOfArray, int * errorCode)
{
    size_t finalSize = sizeOfArray;
    short isDivision = false;

    if(!(charArray[0] == subChar || charArray[0] == addChar || charArray[0] == mulChar || charArray[0] == divChar || charArray[0] == powChar || charArray[0] == sqrChar || charArray[0] == sidChar || charArray[0] == eqChar || (charArray[0] < 58 && charArray[0] > 47 )))
        *errorCode = 3;
    
    bool detectedEqual = false;

    for(int i = 0; i < sizeOfArray;i++)
    {
        if(charArray[i] == '=' && !detectedEqual)
            detectedEqual = true;
        else if(charArray[i] == '=' && detectedEqual)
            *errorCode = 5;
        if(!(charArray[i] == subChar || charArray[i] == addChar || charArray[i] == mulChar || charArray[i] == divChar || charArray[i] == powChar || charArray[i] == sqrChar || charArray[i] == sidChar || charArray[i] == eqChar || (charArray[i] < 58 && charArray[i] > 47 )))
            *errorCode = 4;
    }
    if(!detectedEqual)
    {
        *errorCode = 6;
    }

    return finalSize;
}