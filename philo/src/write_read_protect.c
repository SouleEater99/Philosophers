/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_read_protect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maim <ael-maim@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 04:56:11 by ael-maim          #+#    #+#             */
/*   Updated: 2024/10/04 04:56:13 by ael-maim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

unsigned long	ft_read_protect(void *value, pthread_mutex_t *mutex)
{
	unsigned long	i;

	i = 0;
	pthread_mutex_lock(mutex);
	i = *((unsigned long *)value);
	pthread_mutex_unlock(mutex);
	return (i);
}

void	ft_write_protect(void *addr, unsigned long new, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	*((unsigned long *)addr) = new;
	pthread_mutex_unlock(mutex);
}

void	ft_usleep(t_data *data, int i)
{
	unsigned long	start;

	start = ft_get_timestamp(data);
	while (ft_get_timestamp(data) - start < (unsigned long)i)
		usleep(100);
}

void	ft_print_msg(char *msg, t_philo *philo, int id)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&philo->write_mutex);
	if (ft_read_protect(&data->died_flag, &data->dead_mutex) != 1)
		printf("%lu %d %s", ft_get_timestamp(data), id, msg);
	pthread_mutex_unlock(&philo->write_mutex);
}
