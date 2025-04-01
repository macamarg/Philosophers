/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macamarg <macamarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:53:59 by macamarg          #+#    #+#             */
/*   Updated: 2024/11/15 13:35:36 by macamarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>//mutex:inti destroy lock unclok, thread:creat join detach
# include <string.h>
# include <stdlib.h>//malloc free
# include <unistd.h>//write usleep
# include <stdio.h>//printf
# include <stdbool.h>
# include <sys/time.h>//time of day
# include <limits.h> //INT_MAX
# include <errno.h>//mutex error

/* Define colors for printf - remenber to reset to RST after*/
# define RST "\033[0m" //default
# define RED "\033[1;31m"
# define GR "\033[1;32m"
# define YEL "\033[1;33m"
# define BLU "\033[1;34m"
# define MAG "\033[1;35m"

/*errors*/
# define WRONG_USE 1
# define NEGATIVE 2
# define NOT_DIGIT 3
# define BIG_NUMBER 4
# define LITTLE 5
# define TIME 6
# define WRITE 7
# define MALLOC 77
# define MUTEX_ERR 78
# define THREAD_ERR 79

typedef enum e_status_code
{
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	FORK_F,
	FORK_S,
}	t_staus_code;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_opcode;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}	t_time_code;

typedef pthread_mutex_t	t_mtx;
typedef struct s_master	t_master;

typedef struct s_fork
{
	t_mtx	fork;
	int		id;
}	t_fork;

//collect arguments
typedef struct s_phargs
{
	long			philo_n;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	long			t_think;
	long			meals_lim;
	t_master		*master;
}	t_phargs;

//philosofers managment
typedef struct s_philo
{
	int				id;
	int				meals_count;
	bool			full;
	bool			dead;
	long			last_meal;
	pthread_t		thread;
	t_fork			*fork_f;
	t_fork			*fork_s;
	t_mtx			philo_mutex;
	t_master		*flags;
	t_phargs		*data;
}	t_philo;

typedef struct s_master
{
	t_phargs		*data;
	t_philo			*phi;//array for all the t_philos
	t_fork			*forks;//array for all the forks
	pthread_t		monitor;
	long			time;
	bool			dead_flag;
	bool			threads_ready;
	t_mtx			master_mutex;//avoid races
	t_mtx			write_mutex;
	long			start_sim;//time of the start
	bool			end_sim;

}	t_master;

//init and clean
void	philo_init(t_master *master);
void	data_init(t_master *master);
void	philo_clean(t_master *master);

//parsing
void	parse_input(t_phargs *data, char **argv);

//utils
int		exit_err(char *msg, int err);
int		exit_err_args(char *msg, int err, t_phargs *data);
long	get_time(t_time_code time_code);
void	ft_usleep(long usec, t_master *plato);//precise usleep

//simulation
void	start_sim(t_master *master);
void	*monitor_sim(void *master);
void	*eat_sim(void *philo);

//one philosopher
void	one_philo(t_master *master);

//actions
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);

//write
void	write_status(t_staus_code status, t_philo *phi);

//sync
void	wait_threads(t_master *master);

//safe fnction
void	*safe_malloc(size_t bytes);
void	safe_threads_handler(pthread_t *thread, void *(rot)(void *),
			void *data, t_opcode opcode);
void	safe_mutex_handler(t_mtx *mutex, t_opcode opcode);

//getter and setter
void	set_bool(t_mtx *mutex, bool *dest, bool value);
bool	get_bool(t_mtx *mutex, bool *value);
void	set_long(t_mtx *mutex, long *dest, long value);
long	get_long(t_mtx *mutex, long *value);
bool	simulation_finished(t_master *master);

#endif