#include "assembler.h"

#define DEF_CMD(name, num, args, ...)                       \
    case num:                                               \
    {                                                       \
        fprintf(disasmCmd, "%3d\t%s", *ip + 1, #name);      \
        (*ip)++;                                            \
                                                            \
        if (args == 1)                                      \
        {                                                   \
                                                            \
                                                            \
            if (num & 0x20)                                 \
            {                                               \
                NumToReg(disasmCmd, (int) *(code + *ip));   \
                (*ip)++;                                    \
            }                                               \
            else                                            \
            {                                               \
                                                            \
                fprintf(disasmCmd, " %d", (int) *(code + *ip));\
                (*ip) += sizeof(int);                       \
            }                                               \
        }                                                   \
                                                            \
        fprintf(disasmCmd, "\n");                           \
                                                            \
                                                            \
        break;                                              \
    }

static const char* DISASMCMD = "disasmCmd.txt";
static const char* BINCODE = "binCode.bin";

char* DisAssembler(void)
{
    size_t sizeBuf = GetSizeBuf(BINCODE);

    char* code = (char*) CreateBuf(&sizeBuf, BINCODE);      /////////////////////////

    FILE* disasmCmd = fopen(DISASMCMD, "w");
    int ip = 0;
                                                                        //size_t numCmd = sizeBuf / sizeof(int);
    while (true)                                                        //for (int ip = 0; ip < numCmd; ip++)
    {
        if (*(code + ip) == (char) CMD_HLT)
        {
            fprintf(disasmCmd, "%3d\tHLT", ip + 1);

            break;
        }

        Disasembling(disasmCmd, code, &ip);
    }
}

void Disasembling(FILE* disasmCmd, char* code, int* ip)            //////////
{
    assert (disasmCmd != NULL);
    assert (code != NULL);
    assert (ip != NULL);
    assert (*ip >= 0);

    switch ((int) *(code + *ip))                                 ///////
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

void NumToReg(FILE* disasmCmd, int num)
{
    switch (num)
    {
        case 1:
            fprintf(disasmCmd, " rax");
            break;

        case 2:
            fprintf(disasmCmd, " rbx");
            break;

        case 3:
            fprintf(disasmCmd, " rcx");
            break;

        case 4:
            fprintf(disasmCmd, " rdx");
            break;

        default:
            assert(0);
            break;
    }
}
