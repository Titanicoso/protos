#ifndef PARITYCALCULATOR_H
#define PARITYCALCULATOR_H

#define REQ_ARGUMENTS 2
#define BUFFER_SIZE 512

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef enum {ARGUMENT_ERR = 1, PIPE_ERR, FORK_ERR} errorCodes;
typedef enum {READ_END = 0, WRITE_END = 1} pipeManagement;

int calculateParity(int childToParent, int parentToChild);

int calculateNByteParity(ssize_t bytes, const char * string);

#endif
