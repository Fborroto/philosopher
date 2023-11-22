/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fborroto <fborroto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:56:07 by fborroto          #+#    #+#             */
/*   Updated: 2023/11/22 14:12:53 by fborroto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#define TAKE_FORK_STR "has taken a fork\n"
#define EAT_STR "is eating\n"
#define THINK_STR "is thinking\n"
#define SLEEP_STR "is sleeping\n"
#define DEAD_STR "died\n"

void	monitoring(t_platone *philo, t_e_state event_id)
{
	suseconds_t	timestamp;
	const char	*events[5];

	events[0] = DEAD_STR;
	events[1] = EAT_STR;
	events[2] = THINK_STR;
	events[3] = SLEEP_STR;
	events[4] = TAKE_FORK_STR;
	pthread_mutex_lock(&philo->info->monitoring_mutex);
	if (philo->info->end)
	{
		pthread_mutex_unlock(&philo->info->monitoring_mutex);
		return ;
	}
	if (event_id != DROP)
	{
		timestamp = ft_get_time() - philo->time_start;
		printf("%ld %d %s", timestamp, philo->index, events[event_id]);
	}
	pthread_mutex_unlock(&philo->info->monitoring_mutex);
}
