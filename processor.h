#ifndef PROCESSOR
#define PROCESSOR

#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "enum.h"
#include "MyStack.h"
#include "SortText.h"

const int DESTROYED = -333;
const int NUMREGS = 5;

const int ERRORINPUT = 0;
const int GOODINPUT  = 1;

const int STARTINDEX = 0;

struct CPU
{
    Stack stk = {};
    int registers[NUMREGS] = {};
    char* code = {};
    size_t ip = 0;
};

int Execute(const char* BINCODE);
int ProcCtor(CPU* pcpu, const char* BINCODE);
void CheckCmd(CPU* pcpu);
int ProcAssert(CPU* pcpu);
int ProcDtor(CPU* pcpu);
int DestReg(CPU* pcpu);

int GetValue(int* value);
void ClearInputBuf(void);

#endif // PROCESSOR
