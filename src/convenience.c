#include "headers/convenience.h"

void arrayPrinter(char * charArray, size_t SizeOfArray)
{

    for(int i = 0; i < SizeOfArray;i++)
    {
        printf("%c",charArray[i]);
    }
    printf("\n");

    return;
}

size_t sizeOfString(char * charArray)
{
    size_t finalSize = 0;

    while(charArray[finalSize] != 0)
    {
        finalSize++;
    }

    return finalSize;
}

bool checkForErrors(int errorCode)
{
    bool Error = true;

    switch(errorCode) {
        case 1:
            printf(ERRORSTRING "system error\033[39;49m\n",errorCode);
            break;
        case 2:
            printf(ERRORSTRING "empty input\033[39;49m\n",errorCode);
            break;
        case 3:
            printf(ERRORSTRING "unsupported starting character\033[39;49m\n",errorCode);
            break;
        case 4:
            printf(ERRORSTRING "unsupported character\033[39;49m\n",errorCode);
            break;
        case 5:
            printf(ERRORSTRING "two equal characters detected\033[39;49m\n",errorCode);
            break;
        case 6:
            printf(ERRORSTRING "no equal characters detected\033[39;49m\n",errorCode);
            break;

        Error = false;
    }
    return Error;

}
