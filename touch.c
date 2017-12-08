#include"xv6/types.h"
#include"xv6/stat.h"
#include"stdio.h"
#include"xv6/fcntl.h"
#include"syscall.h"

int main (int argc, char *argv[])
{
    int fd;
	if (argc < 2 || argc > 2)
	{
		printf("format penggunaan: touch [file yang akan dibuat]\n");
		return 1;
	}
	
	if ((fd = open(argv[1], O_CREAT|O_RDWR)) < 1)
	{
		printf("%s gagal dibuat\n", argv[1]);
	}
	else
	{
		printf("%s berhasil dibuat\n", argv[1]);
	}
	sysexit();
}
