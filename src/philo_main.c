/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macamarg <macamarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:53:56 by macamarg          #+#    #+#             */
/*   Updated: 2024/11/22 10:33:00 by macamarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char **argv)
{
	t_master	*master;
	t_phargs	*data;
	int			i;

	i = -1;
	if (argc == 5 || argc == 6)
	{
		data = safe_malloc(sizeof(t_phargs));
		parse_input(data, argv);
		master = safe_malloc(sizeof(t_master));
		data->master = master;
		master->data = data;
		data_init(master);
		start_sim(master);
		philo_clean(master);
	}
	else
		exit_err("Wrong usage", WRONG_USE);
	return (0);
}
