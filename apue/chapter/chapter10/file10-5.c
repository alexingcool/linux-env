#include <stdio.h>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>

static jmp_buf env_alrm;

static void sig_alrm(int signo) {
	printf("sig_alrm\n");
	longjmp(env_alrm, 1);
	printf("can't be here\n");
}

unsigned int sleep2(unsigned int nsecs) {
	if (signal(SIGALRM, sig_alrm) == SIG_ERR) {
		return nsecs;
	}
	if (setjmp(env_alrm) == 0) {
		printf("here\n");
		alarm(nsecs);
		pause();
	}
	return alarm(0);
}

int main() {
	printf("before sleep\n");
	sleep2(5);
	printf("after sleep\n");
	return 0;
}
