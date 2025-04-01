/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_act.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macamarg <macamarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:32:00 by macamarg          #+#    #+#             */
/*   Updated: 2024/11/22 10:54:57 by macamarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_f->fork);
	write_status(FORK_F, philo);
	pthread_mutex_lock(&philo->fork_s->fork);
	write_status(FORK_S, philo);
	philo->meals_count++;
	set_long(&philo->philo_mutex, &philo->last_meal, get_time(MILLISECOND));
	write_status(EATING, philo);
	ft_usleep(philo->data->t_eat, philo->flags);
	if (philo->data->meals_lim > 0
		&& philo->meals_count == philo->data->meals_lim)
		set_bool(&philo->philo_mutex, &philo->full, true);
	pthread_mutex_unlock(&philo->fork_f->fork);
	pthread_mutex_unlock(&philo->fork_s->fork);
}

void	sleeping(t_philo *philo)
{
	write_status(SLEEPING, philo);
	ft_usleep(philo->data->t_sleep, philo->flags);
}

//use to change values to make the sistem fair
void	thinking(t_philo *philo)
{
	write_status(THINKING, philo);
	ft_usleep(philo->data->t_think, philo->flags);
}
