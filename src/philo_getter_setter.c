/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_getter_setter.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macamarg <macamarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:14:24 by macamarg          #+#    #+#             */
/*   Updated: 2024/11/22 10:54:04 by macamarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*
*	to lock and unlock mutex
*/

//bool

void	set_bool(t_mtx *mutex, bool *dest, bool value)
{
	safe_mutex_handler(mutex, LOCK);
	*dest = value;
	safe_mutex_handler(mutex, UNLOCK);
}

bool	get_bool(t_mtx *mutex, bool *value)
{
	bool	ret;

	safe_mutex_handler(mutex, LOCK);
	ret = *value;
	safe_mutex_handler(mutex, UNLOCK);
	return (ret);
}

//long

void	set_long(t_mtx *mutex, long *dest, long value)
{
	safe_mutex_handler(mutex, LOCK);
	*dest = value;
	safe_mutex_handler(mutex, UNLOCK);
}

long	get_long(t_mtx *mutex, long *value)
{
	long	ret;

	safe_mutex_handler(mutex, LOCK);
	ret = *value;
	safe_mutex_handler(mutex, UNLOCK);
	return (ret);
}

//end sim

bool	simulation_finished(t_master *master)
{
	return (get_bool(&master->master_mutex, &master->end_sim));
}
