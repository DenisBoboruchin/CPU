#ifndef ENUM
#define ENUM

#define DEF_CMD(name, num, ...)     \
        CMD_##name = num,

enum cmd
{
    #include "commands.h"
};
#undef DEF_CMD

#endif
