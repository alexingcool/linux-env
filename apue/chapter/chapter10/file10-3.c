#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

static void sig_cld(int);

int main() {
	pid_t pid;
	if (signal(SIGCLD, sig_cld) == SIG_ERR) {
		printf("signal error");
	}
	if ((pid = fork()) < 0) {
		printf("fork error\n");
	} else if (pid == 0) {
		_exit(0);
	}

	pause();
	exit(0);
}

static void sig_cld(int signo) {
	pid_t pid;
	int status;
	printf("SIGCLD received\n");
	if (signal(SIGCLD, sig_cld) == SIG_ERR) {
		printf("signal error\n");
	}
	if ((pid = wait(&status)) < 0) {
		printf("wait error\n");
	}
	printf("pid = %d\n", pid);
}
