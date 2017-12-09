#include"xv6/types.h"
#include"xv6/stat.h"
#include"stdio.h"
#include"xv6/fcntl.h"
#include"syscall.h"

int main (int argc, char *argv[])
{
	int fd1, fd2, byte, line;
	char t1, t2;
    	if(argc != 3)
    	{
		printf ("format penggunaan: cmp [nama file1] [nama file2]\n");
        	return 0;
    	}
	if((fd1 = open(argv[1], O_RDONLY)) < 0)
    	{
      		printf("%s tidak ditemukan\n", argv[1]);
        	return 0;
    	}

    	else if((fd2 = open(argv[2], O_RDONLY)) < 0)
    	{	
        	printf("%s tidak ditemukan\n", argv[2]);
        	return 0;
    	}
	else if((fd2 = open(argv[2], O_RDONLY)) < 0 || (fd1 = open(argv[1], O_RDONLY)) < 0)
    	{	
        	printf("%s dan %s tidak ditemukan\n", argv[1], argv[2]);
        	return 0;
    	}
	else
	{
		byte = 0;
		line = 1;
		while (1)
		{
        		if((read(fd1, &t1, sizeof(t1))) <= 0 || (read(fd2, &t2, sizeof(t2))) <= 0)
			{
				break;
			}
			if(t1 == '\n' && t2 == '\n')
			{
				++line;
			}
        		if(t1 != t2)
			{
            			break;
        		}
			++byte;
		}

		if(read(fd1, &t1, sizeof(t1))!=0 || read(fd2, &t2, sizeof(t2))!=0)
    		{
	 		printf("file %s dan file %s berbeda pada: byte %d line %d\n", argv[1], argv[2], byte, line);
    		}
		else
		{
			printf("tidak ada perbedaan\n");
		}
		close(fd1);
    		close(fd2);
        return 0;
	}
    sysexit();
	
}
