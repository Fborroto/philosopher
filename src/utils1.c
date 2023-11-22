/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fborroto <fborroto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:13:10 by fborroto          #+#    #+#             */
/*   Updated: 2023/11/22 14:37:27 by fborroto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// void	ft_sleep(size_t milliseconds, t_platone *philo)
// {
// 	unsigned long	start;

// 	start = ft_get_time();
// 	pthread_mutex_lock(&philo->info->monitoring_mutex);
// 	while (philo->info->died == 0 && (ft_get_time() - start) < milliseconds)
// 		usleep(50);
// 	pthread_mutex_unlock(&philo->info->monitoring_mutex);
// }

unsigned long	ft_get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

static void	pick_forks(t_platone *philo)
{
	if (philo->index % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork_lock);
		monitoring(philo, FORK);
		pthread_mutex_lock(&philo->next->fork_lock);
		monitoring(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->next->fork_lock);
		monitoring(philo, FORK);
		pthread_mutex_lock(&philo->fork_lock);
		monitoring(philo, FORK);
	}
}

static void	drop_forks(t_platone *philo)
{
	if (philo->index % 2 == 0)
	{
		pthread_mutex_unlock(&philo->fork_lock);
		monitoring(philo, DROP);
		pthread_mutex_unlock(&philo->next->fork_lock);
		monitoring(philo, DROP);
	}
	else
	{
		pthread_mutex_unlock(&philo->next->fork_lock);
		monitoring(philo, DROP);
		pthread_mutex_unlock(&philo->fork_lock);
		monitoring(philo, DROP);
	}
}

void	ft_eating(t_platone *philo)
{
	pick_forks(philo);
	monitoring(philo, EAT);
	pthread_mutex_lock(&philo->info->monitoring_mutex);
	philo->last_meal = ft_get_time();
	philo->n_meals++;
	pthread_mutex_unlock(&philo->info->monitoring_mutex);
	usleep(philo->info->time_to_eat * 1000);
	drop_forks(philo);
}
