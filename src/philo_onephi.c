/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_onephi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macamarg <macamarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:25:52 by macamarg          #+#    #+#             */
/*   Updated: 2024/11/22 10:52:32 by macamarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*one_philo_sim(void *philo)
{
	t_philo	*phi;

	phi = (t_philo *)philo;
	write_status(FORK_F, philo);
	while (!simulation_finished(phi->flags))
	{
		phi->flags->time = get_time(MILLISECOND) - phi->last_meal;
		if (phi->flags->time > phi->data->t_die)
		{
			phi->flags->dead_flag = true;
			phi->flags->end_sim = true;
			write_status(DIED, phi);
			break ;
		}
	}
	return (NULL);
}

void	one_philo(t_master *master)
{
	master->start_sim = get_time(MILLISECOND);
	safe_threads_handler(&master->phi[0].thread, one_philo_sim,
		&master->phi[0], CREATE);
	safe_threads_handler(&master->phi[0].thread, NULL, NULL, JOIN);
	printf("end of simulation\n");
	philo_clean(master);
	exit(0);
}
