#include "apue.h"
#include <fcntl.h>

#define RWRWRW (S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IXGRP|S_IWGRP|S_IXOTH|S_IROTH|S_IWOTH)

int
main(void)
{
//	umask(0);
//	if (creat("foo", RWRWRW)  ==0)
//		err_sys("creat error for ffoofoooo");
	if (creat("foo", RWRWRW) < 0)
		err_sys("creat error for foo");
	//umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	umask(0);
	if (creat("bar", RWRWRW) < 0)
		err_sys("creat error for bar");
	exit(0);
}
