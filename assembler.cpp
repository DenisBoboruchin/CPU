#include "assembler.h"

#define DEF_CMD(name, num, ...)                                                         \
    if (!stricmp((strings + index)->str, #name))                                        \
    {                                                                                   \
        *(codeMassive + *size) = (char) num;                                   \
        *size += sizeof(char);                                                          \
                                                                                        \
        if ((num & 0x40) && (num & 0x80))                                               \
        {                                                                                \
            index++;                                                                      \
            SkipTabs(strings, &index);                                                     \
                                                                                            \
            ERROR |= WorkWthJMP((strings + index)->str, codeMassive, size, labels, *nJMP);  \
            continue;                                                                         \
        }                                                                                   \
                                                                                            \
        if (num & 0x10)                                                                     \
        {                                                                                   \
            index++;                                                                   \
            SkipTabs(strings, &index);                                                   \
                                                                                           \
            ERROR |= CheckTypeARG((strings + index)->str, codeMassive, size, num);         \
        }                                                                           \
                                                                                    \
        continue;                                                                   \
    }

static const char* BINCODE = "binCode.bin";

char* Assembler(const char* CMD)
{
    size_t sizeBuf = GetSizeBuf(CMD);
    char* buffer = CreateBuf(&sizeBuf, CMD);

    size_t numLines = NumberOfLines(buffer, sizeBuf);
    struct pointStr* strings = CrtorStrs(numLines, sizeBuf, buffer);

    char* codeMassive = (char*) calloc(numLines + 1, sizeof(int));
    struct Label* labels = (struct Label*) calloc(NUMLBL, sizeof(struct Label));
    int sizeCode = 0;
    int nJMP = 0;

    int ERRORFLAG = Assembling(strings, codeMassive, &sizeCode, numLines, &labels, &nJMP);

    OutPutLabel(labels, nJMP);

    codeMassive = (char*) realloc(codeMassive, (sizeCode + 1) * sizeof(char));

    FILE* binCode = fopen(BINCODE, "wb");

    assert(fwrite(codeMassive, sizeof(char), sizeCode + 1, binCode) == sizeCode + 1);

    assert (fclose(binCode) == 0);

    //free(codeMassive);
    free(buffer);
    free(strings);
    free(labels);

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

int Assembling(struct pointStr* strings, char* codeMassive, int* size, int numLines, struct Label** labels, int* nJMP)
{
    assert (strings != NULL);
    assert (codeMassive != NULL);
    assert (size != NULL);
    assert (*size >= 0);
    assert (numLines >= 0);

    int ERROR  = NOMISTAKE;
    int HLTFLG = 0;

    for (int index = 0; index < numLines; index++)
    {
        if (strlen((strings + index)->str) == 0)
            continue;

        HLTFLG |= CheckHLT((strings + index)->str);

        #include "commands.h"

        ERROR |= AddToLabel((strings + index)->str, *size, labels, nJMP);
    }
    #undef DEF_CMD

    LogHLT(HLTFLG);

    return ERROR || (!HLTFLG);
}

int CheckTypeARG(char* str, char* codeMassive, int* size, int num)
{
    assert (str != NULL);
    assert (codeMassive != NULL);
    assert (size != NULL);
    assert (*size >= 0);

    if (char result = CheckRegs(str))
    {
        *(codeMassive + *size - 1) = (char) num | (1 << 5);
        *(codeMassive + *size) = result;

        *size += sizeof(char);

        return NOMISTAKE;
    }

    if (int value = CheckOnNum(str))
    {
        int check = CheckCorrect(num);                         //Äëÿ POP

        *((int*) (codeMassive + *size)) = value;
        *size += sizeof(int);

        return check;
    }

    return CheckCmd(str, ERRORCMD);
}

int SkipTabs(struct pointStr* strings, int* index)
{
    while (strlen((strings + *index)->str) == 0)
        (*index)++;
}

int WorkWthJMP(char* str, char* codeMassive, int* size, struct Label** labels, int nJMP)
{
    if (int value = CheckOnNum(str))
    {
        *((int*) (codeMassive + *size)) = value;
        *size += sizeof(int);

        return NOMISTAKE;
    }

    if (int num = FindMark(str, labels, nJMP))
    {
        *((int*) (codeMassive + *size)) = num;
        *size += sizeof(int);

        return NOMISTAKE;
    }

    return MISTAKE;
}

int FindMark(char* str, struct Label** labels, int nJMP)
{
    for (int num = 0; num < nJMP; num++)
    {
        if (!strcmp(str, (*labels)[num].mark))
            return (*labels)[num].ip;
    }

    return 0;
}

int AddToLabel(char* str, int point, struct Label** labels, int* nJMP)
{
    assert (str != NULL);
    assert (labels != NULL);
    assert (*labels != NULL);
    assert (point >= 0);

    if (!CheckRepeat(str, labels, *nJMP))
    {
        (*labels)[*nJMP].ip = point;
        strcpy((*labels)[*nJMP].mark, str);

        (*nJMP)++;
        return NOMISTAKE;
    }
    else
        return MISTAKE;
}

int CheckRepeat(char* str, struct Label** labels, int nJMP)
{
    if (CheckOnNum(str))
    {
        printf("%s is unknown command!\n", str);
        fprintf(logAsm, "%s is unknown command!\n", str);

        return MISTAKE;
    }

    for (int i = 0; i < nJMP; i++)
    {
        if (!strcmp(str, (*labels)[i].mark))
        {
            printf("%s occurs twice!\n", str);
            fprintf(logAsm, "%s occurs twice!\n", str);

            return MISTAKE;
        }

    }

    return NOMISTAKE;
}

int OutPutLabel(struct Label* labels, int nJMP)
{
    assert (labels != NULL);
    assert (nJMP >= 0);

    for (int i = 0; i < nJMP; i++)
    {
        printf("ip:     %d\n", labels[i].ip);
        printf("mark:   %s\n", labels[i].mark);
        printf("status: %d\n", labels[i].condition);
    }
}

int CheckOnNum(char* str)
{
    int value = 0;
    char checkEnd = 0;
    if (sscanf(str, "%d%c", &value, &checkEnd) == 1)
        return value;
    else
        return 0;
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
