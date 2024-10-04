/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maim <ael-maim@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 04:52:19 by ael-maim          #+#    #+#             */
/*   Updated: 2024/10/04 04:52:21 by ael-maim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_creat_threads(t_data *data, t_philo *philo)
{
	int		i;
	int		j;
	t_philo	*head;

	head = philo;
	j = 0;
	i = 0;
	if (!data || !philo)
		return ;
	pthread_mutex_lock(&data->main_mutex);
	while (i < data->n_philo)
	{
		if (pthread_create(&data->th[i], NULL, ft_routine, head) != 0)
			ft_free_all(data, "Error in creating threads\n", 1);
		if (head)
			head = head->next;
		i++;
	}
	if (gettimeofday(&data->start, NULL) != 0)
		ft_free_all(data, "Error in gettimeofday\n", 1);
	pthread_mutex_unlock(&data->main_mutex);
	ft_monitor(data, philo);
	while (j < data->n_philo)
		if (pthread_join(data->th[j++], NULL) != 0)
			ft_free_all(data, "Error in pthread join\n", 1);
}

int	main(int ac, char **av)
{
	t_data	*data;

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
	ft_creat_threads(data, data->philo);
	ft_destroy_mutex(data);
	return (0);
}
