#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "get_next_line_bonus.h"

#define INT_DIGITS 19		/* enough for 64 bit integer */
#define UINT_DIGITS 20

char *itoa(int i)
{
  /* Room for INT_DIGITS digits, - and '\0' */
  static char buf[INT_DIGITS + 2];
  char *p = buf + INT_DIGITS + 1;	/* points to terminating '\0' */
  if (i >= 0) {
    do {
      *--p = '0' + (i % 10);
      i /= 10;
    } while (i != 0);
    return p;
  }
  else {			/* i < 0 */
    do {
      *--p = '0' - (i % 10);
      i /= 10;
    } while (i != 0);
    *--p = '-';
  }
  return p;
}

char	*white(void) {
	return ("\033[0;37m");
}

void	KO(void) {
	printf("\033[0;31mKO\n");
}

void	OK(void) {
	printf("\033[0;32mOK\n");
}

void	test_0(char *line, int fd) {
	printf("%ssingle line file with nl\n", white());
	strcmp("salut a tous\n", line) ? KO() : OK();
	free(line);

	line = get_next_line(fd);
	free(line);
}

void	test_1(char *line, int fd) {
	printf("%ssingle without nl\n", white());
	strcmp("oui", line) ? KO() : OK();
	free(line);

	line = get_next_line(fd);
	free(line);
}

void	test_2(char *line, int fd) {
	printf("%sempty file\n", white());
	line ? KO() : OK();
	free(line);
}

void	test_3(char *line, int fd) {
	printf("%smultiple lines without ln at the last one\n", white());

	strcmp("salut a tous\n", line) ? KO() : OK();
	free(line);

	line = get_next_line(fd);
	strcmp("comment\n", line) ? KO() : OK();
	free(line);

	line = get_next_line(fd);
	strcmp("ca va\n", line) ? KO() : OK();
	free(line);

	line = get_next_line(fd);
	strcmp("test", line) ? KO() : OK();
	free(line);

	line = get_next_line(fd);
	free(line);
}

void	test_4(char *line, int fd) {
	printf("%smultiple lines\n", white());

	strcmp("salut a tous\n", line) ? KO() : OK();
	free(line);

	line = get_next_line(fd);
	strcmp("comment\n", line) ? KO() : OK();
	free(line);

	line = get_next_line(fd);
	strcmp("ca va\n", line) ? KO() : OK();
	free(line);

	line = get_next_line(fd);
	free(line);
}

int	main() {
	char *line;
	int fd;

	void (*fn[5])(char *line, int fd);
	fn[0] = test_0;
	fn[1] = test_1;
	fn[2] = test_2;
	fn[3] = test_3;
	fn[4] = test_4;
	
	for (int i = 0; i <= 4; i++)
	{
		fd = open(itoa(i), O_RDONLY);
		line = get_next_line(fd);
		fn[i](line, fd);
		close(fd);
	}
}
