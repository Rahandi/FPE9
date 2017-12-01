#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

char buf[512];

int
main(int argc, char *argv[])
{
	int fd0, fd1, n;

	//cek jumlah argument
	if(argc < 3 || argc > 4){
		printf(1, "format penggunaan: cp [sumber] [tujuan] [option]\n");;
		exit();
	}

	//jika penggunaan tanpa option
	if(argc == 3){

		//cek jika penggunaan untuk semua file
		if(strcmp(argv[1], "*") == 0){
			printf(1, "argument 2 adalah *\n");
			exit();
		}

		//cek apakah source merupakan folder atau bukan
		struct stat st;
		fstat(*argv[1], &st);
		if(st.type == T_DIR){
			printf(1, "cp: gabisa mengcopy folder\n");
			exit();
		}
		
		//cek apakah source bisa dibuka
		if((fd0 = open(argv[1], O_RDONLY)) < 0){
			printf(1, "cp: tidak membisa buka file yang mau dicopy %s\n", argv[1]);
			exit();
		}

		//cek apakah dest merupakan folder atau bukan
		struct stat dt;
		fstat(*argv[2], &dt);
		if(dt.type == T_DIR){
			char *ptr, *dirdest;
			dirdest = argv[2];
			ptr = argv[1];
			while(*ptr != 0){ 
				ptr = ptr + 1;
			}
			while(ptr > argv[1] && *ptr != '/'){
				ptr = ptr - 1;
			}
			if(*ptr == '/'){
				ptr = ptr + 1;
			}
			while(*dirdest != 0){
				dirdest = dirdest + 1;
			}
			dirdest = dirdest - 1;
			if(*dirdest != '/'){
				dirdest = dirdest + 1;
				*dirdest = '/';
				dirdest = dirdest + 1;
				*dirdest = '0';
			}
			else{
				dirdest = dirdest + 1;
			}
			while(*ptr != 0) *dirdest++ = *ptr++;
			*dirdest++ = 0;
			printf(1, "masuk folder %s\n", argv[2]);
		}

		//cek apakah dest bisa dibuka
		if((fd1 = open(argv[2], O_CREATE|O_RDWR)) < 0){
			printf(1, "cp: tidak bisa membuka file tujuan %s\n", argv[2]);
			exit();
		}

		//copy isi file source ke dest
		while((n = read(fd0, buf, sizeof(buf)))>0){
			write(fd1, buf, n);
		}

		close(fd0);
		close(fd1);
	}

	if(argc == 4){
		printf(1, "4 argument\n");
		if(strcmp(argv[3], "-R") == 0){
			printf(1, "argument 4 adalah -R\n");
		}
	}
	exit();
}
