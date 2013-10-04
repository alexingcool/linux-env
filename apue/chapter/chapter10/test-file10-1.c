#include <signal.h>
#include <stdio.h>

void sig_usr(int signo) {
	if (signo == SIGUSR1) {
		printf("the signo is sigusr1\n");
	}
	if (signo == SIGUSR2) {
		printf("the signo is SIGUSR2\n");
	}
}

int main() {
	if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
		printf("signal failed\n");
	}
	if (signal(SIGUSR2, sig_usr) == SIG_ERR) {
		printf("signal failed\n");
	}
	for (;;) {
		pause();
	}
	return 0;
}
