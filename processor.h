#ifndef PROCESSOR
#define PROCESSOR

#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "enum.h"
#include "MyStack.h"
#include "SortText.h"

struct CPU
{
    Stack stk = {};
    int registers[5] = {};
    char* code = {};
    size_t ip = 0;
};

int Execute(void);
void CheckCmd(CPU* pcpu);

#endif // PROCESSOR
