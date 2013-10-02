#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <setjmp.h>

jmp_buf env_alrm;

void sig_alrm(int signo) {
	printf("\nsignal ing\n");
}

unsigned int sleep1(unsigned int nsecs) {
	if (signal(SIGALRM, sig_alrm) == SIG_ERR) {
		return nsecs;
	}
	alarm(nsecs);
	pause();
	return alarm(0);
}

void sig_chld(int arg) {
	printf("received sigchld\n");
	longjmp(env_alrm, 1);
}

int main() {
	int n = 10;
	if (signal(SIGCHLD, sig_chld) == SIG_ERR) {
		printf("signal failed\n");
		return -1;
	}
	pid_t pid;
	pid = fork();
	if (pid < 0) {
		printf("fork process failed\n");
		return -1;
	} else if (pid == 0) {
		sleep1(n);
		exit(0);
	}

	if (setjmp(env_alrm) == 0) 
	{
		while (1) {
			printf("!");
			fflush(stdout);
			sleep(1);
		}
	}

	return 0;
}
