#include "./include/philo.h"

unsigned long ft_read_protect(void *value, pthread_mutex_t *mutex)
{
        unsigned long i;

        i = 0;
        pthread_mutex_lock(mutex);
        i = *((unsigned long *)value);
        pthread_mutex_unlock(mutex);
        return (i);
}

void ft_write_protect(void *addr, unsigned long new, pthread_mutex_t *mutex)
{
        pthread_mutex_lock(mutex);
        *((unsigned long *)addr) = new;
        pthread_mutex_unlock(mutex);
}

void ft_usleep(t_data *data, int i)
{
        unsigned long start;

        start = ft_get_timestamp(data);
        while (ft_get_timestamp(data) - start < (unsigned long)i)
                ;
}

void ft_print_msg(char *msg, t_philo *philo, int id)
{
        t_data *data;

        data = philo->data;
        pthread_mutex_lock(&philo->write_mutex);
        if (ft_read_protect(&data->died_flag, &data->dead_mutex) != 1)
                printf("%lu %d %s", ft_get_timestamp(data), id, msg);
        pthread_mutex_unlock(&philo->write_mutex);
}

int ft_is_eating(t_data *data, t_philo *philo)
{

        if (philo->id % 2 == 1)
        {

                pthread_mutex_lock(philo->left_f);
                ft_print_msg("has taken a fork\n", philo, philo->id + 1);
                pthread_mutex_lock(philo->rghit_f);
                ft_print_msg("has taken a fork\n", philo, philo->id + 1);
        }
        else
        {
                pthread_mutex_lock(philo->rghit_f);
                ft_print_msg("has taken a fork\n", philo, philo->id + 1);
                pthread_mutex_lock(philo->left_f);
                ft_print_msg("has taken a fork\n", philo, philo->id + 1);
        }
        ft_write_protect(&philo->still_eat, 0, &philo->still_eat_mutex);
        ft_print_msg("is eating\n", philo, philo->id + 1);
        ft_write_protect(&philo->last_meal, ft_get_timestamp(data), &philo->meal_mutex);
        if (data->t_die <= data->t_eat)
                ft_usleep(data, data->t_die);
        else
                ft_usleep(data, data->t_eat);
        ft_write_protect(&philo->still_eat, 1, &philo->still_eat_mutex);
        pthread_mutex_unlock(philo->rghit_f);
        pthread_mutex_unlock(philo->left_f);
        return (1);
}

void *ft_routine(void *arg)
{
        t_philo *philo;
        t_data *data;

        philo = (t_philo *)arg;
        data = (t_data *)philo->data;
        pthread_mutex_lock(&data->main_mutex);
        pthread_mutex_unlock(&data->main_mutex);
        while (ft_read_protect(&data->died_flag, &data->dead_mutex) != 1)
        {
                ft_is_eating(data, philo);
                ft_print_msg("is sleeping\n", philo, philo->id + 1);
                ft_usleep(data, data->t_sleep);
                ft_print_msg("is thinking\n", philo, philo->id + 1);
                if (--philo->n_philo_eat == 0)
                {
                        ft_write_protect(&philo->eating_flag, 1, &philo->eat_mutex);
                        break;
                }
        }
        return (NULL);
}

int ft_check_is_all_eat(t_philo *philo)
{
        t_philo *head;

        head = philo;
        while (head)
        {
                if (ft_read_protect(&head->eating_flag, &head->eat_mutex) != 1)
                        return (0);
                head = head->next;
        }
        return (1);
}

void ft_monitor(t_data *data, t_philo *philo)
{
        t_philo *head;

        if (!philo)
                return;
        head = philo;
        while (1)
        {
                if (ft_check_is_all_eat(philo) == 1)
                        break;
                if (ft_read_protect(&head->eating_flag, &head->eat_mutex) != 1)
                {
                        if (ft_read_protect(&head->still_eat, &head->still_eat_mutex) == 1)
                        {
                                if ((ft_get_timestamp(data) - ft_read_protect(&head->last_meal, &head->meal_mutex)) >= (unsigned long)data->t_die)
                                {

                                        printf("last meal is %lu of %d\n", head->last_meal, head->id + 1);
                                        printf("time to die is %d\n", data->t_die);
                                        ft_write_protect(&data->died_flag, 1, &data->dead_mutex);
                                        usleep(100);
                                        pthread_mutex_lock(&data->write_mutex);
                                        printf("%lu %d died\n", ft_get_timestamp(head->data), head->id + 1);
                                        pthread_mutex_unlock(&data->write_mutex);
                                        break;
                                }
                        }
                }
                if (!head->next)
                        head = philo;
                else
                        head = head->next;
        }
}

void ft_creat_threads(t_data *data, t_philo *philo)
{
        int i;
        int j;
        t_philo *head;

        head = philo;
        j = 0;
        i = 0;
        if (!data || !philo)
                return;
        pthread_mutex_lock(&data->main_mutex);
        while (i < data->n_philo)
        {
                if (pthread_create(&data->th[i], NULL, ft_routine, head) != 0)
                        ft_free_all(data, "Error in creating threads\n", 1);
                if (head)
                        head = head->next;
                i++;
        }
        if (gettimeofday(&data->start, NULL) != 0)
                ft_free_all(data, "Error in gettimeofday\n", 1);
        pthread_mutex_unlock(&data->main_mutex);
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