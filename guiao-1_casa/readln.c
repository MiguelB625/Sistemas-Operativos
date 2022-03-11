#include <sys/types.h>
#include <unistd.h>

// Versão 1: Lê um carater de cada vez
ssize_t readln(int fd, char* line, size_t size){
	// Lê um carater de cada vez
	// Pára se:  ler um \n
	//           chegar ao fim do ficheiro
	// 			 Acabar o espaço
	size_t bytes_read = 0;
	while (bytes_read < size && read(fd, line+bytes_read, 1) > 0){
		if (line[bytes_read++] == '\n') break;
	}

	return bytes_read;
}

// Versão 2: Lê vários carateres de cada vez
ssize_t readln2(int fd, char* line, size_t size){
	// Lê tudo para o buffer
	// Percorre o buffer até encontrar \n
	// Se encontrar, usa lseek de modo a poder voltar a ler bytes que não pertencem a linha

	ssize_t bytes_read = read(fd, line, size);
	
	int i;
	for(i=1; i<bytes_read; i++){
		if (line[i] == '\n'){
			lseek(fd, i-bytes_read, SEEK_CUR);
		}
	}
	return i;



}

// Versão 3: Usa um buffer global, de modo a evitar lseeks desnecessários
ssize_t readln3(int fd, char* line, size_t size, char* readln_global_buf, int* read_pos, int global_buf_size){
	int i=0;

	while (readln_global_buf[*read_pos] != '\0' && readln_global_buf[*read_pos] != '\n'){
		line[i++] = readln_global_buf[(*read_pos)++]; 
		if (*read_pos == global_buf_size){
			*read_pos = 0;
			ssize_t bytes_read = read(0, readln_global_buf, global_buf_size);
			if (bytes_read < global_buf_size){ 
				readln_global_buf[bytes_read] = '\0';
			}
		}
	}
	return i;
}
