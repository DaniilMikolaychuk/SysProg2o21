#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    int fds[2];

    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s <progname> <arg>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (pipe(fds) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    switch (fork())
    {
        case -1:
            perror("fork");
            return 1;

        case 0: /* child*/
            close(1);
            dup(fds[1]);
            close(fds[0]);
            execl(argv[1], argv[1], argv[2], NULL);
            perror("execl");
            _exit(EXIT_FAILURE);

        default: /* parent */
            {
                char ch;
                int count = 0;
                close(fds[1]);
                while (read(fds[0], &ch, 1) == 1)
                {
                    if (ch == '0')
                    {
                        count++;
                    }
                }
                printf("%d\n", count);
                wait(NULL);
            }
    }

    return 0;
}
