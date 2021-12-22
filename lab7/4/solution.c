#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#define INFINITE_LOOP while(1)

int main() {
	int pid = fork();

	if (!pid) {
		signal(SIGURG, exit);
		setsid();
		chdir("/");

		while (4 > pid)
			close(pid++);

		INFINITE_LOOP;
	}

	return printf("%d\n", pid) & 0;
}
