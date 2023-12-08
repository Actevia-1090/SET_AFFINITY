#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include<pthread.h>
#include <sys/wait.h>
#include <sys/prctl.h>

enum Status {     STATUS_SUCCESS = 0,     STATUS_FAILURE = -1, };
void set_core_withPID(pid_t pid, int core_id) 
{

    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(core_id, &mask);

    pthread_t current_thread = pthread_self();

    if (sched_setaffinity(pid, sizeof(cpu_set_t), &mask) != STATUS_SUCCESS) {
        perror("pthread_setaffinity_np");
        exit(EXIT_FAILURE);
    }
}

int main()
{
    pid_t pid;
    int core_id;
    
    printf("Input pid: ");
    if (scanf("%d", &pid) != 1)
    {
        fprintf(stderr, "Error reading pid\n");
        exit(EXIT_FAILURE);
    }

    printf("Input which core you need to run on: ");
    if (scanf("%d", &core_id) != 1)
    {
        fprintf(stderr, "Error reading core_id\n");
        exit(EXIT_FAILURE);
    }

    set_core_withPID(pid, core_id);
    return 0;
}
