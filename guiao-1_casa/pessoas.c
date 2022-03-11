#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h> 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define PRINT_ERROR printf("Msg: %s, Nr: %d\n", strerror(errno), errno);

struct pessoa {
	char nome[20];
	int idade;
};

typedef struct pessoa Pessoa;

void imprimePessoa(Pessoa p){
	printf("Nome: %s\nIdade: %d\n", p.nome, p.idade);
}

int main(int argc, char* argv[]){
	// pessoas -i -> Adicionar ao final do ficheiro Pessoas.bin
	// pessoas -u -> Atualizar o ficheiro (nome = key, idade = value)
	if (argc == 4){
		if (strcmp(argv[1], "-i") == 0){
			int fd = open("Pessoas.bin", O_WRONLY | O_CREAT | O_APPEND, 0640);
			if (fd == -1){
				PRINT_ERROR
			}
			// Diferença entre passar argumentos com " e sem "
			Pessoa p1; strcpy(p1.nome, argv[2]); p1.idade = atoi(argv[3]);
			write(fd, &p1, sizeof(struct pessoa));
		}
		else if (strcmp(argv[1], "-u") == 0){
			int fd = open("Pessoas.bin", O_RDWR, 0640);
		  	if (fd == -1) PRINT_ERROR	
			Pessoa p1;
			ssize_t bytes_read;
			while ((bytes_read = read(fd, &p1, sizeof(struct pessoa))) > 0){
				printf("Bytes lidos: %ld\n", bytes_read);
				imprimePessoa(p1);
				if (strcmp(argv[2], p1.nome) == 0){
					p1.idade = atoi(argv[3]);
					lseek(fd, -sizeof(struct pessoa), SEEK_CUR);
					write(fd, &p1, sizeof(struct pessoa));
					imprimePessoa(p1);
				}
			}
		}
	}
}
