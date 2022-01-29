#include "processor.h"

#define DEF_CMD(name, num, arg, ...)     \
    case CMD_##name:                     \
        __VA_ARGS__                      \
                                         \

int Execute(const char* BINCODE)
{
    CPU cpu = {};

    ProcCtor(&cpu, BINCODE);

    while (true)
    {
        if (*(cpu.code + cpu.ip) == (char) CMD_HLT)
            break;

        CheckCmd(&cpu);
    }

    ProcDtor(&cpu);
}

int ProcCtor(CPU* pcpu, const char* BINCODE)
{
    StackCtor(&(pcpu->stk));

    size_t sizeBuf = GetSizeBuf(BINCODE);

    char* code = (char*) CreateBuf(&sizeBuf, BINCODE);

    pcpu->code = code;
    pcpu->ip = 0;

    ProcAssert(pcpu);
}

void CheckCmd(CPU* pcpu)
{
    ProcAssert(pcpu);

    switch ((int)* ((unsigned char*) pcpu->code + pcpu->ip))
    {
        #include "commands.h"

        default:
        {
            assert(!"unknown command");

            break;
        }
    }

    #undef DEF_CMD
}

int ProcAssert(CPU* pcpu)
{
    assert (pcpu != NULL);
    assert (pcpu->code != NULL);
    assert (pcpu->ip >= 0);
}

int ProcDtor(CPU* pcpu)
{
    ProcAssert(pcpu);

    StackDtor(&pcpu->stk);
    free(pcpu->code);
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
