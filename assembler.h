#ifndef ASSEMBLER
#define ASSEMBLER

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "SortText.h"
#include "enum.h"

char* Assembler(void);
void CheckCmd(char* str, int j);
size_t NumberOfLines(char* buffer, const size_t sizeBuf);
char CheckRegs(char* str);

char* DisAssembler(void);
void Disasembling(FILE* disasmCmd, char* code, int* ip);
void NumToReg(FILE* disasmCmd, int num);

#endif // ASSEMBLER
