#include"types.h"
#include"stat.h"
#include"user.h"
#include"fcntl.h"
#include"fs.h"

int main (int argc, char *argv[])
{
	int fd;
	if (argc < 2)
	{
		printf (1, "format penggunaan: touch [file yang akan dibuat]\n");
		exit();
	}
	
	if ((fd = open(argv[1], O_CREATE|O_RDWR)) < 1)
	{
		printf (1,"%s gagal dibuat\n", argv[1]);
	}
	else
	{
		printf (1, "%s berhasil dibuat\n", argv[1]);
	}
	exit();
}
