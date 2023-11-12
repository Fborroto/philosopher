/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fborroto <fborroto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:13:10 by fborroto          #+#    #+#             */
/*   Updated: 2023/11/12 18:47:13 by fborroto         ###   ########.fr       */
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

void	print_state(char *str, t_platone *philo)
{
	pthread_mutex_lock(&philo->time_lock);
	printf("%zu %i %s", ft_get_time() - philo->time_start, philo->index, str);
	pthread_mutex_unlock(&philo->time_lock);
}

void	ft_eating(t_platone *philo)
{
	pthread_mutex_lock(&philo->fork_lock);
	monitoring(philo, FORK);
	pthread_mutex_lock(&philo->next->fork_lock);
	monitoring(philo, FORK);
	pthread_mutex_lock(&philo->info->monitoring_mutex);
	philo->last_meal = ft_get_time();
	philo->n_meals++;
	pthread_mutex_unlock(&philo->info->monitoring_mutex);
	monitoring(philo, EAT);
	usleep(philo->info->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->fork_lock);
	pthread_mutex_unlock(&philo->next->fork_lock);
}


