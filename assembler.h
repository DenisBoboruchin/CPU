#ifndef ASSEMBLER
#define ASSEMBLER

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "SortText.h"
#include "enum.h"

static FILE* logAsm = fopen("logAsm.txt", "w");

const int ERRORCMD = -17;

char* Assembler(void);
int Assembling(FILE* code, struct pointStr* strings, char* codeMassive, int* size, int numLines);
int CheckType(FILE* code, char* str, char* codeMassive, int* size, int num);
int CheckCmd(char* str, int j);
size_t NumberOfLines(char* buffer, const size_t sizeBuf);
char CheckRegs(char* str);
int CheckCorrect(char num);
int CheckHLT(char* str);
void LogHLT(int HLTFLG);
void Verificat(int ERROR);

char* DisAssembler(void);
void Disasembling(FILE* disasmCmd, char* code, int* ip, int* index);
void NumToReg(FILE* disasmCmd, int num);

#endif // ASSEMBLER
