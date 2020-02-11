int language;

void greetuser(char *str) {
	/* sub    esp,0x58 */
	char buffer[88]

	/*
		test   eax,eax
		jne    0x804850a <greetuser+134>
	*/
	if (language == 0) {
		/*
			mov    edx,0x8048710
			lea    eax,[ebp-0x48]
			mov    ecx,DWORD PTR [edx]
			mov    DWORD PTR [eax],ecx
			movzx  ecx,WORD PTR [edx+0x4]
			mov    WORD PTR [eax+0x4],cx
			movzx  edx,BYTE PTR [edx+0x6]
			mov    BYTE PTR [eax+0x6],dl

			put 0x8048710 string ("Hello ") on EDX and move byte by byte in EAX with ECX as a tmp register
			equivalent to strcpy
		*/
		strcpy(buffer, "Hello ");
	}
	/*
		je     0x80484ba <greetuser+54>
		cmp    eax,0x1
	*/
	else if (language == 1) {
		strcpy(buffer, "Hyvää päivää ");
	}
	/*
		cmp    eax,0x2
		je     0x80484e9 <greetuser+101>
	*/
	else if (language == 2) {
		strcpy(buffer, "Goedemiddag! ");
	}

	strcat(buffer, str);
	puts(buffer);
	return;
}

int main(int ac,char **av) {
	char	buffer[80]; // ???
	char	*lang_env;

	if (ac == 3) {
		/*
			lea    ebx,[esp+0x50]
			mov    eax,0x0
			mov    edx,0x13
			mov    edi,ebx
			mov    ecx,edx
			rep stos DWORD PTR es:[edi],eax		<--- put EAX (0) on each byte EBX

			equivalent to bzero
		*/
		bzero(buffer, 19);
		/*
			mov    eax,DWORD PTR [ebp+0xc]		<--- av[0]
			add    eax,0x4						<--- av[0] + 4 = av[1]
			mov    eax,DWORD PTR [eax]
			mov    DWORD PTR [esp+0x8],0x28		<--- 3rd arg -> len
			mov    DWORD PTR [esp+0x4],eax		<--- 2nd arg -> src
			lea    eax,[esp+0x50]				<--- buffer size = 80
			mov    DWORD PTR [esp],eax			<--- 1st arg -> dest
			call   0x80483c0 <strncpy@plt>
		*/
		strncpy(buffer, av[1], 40);
		/*
			mov    eax,DWORD PTR [ebp+0xc]		<--- av[0]
			add    eax,0x8						<--- av[0] + 8 = av[2]
			mov    eax,DWORD PTR [eax]
			mov    DWORD PTR [esp+0x8],0x20		<--- 3rd arg -> len
			mov    DWORD PTR [esp+0x4],eax		<--- 2nd arg -> src
			lea    eax,[esp+0x50]				<--- buffer size = 80
			add    eax,0x28						<--- buffer size + 40 -> 80 - 40 -> start at 40 ?
			mov    DWORD PTR [esp],eax			<--- 1st arg -> dest
			call   0x80483c0 <strncpy@plt>
		*/
		strncpy(&buffer[40], av[2], 32);

		/*
			mov    DWORD PTR [esp],0x8048738	<--- "LANG"
			call   0x8048380 <getenv@plt>
			mov    DWORD PTR [esp+0x9c],eax
		*/
		lang_env = getenv("LANG");
		/*
			cmp    DWORD PTR [esp+0x9c],0x0
			je     0x8048618 <main+239>
		*/
		if (lang_env[0] != 0) {
			/*
				mov    DWORD PTR [esp+0x8],0x2			<--- 3rd arg -> len
				mov    DWORD PTR [esp+0x4],0x804873d	<--- 2nd arg -> s2 = "fi"
				mov    eax,DWORD PTR [esp+0x9c]			<--- 1st arg -> s1 = lang_env
				mov    DWORD PTR [esp],eax
				call   0x8048360 <memcmp@plt>
			*/
			if (memcmp(lang_env, "fi", 2) == 0) {
				/*
					test   eax,eax
					jne    0x80485eb <main+194>
					mov    DWORD PTR ds:0x8049988,0x1
					jmp    0x8048618 <main+239>
				*/
				language = 1;
			}
			/*
				mov    DWORD PTR [esp+0x8],0x2			<--- 3rd arg -> len
				mov    DWORD PTR [esp+0x4],0x8048740	<--- 2nd arg -> s2 = "nl"
				mov    eax,DWORD PTR [esp+0x9c]			<--- 1st arg -> s1 = lang_env
				mov    DWORD PTR [esp],eax
				call   0x8048360 <memcmp@plt>
			*/
			else if (memcmp(lang_env, "nl", 2) == 0){
				/*
					test   eax,eax
					jne    0x8048618 <main+239>
					mov    DWORD PTR ds:0x8049988,0x2
				*/
				language = 2;
			}
		}

		/*
			mov    edx,esp					<--- ESP (arg for greetuser) in EDX
			lea    ebx,[esp+0x50]			<--- buffer in EBX
			mov    eax,0x13					<--- 19 in EAX
			mov    edi,edx					<--- EDX (ESP) in EDI
			mov    esi,ebx					<--- EBX (buffer) in ESI
			mov    ecx,eax					<--- EAX (19) in ECX
			rep movs DWORD PTR es:[edi],DWORD PTR ds:[esi] <--- move esi in edi while 19

			equivalent to strncpy
		*/
		char *arg_for_greetuser;
		strncpy(arg_for_greetuser, buffer, 19);

		return (greetuser(arg_for_greetuser));
	}
	return 1;
}
