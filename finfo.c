/***********************************************************************
 * @file finfo.c
 * @brief Source file which implements file information
 * Course: CPE2600 - 111
 * Assignment: Lab 9 - System Calls
 * Author: Zoya Mumtaz
 * Date: 10/30/2025
 * Version: 1.0
 * Note: compile with
 *     $ make
 *     run with
 *     $ ./finfo
 *********************************************************************/

 #include <string.h>
 #include <stdio.h>
 #include <sys/stat.h>
 #include <unistd.h>
 #include <time.h>
 #include <stdlib.h>

 /*
 the stat system call retrieves information of a file without opening it
 it takes in a struct stat and fills it with information found
 stat() provides the type, permissions, owner ID, group ID, 
 file size, and timestamps
 */


int main(int argc, char* argv[]){
    if (argc == 2){
        char filename[200];
        strcpy(filename, argv[1]);
        struct stat file_info; //struct holds file information

        //stat() populates the struct with file info
        if (stat(filename, &file_info) == -1){
            //an error occured in stat()
            perror("Error");
            exit(1);
        }

        //getting the file type
        if (S_ISREG(file_info.st_mode)){
            puts("File type: Regular File");
        } else if (S_ISDIR(file_info.st_mode)){
            puts("File type: Directory");
        } else if (S_ISLNK(file_info.st_mode)){
            puts("File type: Symbolic Link");
        } else if (S_ISCHR(file_info.st_mode)){
            puts("File type: Character Special");
        } else if (S_ISBLK(file_info.st_mode)){
            puts("File type: Block Special");
        } else if (S_ISSOCK(file_info.st_mode)){
            puts("File type: Socket");
        } else if (S_ISFIFO(file_info.st_mode)){
            puts("File type: FIFO");
        } else {
            puts("File type: Unknown");
        }

        //getting the permissions
        char permissions[10]; //9 characters for permissions and one for \0
        //use conditions to set each character
        permissions[0] = (file_info.st_mode & S_IRUSR) ? 'r' : '-';
        permissions[1] = (file_info.st_mode & S_IWUSR) ? 'w' : '-';
        permissions[2] = (file_info.st_mode & S_IXUSR) ? 'x' : '-';
        permissions[3] = (file_info.st_mode & S_IRGRP) ? 'r' : '-';
        permissions[4] = (file_info.st_mode & S_IWGRP) ? 'w' : '-';
        permissions[5] = (file_info.st_mode & S_IXGRP) ? 'x' : '-';
        permissions[6] = (file_info.st_mode & S_IROTH) ? 'r' : '-';
        permissions[7] = (file_info.st_mode & S_IWOTH) ? 'w' : '-';
        permissions[8] = (file_info.st_mode & S_IXOTH) ? 'x' : '-';
        permissions[9] = '\0'; //null terminator

        printf("File permissions: %s\n", permissions);

        //Getting the owner of the file by ID
        //%u for unsigned int
        printf("File Owner ID: %u\n", file_info.st_uid);

        //Getting the size of the file in bytes
        //typecasting to long long for safer printing
        printf("File size: %lld bytes\n", (long long)file_info.st_size);

        //Printing the date and time of last modified
        //using ctime() to convert to readable time
        printf("Last modified: %s", ctime(&file_info.st_mtime));

    } else {
        puts("Please enter the name of the file during program execution command.");

    }

    return 0;
}
