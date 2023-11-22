#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int child_id;

void intHandler();
void intHandler2();
void intHandler3();

void process() {
	for(int i = 1; i <= 9; i++) {
		printf("%d단\n", i);
		for(int j = 1; j <= 9; j++) {
			printf("%d x %d = %d\n", i, j, i * j);
		}
		if(i == 9)
			signal(SIGINT, intHandler3);
		sleep(1);
	}
}

int main() {
	int pid;
	if((pid=fork()) == 0) {
		signal(SIGINT, intHandler2);
		process();
		pause();
	}
	else {
		child_id = pid;
		signal(SIGINT, intHandler);
		wait();
	}
}

void intHandler(int signo) {
	kill(child_id, SIGINT);
}

void intHandler2(int signo) {
	printf("\ncannot terminate\n");
}

void intHandler3(int signo) {
	kill(-getppid(), SIGKILL);
}


