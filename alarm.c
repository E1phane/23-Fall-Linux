#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void intHandler();

int main() {
	signal(SIGALRM, intHandler);
	alarm(5);
	printf("loop...\n");
	while(1) {
		sleep(1);
		printf("1 sec...\n");
	}
	printf("End of main\n");
}

void inthandler(int signo) {
	printf("Wake Up!\n");
	exit(0);
}
