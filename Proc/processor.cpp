#include "processor.h"

#define DEF_CMD(name, num, arg, ...)     \
    case CMD_##name:                     \
        __VA_ARGS__                      \
                                         \

int Execute(const char* BINCODE)
{
    CPU cpu = {};

    ProcCtor(&cpu, BINCODE);

    Stack stkForCall = {};
    StackCtor(&stkForCall);

    while (true)
    {
        if (*(cpu.RAM + cpu.ip) == (char) CMD_HLT)
            break;

        CheckCmd(&cpu, &stkForCall);
    }

    StackDtor(&stkForCall);
    ProcDtor(&cpu);
}

int ProcCtor(CPU* pcpu, const char* BINCODE)
{
    StackCtor(&(pcpu->stk));

    size_t sizeBuf = GetSizeBuf(BINCODE);

    char* RAM = (char*) calloc(SIZERAM, sizeof(char));

    FILE* CODE = fopen(BINCODE, "r");
    assert (sizeBuf == fread(RAM, sizeof(char), sizeBuf, CODE));

    pcpu->RAM = RAM;
    pcpu->ip  = STARTINDEX;

    ProcAssert(pcpu);
}

void CheckCmd(CPU* pcpu, Stack* stkForCall)
{
    ProcAssert(pcpu);

    switch ((int)* ((unsigned char*) pcpu->RAM + pcpu->ip))
    {
        #include "../commands.h"

        default:
        {
            assert(!"unknown command");

            break;
        }
    }

    #undef DEF_CMD

    ProcAssert(pcpu);
}

int ProcAssert(CPU* pcpu)
{
    assert (pcpu != NULL);
    assert (pcpu->RAM != NULL);
    assert (pcpu->ip >= 0);
    assert (pcpu->ip < STARTMEM - 1);
}

void CheckAccess (int  cell)
{
    if ((cell < STARTMEM) || (cell > STARTGPU))
        assert (!"ERROR ACCESS!!!\n");
}

int ProcDtor(CPU* pcpu)
{
    ProcAssert(pcpu);

    StackDtor(&pcpu->stk);
    free(pcpu->RAM);
    DestReg(pcpu);
    pcpu->ip = DESTROYED;
}

int DestReg(CPU* pcpu)
{
    int index = NUMREGS;

    while (index > 0)
    {
        pcpu->registers[index] = DESTROYED;
        index--;
    }
}

int GetValue(int* value)
{
    if ((scanf("%d", value) != 1) || (getchar() != '\n'))
    {
        printf("Error argument!\n");
        printf("Enter the argument again\n");

        ClearInputBuf();

        return ERRORINPUT;
    }
    else
        return GOODINPUT;
}

void ClearInputBuf(void)
{
    while (getchar() != ('\n'))
        continue;
}
