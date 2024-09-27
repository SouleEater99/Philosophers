#include "./include/philo.h"

unsigned long     ft_read_protect(void *value, pthread_mutex_t *mutex)
{
        unsigned long i;

        i = 0;
        pthread_mutex_lock(mutex);
        i = *((unsigned long *)value);
        pthread_mutex_unlock(mutex);
        return (i);
}

void     ft_write_protect(void *addr, unsigned long new, pthread_mutex_t *mutex)
{
        pthread_mutex_lock(mutex);
        *((unsigned long *)addr) = new;
        pthread_mutex_unlock(mutex);
}

void    ft_usleep(int time)
{
        unsigned long i;

        i = time * 1000;
        usleep(i);
}

void    ft_is_eating(t_data *data, t_philo *philo)
{
       pthread_mutex_lock(philo->left_f);
       pthread_mutex_lock(philo->rghit_f);
       printf("%lu %d has taken a fork\n", ft_get_timestamp(data), philo->id + 1);
       printf("%lu %d is eating\n", ft_get_timestamp(data), philo->id + 1);
       ft_usleep(data->t_eat);
       philo->last_meal = ft_get_timestamp(data);
       pthread_mutex_lock(philo->left_f);
       pthread_mutex_lock(philo->rghit_f);
}

void    *ft_routine(void *arg)
{
        t_philo *philo;
        t_data  *data;

        philo = (t_philo *)arg;
        data = (t_data *)philo->data;
        pthread_mutex_lock(&data->main_mutex);
        pthread_mutex_unlock(&data->main_mutex);
        while (ft_read_protect(&philo->died_flag, philo->rghit_f) != 1)
        {
                ft_is_eating(data ,philo);
                printf("%lu %d is sleeping\n", ft_get_timestamp(philo->data), philo->id + 1);
                ft_usleep(data->t_sleep);
                printf("%lu %d is thinking\n", ft_get_timestamp(philo->data), philo->id + 1);
        }
        return (NULL);
}

void    ft_monitor(t_data *data, t_philo *philo)
{
        t_philo *head;

        if (!philo)
                return ;
        head = philo;
        while (1)
        {
                if ((ft_get_timestamp(data) - head->last_meal) > (unsigned long)data->t_die)
                {
                        ft_write_protect(&head->died_flag, 1, head->rghit_f);
                        break;
                }
                if (!head->next)
                        head = philo;
                else
                        head = head->next;
        }
        printf("%lu %d died\n", ft_get_timestamp(philo->data), philo->id + 1);
}

void    ft_creat_threads(t_data *data, t_philo *philo)
{
        int     i;
        int     j;
        t_philo *head;

        head = philo;
        j = 0;
        i = 0;
        if (!data || !philo)
                return ;
        pthread_mutex_lock(&data->main_mutex);
        while (i < data->n_philo)
        {
                if (pthread_create(&data->th[i++], NULL, ft_routine, head) != 0)
                        ft_free_all(data, "Error in creating threads\n", 1);
                if (head)
                   head = head->next;
                i++;
        }
        pthread_mutex_unlock(&data->main_mutex);
        if (gettimeofday(&data->start, NULL) != 0)
                ft_free_all(data, "Error in gettimeofday\n", 1);
        ft_monitor(data, philo);
        while (j < data->n_philo)
                if (pthread_join(data->th[j++], NULL) != 0)
                        ft_free_all(data, "Error in pthread join\n", 1);
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
        ft_creat_threads(data, data->philo);

        ft_destroy_mutex(data);
        printf("+++++++++++++ { DONE} +++++++++++++++\n");
        return (0);
}