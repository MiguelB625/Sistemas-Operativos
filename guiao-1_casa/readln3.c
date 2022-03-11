#include <unistd.h>

#define GLB_BUFFER_SIZE 2

ssize_t readln(int fd, char* line, size_t size){
	char* glb_buffer = malloc(GLB_BUFFER_SIZE);
	int read_pos = 0;
	int write_pos = 0;
	do{
		if (read_pos == 0){
			size_t bytes_read = read(fd, glb_buffer, GLB_BUFFER_SIZE);
			for(int i=0; i<bytes_read; i++){
				line[write_pos++] = glb_buffer[i];
				if (glb_buffer[i] == '\n'){
					lseek(fd, GLB_BUFFER_SIZE-i, SEEK_CUR);
					return write_pos;
				}	
			}
			if (bytes_read < GLB_BUFFER_SIZE) return write_pos;
		}
		else {
			while (read_pos != GLB_BUFFER_SIZE){
				line[write_pos++] = glb_buffer[read_pos];
				if (glb_buffer[i] == '\n'){
					lseek(fd, GLB_BUFFER_SIZE-i, SEEK_CUR);
					return write_pos;
				}
				read_pos++;
			}
			read_pos = 0;
		}	
	}while (write_pos + bytes_read <= size);




}
