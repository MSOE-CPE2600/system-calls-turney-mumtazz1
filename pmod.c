/***********************************************************************
 * @file pmod.c
 * @brief Source file which implements nice and nanosleep
 * Course: CPE2600 - 111
 * Assignment: Lab 9 - System Calls
 * Author: Zoya Mumtaz
 * Date: 10/30/2025
 * Version: 1.0
 * Note: compile with
 *     $ make
 *     run with
 *     $ ./pmod
 *********************************************************************/
 
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/resource.h>

/*
nice: changes the scheduling priority of the curret process
where higher nice valye means lower priority and vice versa
nanosleep: pauses the current program for a precise amount of time
*/

int main(int argc, char* argv[])
{
    //------------Using nice()----------------
    int nice1 = getpriority(PRIO_PROCESS, 0); //get initial priority
    printf("The intial nice value is %d\n", nice1);
    errno = 0;
    int nice2 = nice(10); //reduce its own priority by 10
    if (nice2 == -1 && errno != 0){
        //error occured
        perror("Error");
        exit(0);
    }
    printf("The new nice value is %d\n", nice2);

    //-----------Using nanosleep()-------------
    struct timespec ts;
    ts.tv_sec = 1; //1 sec = 1000000000 ns
    ts.tv_nsec = 837272638; //remainder ns after 1 sec
    puts("Sleeping for 1837272638 ns . . .");

    if (nanosleep(&ts, NULL) == 0){
        puts("Sleep has completed. Goodbye!");
    }

    return 0;
}