#include <stdio.h>
#include <unistd.h>

int main() {
	int c;
	while ((c = getc(stdin)) != '\n') {
		if (putc(c, stdout) == EOF) {
			printf("output error\n");
		}
	}

	return 0;
}
