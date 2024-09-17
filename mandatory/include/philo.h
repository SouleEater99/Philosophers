# ifndef PHILo_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>

typedef struct  s_philo
{
    pthread_t       id;
    pthread_mutex_t *left_f;
    pthread_mutex_t *rghit_f;
    struct s_philo  *next;
} t_philo;

typedef struct  s_data
{
    char    **av;
    int     ac;
    
    int              i;
    int              n_philo;
    int              t_die;
    int              t_eat;
    int              t_sleep;
    int              n_philo_eat;
    int              mutex_flag;
    pthread_t        *th;
    pthread_mutex_t  *forks;
    t_philo          *philo;
} t_data;




# endif