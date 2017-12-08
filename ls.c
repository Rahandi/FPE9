#include <stdio.h>
#include <syscall.h>
#include <string.h>
#include <stat.h>

char* fname(char *path)
{
    
}

void ls(char *path)
{
    char buf[512]; int fp; char *tmp;
    struct stat jfile; struct dirent die;
    //printf 0: stdin, 1: stdout, 2:stderr
    if((fp=open(path,0)) < 0) { printf(2, "[ERR] gabisa buka file %s\n", path); return;}
    if(stat(fp,&st) < 0){
        printf(2, "[ERR] %s bukan file, dir, maupun device\n", path); 
        close(fp); return;}

    switch(jfile.type){
        case 1: //kalo dir
            if(strlen(path) + 1 + charMAX + 1 > sizeof buf){ //kalo path <20
            printf(1, "path lebih dari 20\n");
            break;}
            strcpy(buf, path);
            tmp = buf+strlen(buf);
            *tmp++ = '/';
            while(read(fp, &die, sizeof(die)) == sizeof(die)){
                if(die.inum == 0) continue;
                memmove(tmp, die.name, charMAX);
                tmp[charMAX] = 0;
                if(stat(buf, &st) < 0){
                    printf(1, "[ERR] %s bukan file, dir, maupun device\n", buf); continue;}
                printf(1, "%s %d %d %d\n", fname(buf), st.type, st.ino, st.size);
            }
            break;
        case 2: //kalo file
    }
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
