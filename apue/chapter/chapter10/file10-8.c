#include <stdio.h>
#include <setjmp.h>
#include <signal.h>

void sig_alrm(int);
jmp_buf env_alrm;
const int kMaxLine = 1000;

#define STDIN_FILENO 0
#define STDOUT_FILENO 1

int main() {
	int n;
	char line[kMaxLine];
	
	if (setjmp(env_alrm) != 0) {
		printf("read time out\n");
	}
	if (signal(SIGALRM, sig_alrm) == SIG_ERR) {
		printf("signal[SIGALRM] Failed\n");
		return -1;
	}

	printf("here\n");

	alarm(10);
	if ((n = read(STDIN_FILENO, line, kMaxLine)) < 0) {
		printf("read error\n");
	}
	alarm(0);
	write(STDOUT_FILENO, line, n);
	fflush(stdout);
	exit(0);
}

void sig_alrm(int signo) {
	longjmp(env_alrm, 1);
}
