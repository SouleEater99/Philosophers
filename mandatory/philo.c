#include "./include/philo.h"

int     ft_str_are_numbers(char *str)
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

int     ft_check_args(t_data *data)
{
        int     i;

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

int     ft_atoi(const char *str)
{
        int                     i;
        int                     sign;
        long long       count;

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

t_data  *ft_init_data(int ac, char **av)
{
        t_data  *data;

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
        return (data);
}

void    ft_free_all(t_data *data, char *msg, int status)
{
        if (data)
        {
                free(data);
        }
        printf("%s", msg);
        exit(status);
}

int     main(int ac, char **av)
{
        t_data  *data;

        data = NULL;
        if (ac != 6 && ac != 5 )
                return (0);
        data = ft_init_data(ac, av);
        if (!data)
                return (0);
        printf("n_philo : %d\n", data->n_philo);
        printf("n_die : %d\n", data->t_die);
        printf("n_eat : %d\n", data->t_eat);
        printf("n_sleep : %d\n", data->t_sleep);
        printf("n_philo_eat : %d\n", data->n_philo_eat);
        printf("############################\n");
        if (ft_check_args(data) == 0)
                ft_free_all(data, "Input Error\n", 1);
        printf("+++++++++++++ { DONE } +++++++++++++++\n");

    
        return (0);
}