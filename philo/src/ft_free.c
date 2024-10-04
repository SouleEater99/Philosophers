/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maim <ael-maim@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 04:52:01 by ael-maim          #+#    #+#             */
/*   Updated: 2024/10/04 04:52:03 by ael-maim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_free_philos(t_data *data)
{
	t_philo	*head;
	t_philo	*tmp;

	head = data->philo;
	while (head)
	{
		tmp = head->next;
		free(head);
		head = tmp;
	}
}

void	ft_free_all(t_data *data, char *msg, int status)
{
	if (data)
	{
		if (data->th)
			free(data->th);
		if (data->forks)
			free(data->forks);
		if (data->mutex_flag == 1)
			ft_destroy_mutex(data);
		if (data->philo)
			ft_free_philos(data);
		free(data);
	}
	if (msg)
		printf("%s", msg);
	exit(status);
}

void	ft_destroy_mutex(t_data *data)
{
	int		i;
	t_philo	*head;

	i = 0;
	head = data->philo;
	if (!data)
		return ;
	pthread_mutex_destroy(&data->main_mutex);
	pthread_mutex_destroy(&data->dead_mutex);
	pthread_mutex_destroy(&data->write_mutex);
	while (head)
	{
		pthread_mutex_destroy(&head->meal_mutex);
		pthread_mutex_destroy(&head->write_mutex);
		pthread_mutex_destroy(&head->eat_mutex);
		pthread_mutex_destroy(&head->still_eat_mutex);
		head = head->next;
	}
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(&data->forks[i++]);
	}
}
