#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define STR_BUFF 512

int main(void)
{
    FILE* fd;
    char str_n[STR_BUFF] = {0};
    char str_p[STR_BUFF] = {0};

    sprintf(str_n, "/proc/%d/status", getpid());

    fd = fopen(str_n, "r");

    if (fd) {
        while (!strstr(str_p, "PPid:")) {
            fgets(str_p, STR_BUFF, fd);
        }
        printf("%s", strstr(str_p, "\t") + 1);
    }
    else {
        perror(str_n);
        exit(EXIT_FAILURE);
    }

    fclose(fd);

    return 0;
}
