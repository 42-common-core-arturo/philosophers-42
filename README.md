# Philosophers

## Table of Contents
- [Introduction](#introduction)
- [Installation and Usage](#installation-and-usage)
- [Description](#description)
- [Features](#features)
- [Skills Learnt](#skills-learnt)
- [Requirements](#requirements)

## Introduction
Philosophers is a project developed for 42 School that simulates the classic dining philosophers problem. The goal is to implement a solution where a number of philosophers sit at a table and dine, but with constraints on how they can interact with forks (resources) placed between them.


## Installation
To install and run the Philosophers project, follow these steps:

1. Clone the repository:
   ```sh
   git clone https://github.com/yourusername/philosophers.git
   cd philosophers
   ```
2. Compile:
   ```sh
   make
   ```
3. Run program:

   The general syntax is as follows:
   ```sh
   ./philosophers number_of_philosophers time_to_die time_to_eat time_to_sleep [optional: number_of_times_each_philosopher_must_eat]
   ```
   This example simulates 5 philosophers with a time to die of 800 milliseconds, time to eat of 200 milliseconds, and time to sleep of 200 milliseconds.
    ```sh
    ./philosophers 5 800 200 200
   ```

## Description
The Philosophers project involves implementing a solution to the classic computer science dining philosophers problem using threads and mutexes. Philosophers alternate between eating, sleeping, and thinking, while ensuring no two adjacent philosophers can eat simultaneously.

## Features
* Simulates the dining philosophers problem with configurable parameters.
* Implements synchronization mechanisms to prevent deadlocks and starvation.
* Displays real-time status updates and logs for each philosopher's actions.

## Skills learnt
* **Thread Management:** Creating and managing threads in a concurrent environment.
* **Concurrency Control:** Using mutexes to manage shared resources.
* **Problem Solving:** Addressing synchronization challenges in a multi-threaded scenario.
* **C Programming:** Enhancing proficiency in C programming and multi-threaded applications.

## Requirements
* GCC or Clang compiler.
* Make utility.
