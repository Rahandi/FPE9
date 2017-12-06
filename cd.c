#include"types.h"
#include"stat.h"
#include"user.h"
#include"fcntl.h"
#include"fs.h"

int main (int argc, char *argv[])
{
	if (argc < 2 || argc > 2)
	{
		printf (1, "format penggunaan: cd [direktori yang ingin dituju]\n");
		exit();
	}

	int temp=0;
	temp = chdir(argv[1]);

	if (temp < 0)
	{
		printf (1, "tidak bisa pindah directory\n");
		exit();
	}
	printf (1, "berhasil pindah directory ke %s\n", argv[1]);
	exit();
}
