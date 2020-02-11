# Bonus 3

First step - testing the program

	$ ./bonus3
	$ ./bonus3 coucou

	$ ./bonus3 coucou coucou

Not very interesting

Start in GDB

	gdb-peda$ pdisas main
	Dump of assembler code for function main:
	   0x080484f4 <+0>:		push   ebp
	   0x080484f5 <+1>:		mov    ebp,esp
	   0x080484f7 <+3>:		push   edi
	   0x080484f8 <+4>:		push   ebx
	   0x080484f9 <+5>:		and    esp,0xfffffff0
	   0x080484fc <+8>:		sub    esp,0xa0
	   0x08048502 <+14>:	mov    edx,0x80486f0
	   0x08048507 <+19>:	mov    eax,0x80486f2
	   0x0804850c <+24>:	mov    DWORD PTR [esp+0x4],edx
	   0x08048510 <+28>:	mov    DWORD PTR [esp],eax
	   0x08048513 <+31>:	call   0x8048410 <fopen@plt>
	   0x08048518 <+36>:	mov    DWORD PTR [esp+0x9c],eax
	   0x0804851f <+43>:	lea    ebx,[esp+0x18]
	   0x08048523 <+47>:	mov    eax,0x0
	   0x08048528 <+52>:	mov    edx,0x21
	   0x0804852d <+57>:	mov    edi,ebx
	   0x0804852f <+59>:	mov    ecx,edx
	   0x08048531 <+61>:	rep stos DWORD PTR es:[edi],eax
	   0x08048533 <+63>:	cmp    DWORD PTR [esp+0x9c],0x0
	   0x0804853b <+71>:	je     0x8048543 <main+79>
	   0x0804853d <+73>:	cmp    DWORD PTR [ebp+0x8],0x2
	   0x08048541 <+77>:	je     0x804854d <main+89>
	   0x08048543 <+79>:	mov    eax,0xffffffff
	   0x08048548 <+84>:	jmp    0x8048615 <main+289>
	   0x0804854d <+89>:	lea    eax,[esp+0x18]
	   0x08048551 <+93>:	mov    edx,DWORD PTR [esp+0x9c]
	   0x08048558 <+100>:	mov    DWORD PTR [esp+0xc],edx
	   0x0804855c <+104>:	mov    DWORD PTR [esp+0x8],0x42
	   0x08048564 <+112>:	mov    DWORD PTR [esp+0x4],0x1
	   0x0804856c <+120>:	mov    DWORD PTR [esp],eax
	   0x0804856f <+123>:	call   0x80483d0 <fread@plt>
	   0x08048574 <+128>:	mov    BYTE PTR [esp+0x59],0x0
	   0x08048579 <+133>:	mov    eax,DWORD PTR [ebp+0xc]
	   0x0804857c <+136>:	add    eax,0x4
	   0x0804857f <+139>:	mov    eax,DWORD PTR [eax]
	   0x08048581 <+141>:	mov    DWORD PTR [esp],eax
	   0x08048584 <+144>:	call   0x8048430 <atoi@plt>
	   0x08048589 <+149>:	mov    BYTE PTR [esp+eax*1+0x18],0x0
	   0x0804858e <+154>:	lea    eax,[esp+0x18]
	   0x08048592 <+158>:	lea    edx,[eax+0x42]
	   0x08048595 <+161>:	mov    eax,DWORD PTR [esp+0x9c]
	   0x0804859c <+168>:	mov    DWORD PTR [esp+0xc],eax
	   0x080485a0 <+172>:	mov    DWORD PTR [esp+0x8],0x41
	   0x080485a8 <+180>:	mov    DWORD PTR [esp+0x4],0x1
	   0x080485b0 <+188>:	mov    DWORD PTR [esp],edx
	   0x080485b3 <+191>:	call   0x80483d0 <fread@plt>
	   0x080485b8 <+196>:	mov    eax,DWORD PTR [esp+0x9c]
	   0x080485bf <+203>:	mov    DWORD PTR [esp],eax
	   0x080485c2 <+206>:	call   0x80483c0 <fclose@plt>
	   0x080485c7 <+211>:	mov    eax,DWORD PTR [ebp+0xc]
	   0x080485ca <+214>:	add    eax,0x4
	   0x080485cd <+217>:	mov    eax,DWORD PTR [eax]
	   0x080485cf <+219>:	mov    DWORD PTR [esp+0x4],eax
	   0x080485d3 <+223>:	lea    eax,[esp+0x18]
	   0x080485d7 <+227>:	mov    DWORD PTR [esp],eax
	   0x080485da <+230>:	call   0x80483b0 <strcmp@plt>
	   0x080485df <+235>:	test   eax,eax
	   0x080485e1 <+237>:	jne    0x8048601 <main+269>
	   0x080485e3 <+239>:	mov    DWORD PTR [esp+0x8],0x0
	   0x080485eb <+247>:	mov    DWORD PTR [esp+0x4],0x8048707
	   0x080485f3 <+255>:	mov    DWORD PTR [esp],0x804870a
	   0x080485fa <+262>:	call   0x8048420 <execl@plt>
	   0x080485ff <+267>:	jmp    0x8048610 <main+284>
	   0x08048601 <+269>:	lea    eax,[esp+0x18]
	   0x08048605 <+273>:	add    eax,0x42
	   0x08048608 <+276>:	mov    DWORD PTR [esp],eax
	   0x0804860b <+279>:	call   0x80483e0 <puts@plt>
	   0x08048610 <+284>:	mov    eax,0x0
	   0x08048615 <+289>:	lea    esp,[ebp-0x8]
	   0x08048618 <+292>:	pop    ebx
	   0x08048619 <+293>:	pop    edi
	   0x0804861a <+294>:	pop    ebp
	   0x0804861b <+295>:	ret
	End of assembler dump.

A lot of things:

	- An open and read after conditions on "/home/user/end/.pass
	- atoi and strcmp on arg
	- execl("/bin/sh", "sh", 0) after conditions

After translation to C code, we can see how to execute the execl

	if (strcmp(buffer, av[1]) == 0)

This condition need to be true

Just before, the '\0' of the buffer is set by the atoi on the av[1]


	nb = atoi(av[1]);
	buffer[nb] = 0;

So, the buffer should be "" (buffer[0] = '\0') and av[1] should be ""

Let's put "" in arg

	$ ./bonus3 ''
	$

Good!
