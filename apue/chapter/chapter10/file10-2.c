#include <signal.h>
#include <stdio.h>
#include <pwd.h>

static void my_alarm(int signo) {
	struct passwd *rootptr;
	printf("in signal handler\n");
	if ((rootptr = getpwnam("zhangliang08")) == NULL) {
		printf("getpwnam(root) error");
	}
	alarm(1);
}

int main() {
	struct passwd *ptr;
	signal(SIGALRM, my_alarm);
	alarm(1);
	for (;;) {
		if ((ptr = getpwnam("root")) == NULL)
			printf("getpwnam error\n");
		if (strcmp(ptr->pw_name, "root") != 0) {
			printf("return value corrupted@!\n");
		}
	}
	return 0;
}
