build:
	nasm -fobj main.asm
	nasm -fobj functions.asm
	C:\Users\GhostNear\Desktop\Assembly\asm_tools\nasm\ALINK.EXE main.obj functions.obj -oPE -subsys console -entry start

clean:
	del main.exe
	del main.obj
	del functions.obj