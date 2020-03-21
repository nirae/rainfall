class N {
	char *string;
	char string[108]; //??
	int number;

	// constructeur
	/*
	_ZN1NC2Ei = N::N(int)
	*/
	N(int number) {
		this->number = number;
	}

	/*
		mov    eax,DWORD PTR [ebp+0x8]
		mov    edx,DWORD PTR [eax+0x68] <--- 6
		mov    eax,DWORD PTR [ebp+0xc]
		mov    eax,DWORD PTR [eax+0x68] <--- 5
		add    eax,edx <--- 6 + 5
	*/
	int operator+(N &arg) {
		return this->number + arg.number;
	}

	void setAnnotation(char *str) {
		size_t len;

		/*
			0x08048714 <+6>:	mov    eax,DWORD PTR [ebp+0xc]
			0x08048717 <+9>:	mov    DWORD PTR [esp],eax
			0x0804871a <+12>:	call   0x8048520 <strlen@plt>
		*/
		len = strlen(str);
		// memcpy(this + 4, str, len);
		// The overflow is here
		/*
			mov    edx,DWORD PTR [ebp+0x8] 	<--- this
			add    edx,0x4					<--- this + 4 = this->string
			mov    DWORD PTR [esp+0x8],eax	<--- 3rd arg = eax = strlen result
			mov    eax,DWORD PTR [ebp+0xc]
			mov    DWORD PTR [esp+0x4],eax	<--- 2nd arg = param
			mov    DWORD PTR [esp],edx		<--- first arg = this->string
			call   0x8048510 <memcpy@plt>
		*/
		memcpy(this->string, str, len);
		return;
	}
};

int main(int ac,char **av) {
	N nclass_1;
	N nclass_2;

	/*
		cmp    DWORD PTR [ebp+0x8],0x1
		jg     0x8048610 <main+28>
		mov    DWORD PTR [esp],0x1
		call   0x80484f0 <_exit@plt>
	*/
	if (ac < 2) {
		exit(1);
	}

	/*
		mov    DWORD PTR [esp],0x6c
		call   0x8048530 <_Znwj@plt>	<--- new builtin
		mov    ebx,eax
		mov    DWORD PTR [esp+0x4],0x5	<--- arg for constructor
		mov    DWORD PTR [esp],ebx		<--- first arg = class
		call   0x80486f6 <_ZN1NC2Ei>	<--- N constructor
	*/
	nclass_1 = new N(5); // esp+0x1c

	/*
		mov    DWORD PTR [esp],0x6c
		call   0x8048530 <_Znwj@plt>	<--- new builtin
		mov    ebx,eax
		mov    DWORD PTR [esp+0x4],0x6	<--- arg for constructor
		mov    DWORD PTR [esp],ebx		<--- first arg = class
		call   0x80486f6 <_ZN1NC2Ei>	<--- N constructor
	*/
	nclass_2 = new N(6); // esp+0x18

	/*
		mov    eax,DWORD PTR [ebp+0xc]	<--- av[0]
		add    eax,0x4					<--- av[1]
		mov    eax,DWORD PTR [eax]
		mov    DWORD PTR [esp+0x4],eax	<--- av[1] in second arg
		mov    eax,DWORD PTR [esp+0x14]	<--- first arg = class
		mov    DWORD PTR [esp],eax
		call   0x804870e <_ZN1N13setAnnotationEPc> <--- N::setAnnotation(char*)
	*/
	nclass_1->setAnnotation(av[1]);

	return nclass_2.operator+(&nclass_1);;
}
