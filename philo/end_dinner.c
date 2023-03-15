/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_dinner.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoelho- <mcoelho-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 19:08:56 by mcoelho-          #+#    #+#             */
/*   Updated: 2023/03/15 18:04:56 by mcoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Encerra mutexes*/
void	end_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->max_philo)
	{
		if (pthread_mutex_destroy(&data->mutex[i]))
			printf("Fail to destroy mutex[%d]\n", i);
		i++;
	}
	if (pthread_mutex_destroy(&data->doctor))
		printf("Fail to destroy mutex doctor\n");
	if (pthread_mutex_destroy(&data->dinner))
		printf("Fail to destroy mutex dinner\n");
	if (pthread_mutex_destroy(&data->print))
		printf("Fail to destroy mutex print\n");
	if (pthread_mutex_destroy(&data->full))
		printf("Fail to destroy mutex full\n");
}
