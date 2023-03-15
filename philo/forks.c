/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoelho- <mcoelho-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:47:55 by mcoelho-          #+#    #+#             */
/*   Updated: 2023/03/15 18:01:28 by mcoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Filósofo recebe garfo determinado em i*/
int	take_fork(t_philo *people, int fork)
{
	pthread_mutex_lock(&people->data->dinner);
	if (!people->data->forks[fork])
	{
		people->data->forks[fork] = 1;
		pthread_mutex_unlock(&people->data->dinner);
		people->in_hand = people->in_hand + 1;
		pthread_mutex_lock(&people->data->mutex[fork]);
		print_status(people, "has taken a fork");
		return (1);
	}
	pthread_mutex_unlock(&people->data->dinner);
	return (0);
}

/*devolução de fork*/
int	drop_fork(t_philo *people, int fork)
{
	pthread_mutex_lock(&people->data->dinner);
	if (people->data->forks[fork] == 1)
	{
		pthread_mutex_unlock(&people->data->mutex[fork]);
		people->data->forks[fork] = 0;
		pthread_mutex_unlock(&people->data->dinner);
		people->in_hand = people->in_hand - 1;
		return (1);
	}
	pthread_mutex_unlock(&people->data->dinner);
	return (0);
}

/*Garantia de que o filósofo está com 2 garfos.*/
int	both_forks(t_philo *people)
{
	while (people->in_hand != 2 && !end_dinner(people))
	{
		take_fork(people, people->own_fork);
		if (end_dinner(people))
			return (0);
		take_fork(people, people->friend_fork);
		usleep (150);
	}
	return (1);
}

/* Checa se o filósofo está com algum garfo em mãos*/
int	check_forks(t_philo *people)
{
	if (people->in_hand != 0)
	{
		pthread_mutex_lock(&people->data->dinner);
		if (people->data->forks[people->own_fork])
			pthread_mutex_unlock(&people->data->mutex[people->own_fork]);
		if (people->data->forks[people->friend_fork])
			pthread_mutex_unlock(&people->data->mutex[people->friend_fork]);
		pthread_mutex_unlock(&people->data->dinner);
		return (1);
	}
	return (0);
}
