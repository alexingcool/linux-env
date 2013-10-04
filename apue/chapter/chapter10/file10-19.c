#include <stdio.h>
#include <sys/types.h>
#include <signal.h>

static void sig_int(int signo) {
	printf("caught signal\n");
}

static void sig_chld(int signo) {
	printf("caught sigchild\n");
}

int main() {
	if (signal(SIGINT, &sig_int) == SIG_ERR)
		printf("caught SIGINT failed\n");
	if (signal(SIGCHLD, &sig_chld) == SIG_ERR) 
		printf("caught SIGCHLD failed\n");
	if (system("/bin/ed") < 0)
		printf("system() error\n");
	return 0;
}
