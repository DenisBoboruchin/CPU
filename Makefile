CC		= g++
CFLAGS  = -c -w -Wall

all: main.o assembler.o disassembler.o proc.o stack.o sort.o
	$(CC) Asm/assembler.cpp DisAsm/disassembler.cpp Proc/processor.cpp MyStack.cpp SortText.cpp main.cpp -o main 

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

assembler.o: Asm/assembler.o
	$(CC) $(CFLAGS) Asm/assembler.cpp

disassembler.o: DisAsm/disassembler.cpp
	$(CC) $(CFLAGS) DisAsm/disassembler.cpp

proc.o: Proc/processor.cpp
	$(CC) $(CFLAGS) Proc/processor.cpp

stack.o: MyStack.cpp
	$(CC) $(CFLAGS) MyStack.cpp

sort.o: SortText.cpp
	$(CC) $(CFLAGS) SortText.cpp

clean:
	rm -rf *.out *.o main
