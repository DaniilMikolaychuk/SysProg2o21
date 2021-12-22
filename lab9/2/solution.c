#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>


int main(int argc, char* argv[])
{
    if (argc == 2)
    {
        int sfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (sfd != -1)
        {
            struct sockaddr_in sockaddr;
            sockaddr.sin_family = AF_INET;
            sockaddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
            sockaddr.sin_port = htons(atoi(argv[1]));

            if (bind(sfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) == 0)
            {
                char buf[1024];
                for(;;)
                {
                    ssize_t size = recv(sfd, buf, sizeof(buf) - 1, 0);
                    if (size > 0)
                    {
                        buf[size] = '\0';
                        if (!strcmp(buf, "OFF\n"))
                        {
                            break;
                        }
                        else
                        {
                           printf("%s\n", buf);
                        }                        
                    } 
                }
            }
        }
    }
    return 0;
}