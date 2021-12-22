#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {

    int region1_id = shmget(atoi(argv[1]), 1000, 0400); // region 1 id
    int region2_id = shmget(atoi(argv[2]), 1000, 0400); // region 2 id
    int new_region_id = shmget(12345, 1000, IPC_CREAT|0666); // my region id


    int *r1 = (int*) shmat(region1_id, NULL, SHM_RDONLY);
    int *r2 = (int*) shmat(region2_id, NULL, SHM_RDONLY);
    int *r3 = (int*) shmat(new_region_id, 0, 0);

    int i;
    for (i = 0; i < 100; i++)
        *(r3 + i) = *(r1 + i) + *(r2 + i);

    shmdt(r1);
    shmdt(r2);
    shmdt(r3);

    printf("12345\n");

    return 0;
}