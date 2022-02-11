#include <stdio.h>

#include "Proc/processor.h"
#include "Asm/assembler.h"

const char* CMD     = "../cmd.txt";
const char* BINCODE = "../binCode.bin";

int main(void)
{
    Assembler(CMD);
    //DisAssembler(BINCODE);

    Execute(BINCODE);
}
