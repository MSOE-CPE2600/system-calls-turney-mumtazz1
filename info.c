/***********************************************************************
 * @file info.c
 * @brief Source file which implements functions
 * Course: CPE2600 - 111
 * Assignment: Lab 9 - System Calls
 * Author: Zoya Mumtaz
 * Date: 10/30/2025
 * Version: 1.0
 * Note: compile with
 *     $ make
 *     run with
 *     $ ./info
 *********************************************************************/

// info.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <stdint.h>

int main(int argc, char* argv[])
{
    //--------------Finding the current time in nanoseconds------------
    //int clock_gettime(clockid_t clockid, struct timespec *tp);
    struct timespec ts;
    unsigned long long nano;
    //converting sec to ns, type unsigned long long preventing overflow
    unsigned long long sec_to_ns;
    unsigned long long ns_total;

    if (clock_gettime(CLOCK_REALTIME, &ts) == 0){
        nano = (unsigned long long)ts.tv_nsec;
        sec_to_ns = (unsigned long long)ts.tv_sec * (1000000000);
        ns_total = nano + sec_to_ns;

        printf("The current time in nanoseconds is %llu ns\n", ns_total);
    } 

    //--------------Finding information about the system---------------
    //int uname(struct utsname *buf)
    //int gethostname(char *name, size_t size)
    struct utsname buf;
    if (uname(&buf) == 0){
        printf("Operating system's name: %s\n", buf.sysname);
        char hostname[256];
        if (gethostname(hostname, 256) == 0){ 
            printf("Network name: %s\n", hostname);
        }        
        printf("Operating system's release and version: %s %s\n", buf.release, buf.version);
        printf("Hardware type: %s\n", buf.machine);

    }
    
    //int get_nprocs_conf(void)
    int num_cpu = get_nprocs_conf(); //returns number of CPUs configured
    printf("Number of CPUs on the system: %d\n", num_cpu);

    //--------------Finding information about memory in bytes----------
    //Find the memory
    //Using unsigned long long to prevent overflow
    long page_size = getpagesize(); //size of one page
    long total_pages = sysconf(_SC_PHYS_PAGES); //for total memory
    long free_pages = sysconf(_SC_AVPHYS_PAGES); //for free memory
    if (page_size != -1 && total_pages != -1 && free_pages != -1){
    unsigned long long total_memory = (unsigned long long) total_pages * page_size;
    unsigned long long free_memory = (unsigned long long) free_pages * page_size;

    printf("Total Memory in Bytes: %llu bytes\n", total_memory);
    printf("Free Memory in Bytes: %llu bytes\n", free_memory);

    }

    return 0;
}