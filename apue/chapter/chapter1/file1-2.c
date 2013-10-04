#include <stdio.h>
#include <unistd.h>

#define BUFFERSIZE 4096

int main() {
	int n;
	char buf[BUFFERSIZE];

	while ((n = read(STDIN_FILENO, buf, BUFFERSIZE)) > 0) {
		if ((write(STDOUT_FILENO, buf, n)) != n)
			printf("write error\n");
	}

	if (n < 0)
		printf("read error\n");
	
	return 0;
}

