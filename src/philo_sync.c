/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sync.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macamarg <macamarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:06:32 by macamarg          #+#    #+#             */
/*   Updated: 2024/11/22 12:42:58 by macamarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*
*
*	Spinlock - sync multitread programming 
*		it's a busy-wait lock that repeatedly checks (or "spins") 
*		to see if a lock is available, without yielding control 
*		of the processor
*
*/

void	wait_threads(t_master *master)
{
	while (!get_bool(&master->master_mutex, &master->threads_ready))
		;
}
