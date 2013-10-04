#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>

int main() {
	const int kLen = 1000;
	char buff[kLen];
	pid_t pid;
	int status;

	printf("%% ");
	while (fgets(buff, kLen, stdin) != NULL) {
		if (buff[strlen(buff) - 1] == '\n') {
			buff[strlen(buff) - 1] = 0;
		}
		if ((pid = fork()) < 0) {
			printf("fork error\n");
		} else if (pid == 0) {
			execlp(buff, buff, (char*)0);
			printf("couldn't execute: %s", buff);
			exit(127);
		}

		if ((pid = waitpid(pid, &status, 0)) < 0) {
			printf("waitpid error");
		}
		printf("%% ");
	}
	exit(0);
}
