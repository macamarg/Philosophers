# Philosophers - Dining Philosophers Problem

![image](https://github.com/user-attachments/assets/f9baaf90-3503-42b2-8d70-aee3c24ece90)



## 📖 About
This project solves the classic Dining Philosophers problem using thread synchronization in C. The program simulates philosophers sitting around a table, alternating between eating, thinking, and sleeping, while avoiding deadlock and starvation.


## 📜 Rules Implemented

- Philosophers take 2 forks to eat (left and right)
- Forks are shared between adjacent philosophers
- Philosophers die if they don't eat within time_to_die milliseconds
- Simulation stops when a philosopher dies or all complete their meals
- Thread-safe logging with timestamped messages

## 🚀 Features

### Mandatory (Threads & Mutexes)
- Multi-threaded simulation of philosopher behaviors
- Mutex-protected forks to prevent data races
- Configurable timing parameters:
  - Time to eat, sleep, and die
  - Optional meal count limit
- Real-time status logging
- Clean exit on philosopher death or meal completion

## 🛠️ Technical Details

### Mandatory:
- POSIX threads (pthread)
- Mutex locks for shared resources
- Microsecond precision timing

### What worked for me

- impose a sleeping time
- assimetric assign of forks
- avoid spin lock for sleeping time

## 🖥️ Usage

```
./philo_bonus <number_of_philos> <time_to_die> <time_to_eat> <time_to_sleep> [meal_limit]
```

## 📚 Resources And Usefull Links

External functs:
	memset, printf, malloc, free, write,
	usleep, gettimeofday, pthread_create,
	pthread_detach, pthread_join, pthread_mutex_init,
	pthread_mutex_destroy, pthread_mutex_lock,
	pthread_mutex_unlock

- Code Vault
https://youtu.be/d9s_d28yJq0?si=GBViYofyZazcPj2K
https://youtu.be/d9s_d28yJq0?si=J_4DVRekXGLKONvp
https://youtu.be/xoXzp4B8aQk?si=pMszLS8_lPyNBLaS

