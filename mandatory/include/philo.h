# ifndef PHILo_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>

typedef struct  s_data
{
    char    **av;
    int     ac;
    
    int     n_philo;
    int     t_die;
    int     t_eat;
    int     t_sleep;
    int     n_philo_eat;
} t_data;



# endif