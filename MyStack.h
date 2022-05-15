#ifndef MYSTACK
#define MYSTACK

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define INFOCHECK __FILE__, __LINE__, __PRETTY_FUNCTION__

#define STACK_CHECK   Separator(logFile);                                                                         \
                      fprintf(logFile, "IN the program: %s\nIN the line: %d\nIN the function: %s\n", INFOCHECK);  \
                      StackCheck(stk);

typedef int elem_type;
#define ELEM_FMT "%d"

struct Stack
{
    unsigned long long int LEFTSTACKCANARY = 0xC0FFEE1;

    int size = 0;
    int capacity = 0;
    long long int HASHSTACK = 0;
    long long int HASHDATA = 0;

    int* data;

    unsigned long long int RIGHTSTACKCANARY = 0xC0FFEE2;
};

const int STARTSTACKCAPACITY = 8;

static FILE* logFile = fopen("logFile.txt", "w");

enum ERRORS
{
    INVALID_ADDRESS_STACK = -100,
    INVALID_SIZE                ,
    INVALID_CAPACITY            ,
    EXCESS_SIZE                 ,
    EMPTY_STACK                 ,
    INVALID_LEFT_STACK_CANARY   ,
    INVALID_RIGHT_STACK_CANARY  ,
    INVALID_LEFT_DATA_CANARY    ,
    INVALID_RIGHT_DATA_CANARY   ,
    INVALID_DATA_HASH           ,
    INVALID_STACK_HASH          ,
    STACK_DESTROYED             ,
    STACK_OK
};

const unsigned long long int LEFTCANARY  = 0xDEDBAD1;
const unsigned long long int RIGHTCANARY = 0xDEDBAD2;

const int SIZECANARY = sizeof(LEFTCANARY) / sizeof(elem_type);

int StackCtor(Stack* stk);
int StackDtor(Stack* stk);

int StackPush(Stack* stk, elem_type value);
int CheckSize(Stack* stk);
int StackResizeTop(Stack* stk);
void CleanCanary(Stack* stk);
void MyRealloc(Stack* stk);
void CleanData(Stack* stk);

elem_type StackPop(Stack* stk);
int StackResizeDown(Stack* stk);

int StackDump(const Stack* stk, const char*);
int StackCheck(const Stack* stk);
int GetKeyError(const Stack* stk);
int StackPopCheck(const Stack* stk);
int GetKeyErrorPop(const Stack* stk);

long long int CheckDataHash(const Stack* stk);
long long int CheckStackHash(const Stack* stk);
void RecalculationStackHash(Stack* stk);

const char* TypeOfError(const int error);
void OutputData(const Stack* stk);
void FprintfERROR(void);

void Separator(FILE* logFile);

#endif // MYSTACK
