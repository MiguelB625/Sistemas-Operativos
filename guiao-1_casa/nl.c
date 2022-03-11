#include "readln.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int calcDecPlaces(int num){
	int r=0;
	
	while (num){
		num = num / 10;
		r++;
	}
	
	return r;
}

#define BUFFER_SIZE 12
#define SMALL_BUFFER_SIZE 4

/* Versão do main para o readln 1 e 2
int main(int argc, char* argv[]){
	char* buffer = malloc(BUFFER\_SIZE * sizeof(char));
	char* num = malloc(10);
	int counter = 1;
	ssize_t bytes_read;	

	while ((bytes_read = readln2(0, buffer, BUFFER_SIZE)) > 0){
		if (bytes_read == 1) continue;
		snprintf(num, 10, "%d	", counter);
		write(1, num, 1 + calcDecPlaces(counter));
		write(1, buffer, bytes_read);// Usar o printf n dava para ter controlo sobre o número de bits a imprimir		
	
		while (bytes_read == BUFFER_SIZE && buffer[BUFFER_SIZE] != '\n'){
			bytes_read = readln(0, buffer, BUFFER_SIZE);
			write(1, buffer, bytes_read);
		}
	
		counter++;
	}


}*/

int main(int argc, char* argv[]){
	char* buffer = malloc(BUFFER_SIZE * sizeof(char));
	char* global_buffer = malloc(SMALL_BUFFER_SIZE * sizeof(char));
	char* num = malloc(10);
	int counter = 1;
	int* read_pos = malloc(sizeof(int)); *read_pos = 0;
	ssize_t bytes_read;

	bytes_read = read(0, global_buffer, SMALL_BUFFER_SIZE);
	if (bytes_read < SMALL_BUFFER_SIZE){ 
		global_buffer[bytes_read] = '\0';
	}

	while ((bytes_read = readln3(0, buffer, BUFFER_SIZE, global_buffer, read_pos, SMALL_BUFFER_SIZE)) > 0){
		if (bytes_read == 1) continue;
		snprintf(num, 10, "%d	", counter);
		write(1, num, 1 + calcDecPlaces(counter));
		write(1, buffer, bytes_read);// Usar o printf n dava para ter controlo sobre o número de bits a imprimir		
	
		while (bytes_read == BUFFER_SIZE && buffer[BUFFER_SIZE] != '\n'){
			bytes_read = readln(0, buffer, BUFFER_SIZE);
			write(1, buffer, bytes_read);
		}
	
		counter++;
	}





}
