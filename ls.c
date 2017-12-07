#include <types.h>
#include <stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <syscall.h>

void ls(char *path)
{
    
}

int main(int argc, char *argv[])
{
    if(argc < 2){
        ls("."); //file yg namanya diawali dgn "." tidak terdaftar (wikipedia)
        sysexit();
    }
    for(int i=1;i<argc;i++) ls(argv[i]);
    sysexit();
}
