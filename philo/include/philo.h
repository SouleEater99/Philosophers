#ifndef PHILo_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philo
{
    int id;
    unsigned long died_flag;
    unsigned long last_meal;
    void      *data;
    pthread_mutex_t *left_f;
    pthread_mutex_t *rghit_f;
    struct s_philo *next;
} t_philo;

typedef struct s_data
{
    char **av;
    int ac;

    int i;
    int n_philo;
    int t_die;
    int t_eat;
    int t_sleep;
    int n_philo_eat;
    int mutex_flag;
    pthread_t *th;
    pthread_mutex_t *forks;
    pthread_mutex_t main_mutex;
    struct timeval start;
    t_philo *philo;

} t_data;



unsigned long ft_get_timestamp(t_data *data);
t_philo *ft_return_id_node(t_philo *philo, int i);
int ft_atoi(const char *str);
int ft_check_args(t_data *data);
int ft_str_are_numbers(char *str);
void ft_destroy_mutex(t_data *data);
void ft_free_all(t_data *data, char *msg, int status);
t_philo *ft_create_node(t_data *data);
void ft_add_node_to_back(t_philo *philo, t_philo *new);
void ft_setup_forks(t_data *data);
void ft_init_mutex(t_data *data);
t_data *ft_init_data(int ac, char **av);
unsigned long     ft_read_protect(void *value, pthread_mutex_t *mutex);
void     ft_write_protect(void *addr, unsigned long new, pthread_mutex_t *mutex);
void    ft_usleep(int time);
void    ft_is_eating(t_data *data, t_philo *philo);
void    *ft_routine(void *arg);
void    ft_monitor(t_data *data, t_philo *philo);
void    ft_creat_threads(t_data *data, t_philo *philo);

#endif