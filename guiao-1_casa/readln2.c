#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

#define READ_SIZE 2

ssize_t readln2(int fd, char* line, size_t size){
	// Ler 2 carateres de cada vez
	ssize_t bytes_read;
	ssize_t total_bytes_read=0;
	char* temp_buffer = malloc(READ_SIZE);
	while ((bytes_read = read(fd, temp_buffer, READ_SIZE)) > 0){
		//printf("%ld ", bytes_read);
		if (total_bytes_read + bytes_read > size){
			int i=0;
			while (total_bytes_read <= size){
				line [total_bytes_read++] = temp_buffer[i++];
			}
			return size;
		}
		else if (bytes_read < READ_SIZE){
			for(int i=0; i<bytes_read; i++){
                line[total_bytes_read++] = temp_buffer[i++];
                if (temp_buffer[i] == '\n') break;
            }
			return total_bytes_read;
		}
		else {
			strcpy(line + total_bytes_read, temp_buffer);
			total_bytes_read += bytes_read;
            if (temp_buffer[READ_SIZE-1] == '\n') return total_bytes_read;
		}
	}
	free(temp_buffer);
}

int main(){
    char buffer[1024];
    readln2(STDIN_FILENO, buffer, 1024);
}