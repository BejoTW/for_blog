#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

#define key 8888

int main(int *argc, char **argv)
{
    int shmID = 0;
    char *shmaddr = NULL;
    int fp;
    struct stat fs;
    void *fm;

    fp = open("./mail.txt", O_RDONLY);
    if (!fp) {
        printf("open mail.txt fail\n");
        return 0;
    }
    fstat(fp, &fs);

    fm = mmap(NULL, fs.st_size, PROT_READ, MAP_PRIVATE, fp, 0);
    if (fm == MAP_FAILED) {
        printf("Memory mapping fail\n");
        return 0;
    }

    shmID = shmget(key, 1024, IPC_CREAT | 0600);
    
    printf("shmID = %d\n", shmID);
    shmaddr = (char *) shmat(shmID, NULL, 0);
    strcpy(shmaddr, fm);
    munmap(fm, fs.st_size);
    close(fp);
    //exit
    shmdt(shmaddr);
    return 0;
}
