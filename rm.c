#include <stdio.h>
#include <xv6/dirent.h>
#include <xv6/stat.h>
#include <string.h>
#include <xv6/types.h>
#include <errno.h>
#include <xv6/fcntl.h>
#include <syscall.h>

int main(int argc, char *argv[]){
    if(argc < 2){ 
        printf("apa yg mau di remove coba\n");
        return 0;}
    if(argc > 2){ 
        printf("[ERR] format command : rm [file yg akan dihapus]\n");
        return 0;}
    else{
        printf("%s berhasil dihapus\n", argv[1]);
	    unlink(argv[1]);
    }
    sysexit();
}
