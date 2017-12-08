#include <stdio.h>
#include <xv6/dirent.h>
#include <xv6/stat.h>
#include <string.h>
#include <xv6/types.h>
#include <errno.h>
#include <xv6/fcntl.h>
#include <syscall.h>

int main(int argc, char *argv[]){
    printf("berhasil dihapus\n");
	unlink(argv[1]);
    sysexit();
}
