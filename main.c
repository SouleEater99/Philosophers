#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>

// A normal C function that is executed as a thread
// when its name is specified in pthread_create()
int a = 0;
pthread_mutex_t mutex;

void *myThreadFun(void *vargp)
{
    int i = 0;
    while (i++ < 100000)
	{
			pthread_mutex_lock(&mutex);
  	      	a++;
			pthread_mutex_unlock(&mutex);
	}
	pthread_mutex_lock(&mutex);
	printf("value of a = %d\n",a);
	pthread_mutex_unlock(&mutex);
}

int main()
{
	pthread_t t1, t2;

	if (pthread_mutex_init(&mutex, NULL) != 0)
		return (1);
	printf("Before Thread\n");
	if (pthread_create(&t1, NULL, myThreadFun, NULL) != 0)
		return (0);
	if (pthread_create(&t2, NULL, myThreadFun, NULL) != 0)
		return (0);
	if (pthread_join(t2, NULL) != 0)
		return (0);
	if (pthread_join(t1, NULL) != 0)
		return (0);
	pthread_mutex_destroy(&mutex);
	printf("After Thread\n");
	printf("a = %d\n",a);
	exit(0);
}
