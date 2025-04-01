/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macamarg <macamarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:34:12 by macamarg          #+#    #+#             */
/*   Updated: 2024/11/22 10:34:23 by macamarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*
*
*	all philo have to write 
*		[time-ms] [phi.id] [action]
*	each time 
*/

static void	write_philo(long start, int id, char *status)
{
	long	time;

	time = get_time(MILLISECOND);
	printf(BLU"%li"RST" %i"MAG" %s\n"RST, time - start, id, status);
}

void	write_status(t_staus_code status, t_philo *phi)
{
	safe_mutex_handler(&phi->flags->write_mutex, LOCK);
	if (status == EATING && !simulation_finished(phi->flags))
		write_philo(phi->flags->start_sim, phi->id, "is eating");
	else if (status == SLEEPING && !simulation_finished(phi->flags))
		write_philo(phi->flags->start_sim, phi->id, "is sleeping");
	else if (status == THINKING && !simulation_finished(phi->flags))
		write_philo(phi->flags->start_sim, phi->id, "is thinking");
	else if (status == DIED)
		write_philo(phi->flags->start_sim, phi->id, "has died");
	else if (status == FORK_F && !simulation_finished(phi->flags))
		write_philo(phi->flags->start_sim, phi->id, "has taken FORK_L");
	else if (status == FORK_S && !simulation_finished(phi->flags))
		write_philo(phi->flags->start_sim, phi->id, "has taken FORK_R");
	safe_mutex_handler(&phi->flags->write_mutex, UNLOCK);
}
