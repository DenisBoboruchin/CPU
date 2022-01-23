#include "processor.h"

static const char* BINCODE = "binCode.bin";

int Execute(void)
{
    CPU cpu = {};

    StackCtor(&(cpu.stk));

    size_t sizeBuf = GetSizeBuf(BINCODE);

    char* code = (char*) CreateBuf(&sizeBuf, BINCODE);

    cpu.code = code;                                                        //size_t numCmd = sizeBuf / sizeof();
    cpu.ip = 0;
                                                                            //for (cpu.ip = 0; cpu.ip < numCmd; pcpu->ip++)
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
        case CMD_PUSH:
        {
            pcpu->ip++;
            StackPush(&pcpu->stk, *((int*) (pcpu->code + pcpu->ip)));

            pcpu->ip += sizeof(int);
            break;
        }

        case CMD_POP:
        {
            StackPop(&pcpu->stk);

            pcpu->ip++;
            break;
        }

        case CMD_ADD:
        {
            StackPush(&pcpu->stk,  StackPop(&pcpu->stk) +  StackPop(&pcpu->stk));

            pcpu->ip++;
            break;
        }

        case CMD_SUB:
        {
            int value =  StackPop(&pcpu->stk);
            StackPush(&pcpu->stk,  StackPop(&pcpu->stk) - value);

            pcpu->ip++;
            break;
        }

        case CMD_MUL:
        {
            StackPush(&pcpu->stk,  StackPop(&pcpu->stk) * StackPop(&pcpu->stk));

            pcpu->ip++;
            break;
        }

        case CMD_DIV:
        {
            int value =  StackPop(&pcpu->stk);
            StackPush(&pcpu->stk,  StackPop(&pcpu->stk) / value);

            pcpu->ip++;
            break;
        }

        case CMD_SQRT:
        {
            StackPush(&pcpu->stk,  sqrt(StackPop(&pcpu->stk)));

            pcpu->ip++;
            break;
        }

        case CMD_IN:
        {
            int value = 0;

            scanf("%d", &value);
            StackPush(&pcpu->stk,  value);

            pcpu->ip++;
            break;
        }

        case CMD_OUT:
        {
            printf("%d\n", StackPop(&pcpu->stk));

            pcpu->ip++;
            break;
        }

        case CMD_RPUSH:
        {
            pcpu->ip++;

            pcpu->registers[*(pcpu->code + pcpu->ip)] = StackPop(&pcpu->stk);

            pcpu->ip++;
            break;
        }

        case CMD_RPOP:
        {
            pcpu->ip++;

            StackPush(&pcpu->stk, pcpu->registers[*(pcpu->code + pcpu->ip)]);

            pcpu->ip++;
            break;
        }

        default:
        {
            assert(!"unknown command");

            break;
        }
    }
}
