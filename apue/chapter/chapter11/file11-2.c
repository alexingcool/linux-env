#include <stdio.h>
#include <pthread.h>

void* thr_fn1(void *arg) {
	printf("entering thr_fn1\n");
	return ((void*)1);
}

void* thr_fn2(void *arg) {
	printf("entering thr_fn2\n");
	pthread_exit ((void*)2);
}

int main() {
	int err;
	pthread_t tid1, tid2;
	void *tret;

	err = pthread_create(&tid1, NULL, thr_fn1, NULL);
	if (err != 0) {
		printf("can't create pthread1\n");
	}
	err = pthread_create(&tid2, NULL, thr_fn2, NULL);
	if (err != 0) {
		printf("can't create pthread2\n");
	}
	err = pthread_join(tid1, &tret);
	if (err != 0) {
		printf("pthread join failed\n");
	}
	printf("thread1 exit code: %d\n", (int)tret);
	err = pthread_join(tid2, &tret);
	if (err != 0) {
		printf("pthread join failed\n");
	}
	printf("thread2 exit code: %d\n", (int)tret);
	return 0;
}
