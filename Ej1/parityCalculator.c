#include "parityCalculator.h"

int main(int argc, char * argv[]) {
  int parentToChild[2];
  int childToParent[2];
  int pid, inputParity, outputParity;

  if(argc != REQ_ARGUMENTS) {
    fprintf(stderr, "Error: Unexpected number of arguments\n");
    return ARGUMENT_ERR;
  }

  if(pipe(childToParent) < 0 || pipe(parentToChild) < 0) {
    fprintf(stderr, "Error: Pipe failure\n");
    return PIPE_ERR;
  }

  pid = fork();

  if(pid < 0) {
    fprintf(stderr, "Error: Fork failure\n");
    return FORK_ERR;
  }

  if(pid == 0) {
		dup2(childToParent[WRITE_END], STDOUT_FILENO);
    close(childToParent[WRITE_END]);
    dup2(parentToChild[READ_END], STDIN_FILENO);
    close(parentToChild[READ_END]);

    close(childToParent[READ_END]);
    close(parentToChild[WRITE_END]);

    system(argv[1]);

  } else {
    close(parentToChild[READ_END]);
    close(childToParent[WRITE_END]);

    inputParity = calculateParity(STDIN_FILENO, parentToChild[WRITE_END]);
    close(parentToChild[WRITE_END]);
    outputParity = calculateParity(childToParent[READ_END], STDOUT_FILENO);
    putchar('\n');

    fprintf(stderr, "in parity: 0x%X\n", inputParity);
    fprintf(stderr, "out parity: 0x%X\n", outputParity);
  }

  return 0;
}

int calculateParity(int readFd, int writeFd) {
  ssize_t bytes;
  char buffer[BUFFER_SIZE];
  int parity = 0;

  while((bytes = read(readFd, buffer, BUFFER_SIZE - 1)) > 0) {
    parity ^= calculateNByteParity(bytes, buffer);
    write(writeFd, buffer, (size_t) bytes);
  }
  return parity;
}

int calculateNByteParity(ssize_t bytes, const char * string) {
  int i;
  int parity = 0;

  for(i = 0; i < bytes; i++) {
    parity ^= string[i];
  }
  return parity;
}
