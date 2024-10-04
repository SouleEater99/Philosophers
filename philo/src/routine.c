/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maim <ael-maim@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 05:10:28 by ael-maim          #+#    #+#             */
/*   Updated: 2024/10/04 05:10:29 by ael-maim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_take_forks(t_philo *philo)
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
}

int	ft_is_eating(t_data *data, t_philo *philo)
{
	ft_take_forks(philo);
	ft_write_protect(&philo->still_eat, 0, &philo->still_eat_mutex);
	ft_print_msg("is eating\n", philo, philo->id + 1);
	ft_write_protect(&philo->last_meal, ft_get_timestamp(data),
		&philo->meal_mutex);
	if (data->t_die <= data->t_eat)
	{
		ft_usleep(data, data->t_die);
	}
	else if (data->n_philo % 2 == 1)
	{
		if (data->n_philo == (philo->id + 1))
			ft_usleep(data, data->t_eat * 2);
	}
	else
	{
		ft_usleep(data, data->t_eat);
	}
	ft_write_protect(&philo->still_eat, 1, &philo->still_eat_mutex);
	pthread_mutex_unlock(philo->rghit_f);
	pthread_mutex_unlock(philo->left_f);
	return (1);
}

int	routine_one_philo(t_data *data, t_philo *philo)
{
	if (data->n_philo == 1)
	{
		pthread_mutex_lock(philo->rghit_f);
		ft_print_msg("has taken a fork\n", philo, philo->id + 1);
		ft_usleep(data, data->t_die);
		ft_write_protect(&philo->still_eat, 1, &philo->still_eat_mutex);
		pthread_mutex_unlock(philo->rghit_f);
		return (1);
	}
	return (0);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = (t_data *)philo->data;
	pthread_mutex_lock(&data->main_mutex);
	pthread_mutex_unlock(&data->main_mutex);
	if (routine_one_philo(data, philo) == 1)
		return (NULL);
	if ((philo->id + 1) % 2 == 1)
		ft_usleep(data, 10);
	while (ft_read_protect(&data->died_flag, &data->dead_mutex) != 1)
	{
		ft_is_eating(data, philo);
		ft_print_msg("is sleeping\n", philo, philo->id + 1);
		ft_usleep(data, data->t_sleep);
		ft_print_msg("is thinking\n", philo, philo->id + 1);
		if (--philo->n_philo_eat == 0)
		{
			ft_write_protect(&philo->eating_flag, 1, &philo->eat_mutex);
			break ;
		}
	}
	return (NULL);
}
