#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include <signal.h>

pid_t wgetpid;
pthread_cond_t cond;

long GetSize(const char *dirsize);
void sig_arm(void *sigarm) {}

int mystrcmp(const char *lhs, const char *rhs) {
    if (lhs == NULL || rhs == NULL) {
        return -1;
    }

    long lhsize = GetSize(lhs);
    long rhsize = GetSize(rhs);
    printf("lhs = %s\trhs = %s\n", lhs, rhs);
    printf("lhsize = %d\trhsize = %d\n", lhsize, rhsize);
    return lhsize > rhsize;
}

long GetSize(const char *dirsize) {
    if (dirsize == NULL) {
        return -1;
    }

    long totalsize = 0;
    int filelen = strlen(dirsize);
    switch (dirsize[filelen - 1])
    {
        case 'K':
            totalsize = atoi(dirsize) * 1000;
            break;
        case 'M':
            totalsize = atoi(dirsize) * 1000 * 1000;
            break;
        case 'G':
            totalsize = atoi(dirsize) * 1000 * 1000 * 1000;
            break;
        default:
            break;
    }
    return totalsize;
}

void* wgetlog(void *arg) {
	const char *cmd = "wget --limit-rate=100K cq01-mobads-se01.cq01:/home/work/mobads/product/apache/logs/access_log.20130924* 2>/dev/null&printf $!";
    printf("enter popen\n");
	FILE *fp = popen(cmd, "r");
	if (fp == NULL) {
		printf("exec cmd: %s failed\n", cmd);
		pthread_exit((void *)-1);
	}
    printf("popen exit\n");
	const int kResultSize = 1000;
	char result[kResultSize];
    printf("prepare reading\n");
	int n = fread(result, sizeof(char), kResultSize, fp);
	if (n == -1) {
		printf("fread failed\n");
	}
    printf("getting pid\n");
	wgetpid = (pid_t)atoi(result);
    printf("wget pid = %d\n", wgetpid);
    printf("arming\n");
    printf("thread wgetlog success!!!\n");
	pthread_exit((void *)&wgetpid);
}

void* stopwget(void *arg) {
    printf("enter stopwget\n");
	while (1) {
        printf("enter while\n");
		sleep(1);
		FILE *fp = popen("du -sh", "r");
		if (fp == NULL) {
			printf("exec cmd: du -sh failed\n");
			pthread_exit((void *)-1);
		}
		const int kResultSize = 1000;
		char result[kResultSize];
		int i = 0;
		int n = fread(result, sizeof(char), kResultSize, fp);
		if (n == -1) {
			printf("fread failed\n");
		}
		while (i < strlen(result)) {
			if (result[i] == ' ' || result[i] == '\t')
				break;
            i++;
		}
		result[i] = 0;
        printf("size = %s\n", result);
        int ret = mystrcmp(result, "2M");
        printf("strcmp: %d\n", ret);
		if (ret == 0)
			continue;
		else 
			break;
	}
	pid_t *ppid = (pid_t)arg;
    while (*ppid == 0) {
        printf("!");
        sleep(1);
    }
    printf("killing pid: %d\n", (int)(*ppid));
	kill(*ppid, SIGKILL);
	pthread_exit((void *)0);
}

int main() {
	pthread_t tid1, tid2;
	void *tret;
    pthread_cond_init(&cond, NULL);
	int err = pthread_create(&tid1, NULL, wgetlog, NULL);
	if (err != 0) {
		printf("pthread create failed\n");
		return -1;
	}
	err = pthread_create(&tid2, NULL, stopwget, &wgetpid);
	if (err != 0) {
		printf("pthread create failed\n");
		return -1;
	}
	err = pthread_join(tid1, &tret);
	if (err != 0) {
		printf("pthread join failed\n");
		return -1;
	}
	err = pthread_join(tid2, &tret);
	if (err != 0) {
		printf("pthread join failed\n");
		return -1;
	}
	return 0;
}


