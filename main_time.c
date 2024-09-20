/* times: use gettimeofday() to get the elapsed time */
/* Paul Krzyzanowski */

#include <stdio.h>		/* declares printf() */
#include <stdlib.h>		/* declares exit() */
#include <stdint.h>		/* used for casting clock_t to uintmax_t for printf */
#include <sys/time.h>		/* needed for the gettimeofday() system call */

unsigned long     ft_get_timestamp(struct timeval start)
{
        struct timeval end;
        unsigned long u_start;
        unsigned long u_sec;
        unsigned long m_sec;

        gettimeofday(&end, NULL);
        u_start = ((start.tv_sec * 1000000) + start.tv_usec);
        u_sec = ((end.tv_sec * 1000000) + end.tv_usec) - u_start;
        m_sec = u_sec / 1000;
        return (m_sec);
}

int	main(int argc, char **argv) {
	struct timeval start;	/* starting time */
	unsigned long e_usec;	/* elapsed microseconds */

	gettimeofday(&start, 0);	/* mark the start time */
	sleep(2);		/* sleep for 2 seconds */
	e_usec = ft_get_timestamp(start);
	/* now we can do the math. timeval has two elements: seconds and microseconds */
	// e_usec = ((end.tv_sec * 1000000) + end.tv_usec) - ((start.tv_sec * 1000000) + start.tv_usec);

    printf("start tv_sec:  %lu \n", start.tv_sec);
    printf("start tv_usec:  %lu \n", start.tv_usec);
	printf("elapsed time: %lu microseconds\n", e_usec);
	exit(0);
}