#ifndef ASSEMBLER
#define ASSEMBLER

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "SortText.h"
#include "enum.h"

char* Assembler(void);
int CheckType(FILE* code, char* str, char* codeMassive, int* size, int num);
int CheckCmd(char* str, int j);
size_t NumberOfLines(char* buffer, const size_t sizeBuf);
char CheckRegs(char* str);

char* DisAssembler(void);
void Disasembling(FILE* disasmCmd, char* code, int* ip, int* index);
void NumToReg(FILE* disasmCmd, int num);

#endif // ASSEMBLER
