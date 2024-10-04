/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maim <ael-maim@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 04:54:34 by ael-maim          #+#    #+#             */
/*   Updated: 2024/10/04 04:54:35 by ael-maim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_check_is_all_eat(t_philo *philo)
{
	t_philo	*head;

	head = philo;
	while (head)
	{
		if (ft_read_protect(&head->eating_flag, &head->eat_mutex) != 1)
			return (0);
		head = head->next;
	}
	return (1);
}

int	monitor_check_die(t_data *data, t_philo *head)
{
	if ((ft_get_timestamp(data) - ft_read_protect(&head->last_meal,
				&head->meal_mutex)) >= (unsigned long)data->t_die)
	{
		ft_write_protect(&data->died_flag, 1, &data->dead_mutex);
		usleep(300);
		pthread_mutex_lock(&data->write_mutex);
		printf("%lu %d died\n", ft_get_timestamp(head->data), head->id + 1);
		pthread_mutex_unlock(&data->write_mutex);
		return (1);
	}
	return (0);
}

void	ft_monitor(t_data *data, t_philo *philo)
{
	t_philo	*head;

	if (!philo)
		return ;
	head = philo;
	while (1)
	{
		if (ft_check_is_all_eat(philo) == 1)
			break ;
		if (ft_read_protect(&head->eating_flag, &head->eat_mutex) != 1)
			if (ft_read_protect(&head->still_eat, &head->still_eat_mutex) == 1)
				if (monitor_check_die(data, head) == 1)
					break ;
	}
	if (!head->next)
		head = philo;
	else
		head = head->next;
}
