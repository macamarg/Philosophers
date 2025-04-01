/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macamarg <macamarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:46:58 by macamarg          #+#    #+#             */
/*   Updated: 2024/11/22 12:44:14 by macamarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*
* assimetric assign fork for each philo to avoid deadlocks:
*			odd philo take left first
*			even philo take right first
* 
* fork_l == phi_pos
* fork_r == ((id) % philo_n)
* 		ie: id == 5 && && phi_pos == 4 philo_n == 5 
*     		 fork_r == 0 && fork_l == 4  (fork 0-4)
*/

static void	fork_assign(t_philo	*philo, t_fork *forks, size_t philo_n,
	int phi_pos)
{
	if ((philo->id % 2) == 0)
	{
		philo->fork_f = &forks[philo->id % philo_n];
		philo->fork_s = &forks[phi_pos];
	}
	else
	{
		philo->fork_f = &forks[phi_pos];
		philo->fork_s = &forks[philo->id % philo_n];
	}
}

/*
	set flags to the start of simulation /

	init master and write mutex /

	memory allocation and init philo
	memory allocation and init forks


*/

void	philo_init(t_master *master)
{
	int		i;
	t_philo	*tmp;

	i = -1;
	while (++i < master->data->philo_n)
	{
		tmp = master->phi + i;
		tmp->id = i + 1;
		tmp->meals_count = 0;
		tmp->dead = false;
		tmp->full = false;
		tmp->data = master->data;
		tmp->flags = master;
		tmp->last_meal = get_time(MILLISECOND);
		safe_mutex_handler(&tmp->philo_mutex, INIT);
		fork_assign(tmp, master->forks, master->data->philo_n, i);
	}
}

void	data_init(t_master *master)
{
	int	i;

	i = -1;
	master->end_sim = false;
	master->dead_flag = false;
	master->threads_ready = false;
	safe_mutex_handler(&master->master_mutex, INIT);
	safe_mutex_handler(&master->write_mutex, INIT);
	master->forks = safe_malloc(sizeof(t_fork) * master->data->philo_n);
	master->phi = safe_malloc(sizeof(t_philo) * master->data->philo_n);
	while (++i < master->data->philo_n)
	{
		safe_mutex_handler(&master->forks[i].fork, INIT);
		master->forks[i].id = i;
	}
	philo_init(master);
	printf("start of simulation\n");
}

void	philo_clean(t_master *master)
{
	int		i;
	t_philo	*tmp;

	i = -1;
	while (++i < master->data->philo_n)
	{
		tmp = master->phi + i;
		safe_mutex_handler(&tmp->philo_mutex, DESTROY);
		safe_mutex_handler(&master->forks[i].fork, DESTROY);
	}
	safe_mutex_handler(&master->master_mutex, DESTROY);
	safe_mutex_handler(&master->write_mutex, DESTROY);
	free(master->forks);
	free(master->phi);
	free (master->data);
	free(master);
}
