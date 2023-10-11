/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fborroto <fborroto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:12:49 by fborroto          #+#    #+#             */
/*   Updated: 2023/10/11 19:12:50 by fborroto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosophers.h"

int	all_philo_full(t_platone *philo)
{
	int	i;
	int	count;
	int	each_philo_must_eat;

	count = 0;
	i = 0;
	pthread_mutex_lock(&philo->meal_lock);
	if (philo->info->each_philo_must_eat != -1)
	{
		while (i < philo->info->number_of_philosophers)
		{
			if (philo->n_meals >= philo->info->each_philo_must_eat)
				count++;
			if (count == philo->info->number_of_philosophers)
			{
				pthread_mutex_unlock(&philo->meal_lock);
				return (0);
			}
			philo = philo->next;
			i++;
		}
	}
	pthread_mutex_unlock(&philo->meal_lock);
	return (1);
}

void	*philo_routine(void *t_arg)
{
	t_platone	*philo;

	philo = (t_platone *)t_arg;
	if (is_nietzsche_lonely(philo))
		return (NULL);
	else
	{
		if (philo->index % 2 != 0)
			usleep(15000);
		while (dead_platone(philo))
		{
			if (!dead_platone(philo))
				return (NULL);
			ft_eating(philo);
			if (!dead_platone(philo))
				return (NULL);
			if (all_philo_full(philo) == 0)
				return (NULL);
			print_state("is sleeping\n", philo);
			ft_sleep(philo->info->time_to_sleep, philo);
			if (!dead_platone(philo))
				return (NULL);
			print_state("is thinking\n", philo);
		}
	}
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
	int					i;
	t_philosophers_info	*info;
	t_platone			*philo;

	i = 0;
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
