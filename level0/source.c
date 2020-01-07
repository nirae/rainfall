#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define _GNU_SOURCE
#include <unistd.h>
#include <sys/types.h>

int main(int ac, char **av) {
    int number;
	char **tab;
    uid_t uid;
    gid_t gid;

	/* Get the number passed in param */
    number = atoi(av[1]);
	/* Check if the number is 423 */
    if (number == 423) {
        tab[0] = strdup("/bin/sh");
		tab[1] = 0;
		/* Get the uid et gid (level1 because there is the suid) */
		gid = getegid();
        uid = geteuid();
		/* Set the current gid and uid */
        setresgid(gid, gid, gid);
        setresuid(uid, uid, uid);
		/* Execute a shell */
        execv("/bin/sh", tab);
    }
	else {
		fwrite("No !\n", 1, 5, stderr);
    }
    return 0;
}
