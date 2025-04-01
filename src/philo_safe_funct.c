/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_safe_funct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macamarg <macamarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:00:44 by macamarg          #+#    #+#             */
/*   Updated: 2024/11/22 10:26:03 by macamarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
		exit_err("Error in memory allocation", MALLOC);
	return (ret);
}

/*
* MUTEX SAFE
*/
static void	mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	else if (status == EINVAL && (opcode == LOCK || opcode == UNLOCK))
		exit_err("The value specified by mutex	is invalid", MUTEX_ERR);
	else if (status == EINVAL && opcode == INIT)
		exit_err("The value specified by attr is invalid", MUTEX_ERR);
	else if (status == EDEADLK)
		exit_err("A deadlock would occur if"
			" the thread blocked waiting for mutex", MUTEX_ERR);
	else if (status == EBUSY)
		exit_err("Mutex already locked", MUTEX_ERR);
	else if (status == ENOMEM)
		exit_err("The process cannot allocate"
			"enough memory to creat another mutex", MUTEX_ERR);
	else if (status == EPERM)
		exit_err("The current thread does not hold"
			" a lock on a mutex", MUTEX_ERR);
}

void	safe_mutex_handler(t_mtx *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (opcode == UNLOCK)
		mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (opcode == INIT)
		mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (opcode == DESTROY)
		mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		exit_err("Wrong opcode to handle mutex", MUTEX_ERR);
}

/*
* THREAD SAFE
*/

static void	thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	else if (status == EAGAIN)
		exit_err("Insufficient resources to create another thread", THREAD_ERR);
	else if (status == EPERM)
		exit_err("No permission to set", THREAD_ERR);
	else if (status == EINVAL && opcode == CREATE)
		exit_err("Invalid settings in attr", THREAD_ERR);
	else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
		exit_err("thread is not a joinable thread", THREAD_ERR);
	else if (status == ESRCH)
		exit_err("No thread with the ID thread could be found", THREAD_ERR);
	else if (status == EDEADLK)
		exit_err("A deadlock was detected or thread specifies the "
			"calling thread", THREAD_ERR);
}

void	safe_threads_handler(pthread_t *thread, void *(rot)(void *),
		void *data, t_opcode opcode)
{
	if (opcode == CREATE)
		thread_error(pthread_create(thread, NULL, rot, data), opcode);
	else if (opcode == JOIN)
		thread_error(pthread_join(*thread, NULL), opcode);
	else if (opcode == DETACH)
		thread_error(pthread_detach(*thread), opcode);
	else
		exit_err("Wrong opcode to thread handler", THREAD_ERR);
}
