#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define PRINT_ERROR printf("Msg: %s, Nr: %d\n", strerror(errno), errno);

// cp input output
// cp input dir
// cp input1 input2 ... output_directory

int main(int argc, char* argv[]){
	if (argc > 1){
		if (argc == 3){
			int f1, f2;
			// Abertura dos ficheiros
			f1 = open(argv[1], O_RDONLY, 0640);
			f2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0642);
			//printf("f1 - %d, f2 - %d", f1, f2);

			if (f1 == -1){
				PRINT_ERROR	
			}
			if (f2 == -2){
				PRINT_ERROR
			}
			
			int size = 1024;
			char* buffer = malloc(1024);
			if (!buffer){
				PRINT_ERROR
			}

			int iterations=0;			
			ssize_t bytes_read;
			while ( (bytes_read = read(f1, buffer, size)) > 0){
				write(f2, buffer, bytes_read);
				iterations++;
			}

			//printf("Número de iterações: %d\n", iterations);
			free(buffer);
		} else { // cp input1 ... outputdir
			int size = 1024;
			char* buffer = malloc(size);
			int* file_desc = malloc(sizeof(int)*(argc-2));
			int i;
				
			for(i=0; i<argc-2; i++){
				file_desc[i] = open(argv[i+1], O_RDONLY, 0640);
				char output_path[100];
				snprintf(output_path, 100, "%s/%s", argv[argc-1], argv[i+1]);
				printf("%s\n", output_path); 

				int fd = open(output_path, O_WRONLY | O_CREAT | O_TRUNC, 0642);
				if (fd == -1){
					PRINT_ERROR	
				}
				
				ssize_t bytes_read;
				while ( (bytes_read = read(file_desc[i], buffer, size)) > 0){
					write(fd, buffer, bytes_read);
				}  
				 
			}
			free(buffer);
		}
	}



}
