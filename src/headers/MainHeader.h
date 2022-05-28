#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <MKTmisc/MKTSimpleErrorHandling.h>

#ifdef _MKTDEBUGBOOL
#define MKTDEBUGBOOL true
#else
#define MKTDEBUGBOOL false
#endif

#define MKTDOUBLE double

#define SETUP size_t sizeOfArray = sizeOfString(argv[1]);\
    char * equation = malloc(sizeOfArray);\
    for(int i = 0; i < sizeOfArray; i++)\
        equation[i] = argv[1][i];

#define equationString "x/2=1"//x=24 x*(2+3)=1/(x+1)+2+4+(9*659/4) 24/x+x/3+4=x/2+1 x/3+4+1/1+1=x/2+2/2+24/x x/3+4+1/1=x/2+2/2 //pwned// x+3+1-2=x3+1+x-x2 | x+1.7=2.8 | x*2=3

#define ERRORSTRING "\033[31;40mERROR\033[93;40m[%d]\033[31;40m - \033[97;40m"

#define subChar '-'
#define addChar '+'
#define mulChar '*'
#define divChar '/'
#define powChar '^'
#define sqrChar '|'
#define sidChar '.'
#define eqChar '='