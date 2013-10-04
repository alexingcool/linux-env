#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

const int kMaxLine = 100;

int main() 
{
	char buf[kMaxLine];
	char printbuf[2 * kMaxLine];
	pid_t pid;
	int status;

	printf("%% ");
	while (fgets(buf, kMaxLine, stdin) != NULL) {
		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = 0;
		pid = fork();
		if (pid < 0) {
			printf("fork failed\n");
		} else if (pid == 0) {
			strcpy(printbuf, "excuting cmd:");
			strcat(printbuf, buf);
			strcat(printbuf, "\n");
			fputs(printbuf, stdout);
			fflush(stdout);
			execlp(buf, buf, (char*)0);
			exit(0);
		}

		if ((pid = waitpid(pid, &status, 0)) < 0) {
			printf("waitpid failed\n");
		}
		printf("%% ");
	}
	
	return 0;
}
