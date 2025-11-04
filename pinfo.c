/***********************************************************************
 * @file pinfo.c
 * @brief Source file which implements functions
 * Course: CPE2600 - 111
 * Assignment: Lab 9 - System Calls
 * Author: Zoya Mumtaz
 * Date: 10/30/2025
 * Version: 1.0
 * Note: compile with
 *     $ make
 *     run with
 *     $ ./pinfo
 *********************************************************************/

 #define _GNU_SOURCE

 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 #include <sys/types.h>
 #include <sys/resource.h> 
 #include <errno.h>
 #include <sched.h>
 #include <unistd.h>
 #include <signal.h>


//Defining each system call
 /*
 getpid: gets the process ID of the current process
 getpriority:  gets the scheduling priority for a process
 sched_getscheduler: gets the scheduling policy for a process
 getcpu: gets the specific CPU core and NUMA node that calling
 thread is current running on
 getrusage: gets resource usage statistics for a process
 getrlimit: gets resource limits for a process, what the process
 is allowed to do
 */


int main(int argc, char* argv[])
{
    if (argc == 2){ //if user entered a PID
        pid_t pid = (pid_t)atoi(argv[1]);
        
        //check if input PID is valid
        if (pid <= 0){
            puts("Error: Invalid Process ID.");
            exit(0);
        }
        if (kill(pid, 0) != 0){ 
            //sending null signal to check if PID exists
            perror("Error");
            exit(0);
        }

        errno = 0;
        int priority = getpriority(PRIO_PROCESS, pid);
        if (priority == -1 && errno != 0){
            //an actual error happened if both are true
            perror("Error");
            exit(0);
        }

        int policy = sched_getscheduler(pid);
        if (policy == -1){
            perror("Error");
            exit(0);
        }

        const char* policy_name;
        if (policy == SCHED_FIFO){
            policy_name = "SCHED_FIFO";
        } else if (policy == SCHED_RR){
            policy_name = "SCHED_RR";
        } else if (policy == SCHED_DEADLINE){
            policy_name = "SCHED_DEADLINE";
        } else if (policy == SCHED_OTHER){
            policy_name = "SCHED_OTHER";
        } else if (policy == SCHED_BATCH){
            policy_name = "SCHED_BATCH";
        } else if (policy == SCHED_IDLE){
            policy_name = "SCHED_IDLE";
        } else {
            policy_name = "Unknown Scheduling Policy\n";
        }

        printf("Process %d has Priority %d and Scheduling Policy %s\n", pid, priority, policy_name);

    } else { //print info about current PID
        pid_t pid = getpid();

        errno = 0;
        int priority = getpriority(PRIO_PROCESS, pid);
        if (priority == -1 && errno != 0){
            //an actual error happened if both are true
            perror("Error");
            exit(0);
        }

        int policy = sched_getscheduler(pid);
        if (policy == -1){
            perror("Error");
            exit(0);
        }

        const char* policy_name;
        if (policy == SCHED_FIFO){
            policy_name = "SCHED_FIFO";
        } else if (policy == SCHED_RR){
            policy_name = "SCHED_RR";
        } else if (policy == SCHED_DEADLINE){
            policy_name = "SCHED_DEADLINE";
        } else if (policy == SCHED_OTHER){
            policy_name = "SCHED_OTHER";
        } else if (policy == SCHED_BATCH){
            policy_name = "SCHED_BATCH";
        } else if (policy == SCHED_IDLE){
            policy_name = "SCHED_IDLE";
        } else {
            policy_name = "Unknown Scheduling Policy\n";
        }

        printf("Current Process %d has Priority %d and Scheduling Policy %s \n", pid, priority, policy_name);

    }

    return 0;
}