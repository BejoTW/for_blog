#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define key 8888

int main(int argc, char **argv)
{
    int shmID = 0;
    char *shmaddr = NULL;
    struct shmid_ds buf;

   if (argc != 2) {
        printf("please enter shared moemory ID\n");
    }

    shmID = atoi(argv[1]);
    printf("get share ID = %d\n", shmID);    

    shmctl(shmID, IPC_STAT, &buf);
    shmaddr = (char *) shmat(shmID, NULL, 0);

    printf("%s\n", shmaddr);
    shmdt(shmaddr);
//Clear memory
    shmctl(shmID, IPC_RMID, NULL);
    return 0;
}
