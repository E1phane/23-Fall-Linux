#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAXLINE 256	// 최대 메시지 길이
#define NAME_SIZE 10	// 최대 닉네임 길이

int fd1, fd2;

char name[NAME_SIZE] = "[user]"; // 채팅창에 보여질 이름
char msg[MAXLINE];

void *get();
void *send();

int main(int argc, char *argv[]) {
    pthread_t t1, t2;

    if (argc != 2) {		// 입력 예시 ./cli2 [사용할 이름]
        printf("Usage : %s <name>\n", argv[0]);
        exit(1);
    }

    sprintf(name, "[%s]", argv[1]);

    fd1 = open("./chatfifo3", O_RDONLY);
    fd2 = open("./chatfifo4", O_WRONLY);
    if (fd1 == -1 || fd2 == -1) {
        perror("open");
        exit(1);
    }

    printf("* Client starts\n");
    pthread_create(&t1, NULL, get, NULL);
    pthread_create(&t2, NULL, send, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}

void *get() {
    char name_msg[NAME_SIZE + MAXLINE];
    int str;
    while (1) {
        str = read(fd1, name_msg, NAME_SIZE + MAXLINE);
        if (str <= 0) {	// 에러 또는 EOF일 경우 루프를 빠져나옴
            break;
        }
        fputs(name_msg, stdout);
    }
    pthread_exit(NULL);
}

void *send() {
    char name_msg[NAME_SIZE + MAXLINE];
    while (1) {
        fgets(msg, MAXLINE, stdin);
        sprintf(name_msg, "%s %s", name, msg);
        write(fd2, name_msg, strlen(name_msg) + 1);
    }
    pthread_exit(NULL);
}
