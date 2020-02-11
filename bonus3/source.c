int main(int ac,char **av) {
	int i;
	char *local_EDI_61;
	byte bVar1;
	char local_98 [65];
	undefined local_57;
	char local_56 [66];

	FILE *end_pass;

	char *buffer[24]; /* esp+0x18 */
	char *buffer2[66];
	/*
		mov    edx,0x80486f0			<--- "r"
		mov    eax,0x80486f2			<--- "/home/user/end/.pass"
		mov    DWORD PTR [esp+0x4],edx
		mov    DWORD PTR [esp],eax
		call   0x8048410 <fopen@plt>
	*/
	end_pass = fopen("/home/user/end/.pass", "r"); /* esp+0x9c */

	/*
		lea    ebx,[esp+0x18]				<--- buffer[24] in EBX
    	mov    eax,0x0						<--- 0 in EAX
    	mov    edx,0x21						<--- 33 in EDX
    	mov    edi,ebx						<--- EBX (buffer[24]) in EDI
    	mov    ecx,edx						<--- EDX (33) in ECX
    	rep stos DWORD PTR es:[edi],eax		<--- put EAX (0) in EDI while 33

		equivalent to bzero
	*/
	bzero(buffer, 33);

	/*
		cmp    DWORD PTR [esp+0x9c],0x0
		je     0x8048543 <main+79>
		cmp    DWORD PTR [ebp+0x8],0x2
		je     0x804854d <main+89>
	*/
	if (end_pass == 0 || ac != 2) {
		return 0xfffffffff; /* -1 */
	}

	/*
		lea    eax,[esp+0x18]				<--- buffer[24] in EAX
		mov    edx,DWORD PTR [esp+0x9c]		<--- end_pass in EDX
		mov    DWORD PTR [esp+0xc],edx		<--- 4th arg -> file -> end_pass
		mov    DWORD PTR [esp+0x8],0x42		<--- 3rd arg -> nmemb -> 66
		mov    DWORD PTR [esp+0x4],0x1		<--- 2nd arg -> size of nmemb -> 1
		mov    DWORD PTR [esp],eax			<--- 1st arg -> buffer[24]
		call   0x80483d0 <fread@plt>
	*/
	fread(buffer, 1, 66, end_pass);

	/*
		mov    eax,DWORD PTR [ebp+0xc]		<--- av[0]
		add    eax,0x4						<--- av[1]
		mov    eax,DWORD PTR [eax]
		mov    DWORD PTR [esp],eax
		call   0x8048430 <atoi@plt>
	*/
	nb = atoi(av[1]);

	/*
		mov    BYTE PTR [esp+eax*1+0x18],0x0
	*/
	buffer[nb] = 0;

	/*
		lea    eax,[esp+0x18]
		lea    edx,[eax+0x42]				<--- buffer2[66]
		mov    eax,DWORD PTR [esp+0x9c]
		mov    DWORD PTR [esp+0xc],eax		<--- 4th arg -> file -> end_pass
		mov    DWORD PTR [esp+0x8],0x41		<--- 3rd arg -> nmemb -> 65
		mov    DWORD PTR [esp+0x4],0x1		<--- 2nd arg -> size of nmemb -> 1
		mov    DWORD PTR [esp],edx			<--- 1st arg -> buffer[66]
		call   0x80483d0 <fread@plt>
	*/
	fread(buffer2, 1, 65, end_pass);

	/*
		mov    eax,DWORD PTR [esp+0x9c]
		mov    DWORD PTR [esp],eax
		call   0x80483c0 <fclose@plt>
	*/
	fclose(end_pass);

	/*
		0x080485c7 <+211>:	mov    eax,DWORD PTR [ebp+0xc]
		0x080485ca <+214>:	add    eax,0x4					<--- av[1]
		0x080485cd <+217>:	mov    eax,DWORD PTR [eax]
		0x080485cf <+219>:	mov    DWORD PTR [esp+0x4],eax	<--- 2nd arg -> av[1]
		0x080485d3 <+223>:	lea    eax,[esp+0x18]
		0x080485d7 <+227>:	mov    DWORD PTR [esp],eax		<--- 1st arg -> buffer
		0x080485da <+230>:	call   0x80483b0 <strcmp@plt>
	*/
	if (strcmp(buffer, av[1]) == 0) {
		/*
			mov    DWORD PTR [esp+0x8],0x0
			mov    DWORD PTR [esp+0x4],0x8048707
			mov    DWORD PTR [esp],0x804870a
			call   0x8048420 <execl@plt>
		*/
		execl("/bin/sh", "sh", 0);
	} else {
		/*
			0x08048601 <+269>:	lea    eax,[esp+0x18]
			0x08048605 <+273>:	add    eax,0x42				<--- buffer2[66]
			0x08048608 <+276>:	mov    DWORD PTR [esp],eax
			0x0804860b <+279>:	call   0x80483e0 <puts@plt>
		*/
		puts(buffer2);
	}
	return 0;
}
