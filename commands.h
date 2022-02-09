#ifndef COMMANDS

/////////////////////////////////
//! 4ый бит отвечаетза наличие аргумента у команды
//! при этом, если включен 3 бит, то аргументом не может быть число
//! 5ый бит включен, если операция с регистрами
//! 0001 -
//! 0010 -
//! 0100 -
//! 1000 -
//! 0011 -
//! 1100 - JMP

DEF_CMD(HLT  , 0b00000000,   0)

DEF_CMD(ADD  , 0b00000001,   0,
{
    StackPush(&pcpu->stk,  StackPop(&pcpu->stk) +  StackPop(&pcpu->stk));

    pcpu->ip++;
    break;
})

DEF_CMD(SUB  , 0b00000010,   0,
{
    int subtrahend =  StackPop(&pcpu->stk);
    StackPush(&pcpu->stk,  StackPop(&pcpu->stk) - subtrahend);

    pcpu->ip++;
    break;
})

DEF_CMD(MUL  , 0b00000011,   0,
{
    StackPush(&pcpu->stk,  StackPop(&pcpu->stk) * StackPop(&pcpu->stk));

    pcpu->ip++;
    break;
})

DEF_CMD(DIV  , 0b00000100,   0,
{
    int denominator =  StackPop(&pcpu->stk);

    if (denominator == 0)
        assert (!"DIVISION ERROR\n");

    StackPush(&pcpu->stk,  StackPop(&pcpu->stk) / denominator);

    pcpu->ip++;
    break;
})

DEF_CMD(SQRT , 0b00000101,   0,
{
    StackPush(&pcpu->stk,  sqrt(StackPop(&pcpu->stk)));

    pcpu->ip++;
    break;
})

DEF_CMD(IN   , 0b00000110,   0,
{
    int value = 0;

    while (GetValue(&value) != GOODINPUT)
        continue;

    StackPush(&pcpu->stk,  value);

    pcpu->ip++;
    break;
})

DEF_CMD(OUT  , 0b00000111,   0,
{
    printf("%d\n", StackPop(&pcpu->stk));

    pcpu->ip++;
    break;
})
///////////////////////////////////////////////////////////////////
DEF_CMD(PUSH , 0b00010001,   1,
{
    pcpu->ip++;
    StackPush(&pcpu->stk, *((int*) (pcpu->RAM + pcpu->ip)));

    pcpu->ip += sizeof(int);
    break;
})

DEF_CMD(POP  , 0b00011010,   1,
{
    StackPop(&pcpu->stk);

    pcpu->ip++;
    break;
})
///////////////////////////////////////////////////////////////////
DEF_CMD(RPUSH, 0b00110001,   1,
{
    pcpu->ip++;

    pcpu->registers[*(pcpu->RAM + pcpu->ip)] = StackPop(&pcpu->stk);

    pcpu->ip++;
    break;
})

DEF_CMD(RPOP , 0b00111010,   1,
{
    pcpu->ip++;

    StackPush(&pcpu->stk, pcpu->registers[*(pcpu->RAM + pcpu->ip)]);

    pcpu->ip++;
    break;
})
///////////////////////////////////////////////////////////////////
DEF_CMD(JMP  , 0b11000000,   1,
{
    pcpu->ip++;
    pcpu->ip = *((int*) (pcpu->RAM + pcpu->ip));

    break;
})

DEF_CMD(JA   , 0b11000001,   1,
{
    pcpu->ip++;

    int num1 = StackPop(&pcpu->stk);
    int num2 = StackPop(&pcpu->stk);

    if (num2 > num1)
    {
        pcpu->ip = *((int*) (pcpu->RAM + pcpu->ip));

        break;
    }

    pcpu->ip += sizeof(int);
    break;
})

DEF_CMD(JAE   , 0b11001010,   1,
{
    pcpu->ip++;

    int num1 = StackPop(&pcpu->stk);
    int num2 = StackPop(&pcpu->stk);

    if (num2 >= num1)
    {
        pcpu->ip = *((int*) (pcpu->RAM + pcpu->ip));

        break;
    }

    pcpu->ip += sizeof(int);
    break;
})

DEF_CMD(JB   , 0b11000011,   1,
{
    pcpu->ip++;

    int num1 = StackPop(&pcpu->stk);
    int num2 = StackPop(&pcpu->stk);

    if (num2 < num1)
    {
        pcpu->ip = *((int*) (pcpu->RAM + pcpu->ip));

        break;
    }

    pcpu->ip += sizeof(int);
    break;
})

DEF_CMD(JBE   , 0b11000100,   1,
{
    pcpu->ip++;

    int num1 = StackPop(&pcpu->stk);
    int num2 = StackPop(&pcpu->stk);

    if (num2 <= num1)
    {
        pcpu->ip = *((int*) (pcpu->RAM + pcpu->ip));

        break;
    }

    pcpu->ip += sizeof(int);
    break;
})

DEF_CMD(JE   , 0b11000101,   1,
{
    pcpu->ip++;

    int num1 = StackPop(&pcpu->stk);
    int num2 = StackPop(&pcpu->stk);

    if (num2 == num1)
    {
        pcpu->ip = *((int*) (pcpu->RAM + pcpu->ip));

        break;
    }

    pcpu->ip += sizeof(int);
    break;
})

DEF_CMD(JNE   , 0b11000110,   1,
{
    pcpu->ip++;

    int num1 = StackPop(&pcpu->stk);
    int num2 = StackPop(&pcpu->stk);

    if (num2 != num1)
    {
        pcpu->ip = *((int*) (pcpu->RAM + pcpu->ip));

        break;
    }

    pcpu->ip += sizeof(int);
    break;
})

DEF_CMD(CALL   , 0b11000111,   1,
{
    pcpu->ip++;

    pcpu->ip = *((int*) (pcpu->RAM + pcpu->ip));

    break;
})

DEF_CMD(RET   , 0b11001000,   1,
{
    pcpu->ip++;

    pcpu->ip = *((int*) (pcpu->RAM + pcpu->ip));

    break;
})
///////////////////////////////////////////////////////////////////
DEF_CMD(MIAY , 0b10001111,   1,
{
    pcpu->ip++;

    printf("MIAY!!\n");
    break;
})

#endif
