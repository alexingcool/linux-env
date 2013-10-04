#include <stdio.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/param.h>
#include <unistd.h>

int main() {
	long openmax;
	if ((openmax = sysconf(_SC_OPEN_MAX)) < 0) {
		printf("openmax = %d\n", openmax);
	}
	printf("openmax = %d\n", openmax);
	return 0;
}
