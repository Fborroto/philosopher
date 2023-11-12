/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fborroto <fborroto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:12:43 by fborroto          #+#    #+#             */
/*   Updated: 2023/11/12 18:57:24 by fborroto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

bool	check_arg(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_isdigit(argv[i]) == 0)
		{
			return (false);
		}
		i++;
	}
	return (true);
}

static inline bool	starved(t_platone *philo)
{
	return (((ft_get_time() - philo->last_meal)
			>= philo->info->time_to_die));
}

static bool	is_philo_dead(t_platone *philo, int *satisfied_philos)
{
	if (philo->info->each_philo_must_eat > 0 && philo->n_meals >= philo->info->each_philo_must_eat)
		*satisfied_philos += 1;
	if (starved(philo))
	{
		pthread_mutex_unlock(&philo->info->monitoring_mutex);
		monitoring(philo, DEAD);
		pthread_mutex_lock(&philo->info->monitoring_mutex);
		philo->info->end = true;
		pthread_mutex_unlock(&philo->info->monitoring_mutex);
		return (true);
	}
	return (false);
}

static inline void	all_have_eaten(t_platone *philo)
{
	philo->info->end = true;
	printf("Every Philosopher had %d meals!\n", philo->info->each_philo_must_eat);
	pthread_mutex_unlock(&philo->info->monitoring_mutex);
}

void	ft_end(t_platone *philo)
{
	int	satisfied_philos;
	int	i;

	satisfied_philos = 0;
	while (true)
	{
		i = -1;
		pthread_mutex_lock(&philo->info->monitoring_mutex);
		while (++i < philo->info->number_of_philosophers)
		{
			if (is_philo_dead(philo, &satisfied_philos))
				return ;
		}
		if (satisfied_philos == philo->info->number_of_philosophers)
			return (all_have_eaten(philo));
		pthread_mutex_unlock(&philo->info->monitoring_mutex);
	}
}

void	free_list(t_platone **philo)
{
	int			i;
	int			d;
	t_platone	*tmp;

	i = 0;
	d = (*philo)->info->number_of_philosophers;
	while (i < d)
	{
		tmp = (*philo);
		pthread_mutex_destroy(&(*philo)->info->monitoring_mutex);
		pthread_mutex_destroy(&(*philo)->meal_lock);
		pthread_mutex_destroy(&(*philo)->time_lock);
		pthread_mutex_destroy(&(*philo)->fork_lock);
		(*philo) = (*philo)->next;
		free(tmp);
		i++;
	}
}
