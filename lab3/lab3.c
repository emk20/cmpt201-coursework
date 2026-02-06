#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 5
int main() {
  char *buff = NULL;
  size_t size = 0;

  char *lines[MAX_LINES] = {NULL};
  int count = 0; // total lines read so far

  while (1) {
    printf("Enter input: ");

    ssize_t len = getline(&buff, &size, stdin);

    if (len == -1) {
      break; // EOF
    }

    // Remove trailing newline
    if (len > 0 && buff[len - 1] == '\n') {
      buff[len - 1] = '\0';
    }

    // Store line (circular buffer logic)
    int index = count % MAX_LINES;
    free(lines[index]);
    lines[index] = strdup(buff);
    count++;

    // If command is "print"
    if (strcmp(buff, "print") == 0) {
      int start = (count >= MAX_LINES) ? count - MAX_LINES : 0;
      for (int i = start; i < count; i++) {
        int idx = i % MAX_LINES;
        printf("%s\n", lines[idx]);
      }
    }
  }
  // Cleanup
  for (int i = 0; i < MAX_LINES; i++) {
    free(lines[i]);
  }
  free(buff);

  return 0;
}
