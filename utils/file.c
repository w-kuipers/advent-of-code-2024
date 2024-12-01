#include <stdio.h>
#include <stdlib.h>

char *read_file(const char *filename) {
  FILE *file = fopen(filename, "rb");
  if (!file) {
    perror("Failed to open file");
    return NULL;
  }

  // Determine file size
  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  rewind(file);

  // Allocate memory for the file content (+1 for null terminator)
  char *content = (char *)malloc(file_size + 1);
  if (!content) {
    perror("Memory allocation failed");
    fclose(file);
    return NULL;
  }

  // Read the file into the buffer
  size_t read_size = fread(content, 1, file_size, file);
  if (read_size != file_size) {
    perror("Failed to read file");
    free(content);
    fclose(file);
    return NULL;
  }

  // Null-terminate the string
  content[file_size] = '\0';

  fclose(file);
  return content;
}
