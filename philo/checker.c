/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoelho- <mcoelho-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 19:10:06 by mcoelho-          #+#    #+#             */
/*   Updated: 2023/03/15 16:29:02 by mcoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* confere constantemente se há razão para encerrar o jantar.*/
void	checker(t_data *data)
{
	int	i;

	i = 0;
	while (7)
	{
		pthread_mutex_lock(&data->full);
		if (check_death(&data->people[i]))
		{
			pthread_mutex_unlock(&data->full);
			break ;
		}
		if (satisfied(&data->people[i], data->satisfied))
		{
			pthread_mutex_unlock(&data->full);
			break ;
		}
		pthread_mutex_unlock(&data->full);
		i++;
		if (i == data->max_philo)
			i = 0;
	}
}

/*confere se filósofo está vivo*/
int	check_death(t_philo *people)
{
	unsigned long	time;

	time = get_time() - people->data->time_start;
	if (time - people->last_meal >= people->data->die)
	{
		pthread_mutex_lock(&people->data->doctor);
		people->data->dead = 1;
		pthread_mutex_unlock(&people->data->doctor);
		pthread_mutex_lock(&people->data->print);
		time = get_time() - people->data->time_start;
		printf("%ld %d died\n", time, people->id + 1);
		pthread_mutex_unlock(&people->data->print);
		return (1);
	}
	return (0);
}

/*confere se os filósofos estão satisfeitos*/
int	satisfied(t_philo *people, int satisfied)
{
	if (people->data->max_philo == satisfied)
	{
		pthread_mutex_lock(&people->data->doctor);
		people->data->dead = 1;
		pthread_mutex_unlock(&people->data->doctor);
		return (1);
	}
	return (0);
}

/*Checa flag de encerramento de programa*/
int	end_dinner(t_philo *people)
{
	pthread_mutex_lock(&people->data->doctor);
	if (people->data->dead == 1)
	{
		pthread_mutex_unlock(&people->data->doctor);
		return (1);
	}
	pthread_mutex_unlock(&people->data->doctor);
	return (0);
}
