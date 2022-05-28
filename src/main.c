#include "headers/finder.h"
#define MKT_ERROR_HANDLING_IMPLEMENTATION
#include <MKTmisc/MKTSimpleErrorHandling.h>

int main(int argc, char ** argv)
{
    SETUP_ERROR_HANDLING("./build/errors.txt")

    if(argv[1] == NULL)
        errorCode = 2;
    
    HANDLE_ERRORS // step 0

    SETUP

    HANDLE_ERRORS // step 1
    arrayPrinter(equation,sizeOfArray);

    HANDLE_ERRORS // step 2
    sizeOfArray = basicFirstChecker(equation, sizeOfArray, &errorCode);
    arrayPrinter(equation,sizeOfArray);

    HANDLE_ERRORS // step 3
    sizeOfArray = characterChangerAddSub(equation, sizeOfArray);
    arrayPrinter(equation,sizeOfArray);

    HANDLE_ERRORS // step 4
    sizeOfArray = checkForDivision(equation, sizeOfArray);
    arrayPrinter(equation,sizeOfArray);

    HANDLE_ERRORS // step 5
    sizeOfArray = simpleEquationParser(equation, sizeOfArray);
    arrayPrinter(equation,sizeOfArray);

    HANDLE_ERRORS // step 6
    sizeOfArray = finalPlacer(equation, sizeOfArray);
    arrayPrinter(equation,sizeOfArray);

    
    printf("\n");
    return 0;
}