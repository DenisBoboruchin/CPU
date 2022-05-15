#ifndef PROCESSOR
#define PROCESSOR

#include <stdio.h>
#include <assert.h>
#include <math.h>
//#include <windows.h>

#include "../enum.h"
#include "../MyStack.h"
#include "../SortText.h"

const int   DESTROYED   = -333;
const int   NUMREGS     =    5;

const int   SIZERAM     =  0x10000;
const int   STARTMEM    =  0X01000;
const int   STARTGPU    =  0x0f000;

const int   ERRORINPUT  =   0;
const int   GOODINPUT   =   1;

const int   STARTINDEX  =   0;

struct CPU
{
    Stack  stk                = {};
    int    registers[NUMREGS] = {};
    char*  RAM                = {};
    size_t ip                 =  0;
};

int     Execute     (const char* BINCODE);
int     ProcCtor    (CPU* pcpu, const char* BINCODE);
void    CheckCmd    (CPU* pcpu, Stack* stkForCall);
void    CheckAccess (int  cell);
int     ProcAssert  (CPU* pcpu);
int     ProcDtor    (CPU* pcpu);
int     DestReg     (CPU* pcpu);

int     GetValue        (int* value);
void    ClearInputBuf   (void);

#endif // PROCESSOR
