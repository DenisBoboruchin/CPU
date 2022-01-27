#ifndef COMMANDS

/////////////////////////////////
//! 4ый бит отвечаетза наличие аргумента у команды
//! при этом, если включен 3 бит, то аргументом не может быть число
//! 5ый бит включен, если операция с регистрами

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

    scanf("%d", &value);
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
DEF_CMD(PUSH , 0b00010010,   1,
{
    pcpu->ip++;
    StackPush(&pcpu->stk, *((int*) (pcpu->code + pcpu->ip)));

    pcpu->ip += sizeof(int);
    break;
})

DEF_CMD(POP  , 0b00011011,   1,
{
    StackPop(&pcpu->stk);

    pcpu->ip++;
    break;
})
///////////////////////////////////////////////////////////////////
DEF_CMD(RPUSH, 0b00110010,   1,
{
    pcpu->ip++;

    pcpu->registers[*(pcpu->code + pcpu->ip)] = StackPop(&pcpu->stk);

    pcpu->ip++;
    break;
})

DEF_CMD(RPOP , 0b00111011,   1,
{
    pcpu->ip++;

    StackPush(&pcpu->stk, pcpu->registers[*(pcpu->code + pcpu->ip)]);

    pcpu->ip++;
    break;
})

DEF_CMD(HLT  , 0b10000000,   0)

#endif
