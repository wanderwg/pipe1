#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
    //管道必须创建于创建子进程之前，这样子进程才能复制到管道的操作句柄
    //int pipe(int pipefd[2]);
    int pipefd[2];
    int ret=pipe(pipefd);
    if(ret<0){
        perror("pipe error");
        return -1;
    }
    int pid=fork();
    if(pid==0){
        //子进程
        close(pipefd[0]);
        char buf[1024]={0};
        int ret=read(pipefd[0],buf,1023);
        printf("child read:%d--%s\n",ret,buf);
        exit(0);
    }
    else if(pid>0){
        //父进程
        sleep(1);
        close(pipefd[0]);
         int total_len=0;
         total_len+= write(pipefd[1],"hello world",11);
    }
    printf("----------------------\n");
    return 0;
}
