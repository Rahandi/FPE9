#include <stdio.h>
#include <syscall.h>
#include <string.h>
#include <xv6/stat.h>
#include <xv6/dirent.h>
#include <xv6/fcntl.h>

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
    static char buf[NAME_MAX+1];
    char *p;
    for(p=path+strlen(path); p >= path && *p != '/'; p--) //ngambil karakter prtama setelah '/'
        ;p++;
    if(strlen(p) >= NAME_MAX)
        return p;
    memmove(buf, p, strlen(p)); //copy nama file
    memset(buf+strlen(p), ' ', NAME_MAX-strlen(p));
    return buf;
}

void ls(char *path)
{
    char buf[512]; int fp; char *tmp;
    struct stat st; struct dirent die;
    //printf 0: stdin, 1: stdout, 2:stderr
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
                printf("%s %d %d %d\n", fname(buf), st.type, st.ino, st.size); //nampilin nama filenya, tipe file *stat*, inode, size of file
            }
            break;
        case 2: //kalo file
            printf("%s %d %d %d\n", fname(path), st.type, st.ino, st.size);
            break;
    }
    close(fp);
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
