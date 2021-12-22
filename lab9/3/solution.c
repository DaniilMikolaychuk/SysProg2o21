#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int cmpstringp(const void *p1, const void *p2) {
	return strcmp((char const *)(p1), (char const *)(p2)) * -1;
}

struct sockaddr_in local;

int main(int argc, char *argv[]) {
	int server_socket = socket(AF_INET, SOCK_STREAM, 0);
	int port = atoi(argv[1]);

	inet_aton("127.0.0.1", &local.sin_addr);
	local.sin_family = AF_INET;
	local.sin_port = htons((uint16_t)port);

	bind(server_socket, (struct sockaddr *) &local, sizeof(local));
	listen(server_socket, 5);

	int client_socket = accept(server_socket, NULL, NULL);

	char buf[BUFSIZ];

	while (1) {		
		ssize_t count = recv(client_socket, buf, sizeof(buf), 0);

		if (strcmp(buf, "OFF") == 0) {
			close(client_socket);
			break;
		}

		qsort(buf, strlen(buf), sizeof(char), cmpstringp);

		send(client_socket, buf, strlen(buf), 0);

		memset(buf, 0, BUFSIZ * (sizeof buf[0]));
	}
	

	return 0;
}