#include "./include/philo.h"

void ft_free_all(t_data *data, char *msg, int status)
{
        if (data)
        {
                if (data->th)
                        free(data->th);
                if (data->forks)
                        free(data->forks);
                if (data->mutex_flag == 1)
                        ft_destroy_mutex(data);
                free(data);
        }
        printf("%s", msg);
        exit(status);
}

void ft_destroy_mutex(t_data *data)
{
        int i;

        i = 0;
        if (!data)
                return;
        pthread_mutex_destroy(&data->main_mutex_left);
        pthread_mutex_destroy(&data->main_mutex_right);
        while (i < data->n_philo)
        {
                pthread_mutex_destroy(&data->forks[i++]);
        }
                        
}