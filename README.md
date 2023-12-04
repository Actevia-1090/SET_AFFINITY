# Multi-Process And Multi-Thread CPU Affinity Demo


This repository contains two C programs that demonstrate the use of multi-processes and multi-threads in conjunction with CPU affinity settings.

1. Multi-Process Affinity Demo
Description
The multi_process_affinity.c program showcases the creation of multiple child processes, each running on a specific CPU core. Each child process further spawns a thread that performs a simple task and periodically prints information about the process, thread, and the core it is running on.

Instructions
Compile the program: gcc multi_process_affinity.c -o multi_process_affinity -lpthread

Run the executable: ./multi_process_affinity

2. CPU Affinity Setter with PID
Description
The cpu_affinity_setter.c program allows you to set the CPU affinity of a specific process identified by its PID. It prompts the user for a PID and the desired CPU core ID and sets the affinity accordingly.

Instructions
Compile the program: gcc cpu_affinity_setter.c -o cpu_affinity_setter -lpthread

Run the executable: ./cpu_affinity_setter


