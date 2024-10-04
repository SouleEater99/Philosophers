/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maim <ael-maim@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 04:52:07 by ael-maim          #+#    #+#             */
/*   Updated: 2024/10/04 04:52:09 by ael-maim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_philo	*ft_create_node(t_data *data)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		ft_free_all(data, "Allocation Failed Creating node\n", 1);
	new = memset(new, 0, sizeof(t_philo));
	if (data->i == 0)
		new->left_f = &data->forks[data->n_philo - 1];
	else
		new->left_f = &data->forks[data->i - 1];
	new->rghit_f = &data->forks[data->i];
	new->data = data;
	new->id = data->i;
	new->n_philo_eat = data->n_philo_eat;
	if (pthread_mutex_init(&new->write_mutex, NULL) != 0)
		ft_free_all(data, "Error in init mutex\n", 3);
	if (pthread_mutex_init(&new->meal_mutex, NULL) != 0)
		ft_free_all(data, "Error in init mutex\n", 3);
	if (pthread_mutex_init(&new->eat_mutex, NULL) != 0)
		ft_free_all(data, "Error in init mutex\n", 3);
	if (pthread_mutex_init(&new->still_eat_mutex, NULL) != 0)
		ft_free_all(data, "Error in init mutex\n", 3);
	new->next = NULL;
	return (new);
}

void	ft_add_node_to_back(t_philo *philo, t_philo *new)
{
	t_philo	*head;

	head = philo;
	if (!head)
		return ;
	while (head->next)
		head = head->next;
	if (head)
		head->next = new;
}

void	ft_setup_forks(t_data *data)
{
	t_philo	*new;

	new = NULL;
	data->philo = ft_create_node(data);
	while (++data->i < data->n_philo)
	{
		new = ft_create_node(data);
		ft_add_node_to_back(data->philo, new);
	}
}
