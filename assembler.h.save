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

const int NOTFOUND = -1;

const int FIRSTPASS  =  1;
const int SECONDPASS =  2;
const int STARTSIZE  =  0;
const int STARTnJMP  =  0;
const int LASTMARK   = -1;

const char RAX  = 1;
const char RBX  = 2;
const char RCX  = 3;
const char RDX  = 4;
const char NREG = 0;

const int NUMLBL    = 100;
const int MAX_MRKSZ =  15;
const int STip = -1;

struct Label
{
    int ip = STip;
    char mark[MAX_MRKSZ] = {};
    int status = 0;
};

char* Assembler(const char* CMD);
size_t NumberOfLines(char* buffer, const size_t sizeBuf);
int Assembling(struct pointStr* strings, char* codeMassive, int* size, int numLines, struct Label** labels, int* nJMP, int* nPass);
int CheckTypeARG(char* str, char* codeMassive, int* size, int num);
int CheckCmd(char* str, int j);
char CheckRegs(char* str);
int CheckOnNum(char* str);
int SkipTabs(struct pointStr* strings, int* index);

int CheckCorrect(char num);
int CheckHLT(char* str);
void LogHLT(int HLTFLG);
void Verificat(int ERROR);

int DisAssembler(const char* BINCODE);
void Disasembling(FILE* disasmCmd, char* code, int* ip, int* index);
void NumToReg(FILE* disasmCmd, int num);

int AddToLabel(char* str, int size, struct Label** labels, int* nJMP);
int WorkWthJMP(char* str, char* codeMassive, int* point, struct Label** labels, int nJMP);
int WorkWthRET(char* codeMassive, int* size, struct Label** labels);
int FindMark(char* str, struct Label** labels, int nJMP);
int CheckLabels(struct Label** labels, int nJMP);
int CheckRepeat(char* str, struct Label** labels, int nJMP);
int OutPutLabel(struct Label* labels, int nJMP);

#endif // ASSEMBLER
