/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fborroto <fborroto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:12:49 by fborroto          #+#    #+#             */
/*   Updated: 2023/11/12 18:49:02 by fborroto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_routine(void *t_arg)
{
	t_platone	*philo;

	philo = (t_platone *)t_arg;
	if (is_nietzsche_lonely(philo))
		return (NULL);
	if (philo->index % 2 != 0)
		usleep(15000);
	while (true)
	{
		pthread_mutex_lock(&philo->info->monitoring_mutex);
		if (philo->info->end)
		{
			pthread_mutex_unlock(&philo->info->monitoring_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->info->monitoring_mutex);
		ft_eating(philo);
		monitoring(philo, SLEEP);
		usleep(philo->info->time_to_sleep * 1000);
		monitoring(philo, THINK);
	}
	return (NULL);
}

static void	create_threads(t_philosophers_info *info, t_platone *philo)
{
	int	i;

	i = 0;
	while (i < info->number_of_philosophers)
	{
		pthread_create(&philo->newthread, NULL, philo_routine, philo);
		philo = philo->next;
		i++;
	}
}

static void	join_threads(t_philosophers_info *info, t_platone *philo)
{
	int	i;

	i = 0;
	while (i < info->number_of_philosophers)
	{
		pthread_join(philo->newthread, NULL);
		philo = philo->next;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philosophers_info	*info;
	t_platone			*philo;

	if (argc != 5 && argc != 6)
		return (0);
	if (!check_arg(argv))
		return (0);
	info = init_info(argv);
	philo = init_platones(info);
	create_threads(info, philo);
	ft_end(philo);
	join_threads(philo->info, philo);
	free_list(&philo);
	free(info);
}
