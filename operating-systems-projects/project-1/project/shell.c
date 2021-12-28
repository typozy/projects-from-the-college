#include <stdio.h>
#include <string.h>

int main(int argc, char * argv[]){
	char buffer[50];
	int intro = 1;
	while(1){
		if(intro){
			printf("Enter the program name to execute (with ShowPrimes, Factorize ");
			printf("or BubbleSort command) or exit the shell (with Exit command): ");
		}
		scanf("%s",buffer);
		intro = 1;
		if(strcmp(buffer,"ShowPrimes") == 0){
			printf("\n--CreateProcess syscall will be handled here--\n\n");

			//CreateProcess syscall

		}
		else if(strcmp(buffer,"Factorize") == 0){
			printf("\n--CreateProcess syscall will be handled here--\n\n");

			//CreateProcess syscall

		}
		else if(strcmp(buffer,"BubbleSort") == 0){
			printf("\n--CreateProcess syscall will be handled here--\n\n");

			//CreateProcess syscall
			
		}
		else if(strcmp(buffer,"") == 0){
			printf("Please enter a command : ");
			intro = 0;
		}
		else if(strcmp(buffer,"Exit") == 0){
			break;
		}
		else{
			printf("Enter the command truly: ");
			intro = 0;
		}
	}
	printf("Goodbye!\n");
	return 0;
}