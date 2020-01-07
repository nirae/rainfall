void p(void) {
    uint32_t	unaff_retaddr;
    char		*src;
    int32_t		var_ch;

    fflush(_section..bss);
    gets(&src);
    if ((unaff_retaddr & 0xb0000000) == 0xb0000000) {
        printf("(%p)\n", unaff_retaddr);
        exit(1);
    }
    puts(&src);
    strdup(&src);
    return;
}

int main(void) {
	p();
	return 0;
}
