#include"types.h"
#include"stat.h"
#include"user.h"
#include"fcntl.h"
#include"fs.h"

int main (int argc, char *argv[])
{
    	if(argc != 3)
    	{
		printf (1, "format penggunaan: cmp [nama file1] [nama file2]\n");
        	exit();
    	}
    	
	int fd1, fd2;
	if((fd1 = open(argv[1], O_RDONLY) < 0)
    	{
      		printf(1, "%s tidak ditemukan\n", argv[1]);
        	exit();
    	}

    	else if((fd2 = open(argv[2], O_RDONLY) < 0)
    	{	
        	printf(1, "%s tidak ditemukan\n", argv[2]);
        	exit();
    	}
	
	else
	{
		
	}
}
