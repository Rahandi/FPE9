#include <types.h>
#include <stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <syscall.h>

void cal(char *path)
{
    
}

int main(int argc, char *argv[])
{
    if(argc > 1){
        printf(1, "That syntax does not exist in this system");
    }
    sysexit();
}
