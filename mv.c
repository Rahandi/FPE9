#include <xv6/types.h> 
#include <xv6/stat.h> 
#include <stdio.h> 
#include <xv6/fcntl.h> 
#include <syscall.h> 
#include <string.h> 
 
char buf[512]; 
 
int move_to_dir(char *source, char *dest){ 
    int fd0, fd1, n; 
    char anu[512];
    strcpy(anu, source);
    strcat(dest, "/"); 
    strcat(dest, anu);
 
    if((fd0 = open(anu, O_RDONLY)) < 0){ 
        printf("[ERR] tidak bisa membuka file (%s) yang mau dimove.\n", anu); 
        return -1; 
    } 
    if((fd1 = open(dest, O_CREAT|O_RDWR)) < 0){ 
        printf("[ERR] mv: tidak bisa membuka file tujuan %s\n", dest); 
        return -1; 
    } 
    while((n = read(fd0, buf, sizeof(buf))) > 0){ 
        write(fd1, buf, n); 
    } 
 
    close(fd0); 
    close(fd1); 
    unlink(anu);
    return 0; 
} 
 
int main(int argc, char *argv[]) 
{ 
    struct stat st, dt; 
    int sts, dts, catch; 
 
    if((sts = open(argv[1], 0)) < 0){ 
        printf("[ERR] tidak bisa membuka file/dir %s yang mau dimove\n", argv[1]); 
        return -1; 
    } 
    if((dts = open(argv[2], 0)) < 0){ 
        printf("[ERR] ga bisa buka argv[2]\nformat command: mv [srcfile] [destdir]\n");
        return -1; 
    } 
    if(fstat(sts, &st) < 0){ 
        close(sts); 
        printf("[ERR] mv: source bukan merupakan file/dir %s\n", argv[1]); 
        return -1; 
    } 
    close(sts); 
    if(fstat(dts, &dt) < 0){ 
        close(dts); 
        printf("[ERR] mv: destination bukan merupakan file/dir %s\n", argv[2]); 
        return -1; 
    } 
    close(dts); 
    if(dt.type == 2){ //kalo file
        printf("[ERR] gak bisa move to file :(\n");
    } 
    if(dt.type == 1){  //kalo ke dir
        catch = move_to_dir(argv[1], argv[2]); 
        if(catch == 0)
            printf("move file %s to dir %s berhasil\n", argv[1], argv[2]); 
    }
 
 sysexit(); 
}
