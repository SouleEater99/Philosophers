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

t_philo         *ft_return_id_node(t_philo *philo, int i)
{
        t_philo *ph;

        ph = philo;
        while (ph)
        {
                if (ph->id == i)
                        break;
                ph = ph->next;
        }
        return (ph);
}

unsigned long     ft_get_timestamp(t_data *data)
{
        struct timeval end;
        unsigned long u_start;
        unsigned long u_sec;
        unsigned long m_sec;

        gettimeofday(&end, NULL);
        u_start = ((data->start.tv_sec * 1000000) + data->start.tv_usec);
        u_sec = ((end.tv_sec * 1000000) + end.tv_usec) - u_start;
        m_sec = u_sec / 1000;
        return (m_sec);
}

