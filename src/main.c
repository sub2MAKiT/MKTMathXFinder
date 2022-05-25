#include "headers/finder.h"

int main(int argc, char ** argv)
{
    short step = 0;
    int errorCode = 0;
    if(argv[1] == NULL)
        errorCode = 2;
    
    HANDLE_ERRORS
    1;

    SETUP

    HANDLE_ERRORS
    sizeOfArray = basicFirstChecker(equation, sizeOfArray, &errorCode);

    HANDLE_ERRORS
    sizeOfArray = characterChangerAddSub(equation, sizeOfArray);

    HANDLE_ERRORS
    sizeOfArray = checkForDivision(equation,sizeOfArray);

    HANDLE_ERRORS
    sizeOfArray = finalPlacer(equation,sizeOfArray);
    
    arrayPrinter(equation,sizeOfArray);
    printf("\n");
    return 0;
}