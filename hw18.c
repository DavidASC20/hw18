#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(){
	int fds[2];
	pipe(fds);

	int fds2[2];
	pipe(fds2);

	int forker = fork();


	if (forker){
		close(fds[0]);
		close(fds2[1]);
		while (1){
			char * message = calloc(1000, 1);
			printf("input: \n");
			fgets(message, 1000, stdin);
			write(fds[1], message, strlen(message));
			read(fds2[0], message, 1000);
			printf("manipulated B): %s\n", message);
			free(message);
		}
	} else {
		close(fds[1]);
		close(fds2[0]);
		while (1){
			char * message = calloc(1000, 1);
			int thing = read(fds[0], message, 1000);
			char * temp = calloc(1000, 1);

			int i;
			for (i = strlen(message) - 1; i >= 0; i--){
				if (*(message + i) != 10){
					strncat(temp, message + i, 1);
				}
			}

			write(fds2[1], temp, 1000);
			free(message);
			free(temp);
		}
	}

	return 0;
	
}
