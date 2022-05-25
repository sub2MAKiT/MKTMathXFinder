#pragma once
#include "convenience.h"

size_t numberRemover(char * charArray,size_t sizeOfArray, short number);
size_t smartCharacterPlacer(char * charArray, size_t sizeOfArray,short place, MKTDOUBLE number, bool isX, bool isNegative);
size_t checkForNumberSize(MKTDOUBLE number);
size_t characterPlacer(char * charArray, size_t sizeOfArray,bool placeOnLeft, MKTDOUBLE number, bool isX, bool isNegative);
size_t basicFirstChecker(char * charArray, size_t sizeOfArray, int * errorCode);