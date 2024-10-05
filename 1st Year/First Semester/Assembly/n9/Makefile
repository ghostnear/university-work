build:
	nasm -fwin32 functions.asm -g -o functions.obj
	cl /Z7 main.c /link functions.obj

clean:
	del main.exe
	del main.ilk
	del main.obj
	del main.pdb
	del functions.obj