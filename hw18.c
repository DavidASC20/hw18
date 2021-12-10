#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#define READ 0
#define WRITE 1

int main() {
	int cPipe[2];
	int pPipe[2];
	pipe(cPipe);
	pipe(pPipe);

	int pid = fork();

	if (pid == -1) {
		printf("Error, Message is: %s\n", strerror(errno));
		return 1;
	}

	if (pid == 0) {
		close(cPipe[WRITE]);
		close(pPipe[READ]);

		char str[10000];
		int x = -1;
		while (x != 0) {
    
			x = read(cPipe[READ], str, sizeof(str));
			int i;
			for (i = 0; i < strlen(str); i++) {
				if (str[i] >= 65 && str[i] <= 90) str[i] += 32;
			}
			write(pPipe[WRITE], str, strlen(str));
		}
	} else {
		close(pPipe[WRITE]);
		close(cPipe[READ]);

		char str[10000];
		while (1 == 1) {
			printf("Uppercase String: ");
			str[0] = '\0';
			fgets(str, sizeof(str), stdin);
			if (strlen(str) == 0) return 0;
			write(cPipe[WRITE], str, sizeof(str));
			read(pPipe[READ], str, sizeof(str));
			printf("Returned lowercase: %s", str);
		}
	}
}