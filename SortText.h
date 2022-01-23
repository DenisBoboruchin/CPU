#ifndef SORTTEXT
#define SORTTEXT

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>


struct pointStr
{
    char* str = nullptr;
    char* strEnd = nullptr;
};


void SortText(const char* NAME, const char* RESULT);
size_t GetSizeBuf(const char* name);
char* CreateBuf(size_t* sizeBuf, const char* name);
size_t NumberLines(char* buffer, const size_t sizeBuf);
int CheckNewLine(char* buffer);
struct pointStr* CrtorStrs(const size_t numLines, const size_t newSize, char* buffer);

int Compare(const struct pointStr* struct1, const struct pointStr* struct2);
char* GoodSymbolForCompare(char* str);
int ReverceCompare(const struct pointStr* struct1, const struct pointStr* struct2);
char* GoodSymbolForReverceCompare(char* str);

void OutputText(FILE* resultFile, const struct pointStr* strings, const size_t numLines, const char* text);
void OutputFromBuf(char* buffer, const size_t sizeBuf, FILE* resultFile, const char* text);
void Separator(FILE* resultFile, const char* text);

void GenerateBredStanzas(const int NUMBERSTANZAS, FILE* resultFile, const struct pointStr* strings, const size_t numLines);
void BredGenerateAndOutput(FILE* resultFile, const struct pointStr* strings, const size_t numLines, int j);
void StrSelection(const struct pointStr* strings, char* bred[], int numLines, int index);
void MakeStanza(char* bred[]);


#endif // SORTTEXT
