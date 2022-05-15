#include "MyStack.h"

int StackCtor(Stack* stk)
{
    stk->capacity = STARTSTACKCAPACITY;

    stk->data = (elem_type*) calloc(stk->capacity + 2 * SIZECANARY + 1, sizeof(elem_type));
    CleanData(stk);

    stk->data = (elem_type*) stk->data + SIZECANARY;
    *(unsigned long long int*) (stk->data - SIZECANARY) = LEFTCANARY;
    *((unsigned long long int*) (stk->data + stk->capacity)) = RIGHTCANARY;

    stk->size = 0;
    stk->HASHSTACK = 41 * stk->size % 113 + 2 * (stk->capacity - 2) % 337 + 3 * (- 3) + 337;

    STACK_CHECK
}

int StackDtor(Stack* stk)
{
    STACK_CHECK

    free(stk->data - SIZECANARY);

    stk->capacity = -1;
    stk->size = -1;

    stk->HASHSTACK = -1;
    stk->HASHDATA = -1;

    stk->LEFTSTACKCANARY = -1;
    stk->RIGHTSTACKCANARY = -1;
}

int StackPush(Stack* stk, elem_type value)
{
    STACK_CHECK
    CheckSize(stk);

    *(stk->data + stk->size) = value;

    stk->HASHDATA += (37 * value) + 13 * stk->size % 7;
    stk->HASHSTACK -= 41 * stk->size % 113;

    (stk->size)++;

    stk->HASHSTACK += 41 * stk->size % 113;

    CheckSize(stk);
    STACK_CHECK
}

elem_type StackPop(Stack* stk)
{
    STACK_CHECK
    CheckSize(stk);

    (stk->size)--;

    stk->HASHSTACK -= 41 * (stk->size + 1) % 113;
    stk->HASHSTACK += 41 * stk->size % 113;

    elem_type temp = *(stk->data + stk->size);
    *(stk->data + stk->size) = -1;

    stk->HASHDATA -= ((37 * temp) + 13 * stk->size % 7);

    CheckSize(stk);
    STACK_CHECK

    return temp;
}

int CheckSize(Stack* stk)
{
    if (stk->size >= stk->capacity)
        StackResizeTop(stk);

    else if ((stk->size > 10) && (stk->size * 3 < stk->capacity))
        StackResizeDown(stk);

    STACK_CHECK
}

int StackResizeTop(Stack* stk)
{
    CleanCanary(stk);

    stk->HASHSTACK -= 2 * (stk->capacity - 2) % 337;

    stk->capacity = (stk->capacity) * 1.7 + 1;

    stk->HASHSTACK += 2 * (stk->capacity - 2) % 337;

    MyRealloc(stk);

    *((unsigned long long int*) (stk->data + stk->capacity)) = RIGHTCANARY;

    STACK_CHECK
}

int StackResizeDown(Stack* stk)
{
    CleanCanary(stk);

    stk->HASHSTACK -= 2 * (stk->capacity - 2) % 337;

    stk->capacity = (stk->capacity) / 2 + 1;

    stk->HASHSTACK += 2 * (stk->capacity - 2) % 337;

    MyRealloc(stk);

    *((unsigned long long int*) (stk->data + stk->capacity)) = RIGHTCANARY;

    STACK_CHECK
}

void CleanCanary(Stack* stk)
{
    for (int i = 0; i < SIZECANARY; i++)
        *((elem_type*) (stk->data + stk->capacity + i + 1)) = 0;
}

void MyRealloc(Stack* stk)
{
    stk->data = (elem_type*) realloc(stk->data - SIZECANARY, (stk->capacity + 2 * SIZECANARY + 1) * sizeof(elem_type));
    stk->data = stk->data + SIZECANARY;

    for (int i = stk->size; i < stk->capacity; i++)
        *(stk->data + i) = -1;
}

void CleanData(Stack* stk)
{
    for (int i = 0; i < stk->capacity + 2 * SIZECANARY + 1; i++)
        *(stk->data + i) = -1;
}

int StackCheck(const Stack* stk)
{
    int keyError = GetKeyError(stk);

    if (keyError != STACK_OK)
    {
        FprintfERROR();

        StackDump(stk, TypeOfError(keyError));
        assert (0 && "ERROR");
    }
    else
        StackDump(stk, TypeOfError(keyError));
}

void FprintfERROR(void)
{
    fprintf(logFile, "\n");

    for (int i = 0; i < 5; i++)
        fprintf(logFile, "ERROR_ERROR_ERROR_ERROR_ERROR_ERROR_ERROR_ERROR_ERROR_ERROR_ERROR_ERROR_ERROR_ERROR_ERROR\n");

    fprintf(logFile, "\n");
}

int GetKeyError(const Stack* stk)
{
    if ((stk->size == -1) && (stk->capacity == -1))
        return STACK_DESTROYED;

    if (!stk)
        return INVALID_ADDRESS_STACK;

    if (stk->size < 0)
        return INVALID_SIZE;

    if (stk->capacity < 0)
        return INVALID_CAPACITY;

    if (stk->size > stk->capacity)
        return EXCESS_SIZE;

    if (stk->LEFTSTACKCANARY != 0xC0FFEE1)
        return INVALID_LEFT_STACK_CANARY;

    if (stk->RIGHTSTACKCANARY != 0xC0FFEE2)
        return INVALID_RIGHT_STACK_CANARY;

    if ((stk->capacity != 0) && (*(unsigned long long int*) (stk->data - SIZECANARY) != LEFTCANARY))
        return INVALID_LEFT_DATA_CANARY;

    if ((stk->capacity != 0) && (*(unsigned long long int*) (stk->data + stk->capacity) != RIGHTCANARY))
        return INVALID_RIGHT_DATA_CANARY;

    if (CheckDataHash(stk) != stk->HASHDATA)
        return INVALID_DATA_HASH;

    if (CheckStackHash(stk) != stk->HASHSTACK)
        return INVALID_STACK_HASH;

    return STACK_OK;
}

const char* TypeOfError(const int error)
{
    switch (error)
    {
        case STACK_DESTROYED:
            return "stack destroyed!!";

        case INVALID_ADDRESS_STACK:
            return "incorrect struct stack pointer";

        case INVALID_SIZE:
            return "incorrect stack size";

        case INVALID_CAPACITY:
            return "incorrect stack capacity";

        case EXCESS_SIZE:
            return "stack size larger than stack capacity";

        case EMPTY_STACK:
            return "stack size is 0";

        case INVALID_LEFT_STACK_CANARY:
            return "invalid value of left stack canary";

        case INVALID_RIGHT_STACK_CANARY:
            return "invalid value of right stack canary";

        case INVALID_LEFT_DATA_CANARY:
            return "invalid value of left data canary";

        case INVALID_RIGHT_DATA_CANARY:
            return "invalid value of right data canary";

        case INVALID_DATA_HASH:
            return "invalid value of data hash";

        case INVALID_STACK_HASH:
            return "invalid value of stack hash";

        case STACK_OK:
            return "stack Ok!";

        default:
            return "invalid key of error";
    }
}

int StackDump(const Stack* stk, const char* text)
{
    fprintf(logFile, "STATUS: %s\n\n\n", text);

    fprintf(logFile, "stack[%p]\n{\n\t", stk);

    fprintf(logFile, "left  canary for stack: %llX;\n\n\t", stk->LEFTSTACKCANARY);

    fprintf(logFile, "data  hash: %llX;\n\t", stk->HASHDATA);
    fprintf(logFile, "stack hash: %llX;\n\n\t", stk->HASHSTACK);

    fprintf(logFile, "size:     %d;\n\t", stk->size);
    fprintf(logFile, "capacity: %d;\n\n\t", stk->capacity);

    fprintf(logFile, "data[%p]\n\t{\n", stk->data);

    OutputData(stk);

    fprintf(logFile, "right canary for stack: %llX;\n}", stk->RIGHTSTACKCANARY);
}

long long int CheckDataHash(const Stack* stk)
{
    long long int tempHash = 0;

    for (int i = 0; i < stk->size; i++)
        tempHash += 37 * (*(stk->data + i)) + 13 * i % 7;

    return tempHash;
}

long long int CheckStackHash(const Stack* stk)
{
    return (long long int) (41 * stk->size % 113 + 2 * (stk->capacity - 2) % 337 + 3 * (- 3) + 337);
}

void OutputData(const Stack* stk)
{
    if (stk->capacity != 0)
        fprintf(logFile, "\t\t left  canary for data: %llX;\n", *(unsigned long long int*) (stk->data - SIZECANARY));


    for (int i = 0; i < stk->capacity; i++)
    {
        if (i < stk->size)
            fprintf(logFile, "\t\t*[%03d] = "ELEM_FMT";\n", i, *(stk->data + i));
        else
            fprintf(logFile, "\t\t [%03d] = "ELEM_FMT";\n", i, *(stk->data + i));
    }

    if (stk->capacity != 0)
        fprintf(logFile, "\t\t right canary for data: %llX;\n", *(unsigned long long int*) (stk->data + stk->capacity));

    fprintf(logFile, "\t}\n\n\t");
}

void Separator(FILE* logFile)
{
    fprintf(logFile, "\n\n");

    for (int i = 0; i < 4; i++)
    {
        fprintf(logFile, "-----------------------------------------------------------------------------------------\n");
    }

    fprintf(logFile, "\n");
}
