/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fborroto <fborroto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:12:57 by fborroto          #+#    #+#             */
/*   Updated: 2023/10/11 19:12:58 by fborroto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

enum					e_state
{
	ALIVE = 0,
	DEAD = 1,
};

typedef struct s_philosophers_info
{
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					each_philo_must_eat;
	int					died;
	pthread_mutex_t		death_lock;
	pthread_mutex_t		check_lock;
}						t_philosophers_info;

typedef struct s_platone
{
	int					index;
	unsigned long		last_meal;
	unsigned long		time_start;
	int					n_meals;
	int					state;
	pthread_mutex_t		fork_lock;
	pthread_mutex_t		time_lock;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		meal_lock;
	struct s_platone	*next;
	pthread_t			newthread;
	t_philosophers_info	*info;
}						t_platone;

void					ft_sleep(size_t milliseconds, t_platone *philo);
unsigned long			ft_get_time(void);
void					*philo_routine(void *vargp);
t_platone				*init_platones(t_philosophers_info *info);
int						ft_atoi(const char *nptr);
t_philosophers_info		*init_info(char **argv);
bool					check_arg(char **argv);
void					exit_prog(void);
int						all_philo_full(t_platone *philo);
void					print_state(char *str, t_platone *philo);
void					destory_all(t_platone *philo);
bool					dead_platone(t_platone *philo);
void					ft_eating(t_platone *philo);
void					ft_end(t_platone *philo);
bool					all_have_eat(t_platone *philo);
bool					dead_philo(t_platone *philo);
void					free_list(t_platone **philo);
bool					is_nietzsche_lonely(t_platone *nietzsche);
#endif