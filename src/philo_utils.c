/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macamarg <macamarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:21:05 by macamarg          #+#    #+#             */
/*   Updated: 2024/11/22 10:36:09 by macamarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	exit_err(char *msg, int err)
{
	printf(RED"[%i] %s\n"RST, err, msg);
	exit (err);
}

int	exit_err_args(char *msg, int err, t_phargs *data)
{
	printf(RED"[%i] %s\n"RST, err, msg);
	free(data);
	exit (err);
}


long	get_time(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		exit_err("getting time error", TIME);
	if (time_code == SECOND)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (time_code == MILLISECOND)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (time_code == MICROSECOND)
		return ((tv.tv_sec * 1e6) + (tv.tv_usec));
	else
		exit_err("Wrong input to get time", TIME);
	return (0);
}

void	ft_usleep(long usec, t_master *master)
{
	long	start;

	start = get_time(MICROSECOND);
	while ((get_time(MICROSECOND) - start) < usec)
	{
		if (simulation_finished(master))
			break ;
		usleep(1e3);
	}
}
