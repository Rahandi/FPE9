#include <xv6/types.h>  
#include <xv6/stat.h>  
#include <stdio.h>  
#include <xv6/fcntl.h>  
#include <syscall.h>  
#include <string.h>  
#include <xv6/dirent.h> 
 
#define NAME_MAX 14 
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
 
int stpath(char *nbuf, struct stat *st) 
{ 
    int fp, r; 
    fp = open(nbuf, O_RDONLY); 
    if(fp < 0) return -1; 
    r = fstat(fp, st); 
    close(fp); 
    return r; 
} 
 
char* fname(char *path) 
{ 
    static char bufg[NAME_MAX+1]; 
    char *p; 
    for(p=path+strlen(path); p >= path && *p != '/'; p--) //ngambil karakter prtama setelah '/' 
        ;p++; 
    if(strlen(p) >= NAME_MAX) 
        return p; 
    memmove(bufg, p, strlen(p)); //copy nama file 
    memset(bufg+strlen(p), ' ', NAME_MAX-strlen(p)); 
    return bufg; 
} 
 
void ls(char *path, char *dest) 
{ 
 int catch; 
    char buf[512]; int fp; char *tmp; 
    struct stat st; struct dirent die; 
    if((fp=open(path,0)) < 0) { fprintf(stderr, "[ERR] gabisa buka file %s\n", path); return;} 
    if(fstat(fp,&st) < 0){ 
        fprintf(stderr, "[ERR] %s bukan file, dir, maupun device\n", path);  
        close(fp); return;} 
 
    switch(st.type){ 
     case 1: //kalo dir 
            if(strlen(path) + 1 + NAME_MAX + 1 > sizeof buf){ //kalo path <20 
            fprintf(stderr, "path lebih dari 20\n"); 
            break;} 
            strcpy(buf, path); 
            tmp = buf+strlen(buf); 
            *tmp++ = '/'; 
            while(read(fp, &die, sizeof(die)) == sizeof(die)){ //dia bakal nge loop dari dir itu, ngecek kalo file di dlmnya mrupakan st.type yg sesuai 
                if(die.d_ino == 0) continue; 
                memmove(tmp, die.d_name, NAME_MAX); 
                tmp[NAME_MAX] = 0; 
                if(stpath(buf, &st) < 0){ 
                    fprintf(stderr, "[ERR] %s bukan file, dir, maupun device\n", buf); continue;} 

             if(st.type == 2){ 
                 catch = copy_to_dir(fname(buf), dest); 
                 if(catch == 0){ 
                  printf("%s berhasil di copy\n", fname(buf)); 
                 } 
             } 
            } 
            break; 
        case 2: 
            catch = copy_to_dir(fname(path), dest); 
            if(catch == 0){ 
             printf("%s berhasil di copy\n", fname(path)); 
            } 
    } 
    close(fp); 
} 
 
int main(int argc, char *argv[])  
{  
 struct stat st, dt;  
 int sts, dts, catch;  
 
 if(strcmp("*", argv[1]) == 0){ 
  ls(".", argv[2]); 
 } 
 
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
