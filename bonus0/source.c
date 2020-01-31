void p(char *param_1, char *param_2) {
	char *str;
	char buffer[4104];

	puts(param_2);

	read(0, buffer, 4096);

	str = strchr(buffer, 10);

	str[0] = '\0';

	strncpy(param_1, buffer, 20);

	return;
}

void pp(char *str) {
	char	cVar1;
	int		len;
	char	input1[20];
	char	input2[20];

	p(input1, " - ");
	p(input2, " - ");

	strcpy(str, input1);

	len = strlen(str);

	str[len] = 0x20 // 32

	strcat(str, input2);

	return;
}

int main(void) {
	char str[54];

	pp(str);
	puts(str);
	return 0;
}
