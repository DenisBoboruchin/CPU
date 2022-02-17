all: cpu

cpu: Asm Proc

Asm:
	gcc Asm/assembler.cpp -o asm.out
Proc:
	gcc Proc/processor.cpp MyStack.cpp -o proc.out

clean:
	rm -rf *.o *.out Proc_log_file.txt Data_stk_logfile.txt Rets_logfile.txt code.bin
