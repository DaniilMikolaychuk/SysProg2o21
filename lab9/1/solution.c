
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>


int main(int argc, char* argv[])
{
    if (argc == 2)
    {
        struct hostent* h = gethostbyname(argv[1]);
        if (h != NULL)
        {
            int n;
            for (n = 0; h->h_addr_list[n] != NULL; n++)
            {
                char buf[INET6_ADDRSTRLEN];
                if (inet_ntop(h->h_addrtype, h->h_addr_list[n], buf, sizeof(buf)) != NULL)
                {
                    printf("%s\n", buf);
                }
            }
        }   
    }
    return 0;
}