#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char c[50]; /* size ??? */

void m(void) {
  time_t t;

  t = time(0);
  printf("%s - %d\n", c, (int)t);
  return;
}

int main(int ac, char **av) {
  char *str_1;
  char *str_2;
  FILE *pass;

  str_1 = malloc(8);
  str_1[0] = 1;
  str_1[4] = malloc(8);

  str_2 = malloc(8);
  str_2[0] = 2;
  str_2[4] = malloc(8);

  strcpy(str_1[4], av[1]);
  strcpy(str_2[4], av[2]);

  pass = fopen("/home/user/level8/.pass","r");
  fgets(c, 68, pass);
  puts("~~");
  return 0;
}
