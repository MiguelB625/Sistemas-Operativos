#ifndef R_LN
#define R_Ln

#include <stddef.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

ssize_t readln (int fd, char* line, size_t size);
ssize_t readln2(int fd, char* line, size_t size);
ssize_t readln3(int fd, char* line, size_t size, char* readln_global_buf, int* read_pos, int global_buf_size);
	
#endif
