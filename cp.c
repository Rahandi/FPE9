#include <xv6/types.h> 
#include <xv6/stat.h> 
#include <stdio.h> 
#include <xv6/fcntl.h> 
#include <syscall.h> 
#include <string.h> 

char buf[512]; 

int copy(char *source, char *dest){ 
	int fd0, fd1, n; 

	if((fd0 = open(source, O_RDONLY)) < 0){ 
		printf("cp: tidak bisa membuka file yang mau dicopy %s\n", source); 
		return -1; 
	} 

	if((fd1 = open(dest, O_CREAT|O_RDWR)) < 0){ 
		printf("cp: tidak bisa membuka file tujuan %s\n", dest); 
		return -1;
	} 

	while((n = read(fd0, buf, sizeof(buf))) > 0){ 
		write(fd1, buf, n); 
	} 

	close(fd0); 
	close(fd1); 
	return 0; 
} 

int copy_to_dir(char *source, char *dest){ 
	int fd0, fd1, n; 
	char anu[512];
	strcpy(anu, source);
	strcat(dest, "/"); 
	strcat(dest, source);

	if((fd0 = open(anu, O_RDONLY)) < 0){ 
		printf("cp: tidak bisa membuka file yang mau dicopy %s\n", anu); 
		return -1; 
	} 

	if((fd1 = open(dest, O_CREAT|O_RDWR)) < 0){ 
		printf("cp: tidak bisa membuka file tujuan %s\n", dest); 
		return -1; 
	} 

	while((n = read(fd0, buf, sizeof(buf))) > 0){ 
		write(fd1, buf, n); 
	} 

	close(fd0); 
	close(fd1); 
	return 0; 
} 

int main(int argc, char *argv[]) 
{ 
	struct stat st, dt; 
	int sts, dts, catch; 

	if((sts = open(argv[1], 0)) < 0){ 
		printf("cp: tidak bisa membuka file/dir yang mau dicopy %s\n", argv[1]); 
		return -1; 
	} 

	if((dts = open(argv[2], 0)) < 0){ 
		catch=copy(argv[1],argv[2]);
		if(catch == 0){ 
			printf("copy file to file berhasil\n"); 
		} 
		return 0; 
	} 

	if(fstat(sts, &st) < 0){ 
		close(sts); 
		printf("cp: source bukan merupakan file/dir %s\n", argv[1]); 
		return -1; 
	} 
	close(sts); 

	if(fstat(dts, &dt) < 0){ 
		close(dts); 
		printf("cp: destination bukan merupakan file/dir %s\n", argv[2]); 
		return -1; 
	} 
	close(dts); 

	if(st.type == 2 && dt.type == 2){ //kalo file
		printf("file wis enek\n");
	} 

	if(st.type == 2 && dt.type == 1){ //kalo ke dir
		catch = copy_to_dir(argv[1], argv[2]); 
		if(catch == 0){ 
			printf("copy file to dir berhasil\n"); 
		} 
	} 

	sysexit(); 
}