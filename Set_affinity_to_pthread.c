#define _GNU_SOURCE

#include<sched.h>

#include<stdio.h>

#include<stdlib.h>

#include<unistd.h>

#include<pthread.h>

#include<sys/wait.h>

#include<sys/prctl.h>



int Thread_number = 0, core_id = 0;



void *run_in_loop(void *args) {

    int thread_number = ((int *)args)[0];

    int core_id = ((int *)args)[1];



    while (1) {

        printf("Child process PID: %d\n", getpid());

        printf("Thread number %d\n", thread_number);

        printf("Process on core %d completed....!!!!\n", core_id);

        sleep(10);  // Sleep for 10 seconds (adjust as needed)

    }

    return NULL;

}









void run_on_specific_core(int core_id) {

    cpu_set_t mask;

    CPU_ZERO(&mask);

    CPU_SET(core_id, &mask);



    pthread_t current_thread = pthread_self();



    if (pthread_setaffinity_np(current_thread, sizeof(cpu_set_t), &mask) != 0) {

        perror("pthread_setaffinity_np");

        exit(EXIT_FAILURE);

    }



    printf("Process on core %d completed.\n", core_id);

}

int main() {

    pid_t pid1, pid2,pid3,pid4;

	//nice(10);

    // Create the first child process

    pid1 = fork();

    if (pid1 == 0) {

        // First child process logic

        //nice(1);

        char* child = "Child1";

        prctl(PR_SET_NAME, (unsigned long) child);

        Thread_number = 1;

        core_id = 0;

        run_on_specific_core(core_id);

        int args[] = {Thread_number, core_id};

        pthread_t tid;

        if (pthread_create(&tid, NULL, run_in_loop, (void *)args)!= 0) {

        perror("pthread_create");

        exit(EXIT_FAILURE);

    	}

    	if (pthread_join(tid, NULL)!= 0) {

        perror("pthread_create");

        exit(EXIT_FAILURE);

    	}

    }



    // Create the second child process

    pid2 = fork();



    if (pid2 == 0) {

         //Setting name for the processes

         //nice(10);

	char* child1 = "Child2";

        prctl(PR_SET_NAME, (unsigned long) child1);

        Thread_number = 2;

        core_id = 1;

        run_on_specific_core(core_id);

	

        int args[] = {Thread_number, core_id};

        pthread_t tid1;

        if (pthread_create(&tid1, NULL, run_in_loop, (void *)args)!= 0) {

        perror("pthread_create");

        exit(EXIT_FAILURE);

    	}

    	if (pthread_join(tid1, NULL)!= 0) {

        perror("pthread_create");

        exit(EXIT_FAILURE);

    	}

    }

    

    pid3 = fork();



    if (pid3 == 0) {

         //Setting name for the processes

         //nice(10);

	char* child2 = "Child3";

        prctl(PR_SET_NAME, (unsigned long) child2);

        Thread_number = 3;

        core_id = 2;

        run_on_specific_core(core_id);

	

        int args[] = {Thread_number, core_id};

        pthread_t tid2;
        if (pthread_create(&tid2, NULL, run_in_loop, (void *)args)!= 0) {

        perror("pthread_create");

        exit(EXIT_FAILURE);

    	}

    	if (pthread_join(tid2, NULL)!= 0) {

        perror("pthread_create");

        exit(EXIT_FAILURE);

    	}

    }



    pid4 = fork();



    if (pid4 == 0) {

         //Setting name for the processes

         //nice(10);

	char* child3 = "Child4";

        prctl(PR_SET_NAME, (unsigned long) child3);

        Thread_number = 4;

        core_id = 3;

        run_on_specific_core(core_id);

	

        int args[] = {Thread_number, core_id};

        pthread_t tid3;

        if (pthread_create(&tid3, NULL, run_in_loop, (void *)args)!= 0) {

        perror("pthread_create");

        exit(EXIT_FAILURE);

    	}

    	if (pthread_join(tid3, NULL)!= 0) {

        perror("pthread_create");

        exit(EXIT_FAILURE);

    	}

    }

 

   



    // Wait for all child processes to finish

    waitpid(pid1, NULL, 0);

    waitpid(pid2, NULL, 0);

    waitpid(pid3, NULL, 0);

    waitpid(pid4, NULL, 0);



    return 0;

}
