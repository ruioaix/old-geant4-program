#include "apue.h"

#define	BUFFSIZE	4096

int
main(void)
{
	int		n;
	char	buf[BUFFSIZE];

	while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
		if (write(STDOUT_FILENO, buf, n-3) != n-3)
			err_sys("write error");

	if (n < 0)
		err_sys("read error");

	exit(0);
}
