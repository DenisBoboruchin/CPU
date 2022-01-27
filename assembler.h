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

struct labels
{
    int ip = 0;

};

char* Assembler(const char* CMD);
size_t NumberOfLines(char* buffer, const size_t sizeBuf);
int Assembling(FILE* code, struct pointStr* strings, char* codeMassive, int* size, int numLines);
int CheckType(FILE* code, char* str, char* codeMassive, int* size, int num);
int CheckCmd(char* str, int j);
char CheckRegs(char* str);

int CheckCorrect(char num);
int CheckHLT(char* str);
void LogHLT(int HLTFLG);
void Verificat(int ERROR);

int DisAssembler(const char* BINCODE);
void Disasembling(FILE* disasmCmd, char* code, int* ip, int* index);
void NumToReg(FILE* disasmCmd, int num);

#endif // ASSEMBLER
