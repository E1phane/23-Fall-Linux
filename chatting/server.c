#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

#define MAXLINE 256

int fd1, fd2, fd3, fd4;

void setNonBlocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

void *Ctrl_C1() {	// 클라이언트 1 제어
    int n;
    char msg[MAXLINE];
    while (1) {
        n = read(fd2, msg, MAXLINE);
        if (n == -1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {	// 더 이상 데이터를 읽을 수 없음
                break;
            } else {
                perror("read");
                exit(1);
            }
        } else if (n == 0) {	// EOF 도달
            break;
        } else {
            write(fd3, msg, strlen(msg) + 1);
        }
    }
    pthread_exit(NULL);
}

void *Ctrl_C2() {	// 클라이언트 2 제어
    int n;
    char msg[MAXLINE];
    while (1) {
        n = read(fd4, msg, MAXLINE);
        if (n == -1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {	// 더 이상 데이터를 읽을 수 없음
                break;
            } else {
                perror("read");
                exit(1);
            }
        } else if (n == 0) {	// EOF 도달
            break;
        } else {
            write(fd1, msg, strlen(msg) + 1);
        }
    }
    pthread_exit(NULL);
}

void create_fifo(const char *fifo_name) {	// 함수 내에서 mkfifo를 호출하여 파일이 이미 존재하는지 확인 후 생성
    if (access(fifo_name, F_OK) == -1) {	// mkfifo: File Exists 메시지 방지
        if (mkfifo(fifo_name, 0666) == -1 && errno != EEXIST) {
            perror("mkfifo");
            exit(1);
        }
    }
}

int main() {
    pthread_t t1, t2;
    				
    create_fifo("./chatfifo1");	// 각각의 FIFO 파일 생성
    create_fifo("./chatfifo2");
    create_fifo("./chatfifo3");
    create_fifo("./chatfifo4");

    fd1 = open("./chatfifo1", O_WRONLY);	// 쓰기전용 파이프
    fd2 = open("./chatfifo2", O_RDONLY);	// 읽기전용 파이프
    fd3 = open("./chatfifo3", O_WRONLY);	// 쓰기전용 파이프
    fd4 = open("./chatfifo4", O_RDONLY);	// 읽기전용 파이프

    if (fd1 == -1 || fd2 == -1 || fd3 == -1 || fd4 == -1) {
        perror("open");
        exit(3);
    }

    printf("server starts\n");
    pthread_create(&t1, NULL, Ctrl_C1, NULL);
    pthread_create(&t2, NULL, Ctrl_C2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}

