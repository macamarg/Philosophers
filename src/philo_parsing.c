/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macamarg <macamarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:24:35 by macamarg          #+#    #+#             */
/*   Updated: 2024/11/22 12:39:49 by macamarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static inline bool	is_space(const char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static inline bool	is_digit(const char c)
{
	return (c >= '0' && c <= '9');
}

static char	*valid_input(const char *str, t_phargs *data)
{
	int		len;
	char	*num;

	len = 0;
	while (is_space(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		exit_err_args("Use only positive numbers", NEGATIVE, data);
	if (!is_digit(*str))
		exit_err_args("Enter valid numbers", NOT_DIGIT, data);
	num = (char *)str;
	while (str && is_digit(*str))
	{
		str++;
		++len;
	}
	if (len > 10)
		exit_err_args("Number greater then INT_MAX", BIG_NUMBER, data);
	return (num);
}

static long	ft_atol(char *str, t_phargs *data)
{
	long		num;
	char		*nbr;

	num = 0;
	nbr = valid_input(str, data);
	while (is_digit(*nbr))
	{
		num = (num * 10) + (*nbr - '0');
		nbr++;
	}
	if (num > INT_MAX)
		exit_err_args("Number greater then INT_MAX", BIG_NUMBER, data);
	return (num);
}

void	parse_input(t_phargs *data, char **argv)
{
	data->philo_n = ft_atol(argv[1], data);
	data->t_die = ft_atol(argv[2], data);
	data->t_eat = ft_atol(argv[3], data) * 1e3;
	data->t_sleep = ft_atol(argv[4], data) * 1e3;
	data->t_think = ((data->t_die * 1e3) - (data->t_eat
				+ data->t_sleep)) / 2;
	if (data->t_die < 60 || data->t_eat < 6e4 || data->t_sleep < 6e4)
		exit_err("Use time stamps bigger than 6 ms", LITTLE);
	if (argv[5])
		data->meals_lim = ft_atol(argv[5], data);
	else
		data->meals_lim = -1;
}

