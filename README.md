# philosophers

A project on the use of multiple threads and/or child processes, and how race conditions can be avoided using mutexes and semaphores.

### Installing

Clone the repository and `make` in either the philo or philo_bonus directory.

### Running

The program is run as `./philo` and takes 4 - 5 arguments. Times are given in milliseconds.

`./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]`

#### Examples
`./philo 4 410 200 200 4`

The philosophers will each eat 4 times, after which the simulation will end.

`./philo 4 390 200 200 4`

The philosophers do not all have time to eat before time_to_die, meaning a philosopher will die and the simulation will end.

### Premise of the project

- There is a round table with a bowl of spaghetti in the middle.
- Philosophers are seated in order around that table, and there are as many forks as there are philosophers.
- Forks are either to the right of each philosopher (philo) or in the center of the table (philo_bonus)
- Philosophers consequtively think, eat, and sleep, with eat and sleep times (ms) given as arguments.
- The philosophers must eat every `time_to_die` ms or they die.
- Philosophers must use 2 forks to eat (left and right in philo, any 2 in philo_bonus).
- The philosophers should survive as long as possible.
- If a philosopher dies, the simulation ends.
- If `number_of_times_each_philosopher_must_eat` is given, the simulation also ends once all philosophers have eaten that many times.

### Limitations

- Philosophers cannot communicate in any way or check another philosophers state.
- Each philosopher has to be its own thread (philo) or its own child process (philo_bonus).
- There can be no race conditions.
- Global variables are forbidden.
- Only selected functions are allowed (e.g. pthread_mutex_trylock not allowed)
