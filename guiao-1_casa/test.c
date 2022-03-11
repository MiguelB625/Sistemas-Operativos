#include <stddef.h>
#include <sys/types.h>
#include <unistd.h>
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

// Versão 3: Usa um buffer global, de modo a evitar lseeks desnecessários
ssize_t readln3(int fd, char* line, size_t size, char* readln_global_buf, int* read_pos, int global_buf_size){
	int i=0;

	while (i<size && readln_global_buf[*read_pos] != '\0' && readln_global_buf[*read_pos] != '\n'){
		line[i++] = readln_global_buf[(*read_pos)++]; 
		if (*read_pos == global_buf_size){
			*read_pos = 0;
			ssize_t bytes_read = read(0, readln_global_buf, global_buf_size);
			if (bytes_read < global_buf_size){ 
				readln_global_buf[bytes_read] = '\0';
			}
		}
	}

    if (i<size) line[i] = '\n';
	return i;
}

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
			bytes_read = readln3(0, buffer, BUFFER_SIZE, global_buffer, read_pos, SMALL_BUFFER_SIZE);
			write(1, buffer, bytes_read);
		}
	
		counter++;
	}





}