#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF_SIZE 100

int read_chnl(int fd, char* buf, size_t size)
{
    int num_read_bytes = read(fd, buf, size - 1);
    buf[num_read_bytes] = 0;
    return num_read_bytes;
}

int isConnect2fifo(int* read_res_buf, size_t size) 
{
    int ret = 0;
    int i = 0;
    for(i = 0; i < size; ++i) {
        ret |= read_res_buf[i];
    }
    return ret;
}

int main()
{
    int fd[2];
    if(-1 == (fd[0] = open("in1", O_RDONLY|O_NONBLOCK))) {
        perror("Open: in1");
        return 1;
    }
    if(-1 == (fd[1] = open("in2", O_RDONLY|O_NONBLOCK))) {
        perror("Open: in2");
        return 1;
    }

    fd_set readfds, tmpfds;
    FD_ZERO(&readfds);
    FD_ZERO(&tmpfds);
    FD_SET(fd[0], &readfds);
    FD_SET(fd[1], &readfds);

    int read_res[2] = {0, 0};
    int total = 0;
    char buf[BUF_SIZE];

    do {
        int i = 0;
        tmpfds = readfds;
        if(-1 == select(fd[1]+1, &tmpfds, NULL, NULL, NULL)) {
            perror("select");
            return 2;
        }
        for(i = 0; i < 2; ++i) {
            if(FD_ISSET(fd[i], &tmpfds)) {
                read_res[i] = read_chnl(fd[i], buf, BUF_SIZE);
                if(read_res[i] != 0) {
                    total += atoi(buf);
                } else {
                    FD_CLR(fd[i], &readfds);
                }
            }
        }
    } while(isConnect2fifo(read_res, 2));
    printf("%d\n", total);
    fflush(stdout);

    return 0;
}
