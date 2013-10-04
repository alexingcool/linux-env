#include <signal.h>
#include <unistd.h>

static void sig_alrm(int signo) {
}

unsigned int sleep1(unsigned int nsecs) {
	if (signal(SIGALRM, sig_alrm) == SIG_ERR) {
		return nsecs;
	}
	alarm(nsecs);
	pause();
	return (alarm(0));
}

int main()
{
	printf("sleep before\n");
	int ret = sleep1(10);
	printf("ret = %d\n", ret);
	printf("after before\n");
	return 0;
}
