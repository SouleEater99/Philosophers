# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <time.h>
# include <unistd.h>

void   *ft_thread(void *data)
{
    printf("++++++++++ { starting threads } +++++++++++\n");
    sleep (3);
    printf("++++++++++ { exit threads } +++++++++++\n");
    return (NULL);
}

void    *routine(void *data)
{
    int *i;
    int j;

    printf("++++++++++ { starting threads } +++++++++++\n");
    i = (int *)data;
    j = 0;
    while (j++ < 10000)
    {
            // printf("+++ {i = %d} +++\n", *i);
            *i = *i + 1;
    }
    printf("++++++++++ { exit threads } +++++++++++\n");
    return (i);
}

int main()
{
    pthread_t   t1;
    pthread_t   t2;
    void    *data;
    int i;

    i = 0;
    if (pthread_create(&t1, NULL, routine, &i) != 0)
        return (1);
    if (pthread_create(&t2, NULL, routine, &i) != 0)
        return (2);
    if (pthread_join(t1, NULL) != 0)
        return (3);
    if (pthread_join(t2, NULL) != 0)
        return (3);
    printf("+++++++++++++++ { i : %d } +++++++++++++++\n", i);
    printf("############## { END OF THE PROGRAM} #################\n");
    return (0);
}