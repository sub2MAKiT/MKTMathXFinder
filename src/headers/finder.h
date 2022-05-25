#pragma once
#include "parser.h"

size_t mulParsing(char * charArray, size_t sizeOfArray);
size_t smartMultiply(char * charArray, size_t sizeOfArray, MKTDOUBLE number);
MKTDOUBLE numberChecker(char * charArray,short startingCharacter, bool * isX, size_t sizeOfArray);
size_t finalPlacer(char * charArray, size_t sizeOfArray);
size_t characterChangerAddSub(char * charArray, size_t sizeOfArray);
size_t simpleEquationParser(char * charArray, size_t sizeOfArray);
size_t checkForDivision(char * charArray,size_t sizeOfArray);
size_t bracketCopywriter(char ** charArray, short * currentCharacter, short start, short end);
size_t bracketCopywriterBuffer(char * copy,char * charArray, size_t sizeOfArray);
size_t multiplierInSpace(char * charArray, size_t sizeOfArray, MKTDOUBLE Mul, bool isX, bool isNegative);