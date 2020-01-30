#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char *auth;
char *service;


int main(void) {
	char input[32];

	while (1) {
		/* main+45 */
		printf("%p, %p \n", auth, service);

		/* main+74 */
		if (fgets(input, 128, stdin) == 0) {
			break;
		}

		/*
		 * main+87
		 * equivalent to this strncmp
		 * arg 1 :	0x080485bb <+87>:	lea    eax,[esp+0x20]
		 * 			0x080485bf <+91>:	mov    edx,eax
		 * arg 2 :	0x080485c1 <+93>:	mov    eax,0x8048819
		 * arg 3 :	0x080485c6 <+98>:	mov    ecx,0x5
		 *
		 * condition :
		 * 		0x080485e0 <+124>:	test   eax,eax
		 * 		0x080485e2 <+126>:	jne    0x8048642 <main+222>
		*/
		if (strncmp(input, "auth ", 5) == 0) {
			/*
				0x080485eb <+135>:	call   0x8048470 <malloc@plt>
				0x080485f0 <+140>:	mov    ds:0x8049aac,eax
				0x080485f5 <+145>:	mov    eax,ds:0x8049aac
				0x080485fa <+150>:	mov    DWORD PTR [eax],0x0
			*/
			auth = malloc(4);
			/*
				main+156
				equivalent to this check with strlen
			*/
			if (strlen(input + 5) <= 30) {
				strcpy(auth, input + 5);
			}
		}
		/*
		* main+222
		* same as before, strncmp of 5 with reset this time
		*/
		else if (strncmp(input, "reset", 5) == 0) {
			/* call with arguments start at main+263 */
			free(auth);
		}
		/*
		* main+276
		* same as before, strncmp of 6 with service
		*/
		else if (strncmp(input, "service", 6) == 0) {
			/* call with arguments start at main+317 */
			service = strdup(input + 7);
		}
		/*
		* main+337
		* same as before, strncmp of 5 with login
		*/
		else if (strncmp(input, "login", 5) == 0) {
			if ((*auth + 32) != 0) {
				/* call with arguments start at main+394 */
				system("/bin/sh");
			} else {
				/* call with arguments start at main+411 */
				fwrite("Password:\n", 1, 10, stdout);
			}
		}
	}
	return 0;
}
