#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

const char *password = "lilpa700";	// 지정된 비밀번호
char input[20];				// 입력할 비밀번호

void intHandler();
void intHandler2();

int main() {
	signal(SIGALRM, intHandler);
	signal(SIGINT, intHandler2);
	
	printf("10초 안에 비밀번호 입력 Ctrl + C 입력 시 10초 초기화\n");
	alarm(10);
	while(1) {
		printf("password: ");
		fgets(input, sizeof(input), stdin);
	
		input[strcspn(input, "\n")] = 0;
	
		if(strcmp(input, password) == 0) {
			printf("Correct\n");
			break;
		}
		else {
			printf("Incorrect\n");
		}
	}

	return 0;
}

void intHandler(int signo) {
        printf("\nFire!\n");
        exit(0);
}

void intHandler2(int signo) {
	printf("10 sec reset...\n");
	alarm(10);
}
