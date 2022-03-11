#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
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
	// -i -> diz o índice no ficheiro daquele registo
	// -o -> atualiza diretamente esse registo no ficheiro
	if (argc == 4){
		if (strcmp(argv[1], "-i") == 0){
			int fd = open("Pessoas.bin", O_RDONLY, 0640);
			if (fd == -1) PRINT_ERROR
			else {
				int index = 0;
				ssize_t bytes_read;
				Pessoa temp;
				while((bytes_read = read(fd,&temp, sizeof(struct pessoa))) > 0){
					//imprimePessoa(temp);	
					if (strcmp(argv[2], temp.nome) == 0 && temp.idade == atoi(argv[3])){
						printf("registo %d\n", index);
						break;
					}
					else index++;
				}
			}
		}
		else if (strcmp(argv[1], "-o") == 0){
			int registo = atoi(argv[2]);
			int idade_at = atoi(argv[3]);
			int fd = open("Pessoas.bin", O_RDWR, 0640);
			if (fd == -1) PRINT_ERROR
			else {
				lseek(fd, registo*sizeof(struct pessoa), SEEK_SET);
				Pessoa p1;
				ssize_t bytes_read = read(fd, &p1, sizeof(struct pessoa)); 
				if (bytes_read <= 0) PRINT_ERROR
				else {
					p1.idade = idade_at;
					lseek(fd, -sizeof(struct pessoa), SEEK_CUR);
					write(fd, &p1, sizeof(struct pessoa));
				}
			}
		}
	}
}
