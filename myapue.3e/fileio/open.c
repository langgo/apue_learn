#include "apue.h"
#include <fcntl.h>

int
main(void)
{
	int fd;
	off_t currpos;

	fd = open("./test.txt", O_RDWR | O_APPEND | O_CREAT, 0644);

	printf("%d\n", fd);

	currpos = lseek(fd, 0, SEEK_CUR);

	printf("%ld\n", currpos);
		
	close(fd);

	return 0;
}