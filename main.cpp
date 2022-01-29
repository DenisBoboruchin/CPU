#include <stdio.h>

#include "processor.h"
#include "assembler.h"

const char* CMD     = "cmd.txt";
const char* BINCODE = "binCode.bin";

int main(void)
{
    Assembler(CMD);
    //DisAssembler(BINCODE);

    Execute(BINCODE);
}
