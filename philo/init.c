#include "./include/philo.h"

void ft_init_mutex(t_data *data)
{
        int i;

        i = 0;
        if (!data)
                return;
        if (pthread_mutex_init(&data->main_mutex, NULL) != 0)
                ft_free_all(data, "Error in init mutex\n", 3); 
        if (pthread_mutex_init(&data->dead_mutex, NULL) != 0)
                ft_free_all(data, "Error in init mutex\n", 3);
        if (pthread_mutex_init(&data->write_mutex, NULL) != 0)
                ft_free_all(data, "Error in init mutex\n", 3);
        while (i < data->n_philo)
                if (pthread_mutex_init(&data->forks[i++], NULL) != 0)
                        ft_free_all(data, "Error in init mutex\n", 3);
        data->mutex_flag = 1;
}


t_data *ft_init_data(int ac, char **av)
{
        t_data *data;

        data = malloc(sizeof(t_data));
        if (!data)
                return (NULL);
        data = memset(data, 0, sizeof(t_data));
        data->ac = ac;
        data->av = av;
        data->n_philo = ft_atoi(av[1]);
        data->t_die = ft_atoi(av[2]);
        data->t_eat = ft_atoi(av[3]);
        data->t_sleep = ft_atoi(av[4]);
        if (ac == 6)
                data->n_philo_eat = ft_atoi(av[5]);
        else
                data->n_philo_eat = 0;
        data->th = malloc(sizeof(pthread_t) * data->n_philo);
        data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
        if (!data->th || !data->forks)
                ft_free_all(data, "Error in creating fork or threads\n", 1);
        return (data);
}

