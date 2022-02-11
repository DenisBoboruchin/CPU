#include "assembler.h"

#define DEF_CMD(name, num, ...)                             \
    case num:                                               \
    {                                                       \
        (*index)++;                                         \
        (*ip)++;                                            \
                                                            \
        fprintf(disasmCmd, "%-4d%-6s", *index, #name);      \
                                                            \
        if (num & 0x10)                                      \
        {                                                   \
            index++;                                                \
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

static const char* DISASMCMD = "../disasmCmd.txt";

int DisAssembler(const char* BINCODE)
{
    size_t sizeBuf = GetSizeBuf(BINCODE);
    char* code = (char*) CreateBuf(&sizeBuf, BINCODE);

    FILE* disasmCmd = fopen(DISASMCMD, "w");

    int ip = 0;
    int index = 0;

    while (true)
    {
        if (*(code + ip) == (char) CMD_HLT)
        {
            fprintf(disasmCmd, "%-4d%-6s", index + 1, "HLT");

            break;
        }

        Disasembling(disasmCmd, code, &ip, &index);
    }

    assert(fclose(disasmCmd) == 0);
}

void Disasembling(FILE* disasmCmd, char* code, int* ip, int* index)
{
    assert (disasmCmd != NULL);
    assert (code != NULL);
    assert (ip != NULL);
    assert (*ip >= 0);

    switch ((int) *(code + *ip))
    {
        #include "../commands.h"

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
        case RAX:
            fprintf(disasmCmd, " rax");
            break;

        case RBX:
            fprintf(disasmCmd, " rbx");
            break;

        case RCX:
            fprintf(disasmCmd, " rcx");
            break;

        case RDX:
            fprintf(disasmCmd, " rdx");
            break;

        default:
            assert(0);
            break;
    }
}

