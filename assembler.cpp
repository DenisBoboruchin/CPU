#include "assembler.h"

#define DEF_CMD(name, num, ...)                                                     \
    if (!stricmp((strings + j)->str, #name))                                        \
    {                                                                               \
        *(codeMassive + *size) = (char) num;                                        \
        fprintf(code, "%04d |%5s| %d\n", j, #name, num);                            \
                                                                                    \
        *size += sizeof(char);                                                      \
                                                                                    \
        if (num & 0x10)                                                             \
        {                                                                           \
            j++;                                                                    \
            ERROR |= CheckType(code, (strings + j)->str, codeMassive, size, num);   \
        }                                                                           \
                                                                                    \
        continue;                                                                   \
    }


//static const char* CMD     = "cmd.txt";
static const char* CODE    = "code.txt";
static const char* BINCODE = "binCode.bin";

char* Assembler(const char* CMD)
{
    size_t sizeBuf = GetSizeBuf(CMD);
    char* buffer = CreateBuf(&sizeBuf, CMD);

    size_t numLines = NumberOfLines(buffer, sizeBuf);
    struct pointStr* strings = CrtorStrs(numLines, sizeBuf, buffer);

    FILE* code = fopen(CODE, "w");
    char* codeMassive = (char*) calloc(numLines + 1, sizeof(int));
    int sizeCode = 0;

    int ERRORFLAG = Assembling(code, strings, codeMassive, &sizeCode, numLines);

    codeMassive = (char*) realloc(codeMassive, (sizeCode + 1) * sizeof(char));

    FILE* binCode = fopen(BINCODE, "wb");

    assert(fwrite(codeMassive, sizeof(char), sizeCode + 1, binCode) == sizeCode + 1);

    assert (fclose(binCode) == 0);
    assert (fclose(code)    == 0);

    //free(codeMassive);
    free(buffer);

    Verificat(ERRORFLAG);

    return codeMassive;
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

int Assembling(FILE* code, struct pointStr* strings, char* codeMassive, int* size, int numLines)
{
    assert (code != NULL);
    assert (strings != NULL);
    assert (codeMassive != NULL);
    assert (size != NULL);
    assert (*size >= 0);
    assert (numLines >= 0);

    int ERROR  = NOMISTAKE;
    int HLTFLG = 0;

    for (int j = 0; j < numLines; j++)
    {
        HLTFLG |= CheckHLT((strings + j)->str);

        #include "commands.h"

        ERROR |= CheckCmd((strings + j)->str, j);
    }
    #undef DEF_CMD

    LogHLT(HLTFLG);

    return ERROR || (!HLTFLG);
}

int CheckType(FILE* code, char* str, char* codeMassive, int* size, int num)
{
    assert (code != NULL);
    assert (str != NULL);
    assert (codeMassive != NULL);
    assert (size != NULL);
    assert (*size >= 0);

    if (char result = CheckRegs(str))
    {
        *(codeMassive + *size - 1) = (char) num | (1 << 5);
        *(codeMassive + *size) = result;

        *size += sizeof(char);

        fprintf(code, " | %c\n", result);

        return NOMISTAKE;
    }

    int value = 0;
    if (sscanf(str, "%d", &value))
    {
        int check = CheckCorrect(num);

        *((int*) (codeMassive + *size)) = value;

        fprintf(code, " | %d\n", value);
        *size += sizeof(int);

        return check;
    }

    return CheckCmd(str, ERRORCMD);
}

int CheckCmd(char* str, int j)
{
    assert (str != NULL);

    if ((strlen(str) > 0) && (j > 0))
    {
        printf("%s is unknown command!\t(line %3d)\n", str, j + 1);
        fprintf(logAsm, "%s is unknown command!\t(line %3d)\n", str, j + 1);

        return MISTAKE;
    }

    if ((strlen(str) > 0) && (j == ERRORCMD))
    {
        printf("%s is unknown argument\n", str);
        fprintf(logAsm, "%s is unknown argument\n", str);

        return MISTAKE;
    }

    return NOMISTAKE;
}

char CheckRegs(char* str)
{
    assert (str != NULL);

    if (!stricmp(str, "rax"))
        return RAX;

    if (!stricmp(str, "rbx"))
        return RBX;

    if (!stricmp(str, "rcx"))
        return RCX;

    if (!stricmp(str, "rdx"))
        return RDX;

    return NREG;
}

int CheckCorrect(char num)
{
    if (num & 0x08)
    {
        printf("incorrect argument!\n");

        return MISTAKE;
    }

    return NOMISTAKE;
}

int CheckHLT(char* str)
{
    assert (str != NULL);

    if (!stricmp(str, "HLT"))
        return 1;
    else
        return 0;
}

void LogHLT(int HLTFLG)
{
    if (!HLTFLG)
    {
        printf("Expected \"HLT\"\n");
        fprintf(logAsm, "Expected \"HLT\"\n");
    }
}

void Verificat(int ERROR)
{
    if (ERROR)
    {
        printf("ERROR ASSEMBLING\n");
        fprintf(logAsm, "ERROR ASSEMBLING\n");

        assert(!"ERROR");
    }

    else
    {
        printf("SUCCESS ASSEMBLING\n");
        fprintf(logAsm, "SUCCESS ASSEMBLING\n");
    }
}
