#include "SortText.h"

struct stat stbuf;

const int NUMBERSTANZAS = 10;

void SortText(const char* origName, const char* resName)
{
    FILE* resultFile = fopen(resName, "w");
    assert (resultFile != NULL);

    size_t sizeBuf = GetSizeBuf(origName);

    char* buffer = CreateBuf(&sizeBuf, origName);

    size_t numLines = NumberLines(buffer, sizeBuf);

    fprintf(resultFile, "number of lines   : %d\n", numLines);
    fprintf(resultFile, "number of elements: %d\n", sizeBuf);

    struct pointStr* strings = CrtorStrs(numLines, sizeBuf, buffer);

    qsort(strings, numLines, sizeof(struct pointStr), (int(*) (const void *, const void *)) Compare);
    OutputText(resultFile, strings, numLines,"sorted Text");

    qsort(strings, numLines, sizeof(struct pointStr), (int(*) (const void *, const void *)) ReverceCompare);
    OutputText(resultFile, strings, numLines, "back sorted text");

    OutputFromBuf(buffer, sizeBuf, resultFile, "original");

    Separator(resultFile, "MY BRED");

    GenerateBredStanzas(NUMBERSTANZAS, resultFile, strings, numLines);

    free(buffer);
    free(strings);
    assert (fclose(resultFile) == 0);
}

size_t GetSizeBuf(const char* origName)
{
    assert (origName != NULL);

    stat(origName, &stbuf);

    return stbuf.st_size;
}

char* CreateBuf(size_t* sizeBuf, const char* origName)
{
    assert (sizeBuf != NULL);
    assert (*sizeBuf > 0);

    char* buffer = (char*) calloc(*sizeBuf + 1, sizeof(char));
    assert (buffer != NULL);

    FILE* text = fopen(origName, "r");
    assert (text != NULL);

    size_t newSize = fread(buffer, sizeof(*buffer), *sizeBuf, text);
    assert (fclose(text) == 0);

    if (newSize < *sizeBuf)
    {
        *sizeBuf = newSize;
        buffer = (char*) realloc(buffer, *sizeBuf);
    }

    return buffer;
}

struct pointStr* CrtorStrs(const size_t numLines, const size_t sizeBuf, char* buffer)
{
    assert (buffer != NULL);
    assert (numLines > 0);
    assert (sizeBuf > 0);

    struct pointStr* strings = (pointStr*)  calloc (numLines + 2, sizeof(pointStr));
    assert (strings != NULL);

    strings->str = buffer;
    //*(strings->str) = toupper (*buffer);

    size_t index = 1;
    for (size_t i = 0; i < sizeBuf; i++)
    {
        if (*(buffer + i) == '\0')
        {
            (strings + index)->str = buffer + i + 1;
            (strings + index - 1)->strEnd = buffer + i - 1;

            //*((strings + index)->str) = toupper (*(buffer + i + 1));

            index++;
        }
    }

    (strings + index)->strEnd = buffer + sizeBuf - 1;

    return strings;
}

size_t NumberLines(char* buffer, const size_t sizeBuf)
{
    assert (buffer != NULL);
    assert (sizeBuf > 0);

    size_t numLines = 0;

    for (size_t i = 0; i < sizeBuf; i++)
    {
        numLines += CheckNewLine(buffer + i);
    }

    return numLines;
}

int CheckNewLine(char* buffer)
{
    assert (buffer != NULL);

    if (*(buffer) == '\n')
    {
        *buffer = '\0';

        return 1;
    }

    else
        return 0;
}

int Compare(const struct pointStr* struct1, const struct pointStr* struct2)
{
    assert(struct1 != NULL);
    assert(struct2 != NULL);
    assert(struct1->str != NULL);
    assert(struct2->str != NULL);

    char* tmpStr1 = struct1->str;
    tmpStr1 = GoodSymbolForCompare(tmpStr1);

    char* tmpStr2 = struct2->str;
    tmpStr2 = GoodSymbolForCompare(tmpStr2);

    while ((*tmpStr1 == *tmpStr2) && (*tmpStr1 != '\0') && (*tmpStr2 != '\0'))
    {
        tmpStr1++;
        tmpStr2++;

        tmpStr1 = GoodSymbolForCompare(tmpStr1);
        tmpStr2 = GoodSymbolForCompare(tmpStr2);
    }

    return (*tmpStr1 - *tmpStr2);
}

char* GoodSymbolForCompare(char* str)
{
    assert (str != NULL);

    if ((*str == ' ') || (*str == '.') || (*str == ','))
        return GoodSymbolForCompare(++str);
    else
        return str;
}

int ReverceCompare(const struct pointStr* struct1, const struct pointStr* struct2)
{
    assert(struct1 != NULL);
    assert(struct2 != NULL);
    assert(struct1->strEnd != NULL);
    assert(struct2->strEnd != NULL);

    char* tmpStr1 = struct1->strEnd;
    tmpStr1 = GoodSymbolForReverceCompare(tmpStr1);

    char* tmpStr2 = struct2->strEnd;
    tmpStr2 = GoodSymbolForReverceCompare(tmpStr2);

    while ((*tmpStr1 == *tmpStr2) && (*tmpStr1 != '\0') && (*tmpStr2 != '\0'))
    {
        tmpStr1--;
        tmpStr2--;

        tmpStr1 = GoodSymbolForReverceCompare(tmpStr1);
        tmpStr2 = GoodSymbolForReverceCompare(tmpStr2);
    }

    return (*tmpStr1 - *tmpStr2);
}

char* GoodSymbolForReverceCompare(char* str)
{
    assert (str != NULL);

    if ((*str == ' ') || (*str == '.') || (*str == ','))
        return GoodSymbolForReverceCompare(--str);
    else
        return str;
}

void GenerateBredStanzas(const int NUMBERSTANZAS, FILE* resultFile, const struct pointStr* strings, const size_t numLines)
{
    assert (strings != NULL);
    assert (strings != NULL);
    assert (numLines > 0);

    for (int i = 0; i < NUMBERSTANZAS; i++)
        BredGenerateAndOutput(resultFile, strings, numLines, i);
}

void BredGenerateAndOutput(FILE* resultFile, const struct pointStr* strings, const size_t numLines, int j)
{
    assert (strings != NULL);
    assert (strings != NULL);
    assert (numLines > 0);

    srand((unsigned int) time(0) * j + 3 * j);

    int lens = 14;
    char* bred[lens];
    int index = 0;

    for (int i = 0; i < lens / 2; i++)
    {
        StrSelection(strings, bred, numLines, index);

        index += 2;
    }

    MakeStanza(bred);

    for (int i = 0; i < lens; i++)
    {
        fprintf(resultFile,"%s", bred[i]);
        fprintf(resultFile, "\n");
    }
    fprintf(resultFile, "\n");
}

void StrSelection(const struct pointStr* strings, char* bred[], int numLines, int index)
{
    assert (strings != NULL);
    assert (numLines > 0);
    assert (numLines >= 0);

    int shift = rand() % 3 + 2;
    int rndStr = rand() % (numLines - 200) + 200;

    char* firstEnd = (strings + rndStr)->strEnd;
    char* secondEnd = (strings + rndStr + shift)->strEnd;
    char* first = (strings + rndStr)->str;
    char* second = (strings + rndStr + shift)->str;

    int r = 1;

    while (*(firstEnd) != *(secondEnd) || (fabs (strlen(first) - strlen(second)) > 5))
    {
        rndStr = ((r * 5) * rand()) % (numLines - 200) + 200;
        r++;

        firstEnd = (strings + rndStr)->strEnd;
        secondEnd = (strings + rndStr + shift)->strEnd;
        first = (strings + rndStr)->str;
        second = (strings + rndStr + shift)->str;
    }

    bred[index] = first;
    bred[index + 1] = second;
}

void MakeStanza(char* bred[])
{
    char* tmp = bred[1];
    bred[1] = bred[2];
    bred[2] = tmp;
    tmp = bred[9];
    bred[9] = bred[11];
    bred[11] = tmp;
}

void OutputText(FILE* resultFile, const struct pointStr* strings, const size_t numLines, const char* text)
{
    assert (numLines > 0);
    assert (resultFile != NULL);
    assert (strings != NULL);

    Separator(resultFile, text);

    for (size_t i = 0; i < numLines; i++)
    {
        assert ((strings + i) != NULL);
        assert ((strings + i)->str != NULL);

        fprintf(resultFile, "s%4d: %s\n", i, (strings + i)->str);
    }
}

void OutputFromBuf(char* buffer, const size_t sizeBuf, FILE* resultFile, const char* text)
{
    assert (buffer != NULL);
    assert (resultFile != NULL);

    Separator(resultFile, text);

    fprintf(resultFile, "s%4d: %s\n", 0, buffer);

    int index = 1;

    for (size_t i = 0; i < sizeBuf - 1; i++)
    {
        if (*(buffer + i) == '\0')
        {
            fprintf(resultFile, "s%4d: %s\n", index, buffer + i + 1);

            index++;
        }
    }
}

void Separator(FILE* resultFile, const char* text)
{
    assert (resultFile != NULL);

    fprintf(resultFile, "\n--------------------------------------------------------------------------------------\n");
    fprintf(resultFile, "%s\n", text);
    fprintf(resultFile, "--------------------------------------------------------------------------------------\n"  );
    fprintf(resultFile, "--------------------------------------------------------------------------------------\n\n");
}
