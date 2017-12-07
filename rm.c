#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <malloc.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <fnctl.h>
#include <unistd.h>
int main(int argc, char *argv[]){
	unlink(argv[1]);
}