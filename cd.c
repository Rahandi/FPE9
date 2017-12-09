#include <xv6/types.h>
#include <xv6/stat.h>
#include <stdio.h>
#include <xv6/fcntl.h>
#include <syscall.h>

int main (int argc, char *argv[])
{    
	if (argc < 2 || argc > 2)
	{
		printf("format penggunaan: cd [dir]/\n");
		return 1;
	}

	int temp=0;
	temp = chdir(argv[1]);

	if (temp < 0)
	{
		printf("tidak bisa pindah directory\n");
		return 1;
	}
	printf("berhasil pindah directory ke %s\n", argv[1]);
	sysexit();
}
