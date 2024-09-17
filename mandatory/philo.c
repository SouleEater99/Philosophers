#include "./include/philo.h"

int ft_str_are_numbers(char *str)
{
        if (!str || !*str)
                return (0);
        if (*str == '+' || *str == '-')
        {
                str++;
                if (!*str)
                        return (0);
        }
        while (*str)
        {
                if (*str < '0' || *str > '9')
                        return (0);
                str++;
        }
        return (1);
}

int ft_check_args(t_data *data)
{
        int i;

        i = 1;
        while (data->av[i])
                if (ft_str_are_numbers(data->av[i++]) == 0)
                        return (0);
        if (data->n_philo < 0 || data->n_philo_eat < 0 || data->t_die < 0)
                return (0);
        else if (data->t_eat < 0 || data->t_sleep < 0)
                return (0);
        return (1);
}

int ft_atoi(const char *str)
{
        int i;
        int sign;
        long long count;

        i = 0;
        count = 0;
        sign = 1;
        while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
                i++;
        if (str[i] == '-' || str[i] == '+')
                if (str[i++] == '-')
                        sign = -sign;
        while (str[i] >= '0' && str[i] <= '9')
        {
                if (count > 9223372036854775807 / 10)
                {
                        if (sign > 0)
                                return (-1);
                        else
                                return (0);
                }
                count = (count * 10) + (str[i] - '0');
                i++;
        }
        return (count * sign);
}

void ft_destroy_mutex(t_data *data)
{
        int i;

        i = 0;
        if (!data)
                return;
        while (i < data->n_philo)
                pthread_mutex_destroy(&data->forks[i++]); // i need to protect destroy mutex
}

void ft_init_mutex(t_data *data)
{
        int i;

        i = 0;
        if (!data)
                return;
        while (i < data->n_philo)
                pthread_mutex_init(&data->forks[i++], NULL); // i need to protect mutex creation.
        data->mutex_flag = 1;
}

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
                data->n_philo_eat = -1;
        data->th = malloc(sizeof(pthread_t) * data->n_philo);
        data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
        if (!data->th || !data->forks)
                ft_free_all(data, "Error in creating fork or threads\n", 1);
        return (data);
}



t_philo *ft_create_node(t_data *data)
{
        t_philo *new;

        new = malloc(sizeof(t_philo));
        if (!new)
                ft_free_all(data, "Allocation Failed Creating node\n", 1);
        new = memset(new, 0, sizeof(t_philo));
        if (data->i == 0)
                new->left_f = &data->forks[data->n_philo - 1];
        else
                new->left_f = &data->forks[data->i - 1];
        new->rghit_f = &data->forks[data->i];
        new->next = NULL;
        return (new);
}

void ft_add_node_to_back(t_philo *philo, t_philo *new)
{
        t_philo *head;

        head = philo;
        if (!head)
                return;
        while (head->next)
                head = head->next;
        if (head)
                head->next = new;
}

void ft_setup_forks(t_data *data)
{
        t_philo *new;

        new = NULL;
        data->philo = ft_create_node(data);
        while (++data->i < data->n_philo)
        {
                new = ft_create_node(data);
                ft_add_node_to_back(data->philo, new);
        }
}

void *ft_pthread(void *data2)
{
        t_data  *data;

        data = (t_data *)data2;
        printf("+++++ {i : %d} +++++\n", data->i);
        return (NULL);
}

void ft_create_thread(t_data *data, t_philo *philo)
{
        data->i = 0;
        while (data->i < data->n_philo)
        {
                if (pthread_create(&data->th[data->i], NULL, ft_pthread, data) != 0)
                        ft_free_all(data, "Failed Creating Thread\n", 2);
                philo->id = data->th[data->i++];
        }
        data->i = 0;
        while (data->i < data->n_philo)
                pthread_join(data->th[data->i++], NULL);
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