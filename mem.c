#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/ipc.h>
#include <errno.h>
#include <sys/shm.h>

int main() {
    int shmid = shmget(31415926, 200, 0644 | IPC_CREAT);
    printf("shmid: %d\n",shmid);
    char *str = shmat(shmid, 0, 0);
    if (str == (char *)(-1)){
        printf("%s\n", strerror(errno));
        exit(1);
    } if (*str == '\0'){
        printf("There was no data. A new memory segment was succesfully created.\n");
    } else {
        printf("String:\n%s\n", str);
    }

    // vars
    char change[100];
    int code = 0;
    // ask if user wants to modify
    while(! code) {
        printf("Do you want to modify string data in this shared segment? (y/n):");
        fgets(change, 100, stdin);
        change[strlen(change) - 1] = '\0';
        if (strcmp(change,"y") == 0){
            code = 1;
            printf("Input a string to write into the segment: ");
            fgets(str, 200, stdin);
            str[strlen(str) - 1] = '\0';
            printf("\"%s\"\nhas been written successfully\n", str);
        } else if (strcmp(change,"n") == 0){
            code = 1;
            printf("String not changed.\n");
        } else {
            printf("Please enter \"y\" or \"n\" and then press enter\n");
        }
    }

    // ask if user wants to delete
    char delete[100];
    code = 0;
    while (! code){
        printf("\nDo you want to delete the shared memory segment? (y/n):");
        fgets(delete, 100, stdin);
        delete[strlen(delete) - 1] = '\0';
        if (strcmp(delete,"y") == 0) {
            code = 1;
            shmctl(shmid, IPC_RMID, NULL);
            printf("Memory segment successfully deleted! Exiting now...\n");
        } else if (strcmp(delete,"n") == 0){
            code = 1;
            printf("String not deleted.\n");
            if (shmdt(str) == -1){
                printf("There has been an error with shmdt\n");
                exit(1);
            }
        } else{
            printf("Please enter \"y\" or \"n\" and then press enter.\n");
        }
    }
}
