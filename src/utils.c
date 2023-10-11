/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fborroto <fborroto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:13:04 by fborroto          #+#    #+#             */
/*   Updated: 2023/10/11 19:13:05 by fborroto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosophers.h"

int	ft_atoi(const char *nptr)
{
	unsigned int	i;
	int				result;
	char			sign;

	i = 0;
	result = 0;
	sign = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		sign = nptr[i];
		i++;
	}
	while (nptr[i] != '\0' && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		result *= 10;
		result += nptr[i] - '0';
		i++;
	}
	if (sign == '-')
		result *= -1;
	return (result);
}

t_philosophers_info	*init_info(char **argv)
{
	t_philosophers_info	*info;

	info = (t_philosophers_info *)malloc(sizeof(t_philosophers_info));
	pthread_mutex_init(&info->check_lock, NULL);
	pthread_mutex_init(&info->death_lock, NULL);
	info->number_of_philosophers = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->died = 0;
	if (argv[5] != 0)
	{
		info->each_philo_must_eat = ft_atoi(argv[5]);
	}
	else
	{
		info->each_philo_must_eat = -1;
	}
	return (info);
}

static t_platone	*platone_friends(t_platone *friends, int i)
{
	friends->index = i;
	pthread_mutex_init(&friends->time_lock, NULL);
	pthread_mutex_init(&friends->dead_lock, NULL);
	pthread_mutex_init(&friends->fork_lock, NULL);
	pthread_mutex_init(&friends->meal_lock, NULL);
	friends->state = ALIVE;
	friends->last_meal = ft_get_time();
	friends->n_meals = 0;
	friends->time_start = ft_get_time();
	return (friends);
}

t_platone	*init_platones(t_philosophers_info *info)
{
	int			i;
	t_platone	*friends;
	t_platone	*tmp2;
	t_platone	*tmp;

	i = -1;
	friends = (t_platone *)malloc(sizeof(t_platone));
	if (!friends)
		return (NULL);
	tmp2 = friends;
	while (++i < info->number_of_philosophers)
	{
		friends = platone_friends(friends, i);
		friends->info = info;
		if (i == info->number_of_philosophers - 1)
			break ;
		tmp = (t_platone *)malloc(sizeof(t_platone));
		if (!tmp)
			return (NULL);
		friends->next = tmp;
		friends = tmp;
	}
	friends->next = tmp2;
	return (tmp2);
}

bool	is_nietzsche_lonely(t_platone *nietzsche)
{
	if (nietzsche->info->number_of_philosophers == 1)
	{
		while (dead_platone(nietzsche))
		{
			nietzsche->info->number_of_philosophers = 1;
		}
		return (true);
	}
	return (false);
}
