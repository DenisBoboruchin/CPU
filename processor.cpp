#include "processor.h"

#define DEF_CMD(name, num, arg, ...)     \
    case CMD_##name:                     \
        __VA_ARGS__                      \
                                         \


static const char* BINCODE = "binCode.bin";

int Execute(void)
{
    CPU cpu = {};

    StackCtor(&(cpu.stk));

    size_t sizeBuf = GetSizeBuf(BINCODE);

    char* code = (char*) CreateBuf(&sizeBuf, BINCODE);

    cpu.code = code;
    cpu.ip = 0;

    while (true)
    {
        if (*(cpu.code + cpu.ip) == (char) CMD_HLT)
            break;

        CheckCmd(&cpu);
    }


    StackDtor(&cpu.stk);
}

void CheckCmd(CPU* pcpu)
{
    switch ((int) *(pcpu->code + pcpu->ip))
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
