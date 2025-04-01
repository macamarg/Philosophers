/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macamarg <macamarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:56:58 by macamarg          #+#    #+#             */
/*   Updated: 2024/11/28 11:13:09 by macamarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*
*	the start_sim will call eat_sim for each thread
*		wait_thread: waits all phi due to an spinlock
*		run throught eat, sleep and think time until the end of sim
*		returns to main for clean up
*/

void	*eat_sim(void *philo)
{
	t_philo	*phi;

	phi = (t_philo *)philo;
	wait_threads(phi->flags);
	if (phi->id % 2 == 0)
		usleep(1000);
	while (!simulation_finished(phi->flags))
	{
		if (phi->full)
			break ;
		eating(phi);
		if (phi->full)
			break ;
		sleeping(phi);
		thinking(phi);
	}
	return (NULL);
}

/*
*	waits all threads to be ready (it is necessaire thogh?)
*
*	get the time and compares to time to die
*/

void	*monitor_sim(void *master)
{
	t_master	*tmp;
	int			i;

	tmp = (t_master *)master;
	wait_threads(tmp);
	while (!simulation_finished(tmp))
	{
		i = -1;
		while (++i < tmp->data->philo_n && !simulation_finished(master))
		{
			tmp->time = get_time(MILLISECOND)
				- get_long(&tmp->phi[i].philo_mutex, &tmp->phi[i].last_meal);
			if ((tmp->time > tmp->data->t_die) && !tmp->phi->full)
			{
				set_bool(&tmp->master_mutex, &tmp->dead_flag, true);
				set_bool(&tmp->master_mutex, &tmp->end_sim, true);
				write_status(DIED, &tmp->phi[i]);
				break ;
			}
		}
	}
	return (NULL);
}

/*
*	checks if there is meals to have
*	
*	calls the r
*/
void	start_sim(t_master *master)
{
	int	i;

	i = -1;
	if (master->data->meals_lim == 0)
		return ;
	else if (master->data->philo_n == 1)
		one_philo(master);
	else
	{
		while (++i < master->data->philo_n)
			safe_threads_handler(&master->phi[i].thread, eat_sim,
				&master->phi[i], CREATE);
	}
	master->start_sim = get_time(MILLISECOND);
	set_bool(&master->master_mutex, &master->threads_ready, true);
	safe_threads_handler(&master->monitor, monitor_sim, master, CREATE);
	while (--i >= 0)
	{
		safe_threads_handler(&master->phi[i].thread, NULL, NULL, JOIN);
	}
	set_bool(&master->master_mutex, &master->end_sim, true);
	if (!master->dead_flag)
		printf(BLU"All philosofers are full\n"RST);
	printf("end of simulation\n");
	safe_threads_handler(&master->monitor, NULL, NULL, JOIN);
}
