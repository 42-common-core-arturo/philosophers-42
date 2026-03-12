# Philosophers

A concurrent systems simulation of the **Dining Philosophers Problem** implemented in **C** using **POSIX threads** and **mutex-based synchronization**, focusing on deadlock prevention, race-condition safety, and precise timing control.

![Language](https://img.shields.io/badge/language-C-blue)
![Threads](https://img.shields.io/badge/concurrency-pthreads-green)

---

## Table of Contents

- [Overview](#overview)
- [Engineering Focus](#engineering-focus)
- [Key Features](#key-features)
- [Tech Stack](#tech-stack)
- [Architecture](#architecture)
- [Core Concepts / Interesting Engineering Details](#core-concepts--interesting-engineering-details)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
- [Example Usage](#example-usage)
- [Future Improvements](#future-improvements)
- [Engineering Notes](#engineering-notes)
- [License](#license)

## Overview

This project is a C implementation of the **Dining Philosophers Problem**, a classical concurrency problem originally formulated by Edsger Dijkstra. The simulation models `N` philosophers seated around a circular table, each requiring two forks (shared with adjacent philosophers) to eat. The challenge: prevent **deadlock**, **starvation**, and **race conditions** while maintaining accurate millisecond-level timing.

The implementation uses **POSIX threads (`pthreads`)** and **mutexes** as the sole synchronization primitives — no semaphores, no higher-level abstractions. This constraint forces explicit reasoning about lock ordering, shared state visibility, and thread lifecycle management, making it a strong demonstration of low-level concurrency engineering in C.

---

## Engineering Focus

- **Concurrency & Synchronization** — mutex-protected shared state, deadlock prevention via consistent lock ordering
- **Operating System Concepts** — thread creation/joining, process timing with `gettimeofday`, busy-wait sleep loops
- **Low-Level C Design** — zero dynamic allocation after initialization, stack-allocated string buffers, custom `usleep` with adaptive granularity
- **Race Condition Prevention** — all accesses to `last_meal_tm`, `is_full`, and `end` flag are guarded by specific mutexes
- **Performance-Aware Timing** — custom sleep function avoids OS scheduler imprecision by using tiered `usleep` intervals

---

## Key Features

- Supports 1–200 philosophers with configurable timing parameters
- Deadlock-free fork acquisition via a deterministic even/odd pairing strategy
- Sub-millisecond-aware sleep loop to compensate for `usleep` imprecision
- Thread-safe, ordered console output using a dedicated print mutex
- Optional meal-count termination condition: simulation ends cleanly when all philosophers reach a target meal count
- Edge case handling: single-philosopher scenario runs on the main thread without spawning workers
- Graceful shutdown: all threads observe a shared `end` flag before every blocking operation

---

## Tech Stack

| Category | Technology |
|---|---|
| Language | C (C11) |
| Threading | POSIX Threads (`pthread`) |
| Synchronization | `pthread_mutex_t` |
| Timing | `gettimeofday` (`sys/time.h`) |
| Build System | GNU Make |
| Compiler | `cc` with `-Wall -Wextra -Werror` |

No external libraries are used. All utilities (`ft_itoa`, `ft_putstr_fd`, `ft_atoi_long`) are implemented from scratch to comply with 42 School's constraints on standard library usage.

---

## Architecture

The system is structured around two main entity types: a **single shared `t_data` struct** (global simulation state) and an **array of `t_philo` structs** (per-philosopher state).

All philosopher threads receive a pointer to the shared `t_data` structure, which contains:

* fork mutexes
* timing parameters
* global termination state
* shared configuration

Each philosopher maintains local state including:

* philosopher ID
* fork indices
* meal counters
* last meal timestamp

---

### System Overview

```
                     ┌──────────────────────────┐
                     │        Main Thread       │
                     │                          │
                     │  init_simulation()       │
                     │  start_mutexes()         │
                     │  start_threads()         │
                     │                          │
                     │  monitor_loop()          │
                     │  (check_end_dinner)      │
                     │                          │
                     │  join_threads()          │
                     │  destroy_mutexes()       │
                     └─────────────┬────────────┘
                                   │
                     spawns N philosopher threads
                                   │
            ┌──────────────────────┴──────────────────────┐
            │                                             │
     ┌───────────────┐                           ┌───────────────┐
     │ Philosopher 1 │                           │ Philosopher N │
     │   Thread      │                           │   Thread      │
     │               │                           │               │
     │  ft_prep()    │                           │  ft_prep()    │
     │               │                           │               │
     │  loop:        │                           │  loop:        │
     │   take_forks  │                           │   take_forks  │
     │   eat         │                           │   eat         │
     │   sleep       │                           │   sleep       │
     │   think       │                           │   think       │
     └───────────────┘                           └───────────────┘
```

The **main thread acts as a monitor**, continuously checking philosopher state to determine when the simulation should terminate.

Termination conditions include:

* a philosopher exceeding `time_to_die`
* all philosophers reaching the required meal count

When a termination condition is detected, the monitor sets the global `end` flag and joins all philosopher threads before cleaning up resources.

---

### Shared State Synchronization

Shared state is protected using separate mutex domains to reduce contention and ensure predictable locking behavior.

| Mutex            | Guards                              |
| ---------------- | ----------------------------------- |
| `mutex_forks[i]` | Individual fork resources           |
| `mutex_meals`    | `last_meal_tm`, `meals`, `is_full`  |
| `mutex_print`    | Console output and termination flag |

The monitor thread reads philosopher state under `mutex_meals` to safely detect starvation or completion conditions.

---

### Why this architecture works

This design provides several important guarantees:

* **Deadlock avoidance** through deterministic fork acquisition ordering
* **Thread-safe shared state access** via dedicated mutex domains
* **Centralized failure detection** using a monitor thread
* **Clean thread lifecycle management**

Separating **monitoring logic** from **philosopher behavior** simplifies synchronization and avoids complex inter-thread coordination.


## Core Concepts / Interesting Engineering Details

### Deadlock Prevention via Fork Pairing

A naive implementation where each philosopher picks up their left fork then their right fork produces circular wait — the textbook deadlock scenario. This implementation avoids it by assigning each philosopher a **deterministic fork pair** based on their index parity:

```c
data->philo[i].fork1 = i - (i % 2);      // lower-index fork first
data->philo[i].fork2 = i - 1 + (i % 2); // higher-index fork second
```

Odd-indexed philosophers pick up the lower-numbered fork first; even-indexed philosophers do the same. This breaks the circular dependency and guarantees deadlock freedom without a global arbiter or asymmetric philosopher roles.

### Staggered Thread Start

To prevent thundering-herd contention at startup (all philosophers simultaneously competing for forks), odd-indexed philosophers are delayed by `tm_eat - 5` ms before entering their first loop iteration:

```c
void ft_prep(t_philo *philo) {
    philo->last_meal_tm = ft_get_time();
    if (philo->id % 2)
        ft_usleep(philo->data->tm_eat - 5, philo->data);
}
```

This allows even-indexed philosophers to acquire forks first, immediately reducing lock contention and establishing a natural eating cadence.

### Adaptive Sleep (`ft_usleep`)

Standard `usleep` is unreliable for short durations due to OS scheduler granularity. A custom sleep function computes the target wake time, then loops with progressively finer sleep intervals as the deadline approaches:

```c
if (remaining > 10000) usleep(10000);
else if (remaining > 1000) usleep(1000);
else if (remaining > 100)  usleep(100);
else if (remaining > 0)    usleep(10);
```

This tiered approach balances CPU usage against timing accuracy, achieving near-millisecond precision without busy-spinning at full CPU for the entire sleep duration. The loop also checks the `end` flag on each iteration to allow early exit.

### Think Time Calculation

To minimize idle time and prevent starvation in high-philosopher-count scenarios, the think time (`tm_think`) is computed at initialization from the remaining time budget after eating and sleeping:

```c
tm_left = (data->tm_die - (data->tm_sleep + data->tm_eat)) * 0.5;
data->tm_think = (tm_left > 0) ? tm_left : 0;
```

This caps thinking time to a safe window derived from the death deadline, reducing the risk of a philosopher starving while waiting for forks.

### Thread-Safe Output

All console output goes through `ft_putstr_fd` (a `write`-based string emitter) rather than `printf`, to avoid internal `stdio` buffering and locking. The print mutex ensures log lines are never interleaved, and every print site checks the `end` flag before writing to suppress output after a death event.

### Single-Philosopher Edge Case

With one philosopher, deadlock is unavoidable (only one fork exists). This case is short-circuited before mutex/thread initialization: the main thread prints the fork-taken message and spins checking `is_dead` until the death condition triggers, then exits cleanly.

---

## Project Structure

```
philosophers-42/
├── Makefile
├── includes/
│   └── philosophers.h      # All structs, constants, and function declarations
└── srcs/
    ├── main.c              # Entry point: orchestrates init, threads, and teardown
    ├── parsing.c           # Input validation and data/philo struct initialization
    ├── threads.c           # Thread creation (start_threads) and joining (end_threads)
    ├── mutexes.c           # Mutex init/destroy and m_print (meal-state-aware print)
    ├── dinner.c            # Philosopher thread routine: forks, eat, sleep, think
    ├── death.c             # Death detection (is_dead) and monitor loop (check_end_dinner)
    ├── time.c              # ft_get_time (gettimeofday wrapper) and ft_usleep
    ├── utils.c             # ft_exit, ft_atoi_long, dinner_for_one, ft_print
    └── libft.c             # ft_itoa, ft_putstr_fd, size_calc (no-stdlib utilities)
```

Each source file has a single, well-defined responsibility. Shared state is accessed exclusively through the `t_data` pointer embedded in each `t_philo` struct, eliminating global variables.

---

## Getting Started

### Requirements

- GCC or Clang
- GNU Make
- POSIX-compliant OS (Linux or macOS)

### Installation

```sh
git clone https://github.com/yourusername/philosophers-42.git
cd philosophers-42
make
```

### Running the Project

```sh
./philo <num_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [meals_required]
```

All time values are in **milliseconds**. Minimum accepted value for time arguments is 60 ms. Philosopher count must be between 1 and 200.

### Environment Variables

None required. All parameters are passed as command-line arguments.

---

## Example Usage

```sh
# 5 philosophers, dies after 800ms without eating, eats for 200ms, sleeps for 200ms
./philo 5 800 200 200

# Same config, simulation ends after each philosopher eats 7 times
./philo 5 800 200 200 7

# Stress test: 200 philosophers
./philo 200 800 200 200

# Edge case: single philosopher (guaranteed death)
./philo 1 800 200 200
```

Expected output format per event:
```
<timestamp_ms> <philosopher_id> <action>
```
```
0 1 has taken a fork
0 2 has taken a fork
1 1 has taken a fork
1 1 is eating
1 2 has taken a fork
...
801 3 died
```

---

## Future Improvements

- **Signal-based shutdown** instead of polling the `end` flag — reduces latency between death detection and thread termination
- **`pthread_cond_t` condition variables** to replace the busy-wait monitor loop in `check_end_dinner`, lowering CPU usage during idle periods
- **Valgrind / Helgrind integration** in the Makefile as a `make check` target for automated race condition detection
- **Configurable philosopher limit** beyond 200 via heap-allocated fork/philo arrays, removing the fixed-size stack constraint
- **Structured logging** with severity levels and optional JSON output for automated testing harnesses

---

## Engineering Notes

- **Mutex granularity matters**: using a single global lock for all shared state (meals + print + end) initially caused false deadlocks and timing inaccuracies. Splitting into `mutex_meals` and `mutex_print` with clearly defined ownership eliminated the issues.
- **`usleep` is not a timer**: relying on `usleep` for timing directly caused philosophers to die spuriously under load. The adaptive `ft_usleep` loop with `gettimeofday` checkpoints was necessary for correctness.
- **Lock ordering must be total and consistent**: any deviation in the order mutexes are acquired across different code paths immediately reintroduces deadlock risk. Documenting and enforcing lock acquisition order is non-negotiable in mutex-based designs.
- **The monitor/worker split is a fundamental concurrency pattern**: separating the death-detection concern onto the main thread (monitor) rather than having philosophers check each other's state simplified the locking model significantly.

---

## License

This project is open source and available under the [MIT License](LICENSE).


[Back to the top](#philosophers)
