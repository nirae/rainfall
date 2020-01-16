# Level0

First step - testing the program

	$ ./level0
	Segmentation fault (core dumped)

	$ ./level0 coucou
	No !

The program segfault without parameters and print "No !" with a parameter

We can assume the program wait a password in parameters

Start the program in GDB

	$ gdb level0 42
	(gdb) disas main
	...
	   0x08048ed4 <+20>:	call   0x8049710 <atoi>
	   0x08048ed9 <+25>:	cmp    $0x1a7,%eax
	...

The function 'atoi' is called and there is a comp with the result of atoi and 0x1a7 (423)

Try this number

	$ ./level10 423

Good. We have the shell
