#include "assembler.h"

#define DEF_CMD(name, num, args, ...)                                       \
    if (!stricmp((strings + j)->str, #name))                                \
    {                                                                       \
        *(codeMassive + size) = (char) num;                                 \
        fprintf(code, "%04d |%5s| %d\n", j, #name, num);                    \
                                                                            \
        size += sizeof(char);                                               \
                                                                            \
        if (num & 0x10)                                                     \
        {                                                                   \
            j++;                                                            \
            CheckType(code, (strings + j)->str, codeMassive, &size, num);   \
        }                                                                   \
        continue;                                                           \
    }


static const char* CMD     = "cmd.txt";
static const char* CODE    = "code.txt";
static const char* BINCODE = "binCode.bin";

/*
struct token
{
    char* str;
    int type;
    int val;
};
struct token progt[30];
for (int i = 0 ; progt[i].str = strtok (progt, "\n"); i++)
{
}
for ()
*/

char* Assembler(void)
{
    size_t sizeBuf = GetSizeBuf(CMD);

    char* buffer = CreateBuf(&sizeBuf, CMD);

    size_t numLines = NumberOfLines(buffer, sizeBuf);

    struct pointStr* strings = CrtorStrs(numLines, sizeBuf, buffer);

    FILE* code = fopen(CODE, "w");

    char* codeMassive = (char*) calloc(numLines + 1, sizeof(double));
    int size = 0;

    for (int j = 0; j < numLines; j++)
    {
        #include "commands.h"

        CheckCmd((strings + j)->str, j);
    }
    #undef DEF_CMD

    codeMassive = (char*) realloc(codeMassive, (size + 1) * sizeof(char));

    FILE* binCode = fopen(BINCODE, "wb");

    assert(fwrite(codeMassive, sizeof(char), size + 1, binCode) == size + 1);

    assert (fclose(binCode) == 0);
    assert (fclose(code) == 0);

    //free(codeMassive);
    free(buffer);
}

size_t NumberOfLines(char* buffer, const size_t sizeBuf)
{
    assert (buffer != NULL);
    assert (sizeBuf > 0);

    size_t numLines = 0;

    for (size_t i = 0; i < sizeBuf; i++)
    {
        if ((*(buffer + i) == '\n') || (*(buffer + i) == ' '))
        {
            *(buffer + i) = '\0';
            numLines++;
        }
    }

    return numLines;
}

int CheckType(FILE* code, char* str, char* codeMassive, int* size, int num)
{
    if (char result = CheckRegs(str))
    {
        *(codeMassive + *size - 1) = (char) num | (1 << 5);
        *(codeMassive + *size) = result;

        *size += sizeof(char);

        fprintf(code, " | %c\n", result);

        return 0;
    }

    int value = 0;
    if (sscanf(str, "%d", &value))
    {
        CheckCorrect(num);
        *((int*) (codeMassive + *size)) = value;

        *size += sizeof(int);
        fprintf(code, " | %d\n", value);

        return 0;
    }

    return CheckCmd(str, -17);
}

int CheckCmd(char* str, int j)
{
    assert (str != NULL);

    if ((strlen(str) > 0) && (j > 0))
    {
        printf("%s is unknown command!\t(line %3d)\n", str, j + 1);

        return 1;
    }

    if ((strlen(str) > 0) && (j == -17))
    {
        printf("%s is unknown argument\n", str);

        return 1;
    }
}

char CheckRegs(char* str)
{
    if (!stricmp(str, "rax"))
        return 1;

    if (!stricmp(str, "rbx"))
        return 2;

    if (!stricmp(str, "rcx"))
        return 3;

    if (!stricmp(str, "rdx"))
        return 4;

    return 0;
}

int CheckCorrect(char num)
{
    if (num & 0x08)
        printf("incorrect argument!\n");

    return 1;
}
