#include "./include/philo.h"

void *ft_pthread(void *data2)
{
        t_data  *data;
        t_philo *philo;
        int     i;

        data = (t_data *)data2;
        pthread_mutex_lock(&data->main_mutex_left);
        i = data->i;
        printf("++++++++ {%d} ++++++++\n", i);
        pthread_mutex_unlock(&data->main_mutex_left);
        pthread_mutex_lock(&data->main_mutex_right);
        philo = ft_return_id_node(data->philo, i);
        if (!philo)
                ft_free_all(data, "ERROR NULL in PHILO\n", 4);
        printf("++++++ {index : %d} ++++++\n", philo->index);
        pthread_mutex_unlock(&data->main_mutex_right);
        while (1)
        {
                pthread_mutex_lock(philo->left_f);
                pthread_mutex_lock(philo->rghit_f);
                printf("%lu %d has taken a fork\n", ft_get_timestamp(data), i);
                usleep(data->t_eat * 1000);
                printf("%lu %d is eating\n", ft_get_timestamp(data), i);
                pthread_mutex_unlock(philo->left_f);
                usleep(data->t_sleep * 1000);
                printf("%lu %d is sleeping\n", ft_get_timestamp(data), i);
                pthread_mutex_unlock(philo->rghit_f);
                printf("%lu %d is thinking\n", ft_get_timestamp(data), i);
                usleep(100*1000);
        }
        return (NULL);
}

void ft_create_thread(t_data *data, t_philo *philo)
{
        t_philo *head;
        int     j;

        head = philo;
        data->i = 0;
        j = 0;
        pthread_mutex_lock(&data->main_mutex_right); // need to protect mutex
        while (data->i < data->n_philo)
        {
                pthread_mutex_lock(&data->main_mutex_left); // need to protect mutex
                if (pthread_create(&data->th[data->i], NULL, ft_pthread, data) != 0)
                        ft_free_all(data, "Failed Creating Thread\n", 2);
                if (head)
                {
                        head->id = data->th[data->i];
                        head->index = data->i;
                        head = head->next;
                }
                // printf("$$$$$$$$$ {i : %d} $$$$$$$$$$\n", data->i);
                pthread_mutex_unlock(&data->main_mutex_left); // need tp protect mutex
                usleep(1000);
                data->i++;
        }
        pthread_mutex_unlock(&data->main_mutex_right); // need tp protect mutex
        if (gettimeofday(&data->start, NULL) != 0)
                ft_free_all(data, "Failed gettimeofday\n", 2);
        while (j < data->n_philo)
                pthread_join(data->th[j++], NULL);
}

int main(int ac, char **av)
{
        t_data *data;

        data = NULL;
        if (ac != 6 && ac != 5)
                return (0);
        data = ft_init_data(ac, av);
        if (!data)
                return (0);
        if (ft_check_args(data) == 0)
                ft_free_all(data, "Input Error\n", 1);
        ft_init_mutex(data);
        ft_setup_forks(data);
        ft_create_thread(data, data->philo);

        ft_destroy_mutex(data);
        printf("+++++++++++++ { DONE} +++++++++++++++\n");
        return (0);
}