#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void p(void) {
	unsigned int	check;
	char			str[76];

    fflush(stdout);
    gets(str);
    if ((check & 0xb0000000) == 0xb0000000) {
        printf("(%p)\n", check);
        exit(1);
    }
    puts(str);
    strdup(str);
    return;
}

int main(void) {
	p();
	return 0;
}
