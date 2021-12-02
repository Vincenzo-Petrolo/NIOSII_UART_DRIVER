#include <stdio.h>
#include <string.h>

#define DEBUG 1
#define EVER ;;

int main(void)
{

	FILE *fp;
	char recChar;
	char string[] = "You are now elegant. Well Done!\n";

	// opens communication with UART peripheral through drivers
	fp = fopen("/dev/uart_0", "r+");
	// if communication fails, throws an error
	if(fp == NULL){
		fprintf(stderr, "Failed to open /dev/uart_0\n");
		return 1;
	}

	/*for(int c=0; c<strlen(string)-1; c++){
		fprintf(fp, "%c", string[c]);
	}*/

	// sends a string on the line through UART peripheral
	fprintf(fp, "%s", string);

	// endless loop in which UART peripheral will receive
	//		data from the COM line
    for (EVER){
    	recChar = fgetc(fp);
    	printf("%c", recChar);
    }

    fclose(fp);

    return 0;
}
