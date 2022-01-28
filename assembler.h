#ifndef ASSEMBLER
#define ASSEMBLER

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "SortText.h"
#include "enum.h"

static FILE* logAsm = fopen("logAsm.txt", "w");

const int ERRORCMD  = -17;
const int MISTAKE   =   1;
const int NOMISTAKE =   0;

const char RAX  = 1;
const char RBX  = 2;
const char RCX  = 3;
const char RDX  = 4;
const char NREG = 0;

const int NUMLBL    = 100;
const int MAX_MRKSZ =  15;

struct Label
{
    int ip = 0;
    char mark[MAX_MRKSZ] = {};
    int condition = 0;
};

char* Assembler(const char* CMD);
size_t NumberOfLines(char* buffer, const size_t sizeBuf);
int Assembling(struct pointStr* strings, char* codeMassive, int* size, int numLines, struct Label** labels, int* nJMP);
int CheckTypeARG(char* str, char* codeMassive, int* size, char num);
int CheckCmd(char* str, int j);
char CheckRegs(char* str);
int SkipTabs(struct pointStr* strings, int* index);

int CheckCorrect(char num);
int CheckHLT(char* str);
void LogHLT(int HLTFLG);
void Verificat(int ERROR);

int DisAssembler(const char* BINCODE);
void Disasembling(FILE* disasmCmd, char* code, int* ip, int* index);
void NumToReg(FILE* disasmCmd, int num);

int AddToLabel(char* str, int* size, struct Label** labels, int* nJMP);
int CheckNotNum(char* str);
int OutPutLabel(struct Label* labels, int nJMP);

#endif // ASSEMBLER
